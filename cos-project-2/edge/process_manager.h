#ifndef __PROCESS_MANAGER_H__
#define __PROCESS_MANAGER_H__

#include "data/dataset.h"
#include <cstdint>

class ProcessManager {
  private:
    int num;
  public:
    ProcessManager();

    void init();
    uint8_t *processData(DataSet *ds, int *dlen);
};

#endif /* __PROCESS_MANAGER_H__ */
