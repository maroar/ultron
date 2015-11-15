#ifndef MY_STATE
#define MY_STATE

#include "init.h"
#include "action.h"

#include <vector>

using namespace std;

struct state {
  int           score;
  int           cntBlackMills, cntWhiteMills;
  state*        parent;
  vector<color> p;

  state() : score(1), cntBlackMills(-1), cntWhiteMills(-1) {
    p.reserve(24);
  }
  bool   inMill(unsigned i, color c);
  bool   matchMill(unsigned i, color c);
  bool   spotIsFree(unsigned i);
  int    getScoreMill(color c);
  int    getScoreMove(color c);
  int    getScorePlacement(color c);
  int    numberOfBlackMills();
  int    numberOfMills(color c);
  int    numberOfWhiteMills();
  int    pointsForMills(color c);
  int    pointsForMobility(unsigned i);
  int    pointsForPlaces(color c);
  state* makeState(action* a);
  void   init();
  void   init(char** m);
  void   move(action* a);
  void   put(action* a);
  void   remove(action* a);
  void   print();
  void   printDot(int id);
  void   print2(color c);
  void   print(unsigned i);
};

#endif