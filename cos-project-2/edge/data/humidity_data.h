#ifndef __HUMIDITY_DATA_H__
#define __HUMIDITY_DATA_H__

#include <random>
#include <ctime>
#include <string>
#include "info.h"

class HumidityData
{
  private:
    time_t timestamp;
    double avg;
    double min;
    double max;
    string unit;
    HumidityData *next;
  public:
    HumidityData(time_t timestamp, double min, double max, double avg);

    void setNext(HumidityData *data);
    HumidityData *getNext();

    void setValue(double value);
    double getValue();

    void setMin(double min);
    double getMin();

    void setMax(double max);
    double getMax();

    void setTimestamp(time_t timestamp);
    time_t getTimestamp();

    string getUnit();
};

#endif /* __HUMIDITY_DATA_H__ */
