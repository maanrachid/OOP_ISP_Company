#include "service.h"
#include "dialup.h"
#include "dsl.h"

void ServiceFactory::displayTypes(){
  cout<<"Enter "<<dialup<<" For dial up and "<<dsl<<" for DSL:";
}
Service* ServiceFactory::create(){
  int temp;
  Service* s1;
  do{
    ServiceFactory::displayTypes();
    temp=setInt();
  }while(temp!=0 && temp!=1);
  s1= create(temp);
  s1->set();
  return s1;
}
      
Service* ServiceFactory::create(int s1){
  DialupService dus1;
  DSLService dsl1;
  if (s1==1)
    return dsl1.newService();
  else
    return dus1.newService();
}

void Service::edit(){
  ServiceFactory::displayTypes();
  set();
}

void Service::display(bool shortform)const{
  cout<<"Service Type: ";
  if (serviceType) cout<<"DSL"; 
  else cout <<"Dialup";  
  cout<<'\t';
  cout<<"Daily Rate: ";
  moneyDisplay(dailyRate,true);
}

void Service::set(){
  cout<<"Daily Rate: ";
  dailyRate=setReal();
  while(dailyRate<Mindr || dailyRate>Maxdr){
    cout<<"Daily rate must be between$"
	<<Mindr<<" and $"<<Maxdr<<".Please try again.\n";
    cout<<"Daily Rate: ";
    dailyRate=setReal();
  }
  
}

void Service::read(ifstream& f){
  
  f>>dailyRate; 
}

ServiceT Service::getSType() const{
  return serviceType;
}

void Service::setdailyrate(){
  cout<<"Daily Rate: ";
  dailyRate=setReal();
  while(dailyRate<Mindr || dailyRate>Maxdr){
    cout<<"Daily rate must be between$"
	<<Mindr<<" and $"<<Maxdr<<".Please try again.\n";
    cout<<"Daily Rate: ";
    dailyRate=setReal();
  }
  
}

void Service::setservicetype(ServiceT ser){
  serviceType=ser;
}



double Service::getdailyrate()const{
  return dailyRate;
}


void Service::setdailyrate(double dr){
  dailyRate=dr;
}



























