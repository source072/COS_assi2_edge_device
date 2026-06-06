import socket
import requests
import threading
import argparse
import logging
import json
import sys

# 서버 -> 엣지 방향의 제어 opcode
OPCODE_DATA = 1   # (기존) 데이터 보고 opcode
OPCODE_WAIT = 2   # 학습 단계 종료 후 대기 신호
OPCODE_DONE = 3   # 한 인스턴스 처리 완료, 다음 데이터 요청
OPCODE_QUIT = 4   # 전체 종료 신호

# 엣지 payload 내부의 feature mode
# 실제 네트워크 메시지는 OPCODE_DATA || mode || power_max || feature1 || feature2 || month 형태이다.
OPCODE_MODE_TEMP = 0      # temp 모드  : power_max || temp_max  || temp_avg  || month
OPCODE_MODE_HUMID = 1     # humid 모드 : power_max || humid_max || humid_avg || month
OPCODE_MODE_COMBINED = 2  # combined   : power_max || temp_max  || humid_max || month

class Server:
    def __init__(self, name, algorithm, dimension, index, port, caddr, cport, ntrain, ntest):
        logging.info("[*] Initializing the server module to receive data from the edge device")
        self.name = name
        self.algorithm = algorithm
        self.dimension = dimension
        self.index = index
        self.caddr = caddr
        self.cport = cport
        self.ntrain = ntrain
        self.ntest = ntest
        success = self.connecter()

        if success:
            self.port = port
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.bind(("0.0.0.0", port))
            self.socket.listen(10)
            self.listener()

    def connecter(self):
        success = True
        self.ai = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ai.connect((self.caddr, self.cport))
        url = "http://{}:{}/{}".format(self.caddr, self.cport, self.name)
        request = {}
        request['algorithm'] = self.algorithm
        request['dimension'] = self.dimension
        request['index'] = self.index
        js = json.dumps(request)
        logging.debug("[*] To be sent to the AI module: {}".format(js))
        result = requests.post(url, json=js)
        response = json.loads(result.content)
        logging.debug("[*] Received: {}".format(response))

        if "opcode" not in response:
            logging.debug("[*] Invalid response")
            success = False
        else:
            if response["opcode"] == "failure":
                logging.error("Error happened")
                if "reason" in response:
                    logging.error("Reason: {}".format(response["reason"]))
                    logging.error("Please try again.")
                else:
                    logging.error("Reason: unknown. not specified")
                success = False
            else:
                assert response["opcode"] == "success"
                logging.info("[*] Successfully connected to the AI module")
        return success

    def listener(self):
        logging.info("[*] Server is listening on 0.0.0.0:{}".format(self.port))

        while True:
            client, info = self.socket.accept()
            logging.info("[*] Server accept the connection from {}:{}".format(info[0], info[1]))

            client_handle = threading.Thread(target=self.handler, args=(client,))
            client_handle.start()

    def recv_exact(self, client, size):
        buf = b""
        while len(buf) < size:
            chunk = client.recv(size - len(buf))
            if not chunk:
                logging.error("[*] connection closed while receiving data")
                sys.exit(1)
            buf += chunk
        return buf

    def send_instance(self, vlst, is_training):
        if is_training:
            url = "http://{}:{}/{}/training".format(self.caddr, self.cport, self.name)
        else:
            url = "http://{}:{}/{}/testing".format(self.caddr, self.cport, self.name)
        data = {}
        data["value"] = vlst
        req = json.dumps(data)
        response = requests.put(url, json=req)
        resp = response.json()

        if "opcode" in resp:
            if resp["opcode"] == "failure":
                logging.error("fail to send the instance to the ai module")

                if "reason" in resp:
                    logging.error(resp["reason"])
                else:
                    logging.error("unknown error")
                sys.exit(1)
        else:
            logging.error("unknown response")
            sys.exit(1)

    def parse_data(self, buf, is_training, mode):
        # 엣지가 보낸 5바이트 payload를 mode와 무관하게 동일한 바이트 레이아웃으로 파싱한다.
        #   buf[0:2] = power_max (2바이트, 빅엔디안)
        #   buf[2:3] = feature1  (1바이트)
        #   buf[3:4] = feature2  (1바이트)
        #   buf[4:5] = month     (1바이트)
        power = int.from_bytes(buf[0:2], byteorder="big", signed=True)
        feature1 = int.from_bytes(buf[2:3], byteorder="big", signed=True)
        feature2 = int.from_bytes(buf[3:4], byteorder="big", signed=True)
        month = int.from_bytes(buf[4:5], byteorder="big", signed=True)

        # mode에 따라 feature1/feature2의 "의미"만 달라진다(값 위치는 동일). 로그 가독성용 라벨.
        if mode == OPCODE_MODE_TEMP:
            label = "[power_max, temp_max, temp_avg, month]"
        elif mode == OPCODE_MODE_HUMID:
            label = "[power_max, humid_max, humid_avg, month]"
        else:
            label = "[power_max, temp_max, humid_max, month]"

        # AI 모듈로 보낼 인스턴스. 전력값(power)이 index 0에 위치하므로 --index 0 으로 실행한다.
        lst = [power, feature1, feature2, month]
        logging.info("{} = {}".format(label, lst))

        self.send_instance(lst, is_training)


    # TODO: You should implement your own protocol in this function
    # The following implementation is just a simple example
    def handler(self, client):
        logging.info("[*] Server starts to process the client's request")

        ntrain = self.ntrain
        url = "http://{}:{}/{}/training".format(self.caddr, self.cport, self.name)

        while True:
            # Edge protocol:
            #   OPCODE_DATA (1 byte) || mode (1 byte) || power_max (2 bytes)
            #   || feature1 (1 byte) || feature2 (1 byte) || month (1 byte)
            rbuf = self.recv_exact(client, 1)
            opcode = int.from_bytes(rbuf, "big")
            logging.debug("[*] opcode: {}".format(opcode))

            if opcode == OPCODE_DATA:
                payload = self.recv_exact(client, 6)
                mode = payload[0]
                data_buf = payload[1:6]

                if mode not in (OPCODE_MODE_TEMP, OPCODE_MODE_HUMID, OPCODE_MODE_COMBINED):
                    logging.error("[*] invalid mode: {}".format(mode))
                    logging.error("[*] please try again")
                    sys.exit(1)

                logging.info("[*] data report from the edge (mode={})".format(mode))
                logging.debug("[*] received payload: {}".format(payload))
                self.parse_data(data_buf, True, mode)
            else:
                logging.error("[*] invalid opcode: {}".format(opcode))
                logging.error("[*] expected OPCODE_DATA ({})".format(OPCODE_DATA))
                logging.error("[*] please try again")
                sys.exit(1)

            ntrain -= 1

            if ntrain > 0:
                opcode = OPCODE_DONE
                logging.debug("[*] send the opcode OPCODE_DONE")
                client.send(int.to_bytes(opcode, 1, "big"))
            else:
                opcode = OPCODE_WAIT
                logging.debug("[*] send the opcode OPCODE_WAIT")
                client.send(int.to_bytes(opcode, 1, "big"))
                break

        result = requests.post(url)
        response = json.loads(result.content)
        logging.debug("[*] return: {}".format(response["opcode"]))
    
        ntest = self.ntest
        url = "http://{}:{}/{}/testing".format(self.caddr, self.cport, self.name)
        opcode = OPCODE_DONE
        logging.debug("[*] send the opcode OPCODE_DONE")
        client.send(int.to_bytes(opcode, 1, "big"))

        while ntest > 0:
            # Edge protocol:
            #   OPCODE_DATA (1 byte) || mode (1 byte) || power_max (2 bytes)
            #   || feature1 (1 byte) || feature2 (1 byte) || month (1 byte)
            rbuf = self.recv_exact(client, 1)
            opcode = int.from_bytes(rbuf, "big")
            logging.debug("[*] opcode: {}".format(opcode))

            if opcode == OPCODE_DATA:
                payload = self.recv_exact(client, 6)
                mode = payload[0]
                data_buf = payload[1:6]

                if mode not in (OPCODE_MODE_TEMP, OPCODE_MODE_HUMID, OPCODE_MODE_COMBINED):
                    logging.error("[*] invalid mode: {}".format(mode))
                    logging.error("[*] please try again")
                    sys.exit(1)

                logging.info("[*] data report from the edge (mode={})".format(mode))
                logging.debug("[*] received payload: {}".format(payload))
                self.parse_data(data_buf, False, mode)
            else:
                logging.error("[*] invalid opcode: {}".format(opcode))
                logging.error("[*] expected OPCODE_DATA ({})".format(OPCODE_DATA))
                logging.error("[*] please try again")
                sys.exit(1)

            ntest -= 1

            if ntest > 0:
                opcode = OPCODE_DONE
                client.send(int.to_bytes(opcode, 1, "big"))
            else:
                opcode = OPCODE_QUIT
                client.send(int.to_bytes(opcode, 1, "big"))
                break

        url = "http://{}:{}/{}/result".format(self.caddr, self.cport, self.name)
        result = requests.get(url)
        response = json.loads(result.content)
        logging.debug("response: {}".format(response))
        if "opcode" not in response:
            logging.error("invalid response from the AI module: no opcode is specified")
            logging.error("please try again")
            sys.exit(1)
        else:
            if response["opcode"] == "failure":
                logging.error("getting the result from the AI module failed")
                if "reason" in response:
                    logging.error(response["reason"])
                logging.error("please try again")
                sys.exit(1)
            elif response["opcode"] == "success":
                self.print_result(response)
            else:
                logging.error("unknown error")
                logging.error("please try again")
                sys.exit(1)

    def print_result(self, result):
        logging.info("=== Result of Prediction ({}) ===".format(self.name))
        logging.info("   # of instances: {}".format(result["num"]))
        logging.debug("   sequence: {}".format(result["sequence"]))
        logging.debug("   prediction: {}".format(result["prediction"]))
        logging.info("   correct predictions: {}".format(result["correct"]))
        logging.info("   incorrect predictions: {}".format(result["incorrect"]))
        logging.info("   accuracy: {}%".format(result["accuracy"]))

