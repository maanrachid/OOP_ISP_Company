// File: date.h
// A simple implementation of a date class.

#ifndef _DATE_H_
#define _DATE_H_
#include <fstream>
#include <string>   // stl string class
#include <cstdlib>  // for atoi
#include <time.h>
#include "utility.h"
const  char sep = '\n';

using namespace std;

class Date {
 public:
  friend ostream& operator<<(ostream& out, const Date& d) 
    { d.display();   return out; }
  friend istream& operator>>(istream& in, Date& d)
    { d.set();   return in; }
  Date();  // default constructor initializes host obj to  base date.
  Date(int m, int d, int y);  // constructs Date from month/day/year
  void write(ofstream&)const;
  void read(ifstream&);
  void set();  // interactively sets data for host obj from keyboard
  bool set(int m, int d, int y); // sets host object from args if valid.
  void display(bool shortform = true) const;  // displays the host object
  bool operator<(const Date& d) const;   // comparison: host < d
  bool operator==(const Date& d) const; // comparison: host == d
  bool operator<=(const Date& d) const; // comparison: host <= d
  int  operator-(const Date& d) const; // computes number of days (host - d)
  Date operator+(int days) const;        // computes the date (host + days)
  void operator+=(int days);               // changes host to (host + days)
  bool areinsameday(const Date& d1)const;
  
 private:
  long dsb;    // days since base date
  Date(long days);     // private constructor creates Date from dsb
  void set_dsb (int month, int day, int year); // computes dsb
  void get_mdy (int& m, int& d, int& y) const; //computes m/d/y from dsb
  static int base_year; 
  static bool leapyear(int year);
  static int yeardays(int year);
  static int monthdays(int month, int year);
  static string monthname(int month);
};

#endif


