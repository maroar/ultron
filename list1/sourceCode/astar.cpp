#include "PacMaze.h"
#include <queue>
priority_queue<Node*> open;
// exerc 3
void SearchGraph::astar() {
  Node* n;

  explored.clear();
  astarInsert(root);

  while(true) {
    n = astarRemove();
    if(!n) {
      cout << "No Solution" << endl;
      return;
    }

    if(nodeIsGoal(n)) {
      //return solution(n);
      return printDot();
    }

    if(!alreadyVisited(n->r, n->c)) {
      n->expand(n->distanceToGoal());
      astarInsertList(n->children);
    }
  }
}

void SearchGraph::astarInsert(Node *n) {
  open.push(n);
}

void SearchGraph::astarInsertList(list<Node*>& l) {
  list<Node*>::const_iterator it;
  for(it = l.begin(); it != l.end(); ++it) {
    open.push(*it);
  }
}

Node* SearchGraph::astarRemove() {
  if(!open.empty()) {
    Node* n = open.top();
    open.pop(); 
    return n;
  }
  else
    return NULL;
}
