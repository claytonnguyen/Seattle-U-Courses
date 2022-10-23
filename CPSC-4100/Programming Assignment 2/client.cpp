#include <cstdlib>
#include <set>
#include <algorithm>
#include <cassert>
#include <iostream>
#include "hw3.h"

#define MX 100000
int A[MX];

void killTree(Node* root) {
	if (root) {
		killTree(root->left_);
		killTree(root->right_);
		delete root;
	}
}
Node* search(Node* root, int val) {
	if (!root)
		return NULL;
	if (root->data_ == val)
		return root;
	if (val < root->data_)
		return search(root->left_, val);
	return search(root->right_, val); 
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " [data.in] [function_mask_string]" << endl;
		return -1;  
	}
	freopen(argv[1], "r", stdin);
	string mask = "ZGSK";
    if (argc >= 3)
		mask = string(argv[2]);
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> A[i];
	sort(A, A+N); 
	Node* root = Prog3::createBalancedBst(A, N); 
	assert(root);
    
	for (int i = 0; i < M; i++) { //handle M queries
		char op;
		int a, b;
		cin >> op;
        bool flag = (mask.find(op) != string::npos);
		switch(op) {
        case 'Z': {//zigzagLevelTraversal
          if (flag) {
            Prog3::zigzagLevelTraversal(root);
            cout << endl;
          }
          break;
        }
        case 'G': {//gap
          cin >> a >> b;
          Node* p = search(root, a);
          Node* q = search(root, b);
          assert(p && q);
          if (flag)
            cout << Prog3::gap(root, p, q) << endl; 
          break;
        }
        case 'S': {//pathSum
          cin >> a >> b;
          Node* p = search(root, a);
          Node* q = search(root, b);
          assert(p && q);
          if (flag)
            cout << Prog3::pathSum(root, p, q) << endl; 
          break;
        }
        case 'K': {//kthLargest
          cin >> a;
          if (flag)
            cout << Prog3::kthLargest(root, a) << endl;
          break;
        }
        case 'B': {//bonus
#ifdef _BONUS
          if (flag)
            cout << Prog3::bonus(root) << endl;
#endif
          break;
        }
        default:
          assert(0);
		}
	}
	killTree(root);
	return 0;
}
