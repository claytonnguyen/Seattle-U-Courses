//AUTHOR: Clay Nguyen                                                                               
//NAME: P2.cpp                                                                                      
//DATE: October 22, 2021                                                                            

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entree.h"
#include "vendor.h"
#include "customer.h"

//Functional decomposition methods for unique pointers arg passing                                  
void InRefDisplay(const unique_ptr<Vendor>& obj, string name);
void Sell(const unique_ptr<Vendor>& obj, Customer& customer, string name);
void Loading(const unique_ptr<Vendor>& obj, Entree& entree);
void isStocked(const unique_ptr<Vendor>& obj, string name);

//Same functional decomposition but for shared pointer arg passing                                  
void InRefDisplay(const shared_ptr<Vendor>& obj, string name);
void Sell(const shared_ptr<Vendor>& obj, Customer& customer, string name);
void Loading(const shared_ptr<Vendor>& obj, Entree& entree);
void isStocked(const shared_ptr<Vendor>& obj, string name);

//methods to generate random numbers for dependency injection                                       
int randPrice();
int randBalance();
int randAccNum();
int randYear();
int randMonth();
int randDay();

int main() {
  srand(time(NULL));
  vector<unique_ptr<Vendor> > vendors;

  string ingredients = "apples$pineapple$grapes$oranges$peaches";
  string nutrition = "apples$pineapple$grapes$oranges$peaches";
  string ingredients1 = "apples$pineapple$grapes$oranges";
  string nutrition1 = "apples$pineapple$grapes$oranges";
  string ingredients2 = "apples$pineapple$grapes$oranges";
  string nutrition2 = "apples$pineapple$grapes$oranges";
  string ingredients3 = "apples$pineapple$grapes$oranges";
  string nutrition3 = "apples$pineapple$grapes$oranges";
  string ingredients4 = "apples$pineapple$grapes$oranges";
  string nutrition4 = "apples$pineapple$grapes$oranges";

  Customer c1(randBalance(), randAccNum());
  Customer c2(randBalance(), randAccNum());
  Customer c3(randBalance(), randAccNum());

  date expir;
  expir.year = randYear();
  expir.month = randMonth();
  expir.day = randDay();

  // creating an Entree class to then be loaded into the vendor class                               
  Entree fruits ("fruit dish", randPrice(), true, true, true, expir, ingredients, nutrition);
  Entree pizza ("pizza", randPrice(), true, true, true, expir, ingredients1, nutrition1);
  Entree pasta ("pasta", randPrice(), true, true, true, expir, ingredients, nutrition);
  Entree pho ("pho", randPrice(), true, true, true, expir, ingredients1, nutrition1);
  Entree stew ("stew", randPrice(), true, true, true, expir, ingredients, nutrition);


  shared_ptr<Vendor> vend1 (new Vendor());
  unique_ptr<Vendor> vend2 (new Vendor());

  //Demonstrating all the functionality within one Vendor class                                     
  Loading(vend1, fruits);
  InRefDisplay(vend1, "fruit dish");
  isStocked(vend1, "fruit dish");
  Sell(vend1, c2, "fruit dish");
  isStocked(vend1, "fruit dish");
  cout << endl;


  // Demonstrating multiple loads and checking list linked functionality                            
  Loading(vend2, pizza);
  Loading(vend2, pasta);
  Loading(vend2, pho);
  isStocked(vend2, "pizza");
  isStocked(vend2, "pasta");
  isStocked(vend2, "pho");
  cout << endl;

  // Demonstrating Deep copy of Vendor                                                             $
  unique_ptr<Vendor> vendDeepCopy (new Vendor(*vend2));

  // Chekcing if the items were made                                                                
  isStocked(vendDeepCopy, "pizza");
  isStocked(vendDeepCopy, "pasta");
  isStocked(vendDeepCopy, "pho");
  cout << endl;

  // Checking to see if poweroutage() and cleanstock() works                                        
  isStocked(vend2, "pizza");
  vend2->PowerOutage();
  Sell(vend2, c3, "pizza");
  vend2->CleanStock();
  cout << endl;

  // Demonstrating using a vector to move the smart pointers                                        
  vendors.push_back(move(vend2));
  vendors.push_back(move(vendDeepCopy));

  vendors.pop_back();
}

void InRefDisplay(const unique_ptr<Vendor>& obj, string name){
  bool refDisplay = obj->IsOnRefDisplay(name);
  if (refDisplay) {
    cout << name << " is on a refrigerated display" << endl;
  } else {
    cout << name << " is not on a refrigerated display" << endl;
  }
}

void Sell(const unique_ptr<Vendor>& obj, Customer& customer, string name){
  bool sold = obj->Sell(name, customer);
  if (sold) {
    cout << name << " sold to customer" << endl;
  } else {
    cout << name << " was not sold. Either could not find the item or the item is spoiled." << endl$
  }
}

void Loading(const unique_ptr<Vendor>& obj, Entree& entree){
  bool loaded = obj->Load(entree);
  string name = entree.GetName();
  if (loaded) {
    cout << name << " was loaded" << endl;
  } else {
    cout << name << " was not loaded" << endl;
  }
}

void isStocked(const unique_ptr<Vendor>& obj, string name){
  bool stocked = obj->IsStocked(name);
  if(stocked) {
    cout << name << " is stocked and not spoiled" << endl;
  } else {
    cout << name << " is not stocked or is spoiled" << endl;
  }
}

void InRefDisplay(const shared_ptr<Vendor>& obj, string name){
  bool refDisplay = obj->IsOnRefDisplay(name);
  if (refDisplay) {
    cout << name << " is on a refrigerated display" << endl;
  } else {
    cout << name << " is not on a refrigerated display" << endl;
  }
}

void Sell(const shared_ptr<Vendor>& obj, Customer& customer, string name){
  bool sold = obj->Sell(name, customer);
  if (sold) {
    cout << name << " sold to customer" << endl;
  } else {
    cout << name << " was not sold. Either could not find the item or the item is spoiled." << endl$
  }
}

void Loading(const shared_ptr<Vendor>& obj, Entree& entree){
  bool loaded = obj->Load(entree);
  string name = entree.GetName();
  if (loaded) {
    cout << name << " was loaded" << endl;
  } else {
    cout << name << " was not loaded" << endl;
  }
}

void isStocked(const shared_ptr<Vendor>& obj, string name){
  bool stocked = obj->IsStocked(name);
  if(stocked) {
    cout << name << " is stocked and not spoiled" << endl;
  } else {
    cout << name << " is not stocked or is spoiled" << endl;
  }
}

int randPrice() {
  return (rand() % 99 + 1);
}

int randBalance() {
  return (rand() % 999 + 1);
}

int randAccNum() {
  return (rand() % 100000 + 9000);
}

int randYear() {
  return (rand() % 2999 + 1000);
}

int randMonth() {
  return (rand() % 12 + 1);
}

int randDay() {
  return (rand() % 30 + 1);
}
