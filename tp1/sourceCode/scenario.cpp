#include "scenario.h"
#include <iostream>

using namespace std;

// scenario
spot***              mills;
vector<pointerSpot> scenario;

void createPiece(color pcolor, int r, int c, int id, int colorCount) {
  switch(pcolor) {
    case black:
      bp[colorCount] = new piece();
      break;
    case white:
      ///////////////////////////////////////////////
      break;
    default:
      cout << "ERROR: createPiece, wrong color" << endl;
      exit(1);
  }
}

void createScenario(char** m) {
  int spotCount = 0, cntWhite = 0, cntBlack = 0;
  for(int r = 0; r < 7; r++) {
    for(int c = 0; c < 7; c++) {
      switch(m[r][c]) {
        case 'B':
          createPiece(black, r, c, spotCount, cntBlack);
          scenario[spotCount]->occupied = true;
          cntBlack++;
          spotCount++;
          break;
        case 'W':
          createPiece(white, r, c, spotCount, cntWhite);
          scenario[spotCount]->occupied = true;
          cntWhite++;
          spotCount++;
          break;
        case 'o':
          createSpot(r, c, spotCount);
          scenario[spotCount]->occupied = false;
          spotCount++;
          break;
        default:
          break;
      }
    }
  }
  createSpotEdges();
}

void createSpotEdges() {
  scenario[0]->addNeighbor(1);
  scenario[0]->addNeighbor(9);
  scenario[1]->addNeighbor(0);
  scenario[1]->addNeighbor(2);
  scenario[1]->addNeighbor(4);
  scenario[2]->addNeighbor(1);
  scenario[2]->addNeighbor(14);
  scenario[3]->addNeighbor(10);
  scenario[3]->addNeighbor(4);
  scenario[4]->addNeighbor(1);
  scenario[4]->addNeighbor(3);
  scenario[4]->addNeighbor(5);
  scenario[4]->addNeighbor(7);
  scenario[5]->addNeighbor(4);
  scenario[5]->addNeighbor(13);
  scenario[6]->addNeighbor(7);
  scenario[6]->addNeighbor(11);
  scenario[7]->addNeighbor(4);
  scenario[7]->addNeighbor(6);
  scenario[7]->addNeighbor(8);
  scenario[8]->addNeighbor(7);
  scenario[8]->addNeighbor(12);
  scenario[9]->addNeighbor(0);
  scenario[9]->addNeighbor(10);
  scenario[9]->addNeighbor(21);
  scenario[10]->addNeighbor(3);
  scenario[10]->addNeighbor(9);
  scenario[10]->addNeighbor(11);
  scenario[10]->addNeighbor(18);
  scenario[11]->addNeighbor(6);
  scenario[11]->addNeighbor(10);
  scenario[11]->addNeighbor(15);
  scenario[12]->addNeighbor(8);
  scenario[12]->addNeighbor(13);
  scenario[12]->addNeighbor(17);
  scenario[13]->addNeighbor(5);
  scenario[13]->addNeighbor(12);
  scenario[13]->addNeighbor(14);
  scenario[13]->addNeighbor(20);
  scenario[14]->addNeighbor(2);
  scenario[14]->addNeighbor(13);
  scenario[14]->addNeighbor(23);
  scenario[15]->addNeighbor(11);
  scenario[15]->addNeighbor(16);
  scenario[16]->addNeighbor(15);
  scenario[16]->addNeighbor(17);
  scenario[16]->addNeighbor(19);
  scenario[17]->addNeighbor(12);
  scenario[17]->addNeighbor(16);
  scenario[18]->addNeighbor(10);
  scenario[18]->addNeighbor(19);
  scenario[19]->addNeighbor(16);
  scenario[19]->addNeighbor(18);
  scenario[19]->addNeighbor(20);
  scenario[19]->addNeighbor(22);
  scenario[20]->addNeighbor(13);
  scenario[20]->addNeighbor(19);
  scenario[21]->addNeighbor(9);
  scenario[21]->addNeighbor(22);
  scenario[22]->addNeighbor(19);
  scenario[22]->addNeighbor(21);
  scenario[22]->addNeighbor(23);
  scenario[23]->addNeighbor(14);
  scenario[23]->addNeighbor(22);
}

void createSpot(int r, int c, int cnt) {
  scenario[cnt] = new spot(r, c, cnt);
}

void printScenario() {
  for(int i = 0; i < 24; i++) {
    cout << "id: " << scenario[i]->id << " "
         << "r: " << scenario[i]->r << " "
         << "c: " << scenario[i]->c << " "
         << scenario[i]->occupiedStr() << " "
         << scenario[i]->neighborsToStr()
         << endl;
  }
}

void setDownScenario() {
  for(int i = 0; i < 16; i++) {
    free(mills[i]);
  }
  free(mills);
}

void setUpScenario() {
  scenario.reserve(24);
  mills = (pointerSpot**) malloc(16 * sizeof(pointerSpot*));
  for(int i = 0; i < 16; i++) {
    mills[i] =  (pointerSpot*) malloc(3 * sizeof(spot***));
  }
}