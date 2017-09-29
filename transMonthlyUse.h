#ifndef _transMonthlyUse_h
#define _transMonthlyUse_h
#include "transaction.h"

class TransMonthlyUse : public Transaction {
 public:
  TransMonthlyUse();
  virtual ~TransMonthlyUse(){}
  void set(CustomerList&);
  void display(bool shortform=true)const;
  void write(ofstream&)const;
  void read(ifstream&);
  Date getstart()const;
  Date getend()const;
  bool operator==(TransMonthlyUse& trl){
    return (Transaction::operator==(trl) && start==trl.start
	    && end==trl.end);}
  TransMonthlyUse* newTransaction() {return new TransMonthlyUse;}
  TransMonthlyUse* clone() {return new TransMonthlyUse(*this);}
  TransMonthlyUse& getobj(){return *this;}
  void edit(const CustomerList& cl);
  void setstart(CustomerList& l1);
  void setend(CustomerList& l1);

 private:
  Date start;
  Date end;
  void setTransAmt(const CustomerList&);
};




#endif


