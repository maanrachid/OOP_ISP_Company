/* Maan Haj Rachid
   11:00pm 10/10/01
*/

#ifndef _service_h
#define _service_h
#include <sstream>
#include "date.h"
#include "utility.h"

enum ServiceT {dialup,dsl};
const double Mindr = 0.25;  //min daily rate
const double Maxdr= 3.00;  //max daily rate
#define seperater '\n'
const double Wsmin = 3;    //web space min
const double Wsmax = 30;   //web space max
const double Infeemin= 0;   //min installation fee
const double Infeemax =200;  //max installation fee



class Service {
 public:
  ServiceT getSType() const;
  double getdailyrate()const;
  virtual void display(bool shortform=true)const;
  virtual void set();
  virtual void read(ifstream&);
  virtual void write(ofstream&)const{}
  virtual double calculateCharges(Date d1, Date d2)=0;
  virtual Service* newService()=0;
  virtual Service* clone()=0;
  virtual void edit();

 protected:
  void setservicetype(ServiceT);
  void setdailyrate(double dr);
  void setdailyrate();

 private:
  ServiceT serviceType;
  double dailyRate;
 
};


class ServiceFactory {
 public:
  static Service* create();         // interactively determine which kind
  // of object is needed and then constructs 
  // one in dynamic memory.
  static void displayTypes();
  static Service* create(int st);  // silently constructs an object based on
  // its serviceType.
};




#endif


