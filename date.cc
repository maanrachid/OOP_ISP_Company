/* Maan Haj Rachid
   9/23/01
   Date library */

/* This library allow to use dates in appropriate way . it store the date as 
   a single integer that represent the number of days since dec 31 999 . */ 

#include <fstream>

#include "utility.h"
#include "date.h"
using namespace std;


int Date::base_year= 1000;


bool Date::areinsameday(const Date& d1)const{
  int m1,day1,y1,m2,day2,y2;
  d1.get_mdy(m1,day1,y1);
  get_mdy(m2,day2,y2);
  return(day1==day2);
}


Date::Date(){      
  dsb=1;
}

Date::Date(int m, int d, int y){ 
  set_dsb(m,d,y);
}

void Date::write(ofstream& f)const{
  
  f<<dsb<<sep;
}


void Date::read(ifstream& i){
  i>>dsb;


}




void Date::set(){     //get the y/m/d from the user
  int year,month,day,checkday;
  
  
  do {
    cout<<"Year: ";
    year=setInt();
    if (year<1000)
      cout<<"Year must not be earlier than 1000. Please try again."<<endl;
  }while (year<1000); 
  
  do {
    cout<<"Month (a number from 1 to 12): ";
    month=setInt();
    if (month>12 || month<1)
      cout<<"Invalid month! Please try again."<<endl;
  }while (month>12 || month<1);
  
  do {
    cout<<"Day of the month: ";
    day=setInt();
    checkday=monthdays(month,year);
    if (day>checkday || day<1)
      cout<<"Invalid day! Please try again."<<endl;
  }while (day>checkday || day<1);  
  


  set(month,day,year);
  

}


bool Date::set(int m, int d, int y){ //set the date by the programmer 
  
  if (m>0 && m<13 && y>base_year-1 &&d>0){
    if (d<=monthdays(m,y)){
      set_dsb(m,d,y);
      return true;
    }
  }
 
    return false;

} 


// display the date in the form determined by shortform
void Date::display (bool shortform) const{ 
  int month;
  int day;
  int year;
  string y;
  
  char sl='/';
  get_mdy(month,day,year);
  if (shortform==true)
    cout<<month<<sl<<day<<sl<<year;
  else
    cout<<monthname(month)<<' '<<day<<','<<' '<< year;

}

bool Date::operator<(const Date& d) const{
  return (dsb<d.dsb);
}

bool Date::operator==(const Date& d) const{
  return (dsb==d.dsb);
}

bool Date::operator<=(const Date& d) const{
  return(dsb<=d.dsb);
}

int Date::operator-(const Date& d)const {
  return (dsb-d.dsb);  //negative results are allowed
    
}


Date Date::operator+(int days) const{
  Date temp(dsb+days);
  return temp;
}

void Date::operator+=(int days){
  dsb+=days;
  if (dsb<1)
    dsb=1;     // when dsb is negative goto base
}

Date::Date(long days){ 
  if (days>0)
    dsb=days;  
  else
    dsb=1;    // when dsb is negative goto base
}
 

bool Date::leapyear(int year){ 
  
  return (((year%4==0) && (year%100!=0)) 
	  || (year%400==0));
}

int Date::yeardays(int year){
  if (leapyear(year))
    return 366;
  else
    return 365;
}

int Date::monthdays(int month, int year){
  if (month==2){
    if (leapyear(year))
      return 29;
    else
      return 28;
  }else if (month==1 || month==3 || month
	    ==5 || month==7 || month==8
	    || month==10 || month==12)
    return 31;
  else 
    return 30;
  
}


string Date::monthname(int month){

  switch (month) {
  case 1:
    return "January";
  case 2:
    return "February";
  case 3:
    return "March";
  case 4:
    return "April";
  case 5:
    return "May";
  case 6:
    return "June";
  case 7:
    return "July";
  case 8:
    return "August";
  case 9:
    return "September";
  case 10:
    return "October";
  case 11:
    return "November";
  case 12:
    return "December";  // no other case can be given     
  }

  return "";
}  

// this function will convert the date to an integer 
void Date::set_dsb (int month, int day, int year){
  int n;
  dsb=0;
  for(n=base_year;n<year;n++){
    dsb+=yeardays(n);
  }

  for(n=1;n<month;n++){
    dsb+=monthdays(n,year);
  }
  dsb+=day;
}


// this function will take care of finding year,day,and month
//of a given integer
void Date::get_mdy (int& m, int& d, int& y) const{
  int n=1;
  m=1;
  d=1;
  y=base_year;

 
  while(n<dsb){
    n+=yeardays(y);   //get the years 
    y++;
  }
  
  if (n==dsb) return;
  else {
    y--;   //if n>dsb that mean the previous year is the one
    m=12;
    while(n>dsb){
      n-=monthdays(m,y);   // get the month
      m--;
    }
  }
  
  m++;     

  if (n<dsb){
    d=dsb-n+1;   //get the day
  }

}













