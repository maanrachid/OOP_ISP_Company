#ifndef _transLateFee_h
#define _transLateFee_h
#include "transaction.h"

class TransLateFee : public Transaction {
 public:
  TransLateFee();
  virtual ~TransLateFee(){}
  void set(CustomerList&);
  void display(bool shortform=true)const;
  void write(ofstream&)const;
  void read(ifstream&);
  bool operator==(TransLateFee& trl){
    return (Transaction::operator==(trl) && due==trl.due
            );}
  Date getdue()const;
  double getlate()const;
  TransLateFee* newTransaction() {return new TransLateFee;}
  TransLateFee* clone() {return new TransLateFee(*this);}
  TransLateFee& getobj(){return *this;}
  void edit(const CustomerList& cl);


 private:
  Date due;
  static double late ;
  void setTransAmt(const CustomerList&);
  void setdue(const CustomerList& l1);
};


#endif









