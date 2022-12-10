// NAME: Clay Nguyen
// DATE: 15 October 2020
// FILE NAME: HW#3

#include <iostream>
using namespace std;

void mergesort(int array[], int start, int end);

void merge(int array[], int lStart, int lEnd, int rStart, int rEnd);

int main(){
  int SIZE, number;
  cout << "Input array size: ";
  cin >> SIZE;
  int *array = new int[SIZE];
  for(int i = 0; i < SIZE; i++){
    cout << "Input number for index " << i
         << ": ";
    cin >> number;
    array[i] = number;
  }
  mergesort(array, 0, SIZE - 1);
  for(int i = 0; i < SIZE; i++){
    cout << "[" << array[i] << "] ";
  }
  cout << endl << endl;
  delete [] array;
}

void mergesort(int array[], int start, int end){
  if(start < end){
    int middle = ((end - start)/2) + start;
    mergesort(array, start, middle);
    mergesort(array, (middle + 1), end);
    merge(array, start, middle, (middle + 1), end);
  }
}

void merge(int array[], int lStart, int lEnd, int rStart, int rEnd){
  while(lStart <= lEnd && rStart <= rEnd){
    if(array[lStart] <= array[rStart]){
      lStart++;
    }
    else{
      int index = rStart;
      int num = array[rStart];
      while(index != lStart){
        array[index] = array[index - 1];
        index--;
      }
      array[lStart] = num;
      lStart++;
      lEnd++;
      rStart++;
    }
  }
}
