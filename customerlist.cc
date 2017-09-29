#include "customerList.h"
#include "transactionList.h"

void CustomerList::clear(){
  b.clear();
}

void CustomerList::fixnogap(Date d,const string strid){
  b[strid].nogap=d;
}

void CustomerList::printcuswithnotrans(const TransactionList& tr)const{
  for(itr i=b.begin();i!=b.end();i++){
    if (!(tr.isInList(i->first))) cout<<(i->first)<<" has no Transactions.\n";
  }
}

void CustomerList::remove(TransactionList& tl){
  string strname,strid;
  if (!isEmpty()){
    cout<<"Enter the first few characters of the customer's name:";
    getline(cin,strname);
    strid=findid(strname);
    if (strid!="not found"){
      if(!tl.isInList(strid)){
	b[strid].display(0);
	cout<<"Are you sure that you want to remove this Customer (y/n)? ";
	if (yes()) remove(strid);
      }else{
	cout<<"*** This Customer has transactions on file which must\n";
	cout<<"*** all be removed before the Customer can be removed.\n";
      }  
    }else cout<<strname<<" "<<strid<<endl;
  }else 
    cout<<'\t'<<"###### Customer List is empty.\n";
}

void CustomerList::edit(){
  string strname,strid;
  cout<<"Enter the first few characters of the customer's name:";
  getline(cin,strname);
  strid=findid(strname);
  if (strid!="not found")
    b[strid].edit();
  else
    cout<<strname<<" "<<strid<<endl;
}

void CustomerList::setAcctBalance(const TransactionList& tl1,string strid){
  if (strid=="All"){
    for(CHAitr i=b.begin();i!=b.end();i++){
      /* using the power of friend .Thats cool!*/
      i->second.accountBalance = tl1.accountTotal(i->first);
    }
  }else if (isInList(strid))
    b[strid].accountBalance =tl1.accountTotal(strid);
}



string CustomerList::findid(const string& info)const{
  int n=info.length();
  for(itr i = b.begin(); i != b.end(); ++i) {
    /* I think compare is better than find because the 
       matching will be with the begining of the word 
       which is how the databases being search usually right?*/
    if ((*i).second.getName().compare(info)==0){
      cout<<"Name: "<< (*i).second.getName() <<'\t';
      cout <<"ID: "<< (*i).second.getCustomerId()<<"? " ;
      if (yes())
	return (*i).second.getCustomerId();
    }
  }
  return "not found";
	  
}

Customer CustomerList::operator[](const string& strid)const{

  Customer cus;

  if (isInList(strid)){
    for(itr i = b.begin(); i != b.end(); ++i) {
      if ((*i).second.getCustomerId()==strid)
	return i->second;
    }
  }
  return cus;
}


void CustomerList::set(){
  Customer cs1;
  do{
    cs1.set();
    cout<<"---------------\n";
    insert(cs1);
    cout<<"Another customer (Y/N)?";
  }while(yes());
}


bool CustomerList::insert(const Customer& cus){
  
  string str1;
  str1=cus.getCustomerId();  
  if (b.find(str1)==b.end()){
    b[str1]=cus;
    cout<<"Not in list yet ....\n";
    b[str1].display(0);
    cout<<"map size so far is: "<<b.size()<<endl;
    return true;
  }else {
    cout<<"CustomerID "<<str1<<" is already in use:\n";
    b[str1].display();
    cout<<"OK to replace (Y/N)?";
    if (yes()){
      b[str1]=cus;
      cout<<"map size so far is: "<<b.size()<<endl;
      return true;
    }else
      return false; 
  }
  
}



void CustomerList::display(string str,bool shortform){
  Customer cs1,i;
  if (str=="All"){
    for(itr i = b.begin(); i != b.end(); ++i) {
      (*i).second.display(shortform);
      cout<<"-----------------\n";
    }
  }else {
    if (b.find(str)!=b.end()){  
      cs1=b[str]; 
      cs1.display(shortform);
    }
  }
}


void CustomerList::remove(string csId){
  
  b.erase(b.find(csId)); //b.erase(csId) doesnt work?
}


itr CustomerList::find(string csId)const{
  return b.find(csId);
}


void CustomerList::read(ifstream& f){
  Customer cs1;
  int i;
  int s;
  string str; 
  f>>s;
  getline(f,str);
  for(i=1;i<=s;i++) {
    cs1.read(f);
    if (!isInList(cs1))
      b[cs1.getCustomerId()]=cs1;
    else{
      cout<<"The customer with ID "<<cs1.getCustomerId()<<" found.\n";
      cout<<cs1.getName()<<"\t  "<<cs1.getAccountdate()<<endl;
      cout<<"Ok to replace(Y/N)? ";
      if (yes())  b[cs1.getCustomerId()]=cs1;     
    }
  }
}

void CustomerList::write(ofstream& f)const{
  f<<b.size()<<seperater;
  for(itr i = b.begin(); i != b.end(); ++i) {
    (*i).second.write(f);
  }    

}

bool CustomerList::isEmpty()const{
  return b.empty();
}


bool CustomerList::isInList(Customer& cus){
  return  isInList(cus.getCustomerId());
}


bool CustomerList::isInList(const string& csId)const{
  return b.count(csId);
}














