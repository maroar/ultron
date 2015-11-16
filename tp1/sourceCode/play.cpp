#include "play.h"
#include <list>
#include <algorithm>

using namespace std;

//bool      flyBlack, flyWhite;
color     acolor, winner, cenemy;
gameStage ostage;
int       trow, tcol, drow, dcol, cntp;
state*    cstate;
state*    ostate;

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
///////////////////////////////////////////////////////////////////////////
bool hasWinner() {
  //return false;
  //list<pnode> ls;
  numBlack = numWhite = 0;
  for(int i = 0; i < 24; i++) {
    if(cstate->p[i] == black) {
      numBlack++;
    }
    else if(cstate->p[i] == white) {
      numWhite++;
    }
  }
  
  if(numWhite < 4 && currentStage == movement) {
    flyWhite = true;
  }

  if(numBlack < 4 && currentStage == movement) {
    flyBlack = true;
  }

  if(currentStage == movement) {
    if(numWhite < 3) {
      cout << "number of pieces" << endl;
      winner = black;
      return true;
    }
    else if(numBlack < 3) {
      cout << "number of pieces" << endl;
      winner = white;
      return true;
    }
  }

  pnode n = new node(cstate->makeState(nullptr), nullptr);
  //pnode n2 = new node(cstate->makeState(nullptr), nullptr);
  //ls = successorMovement(n1, white);
  if(successorMovementNumber(n, white, flyWhite) == 0 && currentStage == movement) {
    cout << "no moves" << endl;
    winner = black;
    return true;
  }
  //ls.remove_if(deleteAll);
  
  //ls = successorMovement(n2, black);
  if(successorMovementNumber(n, black, flyBlack) == 0 && currentStage == movement) {
    cout << "no moves" << endl;
    winner = white;
    return true;
  }
  //ls.remove_if(deleteAll);
  
  delete n;
  //delete n2;
// draw game
  return false;
}

bool isAValidMove() {
  switch(currentStage) {
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
    return flyWhite;
  else
    return flyBlack;
}

bool thereIsAMill(color c) {
  if(c == white) {
    if(cstate->numberOfWhiteMills() > ostate->numberOfWhiteMills())
      return true;
    else
      return false; 
  } 
  else {
    if(cstate->numberOfBlackMills() > ostate->numberOfBlackMills())
      return true;
    else
      return false; 
  }
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
  return currentStage;
}

int searchSpot(int r, int c) {
  if(r < 0) {
    return 99;
  }

  for(int i = 0; i < 24; i++) {
    if((scenario[i]->r == r) && (scenario[i]->c == c)) {
      return i;
    }
  }
  cout << "ERROR: searchSpot, can not find this spot! -_-" << endl;
  exit(1);
  return 99;
}

void addPieceForPlayer() {
  numberOfPieces++;
}

void botPlays(color c) {
  state* old = nullptr;
  if(ostate)
    old = ostate;

  ostate  = cstate;
  pnode  root = new node(cstate, nullptr);
  action* a;

  a      = alphaBetaSearch(root, c);
  cout << a->toString() << endl;
  cstate = ostate->makeState(a);

  lnodes.remove_if(deleteAll);
  if(old)
    delete old;
}

int numPlayerPieces(color c) {
  switch(c) {
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
  switch(currentStage) {
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
  currentStage   = placement;
  cstate         = st;
  flyBlack           = false;
  flyWhite           = false;
  numberOfPieces = 0;
  cntp           = 0;

  while(true) {
    if(currentStage == placement && numberOfPieces == 18) {
      currentStage = movement;
    }
    else {
      addPieceForPlayer();
    }
   MILL:
    if(acolor == mcolor) {
      //cout << "********************************* player1" << endl;
      playerPlays();
      //cout << "********************************* player2" << endl;
      system("clear");
    }
    else {
      //cout << "111111111111111111111111111111111 bot" << endl;
      //cstate->print();
      botPlays(cenemy);
      //cout << "222222222222222222222222222222222 bot" << endl;
    }

    if(currentStage == mill) {
      currentStage = ostage;
    }

    if(hasWinner()) break;

    if(thereIsAMill(acolor)) {
      ostage = currentStage;
      currentStage  = mill;
      goto MILL;
    }

    acolor = invertColor(acolor);
  }

  if(winner == black) {
    cout << "black is the winner!" << endl;
  }
  else if(winner == white) {
    cout << "white is the winner!" << endl;
  }
  else {
    cout << "draw game!" << endl;
  }
}

void playerPlays() {
  char fWhite = flyWhite ? '*' : ' ';
  char fBlack = flyBlack ? '*' : ' ';
  cout << "White" << fWhite << ": " << numWhite << " | Black" 
       << fBlack << ": " << numBlack << endl;
  cstate->print();
  readMove();
  if(!isAValidMove()) {
    cout << "ERROR: playerPlays, bad move! =P" << endl;
    exit(1);
  }

  state* old = nullptr;
  if(ostate)
   old = ostate;
  ostate = cstate;

  int    t, f;
  t = searchSpot(trow, tcol);
  f = searchSpot(drow, dcol);

  action* a = new action(returnKindOfAction(currentStage), mcolor, f, t);
  cstate    = ostate->makeState(a);
  //cout << a->toString() << endl;

  delete a;
  if(old)
    delete old;
}

void readMove() {
  switch(currentStage) {
    case placement:
      cout << "placement (" 
           << (9-cntp) 
           << "):\nrow column" 
           << endl;
      cin >> trow;
      cin >> tcol;
      drow = -1;
      dcol = -1;
      cntp++;
      if(!verify(trow, tcol)) {
        cout << "ERROR: readMove, wrong place." << endl;
        exit(1);
      }

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