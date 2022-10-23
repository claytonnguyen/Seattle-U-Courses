//AUTHOR: Clay Nguyen
//DATE: October 22, 2021
//REVISION HISTORY: FIRST SUBMISSION

#include <iostream>
#include "customer.h"
#include "vendor.h"


Customer::Customer(unsigned int bal, unsigned int accNum) : balance(bal), accountNumber(accNum) {
}

void Customer::addMoney(unsigned int money) {
    balance += money;
}

bool Customer::purchase(unsigned money){
  if(money <= balance){
    balance -= money;
    return true;
  }
  return false;
}

bool Customer::buy(Vendor& vendor) {
  vendor.CleanStock();
  string entreeName;
  string entree2;
  string entree3;
  Entree firstEntree;
  Entree secondEntree;
  Entree thirdEntree;

  
  for (int i = 0; i < 3; i++){
    if(vendor.canBuy() == true){
      entreeName = vendor.getTop();
      if(vendor.getPrice(entreeName) <= GetBalance()){
        if (i == 0){
          firstEntree = buyOne(entreeName, vendor);
        } else if (i == 1){
          secondEntree = buyOne(entreeName, vendor);
        } else {
          thirdEntree = buyOne(entreeName, vendor);
        }
      }
    }
  }
  if (firstEntree.GetName() != "" && secondEntree.GetName() != "" && thirdEntree.GetName() != "")
    {
      Entree returnEntree(firstEntree);
      returnEntree += secondEntree;
      returnEntree += thirdEntree;
      cout << "Bought three entrees" << endl << endl;
      cout << returnEntree << endl << endl;
      return true;
    }
  else if (firstEntree.GetName() != "" && secondEntree.GetName() != "")
    {
      Entree returnEntree(firstEntree);
      returnEntree += secondEntree;
      cout << "Bought two entrees" << endl << endl;
      cout << returnEntree << endl << endl;
      return true;
    }
  else if (secondEntree.GetName() != "" && thirdEntree.GetName() != "")
    {
      Entree returnEntree(secondEntree);
      returnEntree += thirdEntree;
      cout << "Bought two entrees" << endl << endl;
      cout << returnEntree << endl << endl;
      return true;
    }
  else if (firstEntree.GetName() != "" && thirdEntree.GetName() != "")
    {
      Entree returnEntree(firstEntree);
      returnEntree += thirdEntree;
      cout << "Bought two entrees" << endl << endl;
      cout << returnEntree << endl << endl;
      return true;
    }
  else
    {
      // cannot buy for whatever reason                                                           
      return false;
    }
  return false; 
  
}

Entree Customer::buyOne(string name, Vendor& vendor) {
  Entree temp;
  vendor.CleanStock();
  float price = vendor.getPrice(name);
  if(price != -1) {
    unsigned payment = (unsigned)price;
    bool bought = purchase(payment);
    if(bought)
      {
        temp = vendor.Sell();
      }
  }
  return temp;

}

unsigned int Customer::GetBalance() {
    return balance;
}

Customer Customer::operator+(const Customer& b){
  // make and return local copy. add the balances 
  Customer local(b);
  local.balance = balance + b.balance;
  local.accountNumber = accountNumber + b.accountNumber;
  return local;
}

Customer Customer::operator-(const Customer& b){
  // make and return local copy. add the balances
  Customer local(b);
  if(balance < b.balance){
    return local;
  } else {
    local.balance = balance - b.balance;
  }
  return local;
}


Customer Customer::operator+(int inc){
  Customer local(balance, accountNumber);
  local.balance = local.balance + inc;
  return local;
}

Customer Customer::operator-(int inc){
  Customer local(balance, accountNumber);
  if(balance < inc){
    return local;
  } else {
    local.balance = local.balance - inc;
  }
  return local;
}

Customer operator+(int num, Customer& b){
  return b + num;
}

Customer operator-(int num, Customer& b){
  return b - num;
}


Customer Customer::addOne(){
  ++balance;
  return *this;
}

Customer Customer::subOne(){
  --balance;
  return *this;
}

Customer Customer::operator++(){
  return addOne();
}

Customer Customer::operator--(){
  return subOne();
}

Customer Customer::operator++(int x){
  Customer oldState = *this;
  addOne();
  return oldState;
}

Customer Customer::operator--(int x){
  Customer oldState = *this;
  subOne();
  return oldState;
}

bool Customer::operator<(const Customer& b){
  if (balance < b.balance){
    return true;
  } else {
    return false;
  }
}

bool Customer::operator<=(const Customer& b){
  if (balance <= b.balance){
    return true;
  } else {
    return false;
  }
}

bool Customer::operator==(const Customer& b){
  if (balance == b.balance){
    return true;
  } else {
    return false;
  }
}

bool Customer::operator!=(const Customer& b){
  if (balance != b.balance){
    return true;
  } else {
    return false;
  }
}

bool Customer::operator>(const Customer& b){
  if (balance >= b.balance){
    return true;
  } else {
    return false;
  }
}

bool Customer::operator>=(const Customer& b){
  if (balance >= b.balance){
    return true;
  } else {
    return false;
  }
}

// in reality, should not have assignment operator, would lead to
// two people having the same balance and account Number
Customer& Customer::operator=(const Customer& b){
  return *this;
}

Customer& Customer::operator+=(const Customer& b){
  balance += b.balance;
  return *this;
}

Customer& Customer::operator-=(const Customer& b){
  if (balance < b.balance){
    return *this;
  }
  balance += b.balance;
  return *this;
}

ostream& operator<<(ostream& out, const Customer& customer){
  out << "Customer Balance: " << customer.balance << endl;
  return out;
}