def command_line_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--algorithm", metavar="<AI algorithm to be used>", help="AI algorithm to be used", type=str, required=True)
    parser.add_argument("-d", "--dimension", metavar="<Dimension of each instance>", help="Dimension of each instance", type=int, default=1)
    parser.add_argument("-b", "--caddr", metavar="<AI module's IP address>", help="AI module's IP address", type=str, required=True)
    parser.add_argument("-c", "--cport", metavar="<AI module's listening port>", help="AI module's listening port", type=int, required=True)
    parser.add_argument("-p", "--lport", metavar="<server's listening port>", help="Server's listening port", type=int, required=True)
    parser.add_argument("-n", "--name", metavar="<model name>", help="Name of the model", type=str, default="model")
    parser.add_argument("-x", "--ntrain", metavar="<number of instances for training>", help="Number of instances for training", type=int, default=10)
    parser.add_argument("-y", "--ntest", metavar="<number of instances for testing>", help="Number of instances for testing", type=int, default=10)
    parser.add_argument("-z", "--index", metavar="<the index number for the power value>", help="Index number for the power value", type=int, default=0)
    parser.add_argument("-l", "--log", metavar="<log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)>", help="Log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)", type=str, default="INFO")
    args = parser.parse_args()
    return args

def main():
    args = command_line_args()
    logging.basicConfig(level=args.log)

    if args.ntrain <= 0 or args.ntest <= 0:
        logging.error("Number of instances for training or testing should be larger than 0")
        sys.exit(1)

    Server(args.name, args.algorithm, args.dimension, args.index, args.lport, args.caddr, args.cport, args.ntrain, args.ntest)

if __name__ == "__main__":
    main()
