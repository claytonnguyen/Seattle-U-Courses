//AUTHOR: Clay Nguyen                                                                               
//DATE: October 22, 2021                                                                            
//REVISION HISTORY: FIRST SUBMISSION                                                                

#include <iostream>
#include "customer.h"

using namespace std;

Customer::Customer(unsigned int bal, unsigned int accNum) : balance(bal), accountNumber(accNum) {
}

void Customer::addMoney(unsigned int money) {
    balance += money;
}

void Customer::Buy(unsigned int money) {
  if(money < balance){
    balance -= money;
  }
}

unsigned int Customer::GetBalance() {
    return balance;
}