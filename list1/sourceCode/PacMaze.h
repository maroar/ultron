#ifndef MY_SCENARIO_DEF
#define MY_SCENARIO_DEF
#define GOAL '0'

#include <algorithm>
#include <fstream>
#include <functional>
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
  int r,c;

  bool isGoal(int coordX, int coordY);
  Goal(int row, int column) : r(row), c(column) {};
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

extern int                 expandCount;
extern int                 numNodes;
extern list<pair<int,int>> explored;

void printFringe();
bool alreadyVisited(int row, int column);

struct Node {
  bool        visited;
  direction   d;
  float       cost, hcost;
  int         r, c, id, expandAt;
  list<Node*> children;
  Node        *parent;

  Node(Node* p, float pcost, int row, int column, direction _direction) : parent(p), cost(pcost), r(row), c(column), d(_direction) {
    id = numNodes++;
    hcost = distanceToGoal() + cost;
    visited = false;
  };
  ~Node();
  float  distanceToGoal();
  string toDot();
  string toString();
  void   expand();
  void   printChildren();
  void   printDot();
  void   removeNodeFromFringe();
};

struct SearchGraph {
  Node    *root;

  SearchGraph(int row, int column, float initCost) {
    numNodes = 0;
    expandCount = 0;
    root = new Node(NULL, initCost, row, column, NO_MOVE);
  };
  ~SearchGraph();
  bool nodeIsGoal(Node *n);
  void printDot();
  void solution(Node *n);
  // bfs
  Node* bfsRemove();
  void  bfs();
  void  bfsInsert(Node *n);
  void  bfsInsertList(list<Node*>& l);
  // dfs
  Node* dfsRemove();
  void  dfs();
  void  dfsInsert(Node *n);
  void  dfsInsertList(list<Node*>& l);
  // astar
  Node* astarRemove();
  void  astar();
  void  astarInsert(Node *n);
  void  astarInsertList(list<Node*>& l);
};

extern SearchGraph *sg;

#endif