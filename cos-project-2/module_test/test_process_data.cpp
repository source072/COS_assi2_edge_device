#include "../edge/setting.h"
#include "../edge/edge.h"

#include <iostream>
#include <ctime>

#include "../edge/byte_op.h"

#define BUFLEN 1024

using namespace std;

int main(int argc, char *argv[])
{
  DataReceiver *dr;
  ProcessManager *pm;
  DataSet *ds;
  int dlen;
  time_t curr;
  unsigned char *data;

  curr = 1609459200;
  dr = new DataReceiver();
  pm = new ProcessManager();

  dr->init();
  pm->init();

  for (int i=0; i<100; i++)
  {
    ds = dr->getDataSet(curr);
    data = pm->processData(ds, &dlen);
    PRINT_MEM(data, dlen);
    curr += 86400;
  }

	return 0;
}
