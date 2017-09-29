#include "dsl.h"

DSLService::DSLService(){
  setservicetype(dsl);
}

void DSLService::setinstallfee(){
  cout<<"Installation fee: ";
  installationFee=setReal();
  while(installationFee< Infeemin || installationFee>Infeemax){
    cout<<"installation fee must be between $"
        <<Infeemin<<" and $"<<Infeemax<<" .Please try again.\n";
    installationFee=setReal();
  }
}

void DSLService::setipcount(){
  cout<<"Number of fixed IP addresses: ";
  ipAddressCount=setInt();
  while(ipAddressCount<1 || ipAddressCount>20){
    cout<<"Number of fixed IP addresses must be between 1 and 20.\n";
    cout<<"please try again.\n";
    cout<<"Number of fixed IP addresses: ";
    ipAddressCount=setInt();
  }
}

void DSLService::edit(){
  Service::edit();
  cout<<"Installation Fee: "<<installationFee<<'\t'<<"Change (y/n)? ";
  if (yes()) setinstallfee();
  cout<<"Number of fixed IP addresses: "<<ipAddressCount<<'\t'
      <<":: Change (y/n)?";
  if (yes()) setipcount();
}

void DSLService::display(bool shortform)const{
  Service::display();
  cout<<"installation Fee: ";
  moneyDisplay(installationFee,true);
  cout<<"Number of fixed IP addresses: "<<ipAddressCount<<endl;
}

void DSLService::set(){
  Service::set();
  setinstallfee(); 
  setipcount();

}



void DSLService::read(ifstream& f){
  string str;
  Service::read(f);
  f>>installationFee;
  f>>ipAddressCount;
  getline(f,str);
	  
 

}

void DSLService::write(ofstream& f)const{
  f<<dsl<<seperater;
  f<<getdailyrate()<<seperater<<installationFee<<seperater<<ipAddressCount;
  f<<seperater;
}

double DSLService::calculateCharges(Date d1,Date d2){
  return ((d2-d1)*ipAddressCount*getdailyrate());

}













