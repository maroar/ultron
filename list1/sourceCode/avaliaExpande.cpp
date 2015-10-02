#include "PacMaze.h"
#include <string>  

using namespace std;

string::size_type sz;

int main(int argc, char** argv) {
  PacMaze     *pacMaze = new PacMaze(argv[1], stoi(argv[2], &sz), stoi(argv[3], &sz));
  SearchGraph *sg      = new SearchGraph(pacMaze->pacMan->getX(), pacMaze->pacMan->getY());
  sg->printDot();

  delete sg;
  delete pacMaze;
  return 0;
}
