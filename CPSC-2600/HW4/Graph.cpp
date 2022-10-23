#include <iostream>
#include <fstream>
#include <queue>
#include "Graph.h"

using namespace std;

Graph::Graph(){
  vertices = 0;
  matrix = nullptr;
}
Graph::~Graph(){
  for(int i = 0; i < vertices; i++){
    delete[] matrix[i];
  }
  delete matrix;
  delete visitedArr;
  delete vArr;
}
void Graph::load(char *fileName){
  ifstream file;
  file.open(fileName);
  file >> vertices;

  matrix = new int*[vertices];
  for(int i = 0; i < vertices; i++){
    matrix[i] = new int[vertices];
  }
  for(int i = 0; i < vertices; i++){
    for(int j = 0; j < vertices; j++){
      matrix[i][j] = 0;
    }
  }
  int num1, num2;
  while(file >> num1 >> num2){
    matrix[num1][num2] = 1;
    matrix[num2][num1] = 1;
  }
  file.close();
  visitedArr = new bool[vertices];
  vArr = new bool[vertices];
  for(int i = 0; i < vertices; i++){
    visitedArr[i] = false;
    vArr[i] = false;
  }
  cout << fileName << ":" << endl;
}
void Graph::display(){
  for(int i = 0; i < vertices; i++){
    for(int j = 0; j < vertices; j++){
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}
void Graph::displayDFS(int vertex){
  cout << vertex << " ";
  visitedArr[vertex] = true;
  for(int i = 0; i < vertices; i++){
    if(matrix[vertex][i] && visitedArr[i] != true){
      displayDFS(i);
    }
  }
}
void Graph::displayBFS(int vertex){
  queue <int> q;
  int popped;
  q.push(vertex);
  vArr[vertex] = true;
  while(!q.empty()){
    popped = q.front();
    q.pop();
    cout << popped << " ";
    for(int i = 0; i < vertices; i++){
      if(matrix[popped][i] == 1 && vArr[i] != true){
        q.push(i);
        vArr[i] = true;
      }
    }
  }
}
