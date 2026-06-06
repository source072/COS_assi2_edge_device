#include <cstring>
#include <iostream>
#include "data_receiver.h"
#include "data/raw_data.h"
#include "data/power_data.h"
#include "data/temperature_data.h"
#include "data/humidity_data.h"
#include "data/house_data.h"

using namespace std;

DataReceiver::DataReceiver()
{
  this->num = 0;
  for (int i=0; i<NUM_OF_CUSTOMER; i++)
    this->info[i] = NULL;
}

int DataReceiver::getNumOfPeriod()
{
  return this->num;
}

void DataReceiver::init()
{
  double mean, stdev;

  for (int i=0; i<NUM_OF_CUSTOMER; i++)
    this->info[i] = new Info(i);
}

DataSet *DataReceiver::getDataSet(time_t timestamp)
{
  DataSet *ret;
  HouseData *data;
  PowerData *power;
  TemperatureData *temp;
  HumidityData *humid;
  int mean, stdev;
  struct tm *tm;
  char buf[11];
  int midx, didx, value;

  ret = new DataSet(timestamp);
  tm = localtime(&timestamp);
  snprintf(buf, 11, "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);

  for (midx=0; midx<24; midx++)
  {
    if (!strncmp(buf, month[midx], 7))
      break;
  }

  mean = power_avg[midx];
  stdev = (int) (mean * 0.2);

  for (didx=0; didx<730; didx++)
  {
    if (!strncmp(buf, date[didx], 10))
      break;
  }

  temp = new TemperatureData(timestamp, temp_min[didx], temp_max[didx], temp_avg[didx]);
  ret->setTemperatureData(temp);

  humid = new HumidityData(timestamp, humid_min[didx], humid_max[didx], humid_avg[didx]);
  ret->setHumidityData(humid);

  srand(time(NULL));
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<float> dist(mean, stdev);

  for (int i=0; i<NUM_OF_CUSTOMER; i++)
  {
    data = new HouseData(this->info[i]);
    value = (int) dist(gen);
    power = new PowerData(timestamp, value);
    data->setPowerData(power);
    ret->addHouseData(data);
  }

  this->num++;
  return ret;
}
