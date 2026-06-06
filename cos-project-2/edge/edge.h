#ifndef __EDGE_H__
#define __EDGE_H__

#include "setting.h"
#include "data_receiver.h"
#include "network_manager.h"
#include "process_manager.h"

class Edge {
  private:
    DataReceiver *dr;
    NetworkManager *nm;
    ProcessManager *pm;

  public:
    Edge();
    Edge(const char *addr, int port);

    ~Edge();

    void setAddress(const char *addr);
    const char *getAddress();

    void setPort(int port);
    int getPort();

    void init();
    void run();
};

#endif /* __EDGE_H__ */
