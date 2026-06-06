#include "../edge/setting.h"
#include "../edge/edge.h"

#include <iostream>
#include <ctime>

#include "../edge/byte_op.h"

#define BUFLEN 1024

using namespace std;

int main(int argc, char *argv[])
{
  DataReceiver *dr;
  DataSet *ds;
  HouseData *house;
  TemperatureData *tdata;
  HumidityData *hdata;
  PowerData *pdata;
  int num, tmp;
  time_t curr, ts;
  double max_temp, avg_temp, min_temp;
  double max_humid, avg_humid, min_humid;
  double power, sum_power, avg_power, max_power, min_power;
  unsigned char buf[BUFLEN];
  unsigned char *p;

  curr = 1609459200;
  dr = new DataReceiver();
  ds = dr->getDataSet(curr);
  
  // 1. Write a statement to get the timestamp value to 'ts' and print out the value (please refer to dataset.h)
  ts = ds->getTimestamp();
  cout << "timestamp: " << ts << endl;

  // 2. Write a statement to get the number of house data that contains the private information and the power value to 'num' (dataset.h)
  num = ds->getNumHouseData();
  cout << "# of house data: " << num << endl;

  // 3. Write a statement to get the first house data to 'house' (please refer to dataset.h) 
  house = ds->getHouseData(0);
  
  // Write a statement to get the 10th house data to 'house' (dataset.h)
  house = ds->getHouseData(9);
  
  // Get the power data to 'pdata' (house_data.h)
  pdata = house->getPowerData();
  
  // Get the daily power value to 'power' and print out the value (power_data.h)
  power = pdata->getValue();
  cout << "Power: " << power << endl;
  
  // Explicitly cast the type from double to int and assign it to 'tmp', and print out the value
  tmp = (int)pdata->getValue();
  cout << "Power (casted): " << tmp << endl;
  
  // Compute the value averaged over all the power data by using 'sum_power' and 'num', 
  // assign the average value to 'avg_power', and print out the value
  sum_power = 0;
  for (int i=0; i<num; i++)
  {
    house = ds->getHouseData(i);
    pdata = house->getPowerData();
    sum_power += pdata->getValue();
  }
  avg_power = sum_power / num;
  cout << "Power (avg): " << avg_power << endl;
  
  // Find the maximum value among all the power data 
  max_power = -1;
  for (int i=0; i<num; i++)
  {
    house = ds->getHouseData(i);
    pdata = house->getPowerData();
    power = pdata->getValue();

    if (power > max_power)
      max_power = power;
  }
  cout << "Power (max): " << max_power << endl;
  
  // Find the minimum value among all the power data
  min_power = 10000;
  for (int i=0; i<num; i++)
  {
    house = ds->getHouseData(i);
    pdata = house->getPowerData();
    power = pdata->getValue();

    if (power < min_power)
      min_power = power;
  }
  cout << "Power (min): " << min_power << endl;

  // 4. Write a statement to get the temperature data to 'tdata' (dataset.h)
  tdata = ds->getTemperatureData();
  
  // Get the maximum value of the daily temperature (temperature_data.h)
  max_temp = tdata->getMax();
  cout << "Temperature (max): " << max_temp << endl;
  
  // Get the average value of the daily temperature (temperature_data.h)
  avg_temp = tdata->getValue();
  cout << "Temperature (avg): " << avg_temp << endl;
  
  // Get the minimum value of the daily temperature (temperature_data.h)
  min_temp = tdata->getMin();
  cout << "Temperature (min): " << min_temp << endl;
  
  // Explicitly cast the type of the maximum value from double to int, assign the resultant value to 'tmp', and print it out
  tmp = (int)tdata->getMax();
  cout << "Temperature (max, casted): " << tmp << endl;

  // 5. Write a statement to get the humidity data to 'hdata' (dataset.h)
  hdata = ds->getHumidityData();
  
  // Get the maximum value of the daily humidity (humidity_data.h)
  max_humid = hdata->getMax();
  cout << "Humidity (max): " << max_humid << endl;
  
  // Get the average value of the daily humidity (humidity_data.h)
  avg_humid = hdata->getValue();
  cout << "Humidity (avg): " << avg_humid << endl;
  
  // Get the minimum value of the daily humidity (humidity_data.h)
  min_humid = hdata->getMin();
  cout << "Humidity (min): " << min_humid << endl;
  
  // Explicitly cast the type of the minimum value from double to int, assign the resultant value to 'tmp', and print it out
  tmp = (int)hdata->getMin();
  cout << "Humidity (min, casted): " << tmp << endl;

  // 6. Initialize the buffer 'buf' with zeros (its length is defined as BUFLEN) (use the memset() function, please google it!)
  memset(buf, 0, BUFLEN);

  // 7. Write statements to save the values into 'buf' using 'p' as follows:
  // # of house data (2 bytes) || maximum power (integer) (4 bytes) || maximum temperature (integer) (2 bytes)
  // Print out the buffer
  // Please use the macros defined in edge/byte_op.h
  p = buf;
  VAR_TO_MEM_2BYTES_BIG_ENDIAN(num, p);
  tmp = (int)min_power;
  VAR_TO_MEM_4BYTES_BIG_ENDIAN(tmp, p);
  tmp = (int)max_temp;
  VAR_TO_MEM_4BYTES_BIG_ENDIAN(tmp, p);

  tmp = p - buf;
  PRINT_MEM(buf, tmp);

	return 0;
}
