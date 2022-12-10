#include<iostream>
#include<cstring>

// Optimal Substructure:
// f(i) = max{1, max { (j = 0 to i - 1) f(runner) > f(curr) ? 1 : 0 + f(runner)}, f(curr)}
// trying to find f(length(numbers))
// Time Efficiency:
// O(n) = n^2 = n is the length of the sequence

using namespace std;

int chain(int i, int seq[]){
  int dp[i];
  memset(dp, 0, sizeof(dp));
  int max = 0;
  for(int curr = 1; curr <= i; curr++){
    for(int runner = 0; runner < curr; runner++){
      int &x = dp[curr - 1];
        if(seq[curr - 1] < seq[runner] && dp[curr - 1] < dp[runner] + 1){
                x = dp[runner] + 1;
        }
    }
  }
  for(int k = 0; k < i; k++){
    if(max < dp[k]){
      max = dp[k];
    }
  }
  return max + 1;
}

int main(){
  int numbers = 0, num, seqLength;
  cin >> numbers;
  int seq[numbers];
  for(int i = 0; i < numbers; i++){
    cin >> num;
    seq[i] = num;
  }
  seqLength = sizeof(seq)/sizeof(int);
  cout << chain(seqLength, seq) << endl;
  return 0;
}
