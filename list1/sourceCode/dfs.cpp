#include "PacMaze.h"
// exerc 3
list<Node*> fringe;
void SearchGraph::dfs() {
  Node* n;

  explored.clear();
  dfsInsert(root);

  while(true) {
    n = dfsRemove();
    if(!n) {
      cout << "No Solution" << endl;
      return;
    }

    if(nodeIsGoal(n)) {
      return solution(n);
      //return printDot();
    }

    if(!alreadyVisited(n->r, n->c)) {
      n->expand();
      dfsInsertList(n->children);
    } else {
      n->visited = true;
    }
  }
}

void SearchGraph::dfsInsert(Node *n) {
  fringe.push_back(n);
}

void SearchGraph::dfsInsertList(list<Node*>& l) {
  list<Node*>::const_iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    fringe.push_back(*it);
  }
}

Node* SearchGraph::dfsRemove() {
  if(!fringe.empty()) {
    Node* n = fringe.back();
    fringe.pop_back(); 
    return n;
  }
  else
    return NULL;
}
