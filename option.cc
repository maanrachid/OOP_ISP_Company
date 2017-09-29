#include "option.h"

bool Option::clchange=false;
bool Option::tlchange=false;

string OptFactory::optName[]={"Read Customer List","Add Customers",
			      "Display Customers","Find Customer",
			      "Edit Customer","Remove Customer",
			      "Write Customer List","Read Transaction List",
			      "Add Transactions","Display Transactions",
			      "Edit Transaction","Remove Transaction",
			      "Write Transaction List","Quit"};



Option* OptFactory::create(CustomerList& cl, TransactionList& tl, int opt){
  Option* op;
  switch (opt){
  case 0:
    op=new OptReadCust(cl);
    break;
  case 1:
    op=new OptAddCust(cl);
    break;
  case 2:
    op=new OptDisplayCust(cl);
    break;
  case 3:
    op=new OptFindCust(cl);
    break;
  case 4:
    op=new OptEditCust(cl);
    break;
  case 5:
    op=new OptRemoveCust(cl,tl);
    break;
  case 6:
    op=new OptWriteCust(cl);
    break;
  case 7:
    op=new OptReadTrans(tl,cl);
    break;
  case 8:
    op=new OptAddTrans(cl,tl);
    break;
  case 9:
    op=new OptDisplayTrans(cl,tl);
    break;
  case 10:
    op=new OptEditTrans(cl,tl);
    break;
  case 11:
    op=new OptRemoveTrans(cl,tl);
    break;
  case 12:
    op=new OptWriteTrans(tl);
    break;
  case 13:
    op=new OptQuit();
    break;
  }
  return op; 

}


void OptFactory::displayOptTypes(){
  for(int h=0;h<OPTCOUNT;h++){
    cout<<tab<<tab<<'('<<h<<')'<<tab<<optName[h]<<endl;
  }
}

void OptFactory::menu(CustomerList& cl, TransactionList& tl){
  int choice;
  Option* op=NULL;
  do{
    displayOptTypes();
    cout<<tab<<tab<<tab<<"Your choice: ";
    choice=setInt();
    if (choice==OPTCOUNT) break;
    if ((choice<0)||(choice>OPTCOUNT)) continue;
    if (op!=NULL){delete op;} 
    op=create(cl,tl,choice);
    op->execute();
  }while(true);
}


void OptAddCust::execute() {
  cout << getOptName() << endl;
  clptr->set();
}

void OptDisplayCust::execute(){
  bool shortform;
  string id;
  if (clptr->isEmpty())
    cout<<tab<<"###### Customer List is empty.\n";
  else{
    cout << getOptName() << endl;
    cout<< "Use short display format (Y/N)? ";
    shortform=yes();
    cout<<"Enter Customer ID (or \"All\") ";
    getline(cin,id);
    if ((clptr->isInList(id))||(id=="All"))
      clptr->display(id,shortform);
    else
      cout<<tab<<"****** "<<id<<" not found."<<endl;
  }
}

void OptFindCust::execute(){
  string str,id;
  if (clptr->isEmpty())
    cout<<tab<<"###### Customer List is empty .\n";
  else {
    cout << getOptName() << endl;
    cout<<"Enter the first few characters of the customer's name:";
    getline(cin,str);
    id=clptr->findid(str);
    if (id=="not found") cout<<str<<" "<<id<<endl;
    uppercaseString(id);
    cout<<"Requested Customer ID is:"<<id<<endl;
  }
}

void OptReadCust::execute(){
  ifstream f;
  cout<<getOptName()<<endl;
  openInputFile(f);
  if (!clptr->isEmpty()){
    cout<<"*** There are already "<<clptr->size()<<" Customers in the list.\n";
    cout<<"Do you want to keep the old data in the Customer list? ";
    if (!yes())
      clptr->clear();
  }  
  clptr->read(f);
  f.close();
}

