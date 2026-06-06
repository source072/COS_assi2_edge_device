#include "process_manager.h"
#include "opcode.h"
#include "byte_op.h"
#include "setting.h"
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;

ProcessManager::ProcessManager()
{
  this->num = 0;
}

void ProcessManager::init()
{
}

// TODO: You should implement this function if you want to change the result of the aggregation
uint8_t *ProcessManager::processData(DataSet *ds, int *dlen) {
    uint8_t *ret, *p;
    int num;
    HouseData *house;
    PowerData *pdata;
    TemperatureData *tdata;
    HumidityData *hdata;

    int mode;
    int power_max;
    int temp_max, temp_avg;
    int humid_max, humid_avg;
    int month;

    time_t ts;
    struct tm *tm;

    ret = (uint8_t *)malloc(BUFLEN);
    memset(ret, 0, BUFLEN);

    tdata = ds->getTemperatureData();
    hdata = ds->getHumidityData();
    num = ds->getNumHouseData();

    // 1. mode 선택
    // 처음에는 테스트를 쉽게 하려고 고정값으로 시작해도 됨.
    // 0: temp, 1: humid, 2: combined
    mode = 0;

    // 나중에 매일 mode를 바꾸고 싶으면 예:
    // mode = this->num % 3;
    // this->num++;

    // 2. temperature / humidity feature 추출
    temp_max = (int)tdata->getMax();
    temp_avg = (int)tdata->getValue();

    humid_max = (int)hdata->getMax();
    humid_avg = (int)hdata->getValue();

    // 3. power_max 계산
    power_max = 0;
    for (int i = 0; i < num; i++) {
        house = ds->getHouseData(i);
        pdata = house->getPowerData();

        int power = (int)pdata->getValue();
        if (power > power_max) {
            power_max = power;
        }
    }

    // 4. timestamp에서 month 추출
    ts = ds->getTimestamp();
    tm = localtime(&ts);
    month = tm->tm_mon + 1;

    // 5. buffer에 encoding
    p = ret;
    *dlen = 0;

    VAR_TO_MEM_1BYTE_BIG_ENDIAN(mode, p);
    *dlen += 1;

    VAR_TO_MEM_2BYTES_BIG_ENDIAN(power_max, p);
    *dlen += 2;

    if (mode == 0) {
        // temp mode:
        // mode || power_max || temp_max || temp_avg || month
        VAR_TO_MEM_1BYTE_BIG_ENDIAN(temp_max, p);
        *dlen += 1;

        VAR_TO_MEM_1BYTE_BIG_ENDIAN(temp_avg, p);
        *dlen += 1;
    }
    else if (mode == 1) {
        // humid mode:
        // mode || power_max || humid_max || humid_avg || month
        VAR_TO_MEM_1BYTE_BIG_ENDIAN(humid_max, p);
        *dlen += 1;

        VAR_TO_MEM_1BYTE_BIG_ENDIAN(humid_avg, p);
        *dlen += 1;
    }
    else {
        // combined mode:
        // mode || power_max || temp_max || humid_max || month
        VAR_TO_MEM_1BYTE_BIG_ENDIAN(temp_max, p);
        *dlen += 1;

        VAR_TO_MEM_1BYTE_BIG_ENDIAN(humid_max, p);
        *dlen += 1;
    }

    VAR_TO_MEM_1BYTE_BIG_ENDIAN(month, p);
    *dlen += 1;

    return ret;
}
