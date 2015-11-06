#include <string>
#include <iostream>
#include "init.h"
#include "scenario.h"
#include "mill.h"
#include "movement.h"
#include "placement.h"

int main(int argc, char** argv) {
  setUp();
  setUpScenario();
  readInputFile();
printInput();
  createScenario(board);
cout << "________________________" << endl;
printScenario();
cout << "________________________" << endl;
printMills();
  //if(verifyDrawGame())
    //return drawGame();
    
  switch(currentStage) {
    case placement:
      action_placement();
      break;
    case movement:
      action_movement();
      break;
    case mill:
      action_mill();
      break;
    default:
      cout << "ERROR: currentStage" << endl;
      exit(1);
  }
  
  setDownScenario();
  setDown();
  return 0;
}