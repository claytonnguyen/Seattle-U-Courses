//AUTHOR: Clay Nguyen
//DATE: October 22, 2021
//REVISION HISTORY: FIRST SUBMISSION

//Class invariant: allows for arbitrary length of entrees in the class
// since we are implementing with a linked list. constructor sets the top
// node to nullptr. All public functions use linked list maneuvers to go through
// the linked list, error checking along the way. This class has operator overloading,
// read the implementation invariant to know all the operators not implemented.

#ifndef VENDOR_H
#define VENDOR_H

#include "entree.h"
#include <memory>
#include <vector>
using namespace std;

struct node {
  Entree data;
  float price;
  int quantity;
  node* next;
};

class Vendor {
private:
  int uniqueEntrees;
  node* top;

  //PRECONDITIONS: Client must pass in a valid Vendor obj
  //ROSTCONDITIONS: copies the linked list with a deep copy
  void copy(const Vendor& src);

  //PRECONDITIONS: None
  //ROSTCONDITIONS: deletes the linked list held in Vendor and sets top to nullptr
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

  //PRECONDITIONS: client must pass in valid Vendor obj
  //POSTCONDITIONS: adds the left object to the right vendor object, is not destructive to the left or right vendor object
  Vendor operator+(const Vendor& b);

  //PRECONDITIONS: client must pass in valid Vendor obj
  //POSTCONDITIONS: None, returns true if the vendor objects hold the same entree objects in the same order, else false
  bool operator==(const Vendor& b);

  //PRECONDITIONS: client must pass in valid Vendor obj
  //POSTCONDITIONS: None, returns false if the vendor object holds the same entree objects in the same order, else true
  bool operator!=(const Vendor& b);

  //PRECONDITIONS: client must pass in valid Vendor obj
  //POSTCONDITIONS: Returns the left side vendor object as a reference, adding the entrees on the right side vendor object to itself
  Vendor& operator+=(const Vendor& b);

  
  //PRECONDITIONS: None
  //POSTCONDITIONS: swaps heap allocated memory to avoid temp copies
  Vendor(Vendor&& src);

  //PRECONDITIONS: None
  //POSTCONDITIONS: swaps heap allocated memory to avoid temp copies
  Vendor& operator=(Vendor&& src);

  //PRECONDITIONS: client must pass in a valid entree obj
  //POSTCONDITIONS: Creates a new node and sets Entree in it and adds it to the linked list
  bool Load(Entree entree, float price, int quantity);

  //PRECONDITIONS: client must pass in valid arguments for dependency injection
  //POSTCONDITIONS: if the customer can buy the item, the entree's node will be taken out of the linked list
  Entree Sell();

  //PRECONDITIONS: None
  //POSTCONDITIONS: Goes through the linked list and sets all the entrees to have no power = spoiled
  void PowerOutage();

  //PRECONDITIONS: None
  //POSTCONDITIONS: Goes through the linked list and deletes nodes if the entree inside of it is spoiled
  void CleanStock();

  //PRECONDITIONS: client must pass in valid string for file path dependency to read in entrees
  //POSTCONDITIONS: creates entree objects and places them into the vendor linked list
  void Setup(string filePath);

  //PRECONDITIONS: client must pass in valid arguments for dependency injection
  //POSTCONDITIONS: None
  bool Contains(string name, string input);

  //PRECONDITIONS: client must pass in valid arguments for dependency injection
  //POSTCONDITIONS: None
  bool ContainsIngredient(string name, string input);
  
  //PRECONDITIONS: client must pass in valid arguments for dependency injection
  //POSTCONDITIONS: None
  bool IsStocked(string entreeName);

  //PRECONDITIONS: client must pass in valid arguments for dependency injection  
  //POSTCONDITIONS: None
  bool IsOnRefDisplay(string entreeName);

  //PRECONDITIONS: client must pass in valid string
  //POSTCONDITIONS: None
  float getPrice(string name);

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  string getTop();

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  bool canBuy();

  //PRECONDITIONS: client must pass in valid arguments
  //POSTCONDITIONS: None
  float checkNutrition(string name, string input);

  //PRECONDITIONS: client must pass in valid arguments
  //POSTCONDITIONS: returns an ostream object that contains information about vendor object
  friend ostream& operator<<(ostream& out, const Vendor& vendor);
  
};

#endif

//Interface invariant: Client needs to pass a stack allocated entree object to the load
// method and a customer to the sell method to check and change balance.
// client needs to inject dependencies correctly for the methods.

//Implementation invariant: used a linked list to keep from having to resize a array and
// keep track of the length of it.
// Operators not overloaded and reason why:
//
// Only addition and no mixed mode for the mathematical operators since it would not make sense to
// add anything other than two vendor objects and sub, mul, div, or mod two vendor objects
//
// No increment or decrement operator for this class since it just holds a linked list
// wouldn't make sense to increment anything
//
// Only the == and the != operator are the only relational operators since you can't really
// < and >. Can only compare length.
//
// No logical operator included since they do not add any value to the class
//
// Only the addition assignment and assignment operator overloaded since it would not make sense to
// sub, mul, div, or mod one vendor from another
//
// No access operators since it violates encapsulation and the customer could corrupt data
//
// No stream in operator (>>) since it raises coupling between the client and the implementation
// and the client could corrupt the data
//
// No function operator
