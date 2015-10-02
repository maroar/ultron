#include "PacMan.h"

int PacMan::getX(){
  return x;
}

int PacMan::getY() {
  return y;
}

void PacMan::moveTo(int nx, int ny) {
  x = nx;
  y = ny;
}

void PacMan::print() {
  cout << "px: " << x << " py: " << y << endl;;
}