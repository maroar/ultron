#include "searchGraph.h"
#include "scenario.h"

// node
unsigned node::cnt = 0;
list<pnode>    lnodes;

int node::score() {
  switch(currentStage) {
    case placement:
      return st->getScorePlacement(act->acolor);
    case movement:
      return st->getScoreMove(act->acolor);
    case mill:
      return st->getScoreMill(act->acolor);
  }
}

list<pnode> successor(pnode n, color c) {
  switch(currentStage) {
    case placement:
      return successorPlacement(n, c);
    case movement:
      return successorMovement(n, c);
    case mill:
      return successorMill(n, c);
  }
}

list<pnode> successorPlacement(pnode n, color c) {
  list<pnode> ls;
  state*      st;
  action*     a;
  pnode       pn;

  for(int i = 0; i < 24; i++) { // iterate over all spots in the board
    if(n->st->p[i] == nocolor) { // select all of free spots in the board
      a  = new action(put_piece, c, -1, i);
      st = n->st->makeState(a);
      //st->print();
      pn  = n->makeNode(st, a);
      n->succ.push_back(pn);
      ls.push_back(pn);
    }
  }
  return ls;
}

list<pnode> successorMovement(pnode n, color c) { // considerar vôo
  list<pnode> ls;
  state*      st;
  action*     a;
  pnode       pn;

  for(int i = 0; i < 24; i++) { // iterate over all spots in the board
    if(n->st->p[i] == c) { // select all of spots with the colors that I want
      for(auto it : scenario[i]->neighbors) { // iterate over neighbors spots
        if(n->st->spotIsFree(it->id)) { // select free spots to move
          a  = new action(move_piece, c, i, it->id);
          st = n->st->makeState(a);
          pn  = n->makeNode(st, a);
          n->succ.push_back(pn);
          ls.push_back(pn);
          //st->print();
        }
      }
    }
  }
  return ls;
}

list<pnode> successorMill(pnode n, color c) {
  list<pnode> all;
  list<pnode> pieces;
  state*      st;
  action*     a;
  pnode       pn;
  color       enemy = invertColor(c);

  /*for(int i = 0; i < 24; i++) { // iterate over all spots in the board
    if(n->st->p[i] == enemy) {
      if(!matchMill()) {

      }
      all.push_back(n);
    }
  }*/
  return all;
}

node::node(state* st_, action* act_) : st(st_), act(act_) {
  id = cnt++;
}

node::~node() {
  delete act; 
  delete st;
}

pnode node::makeNode(state* s, action* a) {
  pnode n = new node(s, a);
  lnodes.push_back(n);
  return n;
}
