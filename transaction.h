#ifndef _transaction_h
#define _transaction_h
#include "customerList.h"

const int  TTCOUNT = 4;
#define tab '\t'
const int MAXEXTRA =100;
const int MINEXTRA=25;

enum Ttype {monthusecharge,extrafee,latecharge,payment};

class Transaction{
 public:
  Transaction(){}
  Transaction(Ttype);
  virtual ~Transaction(){};
  string gettcustomerid()const;
  Date gettdate()const;
  double gettamount()const;
  Ttype getTType()const;
  virtual Transaction& getobj()=0;
  bool operator==(const Transaction& tr)
  {return ((tcustomerid==tr.tcustomerid)&&(tdate==tr.tdate)&&
	   (tamount=tr.tamount));}
  virtual void set(CustomerList&);
  virtual void display(bool shortform=true) const;
  virtual void read(ifstream&);
  virtual void write(ofstream&)const;
  virtual Transaction* newTransaction()=0;
  virtual Transaction* clone() = 0;
  virtual void edit(const CustomerList& cl);
 

 protected:
  virtual void setTransAmt(const CustomerList&)=0;
  void setAmt(double);
  void setttype(Ttype);

 private:
  string tcustomerid;
  Date tdate;
  Ttype type;
  double tamount;
  void settdate(const CustomerList&);
  void settcustomerid(const CustomerList&);

};

class TransactionFactory {
 public:
  static Transaction* create(CustomerList&);      
  static Transaction* create(int tt);
  static Transaction* create(Transaction* trp);
  // silently constructs an object that is
  // a copy of the object at the given address.
  static string ttname[TTCOUNT] ;
  static void displayTTypes();
};




#endif















