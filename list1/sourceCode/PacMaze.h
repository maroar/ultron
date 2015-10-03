#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF
#define GOAL '0'

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
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
  int       r, c;

  Move(direction _direction, int row, int column) : d(_direction), r(row), c(column){}
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
  
  PacMaze(char* infile, int row, int column) : inputFile(infile) {
    readScenario();
    findGoal();
    pacMan = new PacMan(row, column);
  };
  ~PacMaze();
  bool canMoveTo(int x, int y, direction d);
  int  movePacManTo(direction d);
  int  successor(int x, int y);
  void expand();
  void findGoal();
  void print();
  void printScenario();
  void printSuccessor();
  void putPacManInScenario();
  void readScenario();
  void removePacManFromScenario();
};

extern PacMaze     *pacMaze;
// exerc 2
struct Node;
struct SearchGraph;

extern int                 numNodes;
extern list<pair<int,int>> visited;
extern list<Node*>         frontier;

void printFrontier();
bool alreadyVisited(int id);

struct Node {
  direction   d;
  int         cost, r, c, id;
  list<Node*> children;
  Node        *parent;

  Node(Node* p, int pcost, int row, int column, direction _direction) : parent(p), cost(pcost), r(row), c(column), d(_direction) {
    id = numNodes++;
  };
  ~Node();
  string toDot();
  string toString();
  void   expand();
  void   printChildren();
  void   printDot();
  void   removeNodeFromFrontier();
};

struct SearchGraph {
  Node    *root;

  SearchGraph(int row, int column, int initCost) {
    numNodes=0;
    root = new Node(NULL, initCost, row, column, NO_MOVE);
    frontier.push_back(root);
  };
  ~SearchGraph();
  void printDot();
};

extern SearchGraph *sg;

#endif