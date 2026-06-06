#include <cstdlib>
#include <ctime>
#include "dataset.h"

DataSet::DataSet(time_t timestamp) 
{
  this->timestamp = timestamp;
  this->num = 0;
  this->head = NULL;
  this->tail = NULL;
  this->iterator = 0;
}

int DataSet::getNumHouseData()
{
  return this->num;
}

void DataSet::addHouseData(HouseData *data)
{
  HouseData *curr;

  if (!this->head)
    this->head = data;

  curr = this->tail;
  if (curr)
    curr->setNext(data);
  this->tail = data;

  this->num++;
}

HouseData *DataSet::getHouseData(int index)
{
  HouseData *ret;
  ret = this->head;

  if (index < this->num)
  {
    for (int i=0; i<index; i++)
      ret = ret->getNext();
  }
  else
    ret = NULL;

  return ret;
}

void DataSet::setIterator()
{
  this->iterator = 0;
}

HouseData *DataSet::getNextHouseData()
{
  HouseData *ret;
  ret = this->getHouseData(this->iterator);
  if (ret)
    this->iterator++;
  return ret;
}

void DataSet::setTemperatureData(TemperatureData *temp)
{
  this->temp = temp;
}

TemperatureData *DataSet::getTemperatureData()
{
  return this->temp;
}

void DataSet::setHumidityData(HumidityData *humid)
{
  this->humid = humid;
}

HumidityData *DataSet::getHumidityData()
{
  return this->humid;
}

time_t DataSet::getTimestamp()
{
  return this->timestamp;
}
