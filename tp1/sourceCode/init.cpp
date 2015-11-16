#include "init.h"
#include <iostream>

bool          flyWhite, flyBlack;
char**        board;
color         mcolor;
gameStage     currentStage;
int           numberOfPieces, numBlack, numWhite;
oldMove       oldmove[3];
ppiece*       bp;
ppiece*       wp;
string        colorStr, stageStr;

void allocPlayersPieces() {
  bp = (ppiece*) malloc(numBlack * sizeof(ppiece));
  wp = (ppiece*) malloc(numWhite * sizeof(ppiece));
}

color invertColor(color c) {
  return (c == black) ? white : black;
}

unsigned mrand() {
  return (unsigned) rand() % 10;
}

void printBoard() {
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      cout << board[i][j];
    }
    cout << endl;
  }
}

void printColor(color c) {
  if(c == white) {
    cout << "white" << endl;
  } else if (c == black) {
    cout << "black" << endl;
  } else {
    cout << "nocolor" << endl;
  }
}

void printInput() {
  cout << colorStr << " ";
  cout << stageStr << " ";
  if(stageStr.compare("placement") == 0) {
    cout << numberOfPieces;
  }
  cout << endl;
  printMove(0);
  printMove(1);
  printMove(2);
  printBoard();
}

void printMColor() {
  printColor(mcolor);
}

void printMove(unsigned index) {
  /*if(oldmove[index].player.compare("none") == 0) {
    cout << "none" << endl;
    return;
  }
  cout << oldmove[index].stage << " ";
  cout << oldmove[index].row << " ";
  cout << oldmove[index].column << endl;*/
}

void readBoard() {
  char c;
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      cin >> c;
      board[i][j] = c;
      if(c == 'B') {
        numBlack++;
      }
      else if(c == 'W') {
        numWhite++;
      }
    }
  }
}

void readInputFile() {
  cin >> colorStr;
  cin >> stageStr;
  if(stageStr.compare("placement") == 0) {
    cin >> numberOfPieces;
  }
  readMove(0);
  readMove(1);
  readMove(2);
  readBoard();
  setUpVariables();
}

void readMove(unsigned index) {
  string str;

  cin >> str;  
  if(str.compare("none") == 0) {
    oldmove[index].none = true;
    return;
  }
  if(str.compare("black") == 0) {
    oldmove[index].player = black;
  }
  else {
    oldmove[index].player = white;
  }

  cin >> str;
  if(str.compare("placement") == 0) {
    oldmove[index].stage = placement;
  }
  else if(str.compare("mill") == 0) {
    oldmove[index].stage = mill;
  }
  else {
    oldmove[index].stage = movement;
    cin >> oldmove[index].orow;
    cin >> oldmove[index].ocolumn;
  }

  oldmove[index].none = false;
  cin >> oldmove[index].row;
  cin >> oldmove[index].column;
}

void setDown() {
  for(int i = 0; i < 7; i++) {
    free(board[i]);
  }
  free(board);
  /*for(int i = 0; i < numBlack; i++) {
    delete bp[i];
  }
  for(int i = 0; i < numwhite; i++) {
    delete wp[i];
  }*/
  free(bp);
  free(wp);
}

void setUp() {
  srand(time(NULL));
  flyWhite = flyBlack = false;
  numBlack = numWhite = 0;
  board = (char**) malloc(7 * sizeof(char*));
  for(int i = 0; i < 7; i++) {
    board[i] = (char*) malloc(7 * sizeof(char));
  }
}

void setUpVariables() {
  //game stage
  if(stageStr.compare("placement") == 0) {
    currentStage = placement;
  } 
  else if(stageStr.compare("movement") == 0) {
    currentStage = movement;
  }
  else {
    currentStage = mill;
  }
  //set my color
  if(colorStr.compare("white") == 0) {
    mcolor = white;
  }
  else {
    mcolor = black;
  }
  //set fly state
  if(numBlack == 3) {
    flyBlack = true;
  }
  if(numWhite == 3) {
    flyWhite = true;
  }
  allocPlayersPieces();
}