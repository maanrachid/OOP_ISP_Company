#include "transLateFee.h"

double TransLateFee::late=25;

TransLateFee::TransLateFee(){
  setttype(latecharge);
}

void TransLateFee::edit(const CustomerList& cl){
  Transaction::edit(cl);
  cout<<"Due Date: "<<due<<'\t'<<"::Change(y/n)? ";
  if (yes()) setdue(cl);
  setAmt(late);
}

void TransLateFee::set(CustomerList& l1){
  Transaction::set(l1);
  setdue(l1);
  cout<<"Transaction amount set to ";
  moneyDisplay(late);
  setAmt(late);
  cout<<endl;
}
void TransLateFee::setdue(const CustomerList& l1){
  Date d;
  cout<<"Enter the due date :";
  due.set();
  d=l1[gettcustomerid()].getAccountdate();
  while(due<d){
    cout<<"Due date cannot be earlier than "<<d<<endl;
    due.set();
  }
}

void TransLateFee::display(bool shortform)const{
  Transaction::display();
  cout<<"Late Fee\t";
  moneyDisplay(late);
  cout<<endl;
  cout<<"Due Date: ";
  due.display();
  cout<<tab<<"Late Fee:  ";
  moneyDisplay(late);
  cout<<endl ;

}

void TransLateFee::write(ofstream& f)const{
  Transaction::write(f);
  f<<late<<endl;
  due.write(f);
  
}

void TransLateFee::read(ifstream& f){
  Transaction::read(f);
  f>>late;
  setAmt(late);
  due.read(f);
}

Date TransLateFee::getdue()const{
  return due;

}
double TransLateFee::getlate()const{
  return late;
}

void TransLateFee::setTransAmt(const CustomerList&){
  

}






