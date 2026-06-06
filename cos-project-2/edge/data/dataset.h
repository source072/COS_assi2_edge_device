#ifndef __DATASET_H__
#define __DATASET_H__

#include "house_data.h"
#include "temperature_data.h"
#include "humidity_data.h"

class DataSet
{
  private:
    time_t timestamp;
    int num;
    TemperatureData *temp;
    HumidityData *humid;
    HouseData *head;
    HouseData *tail;
    int iterator;
  public:
    DataSet(time_t timestamp);

    int getNumHouseData();
    void addHouseData(HouseData *data);
    HouseData *getHouseData(int index);
    void setIterator();
    HouseData *getNextHouseData();

    void setTemperatureData(TemperatureData *temp);
    TemperatureData *getTemperatureData();

    void setHumidityData(HumidityData *humid);
    HumidityData *getHumidityData();

    time_t getTimestamp();
};

#endif /* __DATASET_H__ */