void OptEditCust::execute(){
  if (clptr->isEmpty())
    cout<<tab<<"###### Customer List is empty - No transactions are possible.\n";
  else {
  cout<<getOptName()<<endl;
  clptr->edit();
  }
}

void OptRemoveCust::execute(){
  cout<<getOptName()<<endl;
  clptr->remove(*tlptr);
}

void OptWriteCust::execute(){
  ofstream f;
  if (clptr->isEmpty())
    cout<<tab<<"###### Customer List is empty.\n";
  else {
    cout<<getOptName()<<endl;
    openOutputFile(f);
    clptr->write(f);
    f.close();
  }
}

void OptAddTrans::execute(){
  if (clptr->isEmpty())
    cout<<tab<<"###### Customer List is empty - No transactions are possible.\n";
  else {
    cout<<getOptName()<<endl;
    tlptr->set(*clptr);
  }
}

void OptEditTrans::execute(){
  if (tlptr->isEmpty())
    cout<<tab<<"###### Transaction List is empty.\n";
  else {
    cout<<getOptName()<<endl;
    tlptr->edit(*clptr);
  }
}

void OptRemoveTrans::execute(){
  if (tlptr->isEmpty())
    cout<<tab<<"###### Transaction List is empty.\n";
  else {
    cout<<getOptName()<<endl;
    tlptr->remove(*clptr);
  }
}

void OptQuit::execute(){
  if (tlchange || clchange){
    if (clchange) cout<<"Customer List may have been changed.\n";
    if (tlchange) cout<<"Transaction List may have been changed.\n";
    cout<<"Do you want to quit without saving(y/n)? ";
    if (yes()) exit(1);
    else cout<<"Returning to menu.\n";
  }else exit(1);
}

void OptDisplayTrans::execute(){
  bool shortform;
  string str;
  if (tlptr->isEmpty())
    cout<<tab<<"###### Transaction List is empty.\n";
  else {
    cout<<getOptName()<<endl;
    cout<<"Use short display format (y/n)? ";
    shortform=yes();
    cout<<"Enter customer ID (or \"All\") ";
    getline(cin,str);
    if ((str=="All")||(clptr->isInList(str)))
      tlptr->display(*clptr,str,shortform);
    else
      cout<<tab<<"##### No transactions for cust ID:"<<str<<endl;
  }
}

void OptReadTrans::execute(){
  ifstream f;
  if (!clptr->isEmpty()){
    cout<<getOptName()<<endl;
    openInputFile(f);
    if (!tlptr->isEmpty()){
      cout<<"Do you want to keep old data? ";
      if (!yes()) 
	tlptr->clear();
    }
    tlptr->read(f,*clptr);
    f.close();
  }else cout<<'\t'
	    <<"###### Customer List is empty - No transactions are possible."
	    <<endl;
}

void OptWriteTrans::execute(){
  ofstream f;
  if (tlptr->isEmpty())
    cout<<tab<<"###### Transaction List is empty.\n";
  else {
    cout<<getOptName()<<endl;
    openOutputFile(f);
    tlptr->write(f);
    f.close();
  }
}

void openOutputFile(ofstream& outfile) {
  string filename;
  ifstream oldfile;
  while(1) {
    cout << "Please enter the file name for saving this data: " << flush;
    cin >> ws;
    getline(cin, filename);
    oldfile.open(filename.c_str());
    if (!oldfile)
      break;
    cout << "File already exists ... Ok to overwrite (y/n)? " << endl;
    if (yes()) break;
    oldfile.close();
  }
  oldfile.close();
  outfile.open(filename.c_str());
  cout << "Writing to file " << filename << " ..." << endl;
}

void openInputFile(ifstream& infile) {
  string filename;

  while(1) {
    cout << "Name of the file to be read:  " << flush;
    cin >> ws;
    getline(cin, filename);
    infile.open(filename.c_str());
    if (infile)
      break;
    cout << "File does not exist ... Please try again. " << endl;
  }
  cout << "Reading file " << filename << " ..." << endl;
}
