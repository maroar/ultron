#ifndef MY_SEARCH_GRAPH
#define MY_SEARCH_GRAPH

#include "action.h"
#include "state.h"

struct  node;
typedef node* pnode;

struct node {
  static unsigned cnt;
  action*         act;
  list<pnode>     succ;
  state*          st;
  unsigned        id;

  node(state* st_, action* act_);
  ~node();
  int   score();
  pnode makeNode(state* s, action* a);
};

extern list<pnode> lnodes;
list<pnode> successorPlacement(pnode n, color c);
list<pnode> successorMovement(pnode n, color c);
list<pnode> successorMill(pnode n, color c);
list<pnode> successor(pnode n, color c);
#endif
