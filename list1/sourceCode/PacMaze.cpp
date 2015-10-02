#include "PacMaze.h"
list<Move*>  moves;
int numNodes;
// helper methods
string directionToString(direction d) {
  switch(d) {
    case NORTH: return "up";
    case SOUTH: return "down";
    case EAST:  return "right";
    case WEST:  return "left";
    default:    return "null";
  }
}
// Goal methods
bool Goal::isGoal(int coordX, int coordY) {
  return (coordX == x) && (coordY == y);
}

void Goal::print() {
  cout << "gx: " << x << " gy: " << y << endl;
}
// Move methods
string Move::toString() {
  string toReturn = "(";
  toReturn += directionToString(d);
  toReturn += ";";
  toReturn += to_string(x);
  toReturn += ",";
  toReturn += to_string(y);
  toReturn += ")";
  return toReturn;
}
// PacMaze methods
bool PacMaze::canMoveTo(direction d){
  switch(d) {
    case NORTH: return (scenario[(pacMan->getX()-1)%rows][pacMan->getY()]) != '#';
    case SOUTH: return (scenario[(pacMan->getX()+1)%rows][pacMan->getY()]) != '#';
    case EAST:  return (scenario[pacMan->getX()][(pacMan->getY()+1)%columns]) != '#';
    case WEST:  return (scenario[pacMan->getX()][(pacMan->getY()-1)%columns]) != '#';
    default:    return false;
  }
}

void PacMaze::findGoal() {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      if(scenario[i][j]==GOAL) {
        goal = new Goal(i, j);
        return;
      }
    }
  }
}

int PacMaze::movePacManTo(direction d) {
  if(canMoveTo(d)) {
    switch(d) {
      case NORTH: pacMan->moveTo((pacMan->getX()-1)%rows, pacMan->getY()); break;
      case SOUTH: pacMan->moveTo((pacMan->getX()+1)%rows, pacMan->getY()); break;
      case EAST:  pacMan->moveTo(pacMan->getX(), (pacMan->getY()+1)%columns); break;
      case WEST:  pacMan->moveTo(pacMan->getX(), (pacMan->getY()-1)%columns); break;
    }
    return successor();
  }
  return 0;
}

void PacMaze::print() {
  putPacManInScenario();
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      cout << scenario[i][j];
    }
    cout << endl;
  }
  removePacManFromScenario();
}

void PacMaze::putPacManInScenario() {
  charBeforePacMan = scenario[pacMan->getX()][pacMan->getY()];
  scenario[pacMan->getX()][pacMan->getY()] = 'P';
}

void PacMaze::printScenario() {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      cout << scenario[i][j];
    }
    cout << endl;
  }
}

void PacMaze::printSuccessor() {
  list<Move*>::const_iterator iterator;
  for (iterator = moves.begin(); iterator != moves.end(); ++iterator) {
    cout << (*iterator)->toString() << " ";
  }
  cout << endl;
}

void PacMaze::readScenario() {
  int i, j;
  fstream myfile(inputFile, fstream::in);
  if (myfile.is_open()) {
    myfile >> rows;
    myfile >> columns;
    scenario = new char *[rows];
    for(i = 0; i < rows; i++)
      scenario[i] = new char [columns]; 
    for(i = 0; i < rows; i++) {
      for(j = 0; j < columns; j++) {
        myfile >> skipws >> scenario[i][j];
      }
    }
    myfile.close();
  }
  else
    cout << "Unable to open file \"" << inputFile << "\"" << endl; 
}

void PacMaze::removePacManFromScenario() {
  scenario[pacMan->getX()][pacMan->getY()] = charBeforePacMan;
}

int PacMaze::successor() {
  int i = 0;
  moves.clear();
  if(canMoveTo(NORTH)){
    moves.push_back(new Move(NORTH, (pacMan->getX()-1)%rows,pacMan->getY()));
    i++;
  }
  if(canMoveTo(SOUTH)){
    moves.push_back(new Move(SOUTH, (pacMan->getX()+1)%rows,pacMan->getY()));
    i++;
  }
  if(canMoveTo(EAST)){
    moves.push_back(new Move(EAST, pacMan->getX(),(pacMan->getY()+1)%columns));
    i++;
  }
  if(canMoveTo(WEST)){
    moves.push_back(new Move(WEST, pacMan->getX(),(pacMan->getY()-1)%columns));
    i++;
  }
  return i;
}

PacMaze::~PacMaze() {
  for (int i = 0; i < rows; i++)
    delete[] scenario[i];
  delete[] scenario;
  delete pacMan;
  delete goal;
}
// exerc 2
// Node
Node::~Node() {
  if(frontier.size()!=0) {
    list<Node*>::const_iterator iterator;
    for (iterator = frontier.begin(); iterator != frontier.end(); ++iterator) {
      delete *iterator;
    }
  }
}

string Node::toString() {
  string str =  "state: (" + to_string(x) + "," + to_string(y) + ")\\n";
  str += "action: " + directionToString(d) + "\\n";
  str += "cost: " + to_string(cost);
  return str;
}

void Node::expand() {
  //
}

void Node::printDot() {
  cout << " " << id << " [shape=box label=\"" << toString() << "\"]";
  if(parent)
    cout << " " << id << " -> " << parent->id << endl; 
  list<Node*>::const_iterator iterator;
  for (iterator = frontier.begin(); iterator != frontier.end(); ++iterator) {
    delete *iterator;
  }
}
// SearchGraph
SearchGraph::~SearchGraph() {
  delete root;
}

void SearchGraph::printDot() {
  cout << "graph name {" << endl;
  root->printDot();
  cout << "\n}" << endl;
}