//
// Created by Clayton Nguyen on 10/1/22.
//

#include <iostream>

typedef long long LL;

using namespace std;

// Function keeps sorts the two lists, but before it sorts
// it compares the head elements of both lists and if the
// left head is less than the head of the right list, then
// the left head is greater than (hi - right + 1) and will
// return the running sum at the end
LL mergeCount(int A[], int lo, int mid, int hi){
    int* temp = new int[hi-lo+1];
    int left = lo, right = mid+1, it = 0;
    LL sum = 0;
    while(left<=mid && right<=hi){
        if(A[left] < A[right]){
            sum += (hi - right + 1);
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

// Recursively calls this function to find all positive capital
// gains in the left list because the right list should be sorted
// by the time it gets to comparing both the two sorted lists
LL divconq(int A[], int lo, int hi){
    // merge sort
    if (lo >= hi){
        return 0;
    }
    int mid = lo + (hi - lo)/2;
    LL left = divconq(A, lo, mid);
    LL right = divconq(A, mid + 1, hi);
    LL both = mergeCount(A, lo, mid, hi);
    return left + right + both;
}

int main(){
    int n;
    cin >> n;
    int A[n];
    for (int i = 0; i < n; i++){
        cin >> A[i];
    }
    LL fin = divconq(A, 0, n - 1);
    cout << fin << endl;
    return 0;
}
