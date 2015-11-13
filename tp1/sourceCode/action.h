#ifndef MY_ACTION
#define MY_ACTION

#include "init.h"

typedef enum kindOfAction {
  put_piece = 0,
  move_piece,
  remove_piece,
  none
} kindOfAction;

struct action {
  kindOfAction kind;
  color        acolor; // action color
  unsigned     o, t;// origin | target
  action(kindOfAction k, color c, unsigned orig, unsigned target) 
    : kind(k), acolor(c), o(orig), t(target) {};
  void print();
};

#endif
