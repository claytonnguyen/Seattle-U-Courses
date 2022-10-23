// Name: Clayton Nguyen
// File: HW.cpp
// Date: 11/6/2020

#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[]){
  Graph a;
  a.load(argv[1]);
  cout << endl << "Adjacency Matrix" << endl;
  a.display();
  cout << endl << "DFS at vertex 0: ";
  a.displayDFS(0);
  cout << endl << "BFS at vertex 0: ";
  a.displayBFS(0);
  cout << endl;
}
