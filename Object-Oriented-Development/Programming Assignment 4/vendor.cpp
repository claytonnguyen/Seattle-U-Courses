//AUTHOR: Clay Nguyen                                                                               
//DATE: October 22, 2021                                                                            
//REVISION HISTORY: FIRST SUBMISSION                                                                

#include <iostream>
#include <memory>
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
bool Vendor::Load(Entree entree) {
  node* curr = top;
  node* newNode = new node;
  newNode->data = entree;
  // newNode->price = randomPrice();
  // newNode->quantity = randomQuantity();
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

bool Vendor::Sell(string name){
  node* curr = top;
  node* prev = nullptr;
  while (curr != nullptr) {
    if(curr->data.GetName() == name){
      if(!curr->data.IsSpoiled()){
        if(curr->quantity > 1){
          quantity--;
        }
        else{
          if(prev == nullptr){
            top = curr->next;
            delete curr;
          }
          else{
            node* temp = curr->next;
            prev->next = temp;
            delete curr;
          }
          quantity--;
        }
        return true;        
      }
      return false;
    }
    prev = curr;
    curr = curr->next;
  }
  return false;
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
        curr = top;
      }
      else{
        node* temp = curr->next;
        prev->next = temp;
        curr = prev;
      }
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
