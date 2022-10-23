#ifndef Graph_H
#define Graph_H

class Graph{
 private:

  int **matrix;
  bool *visitedArr;
  bool *vArr;
  int vertices;

 public:
  Graph();
  ~Graph();
  void load(char *filename);
  void display();
  void displayDFS(int vertex);
  void displayBFS(int vertex);
};

#endif
