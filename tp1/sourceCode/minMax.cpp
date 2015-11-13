#include "minMax.h"
#include "searchGraph.h"

bool terminalTest() {
  return false;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int utility(pnode n) {
  return n->score();
}

int maxValue(pnode n, int a, int b, unsigned p, color c) {
  if(p >= MAX_DEPTH)
    return utility(n);

  int v = NINF;
  
  for(auto it : successor(n, c)) {
    v = max(v, minValue(it, a, b, ++p, invertColor(c)));
    if(v >= b)
      return v;
    a = max(a, v);
  }
  return v;
}

int minValue(pnode n, int a, int b, unsigned p, color c) {
  if(terminalTest() || p >= MAX_DEPTH)
    return utility(n);

  int v = PINF;

  for(auto it : successor(n, c)) {
    v = min(v, maxValue(it, a, b, ++p, invertColor(c)));
    if(v < a)
      return v;
    b = min(b, v);
  }
  return v;
}

action* alphaBetaSearch(pnode r, color c) {
  int v = maxValue(r, NINF, PINF, 0, c);
  for(auto it : r->succ) {
    if(it->score() == v) {
      return it->act;
    }
  }
  return nullptr;
}
