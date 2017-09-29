#ifndef _transExtraFee_h
#define _transExtraFee_h

#include "transaction.h"

class TransExtraFee : public Transaction {
 public: 
  TransExtraFee();
  virtual ~TransExtraFee(){}
  void set(CustomerList&);
  void read(ifstream&);
  void write(ofstream&)const;
  void display(bool shortform=true)const;
  bool operator==(TransExtraFee& trl){
    return (Transaction::operator==(trl) && servicedate==trl.servicedate
            && description==trl.description);}
  string getdescription()const;
  Date getservicedate()const;
  TransExtraFee* newTransaction() {return new TransExtraFee;}
  TransExtraFee* clone() {return new TransExtraFee(*this);}
  TransExtraFee& getobj(){return *this;}
  void edit(const CustomerList& cl);
  
 private:
  Date servicedate;
  string description;
  void setservicedate(const CustomerList& l1);
  void setdescription();
  void setTransAmt(const CustomerList&);
  
};



#endif



