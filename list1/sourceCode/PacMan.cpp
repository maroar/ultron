#include "PacMan.h"

int PacMan::getRow(){
  return r;
}

int PacMan::getColumn() {
  return c;
}

void PacMan::moveTo(int nr, int nc) {
  r = nr;
  c = nc;
}

void PacMan::print() {
  cout << "row: " << r << " column: " << c << endl;;
}