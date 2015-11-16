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

string colorStr(color c) {
  if(c == white)
    return "white";
  else if(c == black)
    return "black";
  else
    return "nocolor";
}

void movePiece(unsigned orow, unsigned ocolumn, unsigned trow, unsigned tcolumn) {
  cout << orow << " " << ocolumn << " " << trow << " " << tcolumn; 
}

void removePiece(unsigned trow, unsigned tcolumn) {
  cout << trow << " " << tcolumn;
}

void putPiece(unsigned row, unsigned column) {
  cout << row << " " << column;
}

string kindOfActionToString(kindOfAction kind) {
  switch(kind) {
    case put_piece:
      return "placement";
    case move_piece:
      return "movement";
    case remove_piece:
      return "mill";
    default:
      return "none";
  }
}

string action::toString() {
  int trow, tcolumn, orow, ocolumn;
  trow    = scenario[t]->r;
  tcolumn = scenario[t]->c;

  string str = colorStr(acolor);
  str += " ";
  str += kindOfActionToString(kind);

  if(kind == move_piece) {
    orow    = scenario[o]->r;
    ocolumn = scenario[o]->c;
    str += " ";
    str += to_string(orow);
    str += " ";
    str += to_string(ocolumn);
  }

  str += " ";
  str += to_string(trow);
  str += " ";
  str += to_string(tcolumn);
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