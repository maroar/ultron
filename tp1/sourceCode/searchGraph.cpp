#include "searchGraph.h"
#include "scenario.h"

#include <string>
#include <iostream>

using namespace std;

// node
unsigned node::cnt = 0;
list<pnode>    lnodes;

int node::score(color c) {
  switch(currentStage) {
    case placement:
      return st->getScorePlacement(c);
    case movement:
      return st->getScoreMove(c);
    case mill:
      return st->getScoreMill(c);
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
      a  = new action(put_piece, c, 99, i);
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

  if(!st->getFly(c)) {
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
  }
  else {
    for(int i = 0; i < 24; i++) {
      if(n->st->p[i] == nocolor) {
        for(int j = 0; j < 24; j++) {
          if(n->st->p[j] == c) {
            a  = new action(move_piece, c, j, i);
            st = n->st->makeState(a);
            pn  = n->makeNode(st, a);
            n->succ.push_back(pn);
            ls.push_back(pn);
          }
        }
      } 
    }
  }

  return ls;
}

list<pnode> successorMill(pnode n, color c) {
  list<unsigned> all;
  list<unsigned> outOfMills;
  list<pnode>    ls;
  state*         st;
  action*        a;
  pnode          pn;
  color          enemy = invertColor(c);
 
  for(int i = 0; i < 24; i++) { // iterate over all spots in the board
    if(n->st->p[i] == enemy) {
      if(!n->st->inMill(i, enemy)) {
        outOfMills.push_back(i);
      }
      all.push_back(i);
    }
  }

  if(outOfMills.size() != 0) {
    for(auto it : outOfMills) {
      a  = new action(remove_piece, enemy, 99, it);
      st = n->st->makeState(a);
      pn = n->makeNode(st, a);
      n->succ.push_back(pn);
      ls.push_back(pn);
    }
  }
  else {
    for(auto it : all) {
      a  = new action(remove_piece, enemy, 99, it);
      st = n->st->makeState(a);
      pn = n->makeNode(st, a);
      n->succ.push_back(pn);
      ls.push_back(pn);
    }
  }

  return ls;
}

int successorMovementNumber(pnode n, color c, bool fly) { // considerar vôo
  int ret = 0;
  
  if(fly) {
    for(int i = 0; i < 24; i++) {
      if(n->st->p[i] == nocolor)
        ret++;
    }
  }
  else {
    for(int i = 0; i < 24; i++) { // iterate over all spots in the board
      if(n->st->p[i] == c) { // select all of spots with the colors that I want
        for(auto it : scenario[i]->neighbors) { // iterate over neighbors spots
          if(n->st->spotIsFree(it->id)) { // select free spots to move
            ret++;
          }
        }
      }
    }
  }

  return ret;
}

node::node(state* st_, action* act_) : st(st_), act(act_), shp(0), x(false) {
  id = cnt++;
}

node::~node() {
  delete act; 
  delete st;
}

pnode node::makeNode(state* s, action* a) {
  pnode n = new node(s, a);
  n->parent = this;
  lnodes.push_back(n);
  return n;
}

string shape(int s) {
  if(s == 1)
    return "triangle";
  else if(s == -1)
    return "invtriangle";
  else
    return "box";
}

string fill(bool x) {
  if(x)
    return "red";
  else
    return "blue";
}

void node::printDot() {
  cout << " n" << id << " [shape=" << shape(shp) << " color=" << fill(x) << " label=\"" << st->score << "\\n " << act->toString() << "\"]" << endl;
  if(parent)
    cout << " n" << id << " -- n" << parent->id << endl; 
}
