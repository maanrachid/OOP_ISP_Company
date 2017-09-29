#include "transactionList.h"

void TransactionList::clear(){
  for(MIt y=mm.begin();y!=mm.end();y++)
    delete y->second;
  mm.clear();
}

void TransactionList::edit(CustomerList& cl){
  string strid,strname;
  Transaction* ptr;
  if (!isEmpty()){
    cout<<"Enter the first few characters of the customer's name: ";
    getline(cin,strname);
    strid=cl.findid(strname);
    for(MIt y=mm.begin();y!=mm.end();y++){
      if (strid==y->first){
	y->second->display(0);
	cout<<"Edit this Transaction (y/n)? ";
	if (yes()) y->second->edit(cl);
	if (y->second->gettcustomerid()!=y->first){
	  cout<<"*** Transaction has been associated with a different custID.\n";
	  
	  if (y->second!=NULL) ptr=y->second->clone();
	  MIt u=y;
	  mm.erase(u);
	  insert(ptr);
	}
      }
    }
    cl.setAcctBalance(*this,"All");
  }else cout<<'\t'<<"###### Transaction List is empty.\n";
  
}

void TransactionList::insert(Transaction* ptr){
  mm.insert(make_pair(string(ptr->gettcustomerid()),
		      TransactionFactory::create(ptr)));
}

TransactionList::TransactionList(const TransactionList& trl){
  *this=trl;    /*not a shallow copy*/
}
  
TransactionList& TransactionList::operator=(const TransactionList& trl){
  clear();
  for(CONMIt y=trl.mm.begin();y!=trl.mm.end();y++)
    mm.insert(make_pair(string(y->first),y->second->clone()));
  return (*this);
}  



void TransactionList::set(CustomerList& cusl){
  Transaction* ptr;
  do {
    ptr=TransactionFactory::create(cusl);
    insert(ptr);
    cusl.setAcctBalance(*this,ptr->gettcustomerid());
    cout<<"Another Transaction (Y/N)? ";
  }while(yes());

}

void TransactionList::display(CustomerList& cusl,string strid,
			      bool shortform)const{
  
  if(strid=="All"){
    for(CONMIt y=mm.begin(); y != mm.end(); y++){
      if (cusl.isInList(y->first)){
	if (!shortform)  cusl.display(y->first);
	y->second->display();
	cout<<"----------------------\n";
      }
    }
  }else{ 
    for(CONMIt y=mm.begin(); y != mm.end(); y++){
      if (y->second->gettcustomerid()==strid){
	if (!shortform) cusl.display(y->first);
	y->second->display();
	cout<<"----------------------\n";
      }
    }
  }
}

bool TransactionList::isInList(Transaction* ptr)const{
  string str1=ptr->gettcustomerid();
  for(CONMIt y= mm.lower_bound(str1); y!= mm.upper_bound(str1); ++y){
    if (y->second->getTType()==ptr->getTType()){
      if (y->second->getobj()==ptr->getobj()) return true;
    }
  } 
  return false; 
}


bool TransactionList::isInList(const string strid)const{
  for(CONMIt y=mm.begin();y!=mm.end();y++){
    if (y->first==strid)
      return true;
  }
  return false;
}

void TransactionList::remove(CustomerList& cl){
  string strid,strname;
  if (!isEmpty()){
    cout<<"Enter the first few characters of the customer's name: ";
    getline(cin,strname);
    strid=cl.findid(strname);
    remove(strid);
    cl.setAcctBalance(*this,strid);
  }else
    cout<<"###### Transaction List is empty.\n";
}


void TransactionList::remove(string strid){
  MIt t1;
  for(MIt y=mm.begin(); y != mm.end(); y++){
    if (y->first==strid){
      y->second->display();
      cout<<"Delete this transaction(Y/N)? ";
      if (yes()){
	delete y->second;
	t1=y;
	mm.erase(y);
	y=t1;
      }else
	cout<<"Transaction not deleted\n";
      cout<<"Another deletion(Y/N)?  ";
      if (!yes()) break;
    }
  }
  
}

double TransactionList::accountTotal(string strid)const{
  double z=0;
  for(CONMIt y=mm.begin(); y != mm.end(); y++){
    if (y->first==strid)
      z+=(y->second->gettamount());
  }
  return z;
}

void TransactionList::write(ofstream& f)const{
  f<<mm.size()<<endl;
  for(CONMIt y=mm.begin(); y != mm.end(); y++){
    y->second->write(f);
  }
}


void TransactionList::read(ifstream& f, CustomerList& cl){
  int temp,n,l;
  Transaction* ptr;
  f>>temp;
  for(n=1;n<=temp;n++){
    f>>l>>ws;
    ptr=TransactionFactory::create(l);
    ptr->read(f);
    if (!isInList(ptr)&&cl.isInList(ptr->gettcustomerid())) insert(ptr);
    delete ptr;
  }
  cl.setAcctBalance(*this,"All");
  cl.printcuswithnotrans(*this);
}

bool TransactionList::isEmpty()const{
  return mm.empty();
}

int TransactionList::transCount(string strid)const{
  int counter=0;
  for(CONMIt y=mm.begin(); y != mm.end(); y++){
    if (y->first==strid)
      counter++;
  }
  return counter;
}










