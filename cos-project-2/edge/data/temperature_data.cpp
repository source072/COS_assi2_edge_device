#include "temperature_data.h"

TemperatureData::TemperatureData(time_t timestamp, double min, double max, double avg)
{
  this->timestamp = timestamp;
  this->avg = avg;
  this->min = min;
  this->max = max;
  this->next = NULL;
  this->unit = "celcius";
}

void TemperatureData::setNext(TemperatureData *next)
{
  this->next = next;
}

TemperatureData *TemperatureData::getNext()
{
  return this->next;
}

void TemperatureData::setValue(double value)
{
  this->avg = value;
}

double TemperatureData::getValue()
{
  return this->avg;
}

void TemperatureData::setMin(double min)
{
  this->min = min;
}

double TemperatureData::getMin()
{
  return this->min;
}

void TemperatureData::setMax(double max)
{
  this->max = max;
}

double TemperatureData::getMax()
{
  return this->max;
}

void TemperatureData::setTimestamp(time_t timestamp)
{
  this->timestamp = timestamp;
}

time_t TemperatureData::getTimestamp()
{
  return this->timestamp;
}

string TemperatureData::getUnit()
{
  return this->unit;
}
