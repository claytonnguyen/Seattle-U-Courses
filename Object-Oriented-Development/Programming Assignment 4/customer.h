//AUTHOR: Clay Nguyen                                                                               
//DATE: October 22, 2021                                                                            
//REVISION HISTORY: FIRST SUBMISSION                                                                

//Class invariant: customer object is instantiated with an unsigned balance                         
// and a unsigned account Number. Balance will change by adding money or buying                     
// if the user does not call buy themselves, the balance will never be negative.                    
// only the sell function accesses it and it error checks.                                          

#ifndef CUSTOMER_H
#define CUSTOMER_H

using namespace std;

class Customer {
private:
  unsigned int balance;
  unsigned int accountNumber;

public:
  //PRECONDITIONS: Client must pass in valid data members for constructor dependency injection      
  //POSTCONDITIONS: Sets the class data members in accordance to constructor dependency injection   
  Customer(unsigned int bal, unsigned int accountNumber);

  //PRECONDITIONS: client must pass in valid unsigned int to method                                 
  //POSTCONDITIONS: changes the balance to add more money                                           
  void addMoney(unsigned int money);

  //PRECONDITIONS: client must pass in valid unsigned int to method                                 
  //POSTCONDITIONS: changes the balance to have less money. never negative                          
  virtual void Buy(unsigned int money);

  virtual void BuyOne()

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: None                                                                            
  unsigned int GetBalance();

};

#endif

//Interface invariant: Client must inject dependencies into the constructor correctly.              
// client themselves should not call the buy method.                                                

//Implementation invariant: implemented balance as a unsigned int to never allow balances           
// to be negative.    