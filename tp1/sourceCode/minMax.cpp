#include "minMax.h"
#include "searchGraph.h"

#include <iostream>
using namespace std;

color tcolor;

bool terminalTest() {
  return false;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int utility(pnode n, color c) {
  return n->score(c);
}

int maxValue(pnode n, int a, int b, unsigned p, color c) {
  if(p >= MAX_DEPTH) {
    n->x = true;
    return utility(n, tcolor);
  }

  int v = NINF;
  
  for(auto it : successor(n, c)) {
    it->shp = -1;
    v = max(v, minValue(it, a, b, p+1, invertColor(c)));
    //v = max(v, minValue(it, a, b, p+1, c));
    if(v >= b)
      return v;
    a = max(a, v);
  }
  n->st->score = v;
  return v;
}

int minValue(pnode n, int a, int b, unsigned p, color c) {
  if(terminalTest() || p >= MAX_DEPTH) {
    n->x = true;
    return utility(n, tcolor);
  }

  int v = PINF;

  for(auto it : successor(n, c)) {
    it->shp = 1;
    v = min(v, maxValue(it, a, b, p+1, invertColor(c)));
    //v = min(v, maxValue(it, a, b, p+1, c));
    if(v < a)
      return v;
    b = min(b, v);
  }
  n->st->score = v;
  return v;
}

action* alphaBetaSearch(pnode r, color c) {
  r->shp = 1;
  tcolor = c;
  int v = maxValue(r, NINF, PINF, 0, c);
  r->st->score = v;
//  cout << "v: " << v << endl; 
  for(auto it : r->succ) {
    if(it->score(tcolor) == v) {
      return it->act;
    }
  }
  cout << "ERROR: alphaBetaSearch, returning null pointer! ouch!" << endl;
  exit(1);
  return nullptr;
}
