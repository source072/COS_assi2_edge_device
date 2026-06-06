#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <getopt.h>
#include <stdint.h>

#include "../edge/byte_op.h"

#define BUFLEN  1024

void protocol_execution(int sock);
void error_handling(const char *message);

void usage(const char *pname)
{
  printf(">> Usage: %s [options]\n", pname);
  printf("Options\n");
  printf("  -a, --addr       Server's address\n");
  printf("  -p, --port       Server's port\n");
  exit(0);
}

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
  char msg[] = "Hello, World!\n";
	char message[30] = {0, };
	int c, port, tmp, str_len;
  char *pname;
  uint8_t *addr;
  uint8_t eflag;

  pname = argv[0];
  addr = NULL;
  port = -1;
  eflag = 0;

  while (1)
  {
    int option_index = 0;
    static struct option long_options[] = {
      {"addr", required_argument, 0, 'a'},
      {"port", required_argument, 0, 'p'},
      {0, 0, 0, 0}
    };

    const char *opt = "a:p:0";

    c = getopt_long(argc, argv, opt, long_options, &option_index);

    if (c == -1)
      break;

    switch (c)
    {
      case 'a':
        tmp = strlen(optarg);
        addr = (uint8_t *)malloc(tmp);
        memcpy(addr, optarg, tmp);
        break;

      case 'p':
        port = atoi(optarg);
        break;

      default:
        usage(pname);
    }
  }

  if (!addr)
  {
    printf("[*] Please specify the server's address to connect\n");
    eflag = 1;
  }

  if (port < 0)
  {
    printf("[*] Please specify the server's port to connect\n");
    eflag = 1;
  }

  if (eflag)
  {
    usage(pname);
    exit(0);
  }

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr((const char *)addr);
	serv_addr.sin_port = htons(port);

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");
  printf("[*] Connected to %s:%d\n", addr, port);
  
  protocol_execution(sock);

	close(sock);
	return 0;
}

void protocol_execution(int sock)
{
  char msg[] = "Alice";
  char buf[BUFLEN];
  int tbs, sent, tbr, rcvd, offset;
  int len;

  // tbs: the number of bytes to send
  // tbr: the number of bytes to receive
  // offset: the offset of the message

  // 1. Alice -> Bob: length of the name (4 bytes) || name (length bytes)
  // Send the length information (4 bytes)
  len = strlen(msg);
  printf("[*] Length information to be sent: %d\n", len);

  len = htonl(len);
  tbs = 4;
  offset = 0;

  while (offset < tbs)
  {
    sent = write(sock, &len + offset, tbs - offset);
    if (sent > 0)
      offset += sent;
  }

  // Send the name (Alice)
  tbs = ntohl(len);
  offset = 0;

  printf("[*] Name to be sent: %s\n", msg);
  while (offset < tbs)
  {
    sent = write(sock, msg + offset, tbs - offset);
    if (sent > 0)
      offset += sent;
  }

  // 2. Bob -> Alice: length of the name (4 bytes) || name (length bytes)
  // Receive the length information (4 bytes)
  tbr = 4;
  offset = 0;

  while (offset < tbr)
  {
	  rcvd = read(sock, &len + offset, tbr - offset);
    if (rcvd > 0)
      offset += rcvd;
  }
  len = ntohl(len);
  printf("[*] Length received: %d\n", len);

  // Receive the name (Bob)
  tbr = len;
  offset = 0;

  while (offset < tbr)
  {
    rcvd = read(sock, buf + offset, tbr - offset);
    if (rcvd > 0)
      offset += rcvd;
  }

	printf("[*] Name received: %s \n", buf);

  // Implement following the instructions below
  // Let's assume there are two opcodes:
  //     1: summation request for the two arguments
  //     2: reply with the result
  // 3. Alice -> Bob: opcode (4 bytes) || arg1 (4 bytes) || arg2 (4 bytes)
  // The opcode should be 1


  // 4. Bob -> Alice: opcode (4 bytes) || result (4 bytes)
  // The opcode should be 2



}

void error_handling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
