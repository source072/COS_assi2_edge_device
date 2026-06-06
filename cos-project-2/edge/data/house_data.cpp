#include <cstdlib>
#include <iostream>
#include "house_data.h"

HouseData::HouseData(Info *info)
{
  this->info = info;
  this->data = NULL;
}

HouseData::HouseData(Info *info, PowerData *power)
{
  this->info = info;
  this->data = power;
}

void HouseData::setInfo(Info *info)
{
  this->info = info;
}

Info *HouseData::getInfo()
{
  return this->info;
}

string HouseData::getSerial()
{
  return this->info->getSerial();
}

string HouseData::getName()
{
  return this->info->getName();
}

string HouseData::getAddress()
{
  return this->info->getAddress();
}

void HouseData::setPowerData(PowerData *power)
{
  this->data = power;
}

PowerData *HouseData::getPowerData()
{
  return this->data;
}

void HouseData::setNext(HouseData *data)
{
  this->next = data;
}

HouseData *HouseData::getNext()
{
  return this->next;
}
