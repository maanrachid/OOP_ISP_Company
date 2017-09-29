#include "transPayment.h"

TransPayment::TransPayment(){
  setttype(payment);
}

void TransPayment::edit(const CustomerList& cl){
  Transaction::edit(cl);
  cout<<"Transaction payment: "<<gettamount()<<'\t'<<"change?(Y/N) "<<endl;
  if (yes()) setTransAmt(cl);
}

void TransPayment::set(CustomerList& l1){
  Transaction::set(l1);
  setTransAmt(l1);
}

void TransPayment::display(bool shortform)const{
  Transaction::display();
  cout<<"Payment amount: ";
  moneyDisplay(Transaction::gettamount());
  cout<<endl;

}

void TransPayment::read(ifstream& f){
  double d1;
  Transaction::read(f);
  f>>d1>>ws;
  setAmt(d1);
}

void TransPayment::write(ofstream& f)const{
  Transaction::write(f);
  f<<Transaction::gettamount()<<endl;

}


void TransPayment::setTransAmt(const CustomerList&){
  double d1;
  cout<<"Enter the payment amount: ";
  d1=setReal();
  cout<<"Transaction amount set to $"<<-d1<<endl;
  setAmt(-d1);
}





















