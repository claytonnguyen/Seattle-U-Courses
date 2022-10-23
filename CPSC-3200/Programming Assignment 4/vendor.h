//AUTHOR: Clay Nguyen                                                                               
//DATE: October 22, 2021                                                                            
//REVISION HISTORY: FIRST SUBMISSION                                                                

//Class invariant: allows for arbitrary length of entrees in the class                              
// since we are implementing with a linked list. constructor sets the top                           
// node to nullptr. All public functions use linked list maneuvers to go through                    
// the linked list, error checking along the way.                                                   

#ifndef VENDOR_H
#define VENDOR_H

#include "entree.h"
#include "customer.h"
#include <memory>
using namespace std;

struct node {
  Entree data;
  float price;
  uint quantity;
  node* next;
};

class Vendor {
private:
  node* top;
  void copy(const Vendor& src);
  void deleteList();

public:
  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: sets top node to nullptr                                                        
  Vendor();

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: goes through the linked list and deletes the linked list                        
  ~Vendor();

  //PRECONDITIONS: client must pass in valid Vendor obj                                             
  //POSTCONDITIONS: creates a new copied Vendor object from the passed in Vendor obj                
  Vendor(const Vendor& obj);

  //PRECONDITIONS: client must pass in valid Vendor obj                                             
  //POSTCONDITIONS: assigns the left Vendor a deep copy of the right Vendor's data members          
  Vendor& operator=(const Vendor& obj);

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: swaps heap allocated memory to avoid temp copies                                
  Vendor(Vendor&& src);

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: swaps heap allocated memory to avoid temp copies                                
  Vendor& operator=(Vendor&& src);

  //PRECONDITIONS: client must pass in a valid entree obj                                           
  //POSTCONDITIONS: Creates a new node and sets Entree in it and adds it to the linked list         
  bool Load(Entree entree);

  //PRECONDITIONS: client must pass in valid arguments for dependency injection                     
  //POSTCONDITIONS: if the customer can buy the item, the entree's node will be taken out of the li$
  bool Sell(string entreeName, Customer& x);

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: Goes through the linked list and sets all the entrees to have no power = spoile$
  void PowerOutage();

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: Goes through the linked list and deletes nodes if the entree inside of it is sp$
  void CleanStock();

  //PRECONDITIONS: client must pass in valid arguments for dependency injection                     
  //POSTCONDITIONS: None                                                                            
  bool IsStocked(string entreeName);

  //PRECONDITIONS: client must pass in valid arguments for dependency injection                     
  //POSTCONDITIONS: None                                                                            
  bool IsOnRefDisplay(string entreeName);

};

#endif

//Interface invariant: Client needs to pass a stack allocated entree object to the load             
// method and a customer to the sell method to check and change balance.                            
// client needs to inject dependencies correctly for the methods.                                   

//Implementation invariant: used a linked list to keep from having to resize a array and            
// keep track of the length of it.                 