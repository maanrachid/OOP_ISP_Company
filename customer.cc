/* this library will give a define to new class of type customer 
   that will allow the client to set each member of this class 
   alone or together by the function set .and also allow the clent to 
   access the members by the get functions or by the get function 
   to get all the data together.you also may write the data to a
   file and read the data from a file by the wrie and read functions*/




#include "customer.h"
#define seperater '\n'     /* define a seperater
			      between data in the file*/
const unsigned MAX =5;

void Customer::set(){
  setCustomerId();
  setName();
  setAddress();
  setPhone();
  setAccountdate();
  nogap=accountdate;
  setservice();
}

void Customer::edit(){
  cout<<"Name: "<<name<<'\t'<<":: Change (y/n)? ";
  if (yes()) setName();
  cout<<"Address: "<<address<<'\t'<<":: Change (y/n)? ";
  if (yes()) setAddress();
  cout<<"Phone: "<<phone<<'\t'<<":: Change (y/n)? ";
  if (yes()) setPhone();
  cout<<"Account Date: "<<accountdate<<'\t'<<":: Change (y/n)? ";
  if (yes()) {setAccountdate(); nogap=accountdate;}
  cout<<"Change Service(y/n)? ";
  if (yes()) setservice();
    
}

double Customer::getaccountBalance(){
  return accountBalance;
}

double Customer::calculateCharges(Date d1,Date d2){
  return serv->calculateCharges(d1,d2);

}

Customer& Customer::operator=(const Customer& cus){
  if (this!=&cus){
    id = cus.id;
    name=cus.name;
    address=cus.address;
    phone=cus.phone;
    accountdate=cus.accountdate;
    accountBalance=cus.accountBalance;
    nogap=cus.nogap;
    //delete serv;
    if (cus.serv!=NULL){
      serv=(cus.serv)->clone();
    }else 
      serv=NULL;
  }
  return *this;
  

}

void Customer::setservice(){
  delete serv;
  serv = ServiceFactory::create();
}


 


Customer::Customer(const Customer& cus){
  /* this is not a shallow copy the assignment op will 
     take care of business */

  *this=cus;

}


void Customer::display(bool shortform) const{
  cout<<"Id ,Name: "<<id<<", "<<name<<endl;
  cout<<"Account Date:  ";
  accountdate.display(shortform);
  if (shortform==false){
    cout<<"\n";
    cout<<"Account Balance: ";
    moneyDisplay(accountBalance);
    cout<<seperater;
    cout<<"Address:  "<<address<<endl;
    cout<<"Phone: "<<phone<<endl;
    serv->display();
  }
  if (shortform) cout<<"\n";

}

void Customer::write(ofstream& f)const{
  f<<id<<seperater<<name; 
  f<<seperater;
  f<<address<<seperater;
  f<<phone<<seperater;
  accountdate.write(f);
  serv->write(f);

}



void Customer::read(ifstream& f){
  int m;
  getline(f,id);
  getline(f,name);
  getline(f,address);
  getline(f,phone);
  accountdate.read(f);
  nogap=accountdate;
  f>>m;
  delete serv;
  serv=ServiceFactory::create(m);
  serv->read(f);
}



void Customer::setCustomerId(){
  
  string temp;
  cout<<"Customer Id: ";
  getline(cin,temp);
  while((temp.length()!=MAX)){
    cout<<"Customer Id must be exactly 5 letter : ";
    getline(cin,temp);
  }
  id=temp;
}
string Customer::getCustomerId() const{
  return id;
}

void Customer::setPhone(){
  cout<<"Customer phone: ";
  phone=setPhoneString();
}


string Customer::getPhone() const{
  return phone;
}



void Customer::setName(){
  string temp;
  cout<<"Customer Name: ";
  getline(cin,temp);
  while(temp.length()<1 || temp.length()>(8*MAX)){
    cout<<"Customer name must not be empty or more than 40 letters: ";
    getline(cin,temp);
  }
  name=temp;



}
 
string Customer::getName() const{
  return name;
}

void Customer::setAddress(){
  cout<<"Customer Address: ";
  address=setAddrString();
  
}

string Customer::getAddress() const{
  return address;
}
void Customer::setAccountdate(){
  cout<<"Account Date: ";
  accountdate.set();
}

Date Customer::getAccountdate() const{
  return accountdate;
}
























