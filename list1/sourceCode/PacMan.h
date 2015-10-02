#ifndef MY_PACMAN_DEF
#define MY_PACMAN_DEF

#include <iostream>   
#include <string>     

using namespace std;

struct PacMan {
  int x, y;

  int getX();
  int getY();
  void moveTo(int nx, int ny);
  PacMan(int locationX, int locationY) : x(locationX), y(locationY) {};
  void print();
};

#endif