#ifndef _option_h
#define _option_h
#define tab '\t'
#include "transactionList.h"
#include "customerList.h"
const int OPTCOUNT = 14;

void openOutputFile(ofstream& outfile);
void openInputFile(ifstream& infile); 

class Option {
 public:
  virtual ~Option() {}
  virtual void execute() = 0;
  string getOptName() {return optName;}
 protected:
  Option(string name): optName(name) {}
  string optName;
  static bool clchange,tlchange;
};

class OptFactory {
 public:
  static Option* create(CustomerList& cl, TransactionList& tl, int opt);
  static string optName[OPTCOUNT]; // array of Option names
  static void displayOptTypes();
  static void menu(CustomerList& cl, TransactionList& tl); 
};

class OptEditCust : public Option {
 public:
  OptEditCust(CustomerList& cl):
    Option("Edit Customer"), clptr(&cl){clchange=true;}
  void execute();
 private:
  CustomerList* clptr;
};

class OptRemoveCust : public Option {
 public:
  OptRemoveCust(CustomerList& cl,TransactionList& tl):
    Option("Remove Customer"), clptr(&cl),tlptr(&tl){clchange=true;}
  void execute();
 private:
  CustomerList* clptr;
  TransactionList* tlptr;
};



class OptAddCust : public Option {
 public:
  OptAddCust(CustomerList& cl) : 
    Option("Add Customers"), clptr(&cl){clchange=true;}
  void execute();
 private:
  CustomerList* clptr;
};

class OptDisplayCust : public Option { // displays one or all Customers
 public:
  OptDisplayCust(CustomerList& cl) :
    Option("Display Customers"),clptr(&cl){}
  void execute();
 private:
  CustomerList* clptr;
};

class OptFindCust : public Option {     // finds the customer id for a customer
 public:
  OptFindCust(CustomerList& cl) :
    Option("Find Customer"),clptr(&cl){}
  void execute();
 private:
  CustomerList* clptr;
};

class OptReadCust : public Option {   // reads the CustomerList from a file
 public:
  OptReadCust(CustomerList& cl) :
    Option("Read Customer List"),clptr(&cl){}
  void execute();
 private:
  CustomerList* clptr;
};

class OptWriteCust : public Option {    // writes the CustomerList to a file
   public:
  OptWriteCust(CustomerList& cl) :
    Option("Write Customer List"),clptr(&cl){clchange=false;}
  void execute();
 private:
  CustomerList* clptr;
};

class OptAddTrans : public Option {     // add Transactions to the TransList
 public:
  OptAddTrans(CustomerList& cl,TransactionList& tl) :
    Option("Add transactions"),clptr(&cl),tlptr(&tl){tlchange=true;}
  void execute();
 private:
  CustomerList* clptr;
  TransactionList* tlptr;
};        

class OptEditTrans : public Option {     // edit transactions
 public:
  OptEditTrans(CustomerList& cl,TransactionList& tl) :
    Option("Edit transactions"),clptr(&cl),tlptr(&tl){tlchange=true;}
  void execute();
 private:
  CustomerList* clptr;
  TransactionList* tlptr;
};

class OptRemoveTrans : public Option {
  // Remove Transactions from the TransList
 public:
  OptRemoveTrans(CustomerList& cl,TransactionList& tl) :
    Option("Remove Transactions"),clptr(&cl),tlptr(&tl){tlchange=true;}
  void execute();
 private:
  CustomerList* clptr;
  TransactionList* tlptr;
};

class OptDisplayTrans : public Option {  // add Transactions to the TransList
 public:
  OptDisplayTrans(CustomerList& cl,TransactionList& tl) :
    Option("Display transactions"),clptr(&cl),tlptr(&tl){}
  void execute();
 private:
  CustomerList* clptr;
  TransactionList* tlptr;
};



class OptQuit : public Option {
 public:
  OptQuit():
    Option("Quit"){}
  void execute();
 private:
};

class OptReadTrans : public Option { // reads the TransList from a file
 public:
  OptReadTrans(TransactionList& tl,CustomerList& cl) :
    Option("Read Transaction List"),tlptr(&tl),clptr(&cl){}
  void execute();
 private:
  TransactionList* tlptr;
  CustomerList* clptr;
};

class OptWriteTrans : public Option {  // writes the TransList to a file
 public:
  OptWriteTrans(TransactionList& tl) :
    Option("Write Transaction List"),tlptr(&tl){tlchange=false;}
  void execute();
 private:
  TransactionList* tlptr;
};


#endif 
