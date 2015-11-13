#include "scenario.h"
#include "init.h"
#include <iostream>

using namespace std;

// scenario
spot***             mills;
vector<pointerSpot> scenario;

void createScenario(char** m) {
  int spotCount = 0, cntWhite = 0, cntBlack = 0;
  for(int r = 0; r < 7; r++) {
    for(int c = 0; c < 7; c++) {
      switch(m[r][c]) {
        case 'B':
          createSpot(r, c, spotCount);
          cntBlack++;
          spotCount++;
          break;
        case 'W':
          createSpot(r, c, spotCount);
          cntWhite++;
          spotCount++;
          break;
        case 'o':
          createSpot(r, c, spotCount);
          spotCount++;
          break;
        default:
          break;
      }
    }
  }
  createSpotEdges();
  createMills();
}

void createMill(unsigned i, unsigned a, unsigned b, unsigned c) {
  mills[i][0] = scenario[a];
  mills[i][1] = scenario[b];
  mills[i][2] = scenario[c];
}

void createMills() {
  createMill(0,  0,  1,  2);
  createMill(1,  2,  14, 23);
  createMill(2,  21, 22, 23);
  createMill(3,  0,  9,  21);
  createMill(4,  3,  4,  5);
  createMill(5,  5,  13, 20);
  createMill(6,  18, 19, 20);
  createMill(7,  3,  10, 18);
  createMill(8,  6,  7,  8);
  createMill(9,  8,  12, 17);
  createMill(10, 15, 16, 17);
  createMill(11, 6,  11, 15);
  createMill(12, 1,  4,  7);
  createMill(13, 12, 13, 14);
  createMill(14, 16, 19, 22);
  createMill(15, 9,  10, 11);
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

void printMills() {
  cout << "mills:" << endl;
  for(int i = 0; i < 16; i++) {
    cout << "id: " << i << " | " 
         << mills[i][0]->id << " "
         << mills[i][1]->id << " "
         << mills[i][2]->id << " "
         << endl;
  }
}

void printScenario() {
  cout << "scenario:" << endl;
  for(int i = 0; i < 24; i++) {
    cout << "id: " << scenario[i]->id << " "
         << "r: " << scenario[i]->r << " "
         << "c: " << scenario[i]->c << " | "
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