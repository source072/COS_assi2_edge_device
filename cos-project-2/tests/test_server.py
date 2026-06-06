import socket
import threading
import argparse
import logging

def protocol_execution(sock):
    # 1. Alice -> Bob: length of the name (4 bytes) || name (length bytes)
    # Get the length information (4 bytes)
    buf = sock.recv(4)
    length = int.from_bytes(buf, "big")
    logging.info("[*] Length received: {}".format(length))

    # Get the name (Alice)
    buf = sock.recv(length)
    logging.info("[*] Name received: {}".format(buf.decode()))

    # 2. Bob -> Alice: length of the name (4 bytes) || name (length bytes)
    # Send the length information (4 bytes)
    name = "Bob"
    length = len(name)
    logging.info("[*] Length to be sent: {}".format(length))
    sock.send(int.to_bytes(length, 4, "big"))

    # Send the name (Bob)
    logging.info("[*] Name to be sent: {}".format(name))
    sock.send(name.encode())

    # Implement following the instructions below
    # 3. Alice -> Bob: opcode (4 bytes) || arg1 (4 bytes) || arg2 (4 bytes)
    # The opcode should be 1


    # 4. Bob -> Alice: opcode (4 bytes) || result (4 bytes)
    # The opcode should be 2


    sock.close()

def run(addr, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((addr, port))

    server.listen(2)
    logging.info("[*] Server is Listening on {}:{}".format(addr, port))

    while True:
        client, info = server.accept()

        logging.info("[*] Server accept the connection from {}:{}".format(info[0], info[1]))

        client_handle = threading.Thread(target=protocol_execution, args=(client,))
        client_handle.start()

def command_line_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--addr", metavar="<server's IP address>", help="Server's IP address", type=str, default="0.0.0.0")
    parser.add_argument("-p", "--port", metavar="<server's open port>", help="Server's port", type=int, required=True)
    parser.add_argument("-l", "--log", metavar="<log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)>", help="Log level (DEBUG/INFO/WARNING/ERROR/CRITICAL)", type=str, default="INFO")
    args = parser.parse_args()
    return args

def main():
    args = command_line_args()
    log_level = args.log
    logging.basicConfig(level=log_level)

    run(args.addr, args.port)

if __name__ == "__main__":
    main()
