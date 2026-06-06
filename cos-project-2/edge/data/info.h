#ifndef __INFO_H__
#define __INFO_H__
#include <string>
using namespace std;

class Info {
  private: 
    string serial;
    string name;
    string address;
    string generateRandomSerial(int num);
    string generateRandomName(int num);
    string generateRandomAddress(int num);

  public:
    Info(int num);
    Info(string serial, string name, string address);

    void setSerial(string serial);
    string getSerial();

    void setName(string name);
    string getName();

    void setAddress(string address);
    string getAddress();
};

#endif /* __INFO_H__ */
