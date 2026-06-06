#include "info.h"
#include "house_info.h"
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

Info::Info(int num)
{
  this->serial = generateRandomSerial(num);
  this->name = generateRandomName(num);
  this->address = generateRandomAddress(num);
}

Info::Info(string serial, string name, string address)
{
  this->serial = serial;
  this->name = name;
  this->address = address;
}

void Info::setSerial(string serial)
{
  this->serial = serial;
}

string Info::getSerial()
{
  return this->serial;
}

string Info::generateRandomSerial(int num)
{
  int coin, v;
  stringstream ss;
  string ret;
  int seed;

  seed = time(NULL) + 8 * num;
  srand(seed);
  ret = "";

  for (int i=0; i<11; i++)
  {
    coin = rand() % 2;
    if (!coin)
      v = rand() % 10 + '0';
    else
      v = rand() % 26 + 'A';
    ret += v;
  }
  ss << setw(5) << setfill('0') << num;
  ret += ss.str();

  return ret;
}

void Info::setName(string name)
{
  this->name = name;
}

string Info::getName()
{
  return this->name;
}

string Info::generateRandomName(int num)
{
  string ret;
  int count_first, count_last, first_index, last_index;
  int seed;
    
  seed = time(NULL) + 7 * num;
  srand(seed);
  count_first = sizeof(first)/sizeof(string);
  count_last = sizeof(last)/sizeof(string);

  first_index = rand() % count_first;
  last_index = rand() % count_last;

  ret = first[first_index] + " " + last[last_index];

  return ret;
}

void Info::setAddress(string address)
{
  this->address = address;
}

string Info::getAddress()
{
  return this->address;
}

string Info::generateRandomAddress(int num)
{
  string ret;
  int addr, count;
  int seed;

  seed = time(NULL) + 9 * num;
  srand(seed);

  addr = rand() % 50000 + 1;
  ret += to_string(addr) + " ";
  ret += "Songwol-gil, Jongro-gu, Seoul";

  return ret;
}
