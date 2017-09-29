#ifndef _customer_h
#define _customer_h
#include "string"
#include "date.h"
#include <sstream>
#include "service.h"
#include "dsl.h"
#include "dialup.h"

class Customer {
 public:
  Customer(){serv = NULL ;accountBalance=0;}    
  ~Customer(){delete serv;serv=NULL;}
  Customer(const Customer& cus);
  Customer& operator=(const Customer& cus);
  void set();
  void display(bool shortform=true) const;
  void setCustomerId();
  string getCustomerId() const;
  void setPhone();
  string getPhone()const;
  void setName();
  string getName() const;
  void setAddress();
  string getAddress() const;
  void setAccountdate();
  Date getAccountdate() const;
  void setservice();
  void write(ofstream&)const;
  void read(ifstream&);
  double calculateCharges(Date,Date);
  double getaccountBalance();
  friend class CustomerList;
  void edit();
  Date nogap;
  
 private:
  string Id,phone,id,name,address;
  Date accountdate;
  Service* serv;
  double accountBalance;
};

#endif















