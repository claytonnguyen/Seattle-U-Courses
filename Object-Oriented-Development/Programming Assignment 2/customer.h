//AUTHOR: Clay Nguyen
//DATE: October 22, 2021
//REVISION HISTORY: FIRST SUBMISSION

//Class invariant: customer object is instantiated with an unsigned balance
// and a unsigned account Number. Balance will change by adding money or buying
// if the user does not call buy themselves, the balance will never be negative.
// only the sell function accesses it and it error checks. This class has operator
// overloading, read the implementation invariant to know all the operators not
// implemented.

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "vendor.h"

using namespace std;



class Customer {
private:
  unsigned int balance;
  unsigned int accountNumber;

  //PRECONDITIONS: None
  //POSTCONDITIONS: adds one dollar to the balance of the customer
  Customer addOne();

  //PRECONDITIONS: None
  //POSTCONDITIONS: subtracts one dollar from the balance of the customer
  Customer subOne();
  
public:
  //PRECONDITIONS: Client must pass in valid data members for constructor dependency injection
  //POSTCONDITIONS: Sets the class data members in accordance to constructor dependency injection
  Customer(unsigned bal, unsigned accountNumber);

  //PRECONDITIONS: client must pass in valid unsigned int to method
  //POSTCONDITIONS: changes the balance to add more money
  void addMoney(unsigned money);

  //PRECONDITIONS: client must pass in valid unsigned int to method                                 
  //POSTCONDITIONS: changes the balance to add more money                                           
  bool purchase(unsigned money);

  //PRECONDITIONS: client must pass in valid unsigned int to method
  //POSTCONDITIONS: changes the balance to have less money. never negative
  virtual bool buy(Vendor& vendor);

  //PRECONDITIONS: client must pass in valid unsigned int to method                                 
  //POSTCONDITIONS: changes the balance to have less money. never negative                          
  virtual Entree buyOne(string name, Vendor& vendor);
  
  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  unsigned int GetBalance();

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  Customer operator+(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  Customer operator-(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: Changes the balance to add a dollar
  Customer operator++();

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: Changes the balance to subtract a dollar
  Customer operator--();

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: Changes the balance to add a dollar
  Customer operator++(int x);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: Changes the balance to subtract a dollar
  Customer operator--(int x);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: mixed mode add returns a temp entree
  Customer operator+(int inc);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: mixed mode sub returns a temp entree
  Customer operator-(int inc);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  bool operator<(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  bool operator<=(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  bool operator==(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  bool operator!=(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  bool operator>(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  bool operator>=(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: None
  Customer& operator=(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: changes the left side object to add the balance of the right side
  // object to its own balance
  Customer& operator+=(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: changes the left side object to sub the balance of the right side
  // object if the balance of the left side object cannot go below 0
  Customer& operator-=(const Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: must use with the cout object on the left side
  friend ostream& operator<<(ostream& out, const Customer& customer);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: mixed mode reverses the mixed mode call with int on the right
  friend Customer operator+(int inc, Customer& b);

  //PRECONDITIONS: Client must use a valid Customer object
  //POSTCONDITIONS: mixed mode reverses the mixed mode call with int on the right
  friend Customer operator-(int inc, Customer& b);
};

#endif

//Interface invariant: Client must inject dependencies into the constructor correctly.
// client themselves should not call the buy method.

//Implementation invariant: implemented balance as a unsigned int to never allow balances
// to be negative.
// Operators not overloaded and reason why:
//
// No multiplication, division, or modulo because it wouldn’t make sense to get a multiple or
// a modulo remainder for balances between two customers
//
// No logical operators because they do not add value to the class
//
// Only assignment is the addition and subtraction assignment, no assignment operator because
// it wouldn’t make any sense to have two customers with the same balance and accNum (really bad),
// no multiplication, division or modulo operator since it wouldn’t make any sense to multiply,
// divide, or modulo assign a customer to another
//
// no access operators since they violate encapsulation
//
// no stream in operator since it also violates encapsulation and customer could corrupt data
//
// no function operator 
