#ifndef _transactionList_h
#define _transactionList_h
#include <map>
#include <string>
#include "transaction.h"

typedef multimap<string,Transaction*> MMap;
typedef multimap<string,Transaction*>::iterator MIt;
typedef multimap<string,Transaction*>::const_iterator CONMIt;


class TransactionList{
 public:
  TransactionList(){}
  TransactionList(const TransactionList&);
  ~TransactionList(){clear();}
  TransactionList& operator=(const TransactionList&);
  void clear();
  void set(CustomerList&);
  void display(CustomerList&,string strid="All",bool shortform =true
	       )const;
  void remove(string strid);
  double accountTotal(string strid)const;
  void write(ofstream&)const;
  void read(ifstream&,CustomerList& cl);
  bool isEmpty()const;
  int transCount(string strid)const;
  void insert(Transaction* ptr);
  bool isInList(const string)const;
  bool isInList(Transaction* ptr)const;
  void edit(CustomerList& cl);
  void remove(CustomerList& cl);

 private:
  MMap mm;
  



};



#endif





