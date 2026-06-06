#include "network_manager.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <assert.h>

#include "opcode.h"
using namespace std;

NetworkManager::NetworkManager() 
{
  this->sock = -1;
  this->addr = NULL;
  this->port = -1;
}

NetworkManager::NetworkManager(const char *addr, int port)
{
  this->sock = -1;
  this->addr = addr;
  this->port = port;
}

void NetworkManager::setAddress(const char *addr)
{
  this->addr = addr;
}

const char *NetworkManager::getAddress()
{
  return this->addr;
}

void NetworkManager::setPort(int port)
{
  this->port = port;
}

int NetworkManager::getPort()
{
  return this->port;
}

int NetworkManager::init()
{
	struct sockaddr_in serv_addr;

	this->sock = socket(PF_INET, SOCK_STREAM, 0);
	if (this->sock == FAILURE)
  {
    cout << "[*] Error: socket() error" << endl;
    cout << "[*] Please try again" << endl;
    exit(1);
  }

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(this->addr);
	serv_addr.sin_port = htons(this->port);

	if (connect(this->sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == FAILURE)
  {
    cout << "[*] Error: connect() error" << endl;
    cout << "[*] Please try again" << endl;
    exit(1);
  }
	
  cout << "[*] Connected to " << this->addr << ":" << this->port << endl;

  return sock;
}

// TODO: You should revise the following code
int NetworkManager::sendData(uint8_t *data, int dlen) {
    int sock, tbs, sent, offset;
    unsigned char opcode;

    sock = this->sock;

    // 1. 먼저 데이터 전송 opcode를 보냄
    opcode = OPCODE_DATA;
    tbs = 1;
    offset = 0;

    while (offset < tbs) {
        sent = write(sock, &opcode + offset, tbs - offset);
        if (sent > 0) {
            offset += sent;
        }
    }
    assert(offset == tbs);

    // 2. processData()가 만든 payload를 보냄
    // payload:
    // mode || power_max || feature1 || feature2 || month
    tbs = dlen;
    offset = 0;

    while (offset < tbs) {
        sent = write(sock, data + offset, tbs - offset);
        if (sent > 0) {
            offset += sent;
        }
    }
    assert(offset == tbs);

    return 0;
}

// TODO: Please revise or implement this function as you want. You can also remove this function if it is not needed
uint8_t NetworkManager::receiveCommand() 
{
  int sock;
  uint8_t opcode;
  uint8_t *p;

  sock = this->sock;
  opcode = OPCODE_WAIT;

  while (opcode == OPCODE_WAIT)
    read(sock, &opcode, 1);

  assert(opcode == OPCODE_DONE || opcode == OPCODE_QUIT) ;

  return opcode;
}
