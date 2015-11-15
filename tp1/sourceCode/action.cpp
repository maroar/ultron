#include "action.h"
#include "scenario.h"

#include <iostream>

using namespace std;

kindOfAction returnKindOfAction(gameStage g) {
  switch(g) {
    case placement:
      return put_piece;
      break;
    case movement:
      return move_piece;
      break;
    case mill:
      return remove_piece;
      break;
    default:
      cout << "ERROR: returnKindOfAction, wrong game stage! =/" << endl;
      exit(1);
  }
}

/*string action::kindOfActionToString() {
  switch(kind) {
    case put_piece:
      return "put";
    case move_piece:
      return "move " +;
    case remove_piece:
      return "remove";
    default:
      return "none";
  }
}*/

void movePiece(unsigned orow, unsigned ocolumn, unsigned trow, unsigned tcolumn) {
  cout << orow << " " << ocolumn << " " << trow << " " << tcolumn; 
}

void removePiece(unsigned trow, unsigned tcolumn) {
  cout << trow << " " << tcolumn;
}

void putPiece(unsigned row, unsigned column) {
  cout << row << " " << column;
}

string action::toString() {
  string str = "o: ";
  str += to_string(o);
  str += " t: ";
  str += to_string(t);

  return str;
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