#ifndef _transPayment_h
#define _transPayment_h
#include "transaction.h" 

class TransPayment : public Transaction {
 public:
  TransPayment();
  virtual ~TransPayment(){}
  void set(CustomerList&);
  void display(bool shortform=true)const;
  void read(ifstream&);
  void write(ofstream&)const;
  bool operator==(TransPayment& trl){
    return (Transaction::operator==(trl));}
  TransPayment* newTransaction() {return new TransPayment;}
  TransPayment* clone() {return new TransPayment(*this);}
  TransPayment& getobj(){return *this;}
  void edit(const CustomerList& cl);



 private:
  void setTransAmt(const CustomerList&);
};


#endif 

