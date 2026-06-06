#include "power_data.h"

PowerData::PowerData(time_t timestamp, double avg)
{
  this->timestamp = timestamp;
  this->avg = avg;
  this->next = NULL;
  this->unit = "kWh";
}

void PowerData::setNext(PowerData *next)
{
  this->next = next;
}

PowerData *PowerData::getNext()
{
  return this->next;
}

void PowerData::setValue(double value)
{
  this->avg = value;
}

double PowerData::getValue()
{
  return this->avg;
}

void PowerData::setTimestamp(time_t timestamp)
{
  this->timestamp = timestamp;
}

time_t PowerData::getTimestamp()
{
  return this->timestamp;
}

