#include <iostream>
#include <vector>
#include <cassert>

#include "Graph.h"
#include "MatchingEngine.h"

using namespace std;
using namespace Matchbox;

void Test1(void) {
  // create a graph.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(2);
  sVtxVec.push_back(4);
  tVtxVec.push_back(3);
  tVtxVec.push_back(5);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph graph(6, 3, sVtxVec, tVtxVec, edgWghtVec);
  // compute a maximal matching.
  MatchingEngine matchingEngine;
  vector<Size> mateVec;
  Size card;
  matchingEngine.ComputeMxmlMatching(graph, &mateVec, &card);
  // test the matching.
  assert(mateVec.size() == 6);
  assert(mateVec[0] == 3);
  assert(mateVec[1] == 4);
  assert(mateVec[2] == 5);
  assert(mateVec[3] == 0);
  assert(mateVec[4] == 1);
  assert(mateVec[5] == 2);
  assert(card == 3);
  // compute an approximate maximum edge weight matching.
  Val wght;
  matchingEngine.ComputeAprxMaxEdgWghtMatching4(graph, &mateVec, &card, &wght);
  // test the matching.
  assert(mateVec.size() == 6);
  assert(mateVec[0] == 3);
  assert(mateVec[1] == 4);
  assert(mateVec[2] == 5);
  assert(mateVec[3] == 0);
  assert(mateVec[4] == 1);
  assert(mateVec[5] == 2);
  assert(card == 3);
  assert(wght == 6.0);
}

int main(int argc, char** argv) {
  Test1();
  cout << argv[0] << ": all tests passed" << endl;
  return 0;
}
