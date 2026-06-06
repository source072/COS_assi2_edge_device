#ifndef __DATA_RECEIVER_H__
#define __DATA_RECEIVER_H__

#include <ctime>
#include <random>
#include "data/info.h"
#include "data/data.h"
#include "data/dataset.h"
#include "setting.h"

using namespace std;

class DataReceiver {
  private:
    int num;
    Info *info[NUM_OF_CUSTOMER];
    default_random_engine generator;
    normal_distribution<double> dist[24];

  public:
    DataReceiver();

    int getNumOfPeriod();

    void init();
    DataSet *getDataSet(time_t timestamp);
};

#endif /* __DATA_RECEIVER_H__ */
