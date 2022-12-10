//AUTHOR: Clay Nguyen
//DATE: October 22, 2021
//REVISION HISTORY: FIRST SUBMISSION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include "entree.h"
#include "vendor.h"

using namespace std;

Vendor::Vendor(){
  top = nullptr;
}

Vendor::~Vendor(){
  deleteList();
}

void Vendor::copy(const Vendor& src){
  node* curr = top;
  node* prev = nullptr;
  node* copyptr = src.top;
  while(copyptr != nullptr) {
    node* newPtr = new node;
    newPtr->data = Entree(copyptr->data);
    newPtr->price = copyptr->price;
    newPtr->quantity = copyptr->quantity;
    newPtr->next = nullptr;
    if(prev == nullptr){
      top = newPtr;
      curr = top->next;
      prev = top;
      copyptr = copyptr->next;
    }else {
      curr = newPtr;
      prev->next = curr;
      prev = curr;
      copyptr = copyptr->next;
      curr = curr->next;
    }
  }
}
Vendor::Vendor(const Vendor& src){
  copy(src);
}

Vendor& Vendor::operator=(const Vendor& src){
  if(this == &src) return *this;
  deleteList();
  copy(src);
  return *this;
}

Vendor::Vendor(Vendor&& src) {
	top = src.top;
	src.top = nullptr;
}

Vendor& Vendor::operator=(Vendor&& src) {
	top = src.top;
	return *this;
}

