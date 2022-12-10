#include <iostream>
#include <cstring>

// Structure of Optimal Solutions:
// b(j) = max{ i = 0 to i = values b(j), b(j - w[i - 1]) + b(i - 1) (if w[i - 1] <= j)}
// Trying to find b(capacity)
// Time Efficiency
// O(Values*Capacity) = values*capacity

using namespace std;

int rd2(int values, int capacity, int weight[], int benefit[]){
  int dp[capacity + 1];
  memset(dp, 0, sizeof(dp));
  for(int value = 1; value <= values; value++){
      for(int rem = capacity; rem >= 0; rem--){
        if(weight[value - 1] <= rem){
                dp[rem] = max(dp[rem - weight[value - 1]] + benefit[value - 1], dp[rem]);
        }
      }
  }
  return dp[capacity];
}

int main(){
  int values, dollars, wvalue, bvalue, i = 0;
  cin >> values >> dollars;
  values = values * 2;
  int weight[values];
  int benefit[values];
  while(i < values){
    cin >> wvalue >> bvalue;
    weight[i] = wvalue;
    benefit[i++] = bvalue;
    weight[i] = wvalue;
    benefit[i++] = bvalue;
  }

  cout << rd2(values, dollars, weight, benefit) << endl;
  return 0;
}
