#ifndef _customerList_h
#define _customerList_h

#include <map>
#include <string>
#include <iostream>
#include "utility.h"
#include "customer.h"

class TransactionList;


typedef map<string, Customer> Bag; 
typedef map<string, Customer>::const_iterator itr;
typedef map<string, Customer>::iterator CHAitr;
typedef Bag::value_type val;


class CustomerList{
 public:
  void set();
  void clear();
  bool insert(const Customer& cus);
  void display(string str="All",bool shortform=true);
  void remove(string csId);
  itr find(string csId)const;
  void read(ifstream& f);
  void write(ofstream& f)const;
  bool isEmpty()const;
  bool isInList(Customer& cus);
  bool isInList(const string& csId)const;
  Customer operator[](const string&)const;
  string findid(const string&)const;
  void setAcctBalance(const TransactionList&,string strid="ALL");
  void edit();
  void remove(TransactionList& tr);
  int size(){return b.size();}
  void printcuswithnotrans(const TransactionList&)const;
  void fixnogap(Date d,const string strid);
  
 private:
  Bag b;
  
};

#endif