void Vendor::deleteList(){
  node* curr = top;
  node* next = nullptr;
  while(curr != nullptr) {
    next = curr->next;
    delete curr;
    curr = next;
  }
  top = nullptr;
}
bool Vendor::Load(Entree entree, float price, int quantity) {
  if(entree.GetName() != ""){
    cout << "loading: " << entree.GetName() << endl;
    node* curr = top;
    node* newNode = new node;
    newNode->data = entree;
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = nullptr;
    if (top == nullptr) {
      top = newNode;
      return true;
    }
    while(curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = newNode;
    return true;
  }
  return false;
}

Entree Vendor::Sell(){
  Entree temp;
  node* curr = top;
  node* prev = nullptr;
  CleanStock();
  if(curr != nullptr) {
    if(!curr->data.IsSpoiled()){
      temp = Entree(curr->data);
      cout << "sold entree: " << curr->data.GetName() << endl;
      if(curr->quantity > 1){
        int quant = curr->quantity - 1;
        curr->quantity = quant;
      } else {
        if(prev == nullptr){
          top = curr->next;
          delete curr;
        }
        else{
          node* temp = curr->next;
          prev->next = temp;
          delete curr;
        }
      }
      return temp;
    }
  }
  return temp;
}

void Vendor::PowerOutage(){
  node* curr = top;
  while (curr != nullptr) {
    curr->data.PowerDown();
    curr = curr->next;
  }
}
void Vendor::CleanStock(){
  node* curr = top;
  node* prev = nullptr;
  while (curr != nullptr) {
    if(curr->data.IsExpired() == true){
      if(prev == nullptr){
        top = curr->next;
        delete curr;
      }
      else{
        node* temp = curr->next;
        prev->next = temp;
        delete curr;
      }
      uniqueEntrees--;
    }
    prev = curr;
    curr = curr->next;
  }
}


bool Vendor::IsStocked(string name) {
  node* curr = top;
  while(curr != nullptr) {
    if(curr->data.GetName() == name) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

bool Vendor::IsOnRefDisplay(string name){
  node* curr = top;
  while (curr != nullptr) {
    if(curr->data.GetName() == name){
      return curr->data.IsRefrigerated();
    }
    curr = curr->next;
  }
  return false;
}

bool Vendor::canBuy(){
  node* curr = top;
  if (curr != nullptr){
    if (curr->data.IsSpoiled() == false){
      return true;
    }
  }
  return false;
}

bool Vendor::Contains(string name, string input){
  node* curr = top;
  while (curr != nullptr)
    {
      if (curr->data.GetName() == name)
        {
          return curr->data.Contains(input);
        }
      curr = curr->next;
    }
  return false;
}

bool Vendor::ContainsIngredient(string name, string input){
  node* curr = top;
  while (curr != nullptr)
    {
      if (curr->data.GetName() == name)
        {
          return curr->data.ContainsIngredient(input);
        }
      curr = curr->next;
    }
  return false;
}

float Vendor::getPrice(string name){
  node* curr = top;
  while (curr != nullptr)
    {
      if (curr->data.GetName() == name)
        {
          return curr->price;
        }
      curr = curr->next;
    }
  return -1;
}

void Vendor::Setup(string filePath){
  ifstream infile(filePath);
  string line;
  int skipHeader = 0;
  while (getline(infile, line)){
    stringstream ss;
    ss.str(line);
    char delim = '\t';
    string item;
    int count = 0;
    string name;
    float nutrition[11];
    float numberofservings;
    float calories;
    float totalfat;
    float satfat;
    float transfat;
    float cholest;
    float sodium;
    float totcarb;
    float fiber;
    float totsugars;
    float protein;
    string ingreds;
    string contains = "";
    if (skipHeader != 0){
      while (getline(ss, item, delim)){
        if (count == 0){
          name = item;
        } else if (count > 0 && count < 12){
          nutrition[count - 1] = stof(item);
        } else if (count == 12){
          ingreds = item;
        } else {
          contains = item;
        }
        count++;
      }
      date expir;
      expir.year = 3902;
      expir.month = 12;
      expir.day = 2;
      Entree temp(name, true, true, true, expir, ingreds, nutrition, contains);
      Load(temp, 10, 2);
      contains = "";
    }
    skipHeader++;
  }
  cout << endl;
  infile.close();
}

string Vendor::getTop(){
  node* curr = top;
  if (curr != nullptr){
    return curr->data.GetName();
  }
  return "";
}


float Vendor::checkNutrition(string name, string input){
  node* curr = top;
  while (curr != nullptr)
    {
      if (curr->data.GetName() == name)
        {
          return curr->data.checkNutrients(input);
        }
      curr = curr->next;
    }
  return -1;
}

Vendor Vendor::operator+(const Vendor& b){
  Vendor local(b);

  node* lastNode = local.top;
  while (lastNode->next != nullptr) {
    lastNode = lastNode->next;
  }

  node* copyptr = top;
  node* curr = lastNode;
  while(copyptr != nullptr) {
    node* newPtr = new node;
    newPtr->data = Entree(copyptr->data);
    newPtr->price = copyptr->price;
    newPtr->quantity = copyptr->quantity;
    newPtr->next = nullptr;
    if (lastNode != nullptr){
      lastNode->next = newPtr;
    } else {
      lastNode = newPtr;
    }
    lastNode = lastNode->next;
    copyptr = copyptr->next;
  }
  
  // go through the list of entrees in one vendor and add it to the other vendor
  // local.Load()
  return local;
}


bool Vendor::operator==(const Vendor& b){
  node* curr = top;
  node* copyptr = b.top;
  while (curr != nullptr && copyptr != nullptr){
    if (curr->data.GetName() != copyptr->data.GetName()){
      return false;
    }
    curr = curr->next;
    copyptr = copyptr->next;
  }
  if (curr != nullptr || copyptr != nullptr){
    return false;
  }
  return true;
}

bool Vendor::operator!=(const Vendor& b){
  node* curr = top;
  node* copyptr = b.top;
  while (curr == nullptr && copyptr == nullptr){
    if (curr->data.GetName() == copyptr->data.GetName()){
      return false;
    }
    curr = curr->next;
    copyptr = copyptr->next;
  }
  return true;
}

Vendor& Vendor::operator+=(const Vendor& b){
  node* lastNode = top;
  while (lastNode->next != nullptr) {
    lastNode = lastNode->next;
  }

  node* copyptr = b.top;
  node* curr = lastNode;
  while(copyptr != nullptr) {
    node* newPtr = new node;
    newPtr->data = Entree(copyptr->data);
    newPtr->price = copyptr->price;
    newPtr->quantity = copyptr->quantity;
    newPtr->next = nullptr;
    if (lastNode != nullptr){
      lastNode->next = newPtr;
    } else {
      lastNode = newPtr;
    }
    lastNode = lastNode->next;
    copyptr = copyptr->next;
  }
  return *this;
}


ostream& operator<<(ostream& out, const Vendor& vendor){
  node* curr = vendor.top;
  while( curr != nullptr){
    out << curr->data.GetName() << endl;
    curr = curr->next;
  }
  
  return out;
}
