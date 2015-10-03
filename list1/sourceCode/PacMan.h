#ifndef MY_PACMAN_DEF
#define MY_PACMAN_DEF

#include <iostream>   
#include <string>     

using namespace std;

struct PacMan {
  int r, c;

  int getRow();
  int getColumn();
  void moveTo(int nr, int nc);
  PacMan(int row, int column) : r(row), c(column) {};
  void print();
};

#endif