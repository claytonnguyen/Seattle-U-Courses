//AUTHOR: Clay Nguyen
//DATE: October 22, 2021
//REVISION HISTORY: FIRST SUBMISSION

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "entree.h"
using namespace std;

Entree::Entree(){}
Entree::Entree(string _name, 
               bool _refrigeration, 
               bool _refrigerated, 
               bool _electricity, 
               date _expiration,
               string _ingredients,
               float _nutritionStats[],
               string _contains)
{
  name = _name;
  refrigerationNeeded = _refrigeration;
  refrigerated = _refrigerated;
  electricity = _electricity;
  powerIsOff = false;
  expiration = _expiration;  
  ingredients = _ingredients;
  for (int i = 0; i < 11; i++){
    nutritionStats[i] = _nutritionStats[i];
  }
  contains = _contains;
}

void Entree::copy(const Entree& src) {
  name = src.name;
  refrigerationNeeded = src.refrigerationNeeded;
  refrigerated = src.refrigerated;
  electricity = src.electricity;
  powerIsOff = src.powerIsOff;
  expiration = src.expiration;
  ingredients = src.ingredients;
  for (int i = 0; i < 11; i++){
    nutritionStats[i] = src.nutritionStats[i];
  }
  contains = src.contains;
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
    if(expiration.month < 11) {
      if(expiration.day < 15) {
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}

bool Entree::IsSpoiled() {
    if (refrigerationNeeded == true)
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

bool Entree::ContainsIngredient(string ingredient) {
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

bool Entree::Contains(string ingredient) {
  stringstream ss (contains);

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
  if (!name.empty()){
    return name;
  } else {
    return "";
  }
}


float Entree::checkNutrients(string input){
  if(input == "carbs")
    {
      int num = static_cast<int>(TotCarb);
      return nutritionStats[num];
    }
  else if (input == "sugar")
    {
      int num = static_cast<int>(TotSugars);
      return nutritionStats[num];
    }
  else
    {
      return -1;
    }
}

Entree Entree::operator+(const Entree& b){
  // add the nutritional stats together

  Entree local(b);
  local.name = local.name + " and " + name;
  int size = 11;
  for (int i = 0; i < size; i++){
    local.nutritionStats[i] = local.nutritionStats[i] + nutritionStats[i];
  }
  return local;
}

bool Entree::operator<(const Entree& b){
  // checks to see if the number of calories is less than the right side
  if (nutritionStats[1] < b.nutritionStats[1]){
    return true;
  } else {
    return false;
  }
}

bool Entree::operator<=(const Entree& b){
  // checks to see if the number of calories is less than or equal to                            
  // the right side
  if (nutritionStats[1] <= b.nutritionStats[1]){
    return true;
  } else {
    return false;
  }
}

bool Entree::operator==(const Entree& b){
  // checks to see if the objects are the same
  if (name != b.name){
    return false;
  }
  for (int i = 0; i < 11; i++){
    if (nutritionStats[i] != b.nutritionStats[i]){
      return false;
    }
  }
  return true;
}

bool Entree::operator!=(const Entree& b){
  // checks to see if the objects are not the same
  if (name == b.name){
    return false;
  }
  for (int i = 0; i < 11; i++){
    if (nutritionStats[i] == b.nutritionStats[i]){
      return false;
    }
  }
  return true;
}

bool Entree::operator>(const Entree& b){
  // checks to see if the number of calories is greater than the right side 
  if (nutritionStats[1] > b.nutritionStats[1]){
    return true;
  } else {
    return false;
  }
}

bool Entree::operator>=(const Entree& b){
  // checks to see if the number of calories is greater than or equal to
  // the right side
  if (nutritionStats[1] >= b.nutritionStats[1]){
    return true;
  } else {
    return false;
  }
}

Entree& Entree::operator+=(const Entree& b){
  // adds the nutrients from object b to this object.
  // entree.Calories += b.Calories
  name = name + " and " + b.name;
  int size = 11;
  for (int i = 0; i < size; i++){
    nutritionStats[i] = nutritionStats[i] + b.nutritionStats[i];
  }
  return *this;
}

ostream& operator<<(ostream& out, const Entree& entree){
  out << "Entree(s): " << entree.name << endl << "Number of Servings: " << entree.nutritionStats[0] << endl <<
    "Calories: " << entree.nutritionStats[1] << endl << "TotalFat(g): " << entree.nutritionStats[2] << endl <<
    "SatFat(g): " << entree.nutritionStats[3] << endl << "TransFat(g): " << entree.nutritionStats[4] << endl <<
    "Cholest(mg): " << entree.nutritionStats[5] << endl << "Sodium(mg): " << entree.nutritionStats[6] << endl <<
    "TotCarb(g): " << entree.nutritionStats[7] << endl << "Fiber(g): " << entree.nutritionStats[8] << endl <<
    "TotSugars(g): " << entree.nutritionStats[9] << endl << "Protein(g): " << entree.nutritionStats[10] << endl;
  return out;
}
