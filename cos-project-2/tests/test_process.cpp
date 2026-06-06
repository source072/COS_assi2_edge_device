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
  // ts = ;
  // cout << "timestamp: " << ts << endl;

  // 2. Write a statement to get the number of house data that contains the private information and the power value to 'num' (dataset.h)
  // num = ;
  // cout << "# of house data: " << num << endl;

  // 3. Write a statement to get the first house data to 'house' (please refer to dataset.h) 
  // house = ;
  //
  // Write a statement to get the 10th house data to 'house' (dataset.h)
  // house = ;
  //
  // Get the power data to 'pdata' (house_data.h)
  // pdata = ;
  //
  // Get the daily power value to 'power' and print out the value (power_data.h)
  // power = ;
  // cout << "Power: " << power << endl;
  //
  // Explicitly cast the type from double to int and assign it to 'tmp', and print out the value
  // tmp = ;
  // cout << "Power (casted): " << tmp << endl;
  //
  // Compute the value averaged over all the power data by using 'sum_power' and 'num', 
  // assign the average value to 'avg_power', and print out the value
  //
  // cout << "Power (avg): " << avg_power << endl;
  //
  // Find the maximum value among all the power data 
  //
  // cout << "Power (max): " << max_power << endl;
  //
  // Find the minimum value among all the power data
  //
  // cout << "Power (min): " << min_power << endl;

  // 4. Write a statement to get the temperature data to 'tdata' (dataset.h)
  // tdata = ;
  //
  // Get the maximum value of the daily temperature (temperature_data.h)
  // max_temp = ;
  // cout << "Temperature (max): " << max_temp << endl;
  //
  // Get the average value of the daily temperature (temperature_data.h)
  // avg_temp = ;
  // cout << "Temperature (avg): " << avg_temp << endl;
  //
  // Get the minimum value of the daily temperature (temperature_data.h)
  // min_temp = ;
  // cout << "Temperature (min): " << min_temp << endl;
  //
  // Explicitly cast the type of the maximum value from double to int, assign the resultant value to 'tmp', and print it out
  // tmp = ;
  // cout << "Temperature (max, casted): " << tmp << endl;

  // 5. Write a statement to get the humidity data to 'hdata' (dataset.h)
  // hdata = ;
  //
  // Get the maximum value of the daily humidity (humidity_data.h)
  // max_humid = ;
  // cout << "Humidity (max): " << max_humid << endl;
  //
  // Get the average value of the daily humidity (humidity_data.h)
  // avg_humid = ;
  // cout << "Humidity (avg): " << avg_humid << endl;
  //
  // Get the minimum value of the daily humidity (humidity_data.h)
  // min_humid = ;
  // cout << "Humidity (min): " << min_humid << endl;
  //
  // Explicitly cast the type of the minimum value from double to int, assign the resultant value to 'tmp', and print it out
  // tmp = ;
  // cout << "Humidity (min, casted): " << tmp << endl;

  // 6. Initialize the buffer 'buf' with zeros (its length is defined as BUFLEN) (use the memset() function, please google it!)

  // 7. Write statements to save the values into 'buf' using 'p' as follows:
  // # of house data (2 bytes) || maximum power (integer) (4 bytes) || maximum temperature (integer) (2 bytes)
  // Print out the buffer
  // Please use the macros defined in edge/byte_op.h

	return 0;
}
