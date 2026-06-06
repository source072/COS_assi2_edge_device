#ifndef __POWER_DATA_H__
#define __POWER_DATA_H__

#include <random>
#include <ctime>
#include <string>
#include "info.h"

class PowerData
{
  private:
    time_t timestamp;
    double avg;
    string unit;
    PowerData *next;
  public:
    PowerData(time_t timestamp, double avg);

    void setNext(PowerData *data);
    PowerData *getNext();

    void setValue(double value);
    double getValue();

    void setTimestamp(time_t timestamp);
    time_t getTimestamp();

    string getUnit();
};

#endif /* __POWER_DATA_H__ */
