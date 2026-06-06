#include "humidity_data.h"

HumidityData::HumidityData(time_t timestamp, double min, double max, double avg)
{
  this->timestamp = timestamp;
  this->avg = avg;
  this->min = min;
  this->max = max;
  this->next = NULL;
  this->unit = "\%";
}

void HumidityData::setNext(HumidityData *next)
{
  this->next = next;
}

HumidityData *HumidityData::getNext()
{
  return this->next;
}

void HumidityData::setValue(double value)
{
  this->avg = value;
}

double HumidityData::getValue()
{
  return this->avg;
}

void HumidityData::setMin(double min)
{
  this->min = min;
}

double HumidityData::getMin()
{
  return this->min;
}

void HumidityData::setMax(double max)
{
  this->max = max;
}

double HumidityData::getMax()
{
  return this->max;
}

void HumidityData::setTimestamp(time_t timestamp)
{
  this->timestamp = timestamp;
}

time_t HumidityData::getTimestamp()
{
  return this->timestamp;
}

string HumidityData::getUnit()
{
  return this->unit;
}
