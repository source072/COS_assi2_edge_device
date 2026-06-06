#include "edge.h"
#include "opcode.h"
#include <iostream>
#include <ctime>
using namespace std;

Edge::Edge() 
{
  this->dr = new DataReceiver();
  this->nm = new NetworkManager();
  this->pm = new ProcessManager();
}

Edge::~Edge()
{
  delete this->dr;
  delete this->nm;
  delete this->pm;
}

Edge::Edge(const char *addr, int port)
{
  this->dr = new DataReceiver();
  this->nm = new NetworkManager(addr, port);
  this->pm = new ProcessManager();
}

void Edge::init()
{
  this->dr->init();
  this->nm->init();
  this->pm->init();
}

void Edge::run()
{
  time_t curr;
  uint8_t opcode;
  uint8_t *data;
  DataSet *ds;
  int dlen;
  opcode = OPCODE_DONE;

  cout << "[*] Running the edge device" << endl;

  curr = 1609459200;
  while (opcode != OPCODE_QUIT)
  {
    ds = this->dr->getDataSet(curr);
    data = this->pm->processData(ds, &dlen);
    this->nm->sendData(data, dlen);
    opcode = this->nm->receiveCommand();

    curr += 86400;
  }

  cout << "[*] End running" << endl;
}
