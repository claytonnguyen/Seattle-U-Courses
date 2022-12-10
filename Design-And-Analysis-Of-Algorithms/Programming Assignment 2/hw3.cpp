//
// Created by Clayton Nguyen on 10/10/22.
//

#include <iostream>
#include <stack>
#include "hw3.h"

// helper function that sums up the path of a root node
// to end node
long long sum(Node * root, Node * find){
    if (root == nullptr){
        return 0;
    }
    if (root == find){
        return root->data_;
    }
    if (find->data_ > root->data_){
        return root->data_ + sum(root->right_, find);
    } else {
        return root->data_ + sum(root->left_, find);
    }
}

// helper function that sums up the gap between the
// root node and end node
int gsum(Node * root, Node * find){
  if (root == nullptr){
        return 0;
    }
    if (root == find){
        return 0;
    }
    if (find->data_ > root->data_){
        return 1 + gsum(root->right_, find);
    } else {
        return 1 + gsum(root->left_, find);
    }
}

// cuts the array into two and passes it into the recursive
// function, making the array smaller by half each time until
// the size is only 1.
Node *Prog3::createBalancedBst(int *A, int n) {
    // check if n is divisible by 2 and change size_ accordingly
  if (n <= 1){
    if (n == 0) {
      return nullptr;
    }
    int mid = (n - 1) / 2;
    Node* curr = new Node;
        curr->data_ = A[mid];
        curr->size_ = 1;
        curr->left_ = nullptr;
        curr->right_ = nullptr;
        return curr;
    } else {
        int mid = (n - 1) / 2;
        Node *curr = new Node;
        curr->data_ = A[mid];
        curr->size_ = n;
        int* lArr = new int[(n - 1)/2];
        int* rArr = new int[(n - 1) - mid];
        for (int j = 0; j < mid; j++){
            lArr[j] = A[j];
        }
        int l = 0;
        for (int k = mid + 1; k < n; k++){
            rArr[l++] = A[k];
        }
        Node *left = createBalancedBst(lArr, (n - 1) / 2);
        Node *right = createBalancedBst(rArr, (n - 1) - mid);
        curr->left_ = left;
        curr->right_ = right;
        delete [] lArr;
        delete [] rArr;
        return curr;
    }
}

// Uses two stacks to traverse the tree and also inversely push its children onto
// opposite stack based on the stack direction you are popping from. Zigging and zagging.
void Prog3::zigzagLevelTraversal(Node *root) {
  stack<Node *> curr, next;
  bool first = false;
    curr.push(root);
    while (!curr.empty() || !next.empty()){
        while(!curr.empty()) {
          Node * print = curr.top();
          
            if (print->left_ != nullptr) next.push(print->left_);
            if (print->right_ != nullptr) next.push(print->right_);
            curr.pop();
            if (first == true){
              cout << " " << print->data_;
            } else {
              cout << print->data_;
              first = !first;
            }
        }

        while(!next.empty()){
            Node * print = next.top();
            if (print->right_ != nullptr) curr.push(print->right_);
            if (print->left_ != nullptr) curr.push(print->left_);
            next.pop();
            cout << " " << print->data_;
        }

    }
}

// first find the Lowest Common Ancestor then find the path to both nodes
// in terms of levels away from the LCA
int Prog3::gap(Node *root, Node *p, Node *q) {
  if (root == nullptr){
    return 0;
  }
  if (p->data_ > root->data_ && q->data_ > root->data_){
    return gap(root->right_, p, q);
  }
  else if (p->data_ < root->data_ && q->data_ < root->data_){
    return gap(root->left_, p, q);
  }
  else {
    if (root == nullptr) {
      return 0;
    }
    if (root->data_ == q->data_) {
      return gsum(root, p);
    } else if (root->data_ == p->data_){
      return gsum(root, q);
    } else {
      return gsum(root, q) + gsum(root, p);
    }
  }
  return 0;
}

// first find the Lowest Common Ancestor then find the path sum to both nodes
// in terms of the sum from the LCA to both nodes p and q
long long Prog3::pathSum(Node *root, Node *p, Node *q) {
  if (root == nullptr){
    return 0;
  }
  if (p->data_ == q->data_){
    return q->data_;
  }
  if (p->data_ > root->data_ && q->data_ > root->data_){
    return pathSum(root->right_, p, q);
  } else if (p->data_ < root->data_ && q->data_ < root->data_){
    return pathSum(root->left_, p, q);
  } else {
    if (root == nullptr) {
      return 0;
    }
    if (root == q) {
      return sum(root, p);
    } else if (root == p){
      return sum(root, q);
    } else {
      return sum(root, q) + sum(root, p) - root->data_;
    }
  }
  return root->data_;
}

// Function finds if the right most node is the kth largest element
// if not, will go to the left if k > r (modifying the k to be k - r)
// and to the right if k < r.
// If k == r, return the data at the node
int Prog3::kthLargest(Node *root, int k) {
  //cout << ":" << endl;
  if (root == nullptr){
        return 0;
    }
    int r = (root->right_ ? root->right_->size_ : 0) + 1;
    if (r == k){
        return root->data_;
    }
    return k > r ? kthLargest(root->left_, k - r) : kthLargest(root->right_, k);
}

