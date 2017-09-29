#ifndef _dialup_h
#define _dialup_h
#include "service.h"

class DialupService : public Service {
 public:
  DialupService();
  void display(bool shortform=true)const;
  void set();
  void read(ifstream&);
  void write(ofstream&)const;
  double calculateCharges(Date d1,Date d2);
  DialupService* newService() {return new DialupService;}
  DialupService* clone() {return new DialupService(*this);}
  void edit();

 private:
  int webSpaceLimit;
  void setwebspace();
};


#endif





