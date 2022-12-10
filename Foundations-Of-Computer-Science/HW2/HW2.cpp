// Name: Clayton Nguyen
// File Name: HW2.cpp
// Date: 23 September 2020

#include <iostream>
using namespace std;

void conversion(int);

int main(){
  int setA = 0;
  int userInput;
  int setB = 0;
  int unioned, intersection, difference;

  cout << "Welcome to HW 2: programming! Given subsets A and B of a universal set with 10 elements " << endl
       << "{0,1,2,3,4,5,6,7,8,9}, we will use bit strings to find A U B, A n B, and A - B." << endl
       << "Users will be asked to populate each set. For example, if the user enters 1, 2, 6, the bit " << endl
       << "string will display from left to right and display 0110001000." << endl << endl;
  
  while(userInput != -1){
    cout << "Please enter a number for set A (enter -1 to stop): ";
    cin >> userInput;
    for(int j = 0; j < userInput; j++){
      setA |= (1 << userInput);
    }
  }
  cout << endl;
  userInput = 0;
  while(userInput != -1){
    cout << "Please enter a number for set B (enter -1 to stop): ";
    cin >> userInput;
    for(int i = 0; i < userInput; i++){
      setB |= (1 << userInput);
    }
  }
  cout << endl;
  unioned = setA | setB;
  intersection = setA & setB;
  difference = setA & (~setB);
  cout << "Set A:" << "\t\t";
  conversion(setA);
  cout << endl << "Set B:" << "\t\t";
  conversion(setB);
  cout << endl << endl << "Union:" << "\t\t";
  conversion(unioned);
  cout<< endl << "Intersection:" << "\t";
  conversion(intersection);
  cout << endl << "Difference:" << "\t";
  conversion(difference);
  cout << endl;
}

void conversion(int set){
  for(int k = 0; k < 10; k++)
    cout << ((set >> k) & 1);
}
