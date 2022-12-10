////
//// Created by Clayton Nguyen on 10/1/22.
////
#include <iostream>

using namespace std;

// Function keeps track of the highest running sum of the
// highest right list element minus the lowest left list
// element, giving the current largest single transaction
// until you merge the biggest two lists
int mergeCount(int A[], int lo, int mid, int hi){
    int* temp = new int[hi-lo+1];
    int left = lo, right = mid+1, it = 0, sum = 0;
    if ((A[hi] - A[lo] >= sum)){
        sum = A[hi] - A[left];
    }
    while(left<=mid && right<=hi){
        if(A[left] <= A[right]){
            temp[it++] = A[left++];
        }
        else
            temp[it++] = A[right++];
    }
    while(left<=mid) temp[it++] = A[left++];
    while(right<=hi) temp[it++] = A[right++];
    for (int k = 0; k < hi-lo+1; k++){
        A[lo+k] = temp[k];
    }
    delete [] temp;
    return sum;
}

// Recursively calls this function to find out if the max sum
// is in the left array, right array, or straddling between the two
int find_max_sum(int A[], int lo, int hi){
    int sum = 0;
    if (lo >= hi){
        return 0;
    }
    int mid = lo + (hi - lo)/2;
    int left = find_max_sum(A, lo, mid);
    int right = find_max_sum(A, mid + 1, hi);
    int both = mergeCount(A, lo, mid, hi);
    if (left >= right && left >= both){
        sum = left;
    } else if ( right >= left && right >= both){
        sum = right;
    } else{
        sum = both;
    }
    return sum;
}

int main(){
    int n;
    cin >> n;
    int A[n];
    for (int i = 0; i < n; i++){
        cin >> A[i];
    }
    int result = find_max_sum(A, 0, n - 1);
    cout << result << endl;
    return 0;
}
