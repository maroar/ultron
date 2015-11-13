#include "action.h"
#include "scenario.h"

#include <iostream>

using namespace std;

void movePiece(unsigned orow, unsigned ocolumn, unsigned trow, unsigned tcolumn) {
  cout << orow << " " << ocolumn << " " << trow << " " << tcolumn; 
}

void removePiece(unsigned trow, unsigned tcolumn) {
  cout << trow << " " << tcolumn;
}

void putPiece(unsigned row, unsigned column) {
  cout << row << " " << column;
}

void action::print() {
  int trow, tcolumn, orow, ocolumn;
  switch(kind) {
    case put_piece:
      trow    = scenario[t]->r;
      tcolumn = scenario[t]->c;
      putPiece(trow, tcolumn);
      break;
    case remove_piece:
      trow    = scenario[t]->r;
      tcolumn = scenario[t]->c;
      removePiece(trow, tcolumn);
      break;
    case move_piece:
      orow    = scenario[o]->r;
      ocolumn = scenario[o]->c;
      trow    = scenario[t]->r;
      tcolumn = scenario[t]->c;
      movePiece(orow, ocolumn, trow, tcolumn);
      break;
    default:
      cout << "ERROR: executeAction" << endl;
      exit(1);
  }
}