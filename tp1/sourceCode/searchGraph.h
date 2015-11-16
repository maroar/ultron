#ifndef MY_SEARCH_GRAPH
#define MY_SEARCH_GRAPH

#include "action.h"
#include "state.h"

struct  node;
typedef node* pnode;

struct node {
  static unsigned cnt;
  action*         act;
  bool            x;
  int             shp;
  list<pnode>     succ;
  pnode           parent;
  state*          st;
  unsigned        id;

  node(state* st_, action* act_);
  ~node();
  int   score(color c);
  pnode makeNode(state* s, action* a);
  void  printDot();
};

extern list<pnode> lnodes;
list<pnode> successorPlacement(pnode n, color c);
list<pnode> successorMovement(pnode n, color c);
list<pnode> successorMill(pnode n, color c);
list<pnode> successor(pnode n, color c);
int         successorMovementNumber(pnode n, color c, bool fly);
#endif
