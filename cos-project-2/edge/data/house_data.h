#ifndef __HOUSE_DATA_H__
#define __HOUSE_DATA_H__

#include <string>
#include <ctime>
#include "power_data.h"
#include "house_data.h"
#include "info.h"
using namespace std;

class HouseData 
{
  private:
    Info *info;
    PowerData *data;
    HouseData *next;
  public:
    HouseData(Info *info);
    HouseData(Info *info, PowerData *power);
    void setInfo(Info *info);
    Info *getInfo();

    string getSerial();
    string getName();
    string getAddress();

    void setPowerData(PowerData *power);
    PowerData *getPowerData();

    void setNext(HouseData *hd);
    HouseData *getNext();
};

#endif /* __HOUSE_DATA_H__ */
