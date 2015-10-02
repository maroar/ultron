#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF
#define GOAL '0'

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <stdio.h>
#include "PacMan.h"

using namespace std;

struct Goal;
struct Move;
struct PacMaze;
struct SearchGraph;

typedef enum direction {
  NO_MOVE = 0, 
  NORTH, 
  SOUTH, 
  EAST, 
  WEST
} direction;

struct Move {
  direction d;
  int        x, y;
  Move(direction _direction, int cx, int cy) : d(_direction), x(cx), y(cy){}
  string toString();
};
extern list<Move*>  moves;

struct Goal {
  int x,y;

  bool isGoal(int coordX, int coordY);
  Goal(int coordX, int coordY) : x(coordX), y(coordY) {};
  void print();
};

struct PacMaze {
  char         charBeforePacMan;
  char*        inputFile;
  char**       scenario;
  int          rows, columns;
  Goal*        goal;
  PacMan*      pacMan;
  SearchGraph* sg;
  
  PacMaze(char* infile, int x, int y) : inputFile(infile) {
    readScenario();
    findGoal();
    pacMan = new PacMan(x, y);
    successor();
  };
  ~PacMaze();
  bool canMoveTo(direction d);
  int  movePacManTo(direction d);
  int  successor();
  void expand();
  void findGoal();
  void print();
  void printScenario();
  void printSuccessor();
  void putPacManInScenario();
  void readScenario();
  void removePacManFromScenario();
};
// exerc 2
extern int numNodes;

struct Node {
  direction d;
  int cost, x, y, id;
  list<Node*> frontier;
  Node *parent;

  Node(Node* p, int pcost, int cx, int cy, direction _direction) : parent(p), cost(pcost), x(cx), y(cy), d(_direction) {
    id = numNodes++;
  };
  ~Node();
  void expand();
  void printDot();
  string toString();
};

struct SearchGraph {
  Node *root;

  SearchGraph(int x, int y) {
    numNodes=0;
    root = new Node(NULL, 0, x, y, NO_MOVE);
    root->expand();
  };
  ~SearchGraph();
  void printDot();
};

#endif