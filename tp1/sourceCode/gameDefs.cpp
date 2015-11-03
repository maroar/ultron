#include "gameDefs.h"
#include <iostream>

void readMove(oldMove* move) {
  //
}

void readBoard() {
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 7; j++) {
      cin >> board[i][j];
    }
  }
}

void readInputFile() {
  cin >> colorStr;
  cin >> stageStr;
  if(true) {
    cin >> numberOfPieces;
  }
  //readMove(&move[0]);
  //readMove(&move[1]);
  //readMove(&move[2]);
  readBoard();
}