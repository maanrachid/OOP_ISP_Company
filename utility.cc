// utility.cc
// a collection of general purpose functions
// Date of last modification:  10/8/2001


#include <math.h>
#include <limits.h>
#include "utility.h"

int setInt() {
  const int MAX = 50;
  int n;
  double d;
  char numstr[MAX];
  cin >> ws;
  while(1) {
    cin.getline(numstr, MAX-1);
    if (!cin) {
      cout << "\n*** Bad Input! Please try again. ***" << endl;
      cin.clear();
    }
    else {
      if(isdigit(numstr[0]) || 
         ((numstr[0]=='-') && (isdigit(numstr[1])))) {
        d = atof(numstr);
        if (d > INT_MAX) 
          cout << "*** Out of range! Please try again.***" << endl;
        else {
          n = atoi(numstr);
          break;
        }
      }
      else
        cout << "*** Please enter a numeric value! ***" << endl;
    }
  }
  return n;
}


double setReal() {
  while(1) {
    char ch;
    int k = 0;
    double d = 0;
    bool empty = true;
    bool neg = false;
    bool sawPoint = false;
    bool valid = true;
    bool bad = false;
    cin >> ws;
    while((ch = cin.get()) != '\n') {
      if (!cin) {
        cin.clear();
        cout << "\n*** Bad Input! Please try again. ***" << endl;
        valid = false;
        bad = true;
        break;
      }
      if ((ch >= '0') && (ch <= '9')) {
        if (sawPoint)  k++ ;
        d = 10 * d + (ch - '0'); 
      }
      else if ((ch == '.') && (!sawPoint))
        sawPoint = true ;
      else if ((empty) && (ch == '-'))
        neg = true;
      else {
        cout << "*** Please enter a numeric value! ***" << endl;
        valid = false;
        break;
      }
      empty = false;
    } // while(setting characters)
    if(valid) {
      d /=  pow(10,k) ;
      if(neg)
        d *= -1;
      return d;
    }
    if (!bad) 
      cin.ignore(999, '\n');
  } // while(1)
}

int stringToInt(string& s) {
  unsigned i, n;
  char *numstr = new char[1 + s.length()];
  for(i=0; i < s.length(); ++i) {
    if(isdigit(s[i]))
      numstr[i] = s[i];
    else 
      break;
  }
  numstr[i] = '\0';
  n = atoi(numstr);
  delete [] numstr;
  return n;
}

string intToString(int n) {
  stringstream ost;
  ost << n;
  return ost.str();
}

string intToString(int n, unsigned len) {
  stringstream ost;
  ost << n;
  string s = ost.str();
  while(s.length() < len)
    s = "0" + s;
  return s.erase(len);
}

void uppercaseString (string& s) {
  for(unsigned i = 0; i < s.length(); ++i)
    if (s[i]>='a' && s[i]<='z')
      s[i]=s[i]-32;
  //s.replace(i,1, toupper(s[i]));
}

void lowercaseString (string& s) {
  for(unsigned i = 0; i < s.length(); ++i)
    if (s[i]>='A' && s[i]<='Z')
      s[i]=s[i]+32;
  //s.replace(i,1, tolower(s[i]));
}

bool more(string s) {
  string ans;
  cout << "Another " << s << " (y/n)? ";
  getline(cin, ans);
  uppercaseString(ans);
  return ans  == "Y";
}

bool yes() {
  string ans;
  getline(cin, ans);
  uppercaseString(ans);
  return (ans[0] == 'Y');
}

void moneyDisplay(double d, bool newline /*= false */) {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  cout << "$" << d ;
  if(newline)
    cout << endl;
  else
    cout << flush;
}

string setPhoneString() {
  const unsigned FULLPHONELEN = 10;
  const int AREACODELEN = 3;
  const int DASHINDEX = 8;  // assuming format (aaa)bbb-cccc
  string ph;
  while(1) {
    cout << "Enter phone number as a " << FULLPHONELEN << "-digit string: ";
    getline(cin, ph);
    if(ph.length() != FULLPHONELEN) {
      cerr << "First " << AREACODELEN << " digits for area code, then "
           << FULLPHONELEN - AREACODELEN 
           << " digits for local phone number.\n";
      continue;
    }
    bool badphone = false;
    for(unsigned i=0; i < FULLPHONELEN; ++i)
      if(! isdigit(ph[i])) badphone = true;
    if(! badphone) break;
    cerr << "Invalid entry - numerical digits only, please!\n";
  }
  ph.insert(AREACODELEN,")");
  ph.insert(0,"(");
  ph.insert(DASHINDEX,"-");
  return ph;
}

string setAddrString() {
  const unsigned ZIPLENGTH = 5;
  const unsigned STATELENGTH = 2;
  string addrline, as("");
  cout << "Address is entered in the order:\n"
       << "\tFirst address line\n"
       << "\tSecond address line (if necessary)\n"
       << "\tCity\n"
       << "\tState (abbreviation)\n"
       << "\tZip code" << endl;
  cout << "First address line: " << flush;
  getline(cin, addrline);
  if(addrline.length()) 
    as += addrline;
  cout << "Second address line: " << flush;
  getline(cin, addrline);
  if(addrline.length()) 
    as += "; " + addrline;
  cout << "City: " << flush;
  getline(cin, addrline);
  if(addrline.length())
    as += "; " + addrline;
  while(1) {
    cout << "State (" << STATELENGTH << " char abbrev): " << flush;
    getline(cin, addrline);
    uppercaseString(addrline);
    if(addrline.length()==STATELENGTH) break;
  }
  as += "; " + addrline;
  int z;
  cout << "Zip code (" << ZIPLENGTH << ") digits): " << flush;
  z = setInt();
  addrline = intToString(z,ZIPLENGTH);
  as += "; " + addrline;
  return as;
}
