/*
 *  *File: hw3.h
 *
 */

#ifndef _HW3_H
#define _HW3_H
//#define _BONUS   //uncomment this line if you have solved the bonus problem
using namespace std;

struct Node {
  int data_;
  Node* left_;
  Node* right_;
  int size_;
  void* extra_; //only useful for the bonus problem. Ignore it for other problems.
};

class Prog3 {
 public:
  static Node* createBalancedBst(int* A, int n);
  static void zigzagLevelTraversal(Node* root);
  static int gap(Node* root, Node* p, Node* q);
  static long long pathSum(Node* root, Node* p, Node* q);
  static int kthLargest(Node* root, int k);
#ifdef _BONUS
  static int bonus(Node* root);
#endif
};

#endif
