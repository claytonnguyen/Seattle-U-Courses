#include <cstring>
#include <iostream>
#include <climits>

// Optimal Substructure:
// b(i) = minimum number of rubies taken for this ith index, for all
// rubies 0 to j.
// b(i) = min(b(i - w[j]) + 1 (if w[j] <= i), b[i])
// trying to find b(length(dollars))
// Time Efficiency
// O(Remainder*Dollars) = idx*dollars

using namespace std;

int rd1(int idx, int dollars, int type[]){
  int dp[dollars + 1];
  dp[0] = 0;
  for(int rem = 1; rem <= dollars; rem++){
        int minimum = INT_MAX;
      for(int value = 0; value < idx; value++){
        if(type[value] <= rem){
                minimum = min(dp[rem - type[value]] + 1, minimum);
        }
        dp[rem] = minimum;
      }
  }
  return dp[dollars];
}

int main(){
  int values, dollars, num;
  cin >> values >> dollars;
  int type[values];
  for(int i = 0; i < values; i++){
    cin >> num;
    type[i] = num;
  }
  cout << rd1(values, dollars, type) << endl;
  return 0;
}

