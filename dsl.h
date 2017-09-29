#ifndef _dsl_h
#define _dsl_h
#include "service.h"

class DSLService : public Service{
 public:
  DSLService();
  void display(bool shortform=true)const;
  void set();
  void read(ifstream&);
  void write(ofstream&)const;
  double calculateCharges(Date d1,Date d2);
  DSLService* newService() {return new DSLService;}
  DSLService* clone() {return new DSLService(*this);}
  void edit();

 private:
  double installationFee;
  int ipAddressCount;
  void setipcount();
  void setinstallfee();
};

#endif




