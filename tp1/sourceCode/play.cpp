#include "play.h"
#include <list>
#include <algorithm>

using namespace std;

bool      bfly, wfly;
color     acolor, winner, cenemy;
gameStage stage;
int       trow, tcol, drow, dcol;
state*    cstate;

static bool deleteAll(node* theElement) {
  delete theElement; 
  return true; 
}

bool canIMoveToThere() {
  unsigned target = searchSpot(trow, tcol);
  if(cstate->spotIsFree(target)) {
    if(myColorCanfly()) {
      return true;
    }
    else {
      if(scenario[searchSpot(drow, dcol)]->hasNeighbor(target)) {
        return true;
      }
      else {
        cout << "ERROR: canIMoveToThere, are you kidding? The spot is so far! o0" << endl;
        return false;
      }
    }
  }
  else {
    cout << "ERROR: canIMoveToThere, busy spot!" << endl;
    return false;
  }
}

bool canIPutThere() {
  if(cstate->spotIsFree(searchSpot(trow, tcol))) {
    return true;
  }
  else {
    cout << "ERROR: you can not put a piece there!" << endl;
    return false;
  }
}

bool canIRemoveIt() {
  color          enemy       = invertColor(mcolor);
  list<unsigned> all;
  list<unsigned> outOfMills;
  int            spot        = searchSpot(trow, tcol);

  for(int i = 0; i < 24; i++) { // iterate over all spots in the board
    if(cstate->p[i] == enemy) { // select all of spots with the colors that I want
      if(!cstate->inMill(i, enemy)) {
        outOfMills.push_back(i);
      }
      all.push_back(i);
    }
  }

  if((find(outOfMills.begin(), outOfMills.end(), spot) != outOfMills.end())) {
    return true;
  }
  if(outOfMills.size() == 0) {
    return true;
  }
  else {
    cout << "ERROR: canIRemoveIt, you can not remove this piece! =x" << endl;
    return false;
  }
}

bool  hasWinner() {
  return false;
}

bool isAValidMove() {
  switch(stage) {
    case placement:
      return canIPutThere();
      break;
    case movement:
      return canIMoveToThere();
      break;
    case mill:
      return canIRemoveIt();
      break;
  }
}

bool myColorCanfly() {
  if(mcolor == white)
    return wfly;
  else
    return bfly;
}

bool verify(int r, int c) {
  for(int i = 0; i < 24; i++) {
    if(scenario[i]->r == r && scenario[i]->c == c) {
      return true;
    }
  }

  return false;
}

color getActualColor(){
  return acolor;
}

gameStage getStage() {
  return stage;
}

int searchSpot(int r, int c) {
  if(r < 0) {
    cout << "ERROR: searchSpot, can not find a spot to a negative value! -_-" << endl;
    exit(1);

    return 1000000;
  }

  for(int i = 0; i < 24; i++) {
    if((scenario[i]->r == r) && (scenario[i]->c == c)) {
      return i;
    }
  }
  cout << "ERROR: searchSpot, can not find this spot! -_-" << endl;
  exit(1);
  return 10000000;
}

void addPieceForPlayer(color c) {
  numberOfPieces++;
  switch(c) {
    case black:
      numBlack++;
      break;
    case white:
      numWhite++;
      break;
  }
}

void botPlays(color c) {
  state* old  = cstate;
  pnode  root = new node(cstate, nullptr);
  action* a;

  a      = alphaBetaSearch(root, c);
  cstate = old->makeState(a);
  /*for(auto it : lnodes) {
    delete it;
    lnodes.clear();
  }*/
  lnodes.remove_if(deleteAll);
  delete root;
}

int numPlayerPieces() {
  switch(mcolor) {
    case black:
      return numBlack;
      break;
    case white:
      return numWhite;
      break;
    default:
      cout << "ERROR: numPlayerPieces, bad color!" << endl;
  }
}

void makeMove() {
  switch(stage) {
    case placement:
      //
      break;
    case movement:
      //
      break;
    case mill:
      //
      break;
  }
}

void play(color c, state* st) {
  acolor         = c;
  cenemy         = invertColor(mcolor);
  stage          = placement;
  cstate         = st;
  bfly           = false;
  wfly           = false;
  numberOfPieces = 0;
  numBlack       = 0;
  numWhite       = 0;

//int cnt = 0;
  while(true) {
    //system("clear");
    if(acolor == mcolor) {
      //cout << "********************************* player" << endl;
      playerPlays();
    }
    else {
      //cout << "111111111111111111111111111111111 bot" << endl;
      //cstate->print();
      botPlays(cenemy);
      //cout << "222222222222222222222222222222222 bot" << endl;
    }

    if(hasWinner()) break;

    // has a new mill
    
    if( == 18) {
      stage = movement;
    }
    
    acolor = invertColor(acolor);

    //cnt++; if(cnt > 6) break;    
  }
}

void playerPlays() {
  system("clear");
  cstate->print();
  readMove();
  if(!isAValidMove()) {
    cout << "ERROR: playerPlays, bad move! =P" << endl;
    exit(1);
  }

  state* old = cstate;
  int    t, f;
  t = searchSpot(trow, tcol);
  f = searchSpot(trow, tcol);

  action* a = new action(returnKindOfAction(stage), mcolor, f, t);
  cstate    = old->makeState(a);

  delete a;
  delete old;
}

void readMove() {
  switch(stage) {
    case placement:
      cout << "placement (" 
           << (9-numPlayerPieces()) 
           << "):\nrow column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      drow = -1;
      dcol = -1;

      if(!verify(trow, tcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }

      addPieceForPlayer(mcolor);

      break;
    case movement:
      cout << "movement:" << endl 
           << "from_row from_column to_row to_column" 
           << endl;
      cin >> drow;
      cin >> dcol;
      cin >> trow;
      cin >> tcol;

      if(!verify(trow, tcol) || !verify(drow, dcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }

      break;
    case mill:
      cout << "mill:\n" 
           << "row column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      drow = -1;
      dcol = -1;

      if(!verify(trow, tcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }

      break;
  }
}