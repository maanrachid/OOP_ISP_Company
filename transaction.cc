#include "transaction.h"
#include "transMonthlyUse.h"
#include "transExtraFee.h"
#include "transLateFee.h"
#include "transPayment.h"


Transaction* TransactionFactory::create(Transaction* trp){
  if (trp==NULL) return NULL; 
  else return trp->clone();
}


Transaction* TransactionFactory::create(CustomerList& cl){
  int temp;
  Transaction* tr;
  cout<<"Please enter the type of transaction:\n";
  TransactionFactory::displayTTypes();
  cout<<"Enter Transaction Type : ";
  temp=setInt();
  while((temp<monthusecharge)||(temp>payment)){
    cout<<"Please enter a correct choice\n";
    TransactionFactory::displayTTypes();
    cout<<"Enter Transaction Type : ";
    temp=setInt();
  }
  
  tr= create(temp);
  tr->set(cl);
  return tr;
}

Transaction* TransactionFactory::create(int tt){
  if (tt==monthusecharge)
      return new TransMonthlyUse(); 
  else if (tt==extrafee)
    return new TransExtraFee(); 
  else if (tt==latecharge)
    return new TransLateFee(); 
  else
    return new TransPayment(); 
  

}

void Transaction::edit(const CustomerList& cl){
  cout<<"Transaction Date: "<<tdate<<'\t'<<"::Change(y/n)?";
  if (yes()) settdate(cl);
  cout<<"Customer Id: "<<tcustomerid<<'\t'<<"::Change(y/n)?";
  if (yes()) settcustomerid(cl);
}



void TransactionFactory::displayTTypes(){
  cout<<'0'<<tab<<"Monthly Use Charge\n";
  cout<<'1'<<tab<<"Extra Service Fee\n";
  cout<<'2'<<tab<<"Late Fee\n";
  cout<<'3'<<tab<<"Payment\n";

}


Transaction::Transaction(Ttype t1){
  setttype(t1);
}

void Transaction::setttype(Ttype t1){
  type=t1;
}

string Transaction::gettcustomerid()const{
  return tcustomerid;
}

Date  Transaction::gettdate()const{
  return tdate;
}

Ttype Transaction::getTType()const{
  return type;
}
 
double Transaction::gettamount()const{
  return tamount;
}
  

void Transaction::set(CustomerList& l1){
  settcustomerid(l1);
  settdate(l1);
}

void  Transaction::display(bool shortform) const{
  cout<<tcustomerid<<tab<<tdate<<tab;
}

void  Transaction:: read(ifstream& f){
  f>>tcustomerid>>ws;
  tdate.read(f);  
}
 
void  Transaction:: write(ofstream& f)const{
  f<<type<<endl;
  f<<tcustomerid<<endl;
  tdate.write(f);
}



void  Transaction::setAmt(double d1){
  tamount = d1;
}



void Transaction::settdate(const CustomerList& l1){
  Date d;
  cout<<"Enter the transaction date. \n";
  tdate.set();
  d=l1[tcustomerid].getAccountdate();
  while(tdate<d){
    cout<<"The Transaction date cannot be earlier than "<<d<<endl;
    tdate.set();
  }
}

void Transaction::settcustomerid(const CustomerList& l1){
  string str,strid;
  cout<<"Enter the first few characters of the customer's name: ";
  getline(cin,str);
  strid=l1.findid(str);
  while(strid=="not found"){
    cout<<strid<<endl;
    cout<<"Enter the first few characters of the customer's name: ";
    getline(cin,str);
    strid=l1.findid(str);
  }
  tcustomerid=strid;

}
    
















