//
// Created by Clayton Nguyen on 10/1/22.
//

#include <iostream>

using namespace std;

typedef long long LL;

// Function sums up all the elements in the array
LL sum_all(int A[], int lo, int hi){
    LL sum = 0;
    for (int i = lo; i <= hi; i++){
        sum += A[i];
    }
    return sum;
}

// Function finds the current largest sum spanning two
// contiguous arrays and returns it
LL find_max_cross_sum(int A[], int lo, int mid, int hi){
    LL left_sum = -1000000000;
    LL sum = 0;
    for (int k = mid; k >= lo; k--){
        sum = sum + A[k];
        if (sum > left_sum){
            left_sum = sum;
        }
    }
    LL right_sum = -10000000000;
    sum = 0;
    for (int j = mid + 1; j <= hi; j++){
        sum = sum + A[j];
        if (sum > right_sum){
            right_sum = sum;
        }
    }
    return left_sum + right_sum;
}

// Function is recursively called to find the maximum sum
// in an array that is not circular. This max subarray could
// be in the left subarray, right subarray, or crossing both.
LL find_max_sum(int A[], int lo, int hi){
    if (hi == lo){
        return A[lo];
    } else {
        int mid = lo + (hi - lo) / 2;
        LL left_sum = find_max_sum(A, lo, mid);
        LL right_sum = find_max_sum(A, mid + 1, hi);
        LL cross_sum = find_max_cross_sum(A, lo, mid,hi);
        if (left_sum >= right_sum && left_sum >= cross_sum){
            return left_sum;
        } else if (right_sum >= left_sum && right_sum >= cross_sum){
            return right_sum;
        } else {
            return cross_sum;
        }
    }
}

// Function finds the current smallest sum spanning two
// contiguous arrays and returns it
LL find_min_cross_sum(int A[], int lo, int mid, int hi){
    LL left_sum = 10000000000;
    LL sum = 0;
    for (int k = mid; k >= lo; k--){
        sum = sum + A[k];
        if (sum < left_sum){
            left_sum = sum;
        }
    }
    LL right_sum = 100000000000;
    sum = 0;
    for (int j = mid + 1; j <= hi; j++){
        sum = sum + A[j];
        if (sum < right_sum){
            right_sum = sum;
        }
    }
    return left_sum + right_sum;
}

// Function is recursively called to find the minimum sum
// in an array that is not circular. This max subarray could
// be in the left subarray, right subarray, or crossing both.
LL find_min_sum(int A[], int lo, int hi){
    if (hi == lo){
        return A[lo];
    } else {
        int mid = lo + (hi - lo) / 2;
        LL left_sum = find_min_sum(A, lo, mid);
        LL right_sum = find_min_sum(A, mid + 1, hi);
        LL cross_sum = find_min_cross_sum(A, lo, mid,hi);
        if (left_sum <= right_sum && left_sum <= cross_sum){
            return left_sum;
        } else if (right_sum <= left_sum && right_sum <= cross_sum){
            return right_sum;
        } else {
            return cross_sum;
        }
    }
}

// The largest sum subarray could either be in the left subarray,
// right subarray, spanning the two subarrays at the middle, 
// or could be spanning the two subarrays at the ends (circular)
// Finding the max sum subarray is the easy way to find the max sum
// of a subarray that takes care of the first three cases, to get
// the last case where it spans between the end of the right subarray
// and the left subarray, one can simply find the min subarray 
// of the array and subtract it from the total sum of the array,
// since that is what a max sum subarray doesn't want (min subarray)

int main(){
    int n;
    cin >> n;
    int A[n];
    for (int i = 0; i < n; i++){
        cin >> A[i];
    }
    LL middle_min = find_min_sum(A, 0, n - 1);
    LL middle_max = find_max_sum(A, 0, n - 1);
    LL sum = sum_all(A, 0, n - 1);
    LL max = sum - middle_min; // if the maximum spans across n-1 to 0
    if (middle_max > max)
        cout << middle_max << endl;
    else
        cout << max << endl;
    return 0;
}
