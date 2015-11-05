#include "init.h"
#include <iostream>

char**    board;
color     mcolor;
gameStage currentStage;
int       numberOfPieces, numBlack, numWhite;
oldMove   oldmove[3];
ppiece*   bp;
ppiece*   wp;
string    colorStr, stageStr;

void allocPlayersPieces() {
  bp = (ppiece*) malloc(numBlack * sizeof(ppiece));
  wp = (ppiece*) malloc(numWhite * sizeof(ppiece));
}

void printBoard() {
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      cout << board[i][j];
    }
    cout << endl;
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

void printMove(unsigned index) {
  if(oldmove[index].player.compare("none") == 0) {
    cout << "none" << endl;
    return;
  }
  cout << oldmove[index].stage << " ";
  cout << oldmove[index].row << " ";
  cout << oldmove[index].column << endl;
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
  cin >> oldmove[index].player;
  if(oldmove[index].player.compare("none") == 0) {
    oldmove[index].none = true;
    return;
  }
  oldmove[index].none = false;
  cin >> oldmove[index].stage;
  cin >> oldmove[index].row;
  cin >> oldmove[index].column;
}

void setDown() {
  for(int i = 0; i < 7; i++) {
    free(board[i]);
  }
  free(board);
  free(bp);
  free(wp);
}

void setUp() {
  numBlack = numWhite = 0;
  board = (char**) malloc(7 * sizeof(char*));
  for(int i = 0; i < 7; i++) {
    board[i] = (char*) malloc(7 * sizeof(char));
  }
}

void setUpVariables() {
  if(stageStr.compare("placement") == 0) {
    currentStage = placement;
  } 
  else if(stageStr.compare("movement") == 0) {
    currentStage = movement;
  }
  else {
    currentStage = mill;
  }
  if(colorStr.compare("white") == 0) {
    mcolor = white;
  }
  else {
    mcolor = black;
  }
  allocPlayersPieces();
}