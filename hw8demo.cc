// File: hw8demo.cc

#include "customerList.h"
#include "transactionList.h"
#include "option.h"

int main() {
  CustomerList cl;
  TransactionList tl;
  OptFactory::menu(cl, tl);
}

