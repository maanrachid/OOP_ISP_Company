#include "transExtraFee.h"

TransExtraFee::TransExtraFee(){
  setttype(extrafee);

}

void TransExtraFee::edit(const CustomerList& cl){
  Transaction::edit(cl);
  cout<<"Service Date: "<<servicedate<<'\t'<<"::Change(y/n)? ";
  if (yes()) setservicedate(cl);
  cout<<"Service Description: "<<description<<'\t'<<"::Change(y/n)? ";
  if (yes()) setdescription();
  cout<<"Transaction Amount :"<<gettamount()<<'\t'<<"::changed?(Y/N) ";
  if (yes()) setTransAmt(cl);
}

void TransExtraFee::set(CustomerList& l1){
  Transaction::set(l1);
  setTransAmt(l1);
  setservicedate(l1);
  setdescription();
}

void TransExtraFee::read(ifstream& f){
  double d1;
  Transaction::read(f);
  f>>d1;
  Transaction::setAmt(d1);
  servicedate.read(f);
  f>>ws;
  getline(f,description);

}
void TransExtraFee::write(ofstream& f)const{
  Transaction::write(f);
  f<<Transaction::gettamount()<<endl;
  servicedate.write(f);
  f<<description<<endl;


}
void TransExtraFee::display(bool shortform)const{
  Transaction::display();
  cout<<"Extra Service Fee\t";
  moneyDisplay(Transaction::gettamount());
  cout<<endl;
  cout<<"Service Date: ";
  servicedate.display();
  cout<<endl;
  cout<<"Service Description: "<<description<<endl;
  
}
string TransExtraFee::getdescription()const{
  return description;

}
Date TransExtraFee::getservicedate()const{
  return servicedate;

}
void TransExtraFee::setservicedate(const CustomerList& l1){
  Date d;
  cout<<"Enter the date of this extra service: ";
  servicedate.set();
  d=l1[gettcustomerid()].getAccountdate();
  while (servicedate<d){
    cout<<"The Service date cannot be earlier than "<<d<<endl;
    servicedate.set();
  }
}

void TransExtraFee::setdescription(){
  cout <<"Enter a brief description of the service:";
  getline(cin,description);

}

void TransExtraFee::setTransAmt(const CustomerList& l1){
  double d1;
  cout <<"Enter the charge for this extra service: ";
  d1=setReal();
  while((d1<MINEXTRA)||(d1>MAXEXTRA)){
    cout<<"Charge must be between $"<<MINEXTRA
	<<"and $"<<MAXEXTRA<<".please try again.\n";
    d1=setReal();
  }
  setAmt(d1);

}






