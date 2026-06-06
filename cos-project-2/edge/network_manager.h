#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include <cstdint>
#include "setting.h"

class NetworkManager {
  private:
    int sock;
    const char *addr;
    int port;
    uint8_t wbuf[BUFLEN];
    uint8_t rbuf[BUFLEN];

  public:
    NetworkManager();
    NetworkManager(const char *addr, int port);

    void setAddress(const char *addr);
    const char *getAddress();

    void setPort(int port);
    int getPort();

    int init();
    int sendData(uint8_t *data, int dlen);
    uint8_t receiveCommand();
};

#endif /* __NETWORK_MANAGER_H__ */
