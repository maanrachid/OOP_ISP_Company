#include "transMonthlyUse.h"


TransMonthlyUse::TransMonthlyUse(){
  setttype(monthusecharge);
}

void TransMonthlyUse::edit(const CustomerList& cl){
  Transaction::edit(cl);
  cout<<"Usage fee for the period "<<start<<" - "<<end<<": ";
  setTransAmt(cl);
  moneyDisplay(Transaction::gettamount());
  cout<<"\n";
}

void TransMonthlyUse::set(CustomerList& l1){
  Transaction::set(l1);
  setstart(l1);
  setend(l1);
  cout<<"Usage fee for the period "<<start<<" - "<<end<<": ";
  setTransAmt(l1);
  moneyDisplay(Transaction::gettamount());
  cout<<endl;
 
}

void TransMonthlyUse::display(bool shortform)const{
  Transaction::display();
  cout<<"Monthly Use Charge\t";
  moneyDisplay(Transaction::gettamount());
  cout<<endl;
  cout<<"Usage fee for period ";
  start.display();
  cout<<" - " ;
  end.display();
  cout<<": ";
  moneyDisplay(Transaction::gettamount());
  cout <<endl;
  
}

void TransMonthlyUse::write(ofstream& f)const{

  Transaction::write(f);
  f<<Transaction::gettamount()<<endl;
  start.write(f);
  end.write(f);
  
}

void TransMonthlyUse::read(ifstream& f){
  double d1;
  Transaction::read(f);
  f>>d1;
  Transaction::setAmt(d1);
  start.read(f);
  end.read(f);
}

Date TransMonthlyUse::getstart()const{
  return start;
}

Date TransMonthlyUse::getend()const{
  return end;
}

void TransMonthlyUse::setTransAmt(const CustomerList& l1){
  setAmt(l1[Transaction::gettcustomerid()].calculateCharges(start,end));
}

void TransMonthlyUse::setstart(CustomerList& l1){
  start=l1[Transaction::gettcustomerid()].nogap;
}
	 

void TransMonthlyUse::setend(CustomerList& cl){
 
  end=start+28;
  while(!(start.areinsameday(end)))
      end+=1;
  cl.fixnogap(end+1,gettcustomerid());
  
}





