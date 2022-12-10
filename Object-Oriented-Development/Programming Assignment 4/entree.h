//AUTHOR: Clay Nguyen                                                                               
//DATE: October 22, 2021                                                                            
//REVISION HISTORY: FIRST SUBMISSION                                                                

//Class invariant: object instantiation will need to be initialized by the constructor              
// obj will be in right state if the user injects dependecies in correctly.                         

#ifndef ENTREE_H
#define ENTREE_H

#include <iostream>
#include <memory>
using namespace std;

    struct date {
        int year;
        int month;
        int day;
    };

class Entree {
private:
  string name;
  unsigned int price;
  string ingredients;
  string nutritionStats;
  date expiration;
  bool refrigeration;
  bool refrigerated;
  bool electricity;
  bool powerIsOff;
  void copy(const Entree& src);

public:
  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: None                                                                            
  Entree();

  //PRECONDITIONS: Client must pass in valid data members for the constructor call                  
  //POSTCONDITIONS: Sets all the class data members by constructor dependency injection             
  Entree(
         string name,
         unsigned int price,
         bool refrigeration,
         bool refrigerated,
         bool electricity,
         date expiration,
         string ingredients,
         string nutritionStats);
  //PRECONDITIONS: client must pass in a valid entree obj                                           
  //POSTCONDITIONS: creates a new entree class constructed from the passed in one                   
  Entree(const Entree&);

  //PRECONDITIONS: client must pass in a valid entree obj                                           
  //POSTCONDITIONS: assigns the left entree with a deep copy of the data from the right entree      
  Entree& operator=(const Entree&);

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

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: None                                                                            
  string GetName();

  //PRECONDITIONS: None                                                                             
  //POSTCONDITIONS: None                                                                            
  unsigned int GetPrice();
};

#endif

//Interface invariant: Client must inject dependencies correctly.                                   

//Implementation invariant: strings are passed in delimited for the nutrients                       
// and ingredients to avoid storing arrays.      