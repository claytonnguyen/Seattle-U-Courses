//AUTHOR: Clay Nguyen
//DATE: October 22, 2021
//REVISION HISTORY: FIRST SUBMISSION

//Class invariant: object instantiation will need to be initialized by the constructor
// obj will be in right state if the user injects dependecies in correctly.
// This class has operator overloading, read the implementation invariant
// to know all the operators not implemented. 

#ifndef ENTREE_H
#define ENTREE_H

#include <iostream>
#include <memory>
using namespace std;

// struct for date
struct date {
  int year;
  int month;
  int day;
};

class Entree {
private:
  string name;
  string ingredients;
  float nutritionStats[11];
  string contains;
  date expiration;
  bool refrigerationNeeded;
  bool refrigerated;
  bool electricity;
  bool powerIsOff;

  //PRECONDITIONS: must pass in a valid entree object
  //POSTCONDITIONS: deep copies the information from the passed in object to the
  // object being called on
  void copy(const Entree& src);

public:
  enum Ingreds
    {
     NumberOfServings,
     Calories,
     TotalFat,
     SatFat,
     TransFat,
     Cholest,
     Sodium,
     TotCarb,
     Fiber,
     TotSugars,
     Proteins
    };

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  Entree();

  //PRECONDITIONS: Client must pass in valid data members for the constructor call
  //POSTCONDITIONS: Sets all the class data members by constructor dependency injection
  Entree(
         string name, 
         bool refrigerationNeeded, 
         bool refrigerated,
         bool electricity, 
         date expiration,
         string ingredients,
         float nutritionStats[],
         string contains);
  //PRECONDITIONS: client must pass in a valid entree obj
  //POSTCONDITIONS: creates a new entree class constructed from the passed in one
  Entree(const Entree&);

  //PRECONDITIONS: client must pass in a valid entree obj
  //POSTCONDITIONS: assigns the left entree with a deep copy of the data from the right entree 
  Entree& operator=(const Entree&);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: returns a local entree with the sum of the nutrients of the two entrees
  Entree operator+(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: None
  bool operator<(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: None
  bool operator<=(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: None
  bool operator==(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: None
  bool operator!=(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //ROSTCONDITIONS: None
  bool operator>(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: None
  bool operator>=(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //POSTCONDITIONS: assigns the left Entree to the addition of nutrition of
  // the left and right side entree
  Entree& operator+=(const Entree& b);

  //PRECONDITIONS: client must use a valid Entree object
  //ROSTCONDITIONS: must use this with the cout functionality
  friend ostream& operator<<(ostream& out, const Entree& entree);
  
  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  bool IsExpired();

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  bool IsSpoiled();

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  bool IsRefrigerated();

  //PRECONDITIONS: None
  //POSTCONDITIONS: changes the power bool to be off
  void PowerDown();

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  bool Power();

  //PRECONDITIONS: must pass in valid string to method
  //POSTCONDITIONS: None
  bool Contains(string ingredient);

  //PRECONDITIONS: must pass in valid string to method                                              
  //POSTCONDITIONS: None                                                                            
  bool ContainsIngredient(string ingredient);
  
  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  string GetName();

  //PRECONDITIONS: None
  //POSTCONDITIONS: None
  unsigned int GetPrice();

  //PRECONDITIONS: must pass in valid string to method
  //ROSTCONDITIONS: None
  float checkNutrients(string input);
};


#endif

//Interface invariant: Client must inject dependencies correctly.

//Implementation invariant: strings are passed in delimited for the nutrients
// and ingredients to avoid storing arrays. 
// Operators not overloaded and reason why
//
// Only addition overloaded and no mixed mode for any mathematical operators because
// only entrees should be added together and sub, mul, div, and modulo would not make sense
// to include these operators

// No increment or decrement operator overload because it violates encapsulation
// shouldn't be able to change the nutritional stats of an entree, only add them to get
// the cumulative in a meal

// No logical operators because it does not add value to the class

// Only addition assignment and assignment operator since it would not make sense to subtract,
// multiply, divide, or modulo two entrees from each other.

// No access operators since the user could corrupt the data, shouldn't be able to change
// the entree information

// No stream in (>>) operator since this also breaks cohesion and encapsulation. The insert of
// data with this operator would couple the design too much.

// No function operator 
