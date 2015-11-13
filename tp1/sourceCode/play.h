#ifndef MY_PLAY
#define MY_PLAY

#define MAX_PIECES 9

#include <string>
#include <iostream>

#include "init.h"
#include "scenario.h"
#include "state.h"
#include "minMax.h"

bool      hasWinner();
color     getActualColor();
gameStage getStage();
int       numPlayerPieces();
void      botPlays();
void      makeMove();
void      play(color c, state* st);
void      playerPlays();
void      readMove();

#endif