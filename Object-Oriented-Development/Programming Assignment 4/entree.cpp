//AUTHOR: Clay Nguyen                                                                               
//DATE: October 22, 2021                                                                            
//REVISION HISTORY: FIRST SUBMISSION                                                                

#include <iostream>
#include <memory>
#include <sstream>
#include "entree.h"
using namespace std;

Entree::Entree(){}
Entree::Entree(string _name,
               unsigned int _price,
               bool _refrigeration,
               bool _refrigerated,
               bool _electricity,
               date _expiration,
               string _ingredients,
               string _nutritionStats)
{
  name = _name;
  price = _price;
  refrigeration = _refrigeration;
  refrigerated = _refrigerated;
  electricity = _electricity;
  powerIsOff = false;
  expiration = _expiration;
  ingredients = _ingredients;
  nutritionStats = _nutritionStats;
}

void Entree::copy(const Entree& src) {
  name = src.name;
  price = src.price;
  refrigeration = src.refrigeration;
  refrigerated = src.refrigerated;
  electricity = src.electricity;
  powerIsOff = src.powerIsOff;
  expiration = src.expiration;
  ingredients = src.ingredients;
  nutritionStats = src.nutritionStats;
}

Entree::Entree(const Entree& src) {
  copy(src);
}

Entree& Entree::operator=(const Entree& src){
  if (this == &src) return *this;
  copy(src);
  return *this;
}

bool Entree::IsExpired() {
  if(expiration.year < 2021) {
    if(expiration.month < 10) {
      if(expiration.day < 21) {
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}

bool Entree::IsSpoiled() {
    if (refrigeration == true)
    {
        if(refrigerated == true)
        {
            if(Power() == true)
            {
                return false || IsExpired();
            }
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false || IsExpired();
    }
}

void Entree::PowerDown() {
    powerIsOff = true;
}

bool Entree::Power() {
    if (electricity == true)
    {
        return !powerIsOff;
    }
    return false;
}

bool Entree::IsRefrigerated(){
  return refrigerated;
}

bool Entree::Contains(string ingredient) {
  stringstream ss (ingredients);

  string item;
  char delim = '$';

  while(getline (ss, item, delim)) {
    if(item == ingredient) {
      return true;
    }
  }
  return false;
}

string Entree::GetName() {
    return name;
}

unsigned int Entree::GetPrice() {
    return price;
}
