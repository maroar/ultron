#include "PacMaze.h"
int                 numNodes;
list<pair<int,int>> visited;
list<Move*>         moves;
list<Node*>         frontier;
PacMaze             *pacMaze;
SearchGraph         *sg;
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

void printFrontier() {
  list<Node*>::const_iterator it;
  for(it = frontier.begin(); it != frontier.end(); ++it) {
    cout << (*it)->toString() << " "; 
  }
  cout << endl;
}

bool alreadyVisited(int row, int column) {
  pair<int,int> targer;
  targer.first  = row;
  targer.second = column;
  return (find(visited.begin(), visited.end(), targer) != visited.end());
}
// Goal methods
bool Goal::isGoal(int coordX, int coordY) {
  return (coordX == x) && (coordY == y);
}

void Goal::print() {
  cout << "row: " << x << " col: " << y << endl;
}
// Move methods
string Move::toString() {
  string toReturn = "(";
  toReturn += directionToString(d);
  toReturn += ";";
  toReturn += to_string(r);
  toReturn += ",";
  toReturn += to_string(c);
  toReturn += ")";
  return   toReturn;
}
// PacMaze methods
bool PacMaze::canMoveTo(int x, int y, direction d){
  switch(d) {
    case NORTH: return (scenario[(x-1)%rows][y]) != '#';
    case SOUTH: return (scenario[(x+1)%rows][y]) != '#';
    case EAST:  return (scenario[x][(y+1)%columns]) != '#';
    case WEST:  return (scenario[x][(y-1)%columns]) != '#';
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
  if(canMoveTo(pacMan->getRow(), pacMan->getColumn(), d)) {
    switch(d) {
      case NORTH: pacMan->moveTo((pacMan->getRow()-1)%rows, pacMan->getColumn()); break;
      case SOUTH: pacMan->moveTo((pacMan->getRow()+1)%rows, pacMan->getColumn()); break;
      case EAST:  pacMan->moveTo(pacMan->getRow(), (pacMan->getColumn()+1)%columns); break;
      case WEST:  pacMan->moveTo(pacMan->getRow(), (pacMan->getColumn()-1)%columns); break;
    }
    return successor(pacMan->getRow(), pacMan->getColumn());
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
  charBeforePacMan = scenario[pacMan->getRow()][pacMan->getColumn()];
  scenario[pacMan->getRow()][pacMan->getColumn()] = 'P';
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
  for(iterator = moves.begin(); iterator != moves.end(); ++iterator) {
    cout << (*iterator)->toString() << " ";
  }
  cout << endl;
}

void PacMaze::readScenario() {
  int i, j;
  fstream myfile(inputFile, fstream::in);
  if(myfile.is_open()) {
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
  scenario[pacMan->getRow()][pacMan->getColumn()] = charBeforePacMan;
}

int PacMaze::successor(int x, int y) {
  int i = 0;
  moves.clear();
  if(canMoveTo(x, y, NORTH)){
    moves.push_back(new Move(NORTH, (x-1)%rows, y));
    i++;
  }
  if(canMoveTo(x, y, SOUTH)){
    moves.push_back(new Move(SOUTH, (x+1)%rows, y));
    i++;
  }
  if(canMoveTo(x, y, EAST)){
    moves.push_back(new Move(EAST, x, (y+1)%columns));
    i++;
  }
  if(canMoveTo(x, y, WEST)){
    moves.push_back(new Move(WEST, x, (y-1)%columns));
    i++;
  }
  return i;
}

PacMaze::~PacMaze() {
  for(int i = 0; i < rows; i++)
    delete[] scenario[i];
  delete[] scenario;
  delete pacMan;
  delete goal;
}
// exerc 2
// Node
Node::~Node() {
  if(children.size()!=0) {
    list<Node*>::const_iterator iterator;
    for(iterator = children.begin(); iterator != children.end(); ++iterator) {
      delete *iterator;
    }
  }
}

string Node::toDot() {
  string str =  "state: (" + to_string(r) + "," + to_string(c) + ")\\n";
  str += "action: " + directionToString(d) + "\\n";
  str += "cost: " + to_string(cost);
  return str;
}

string Node::toString() {
  string toReturn = "(";
  toReturn += directionToString(d);
  toReturn += ";";
  toReturn += to_string(r);
  toReturn += ",";
  toReturn += to_string(c);
  toReturn += ";";
  toReturn += to_string(cost);
  toReturn += ";";
  if(parent) {
    toReturn += to_string(parent->r);
    toReturn += ",";
    toReturn += to_string(parent->c);
  }
  else
    toReturn += "-1,-1";
  toReturn += ")";
  return toReturn;
}

void Node::expand() {
  if(!alreadyVisited(r, c)) {
    int numChildren;
    list<Move*>::const_iterator it;
    Node *newNode;
    removeNodeFromFrontier();
    numChildren = pacMaze->successor(r, c);
    for(it = moves.begin(); it != moves.end(); ++it) {
      newNode = new Node(this, cost+1, (*it)->r, (*it)->c, (*it)->d);
      frontier.push_back(newNode);
      children.push_back(newNode);
    }
    visited.push_back(make_pair(r,c));
  }
}

void Node::printDot() {
  cout << " n" << id << " [shape=box label=\"" << toDot() << "\"]" << endl;
  if(parent)
    cout << " n" << id << " -- n" << parent->id << endl; 
  list<Node*>::const_iterator iterator;
  for(iterator = children.begin(); iterator != children.end(); ++iterator) {
    (*iterator)->printDot();
  }
}

void Node::printChildren() {
  list<Node*>::const_iterator iterator;
  for(iterator = children.begin(); iterator != children.end(); ++iterator) {
    cout << (*iterator)->toString() << " "; 
  }
  cout << endl;
}

void Node::removeNodeFromFrontier() {
  list<Node*>::const_iterator it;
  for(it = frontier.begin(); it != frontier.end(); ++it) {
    if((*it)->id == id) {
      frontier.remove(*it);
      break;
    } 
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