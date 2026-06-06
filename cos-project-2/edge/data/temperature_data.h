#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include <random>
#include <ctime>
#include <string>
#include "info.h"

class TemperatureData
{
  private:
    time_t timestamp;
    double avg;
    double min;
    double max;
    string unit;
    TemperatureData *next;
  public:
    TemperatureData(time_t timestamp, double min, double max, double avg);

    void setNext(TemperatureData *data);
    TemperatureData *getNext();

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

#endif /* __TEMPERATURE_H__ */
