#include "dialup.h"



DialupService::DialupService(){
  setservicetype(dialup);
}

void DialupService::edit(){
  Service::edit();
  cout<<"Web space Limit: "<<webSpaceLimit<<" MB"<<'\t'
      << ":: Change (y/n)? ";
  if (yes()) setwebspace();
}

void DialupService::display(bool shortform)const{
  Service::display();
  cout<<"Web space Limit: "<<webSpaceLimit<<" MB\n";
}

void DialupService::setwebspace(){
  cout<<"Web space Limit (in MB): ";
  webSpaceLimit=setInt();
  while(webSpaceLimit<Wsmin || webSpaceLimit>Wsmax){
    cout<<"Web space limit must be between 3 and 30.  Please try again.\n";
    cout<<"Web space Limit (in MB): ";
    webSpaceLimit=setInt();
  }
}

void DialupService::set(){
  Service::set();
  setwebspace();

}

void DialupService::read(ifstream& f){
  string str;
  Service::read(f);
  f>>webSpaceLimit;
  getline(f,str);
}

void DialupService::write(ofstream& f)const{
  f<<dialup<<seperater;
  f<<getdailyrate()<<seperater<<webSpaceLimit<<seperater;
}

double DialupService::calculateCharges(Date d1,Date d2){
  return ((d2-d1)*getdailyrate());
}










