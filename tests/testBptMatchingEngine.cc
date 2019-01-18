#include <iostream>
#include <vector>
#include <cassert>

#include "BptGraph.h"
#include "BptMatchingEngine.h"

using namespace std;
using namespace Matchbox;

void Test1(void) {
  // create a graph.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(2);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(0);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph graph(3, 3, 3, sVtxVec, tVtxVec, edgWghtVec);
  // compute a maximal matching from the S-side.
  BptMatchingEngine matchingEngine;
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card;
  matchingEngine.ComputeMxmlMatching
    (graph, &sMateVec, &tMateVec, &card, false);
  // test the matching.
  assert(sMateVec.size() == 3);
  assert(tMateVec.size() == 3);
  assert(sMateVec[0] == 1);
  assert(sMateVec[1] == 2);
  assert(sMateVec[2] == 0);
  assert(tMateVec[0] == 2);
  assert(tMateVec[1] == 0);
  assert(tMateVec[2] == 1);
  assert(card == 3);
  // compute a maximal matching from the T-side.
  matchingEngine.ComputeMxmlMatching(graph, &sMateVec, &tMateVec, &card, true);
  // test the matching.
  assert(sMateVec.size() == 3);
  assert(tMateVec.size() == 3);
  assert(sMateVec[0] == 1);
  assert(sMateVec[1] == 2);
  assert(sMateVec[2] == 0);
  assert(tMateVec[0] == 2);
  assert(tMateVec[1] == 0);
  assert(tMateVec[2] == 1);
  assert(card == 3);
  // compute a maximal matching, side determined automatically.
  matchingEngine.ComputeMxmlMatching(graph, &sMateVec, &tMateVec, &card);
  // test the matching.
  assert(sMateVec.size() == 3);
  assert(tMateVec.size() == 3);
  assert(sMateVec[0] == 1);
  assert(sMateVec[1] == 2);
  assert(sMateVec[2] == 0);
  assert(tMateVec[0] == 2);
  assert(tMateVec[1] == 0);
  assert(tMateVec[2] == 1);
  assert(card == 3);
}

void Test2(GraphSrchType cardGraphSrchType, QueAndStkType queAndStkType,
    IdxdQueType idxdQueType, bool inlz) {
  // create a graph.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(2);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(0);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph graph(3, 3, 3, sVtxVec, tVtxVec, edgWghtVec);
  // compute a maximum cardinality matching from the S-side.
  BptMatchingEngine matchingEngine;
  Err err;
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card;
  err = matchingEngine.SetCardGraphSrchType(cardGraphSrchType);
  assert(err == eErrNone);
  err = matchingEngine.SetQueAndStkType(queAndStkType);
  assert(err == eErrNone);
  err = matchingEngine.SetIdxdQueType(idxdQueType);
  assert(err == eErrNone);
  matchingEngine.SetInlz(inlz);
  matchingEngine.ComputeMaxCardMatching
    (graph, &sMateVec, &tMateVec, &card, false);
  // test the matching.
  assert(sMateVec.size() == 3);
  assert(tMateVec.size() == 3);
  assert(sMateVec[0] == 1);
  assert(sMateVec[1] == 2);
  assert(sMateVec[2] == 0);
  assert(tMateVec[0] == 2);
  assert(tMateVec[1] == 0);
  assert(tMateVec[2] == 1);
  assert(card == 3);
  // compute a maximum cardinality matching from the T-side.
  matchingEngine.ComputeMaxCardMatching
    (graph, &sMateVec, &tMateVec, &card, true);
  // test the matching.
  assert(sMateVec.size() == 3);
  assert(tMateVec.size() == 3);
  assert(sMateVec[0] == 1);
  assert(sMateVec[1] == 2);
  assert(sMateVec[2] == 0);
  assert(tMateVec[0] == 2);
  assert(tMateVec[1] == 0);
  assert(tMateVec[2] == 1);
  assert(card == 3);
  // compute a maximum cardinality matching, side determined automatically.
  matchingEngine.ComputeMaxCardMatching(graph, &sMateVec, &tMateVec, &card);
  // test the matching.
  assert(sMateVec.size() == 3);
  assert(tMateVec.size() == 3);
  assert(sMateVec[0] == 1);
  assert(sMateVec[1] == 2);
  assert(sMateVec[2] == 0);
  assert(tMateVec[0] == 2);
  assert(tMateVec[1] == 0);
  assert(tMateVec[2] == 1);
  assert(card == 3);
}

void Test3(void) {
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0); tVtxVec.push_back(0); edgWghtVec.push_back(1.0);
  sVtxVec.push_back(0); tVtxVec.push_back(1); edgWghtVec.push_back(10.0);
  sVtxVec.push_back(0); tVtxVec.push_back(2); edgWghtVec.push_back(100.0);
  sVtxVec.push_back(1); tVtxVec.push_back(0); edgWghtVec.push_back(1.0);
  sVtxVec.push_back(1); tVtxVec.push_back(1); edgWghtVec.push_back(50.0);
  sVtxVec.push_back(1); tVtxVec.push_back(2); edgWghtVec.push_back(2.0);
  sVtxVec.push_back(2); tVtxVec.push_back(0); edgWghtVec.push_back(200.0);
  sVtxVec.push_back(2); tVtxVec.push_back(1); edgWghtVec.push_back(20.0);
  sVtxVec.push_back(2); tVtxVec.push_back(2); edgWghtVec.push_back(2.0);
  BptGraph graph(3, 3, 9, sVtxVec, tVtxVec, edgWghtVec);
  BptMatchingEngine matchingEngine;
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card;
  Val wght;
  matchingEngine.ComputeMaxEdgWghtMatching
    (graph, &sMateVec, &tMateVec, &card, &wght, false, false);
}

int main(int argc, char** argv) {
  Test1();
  Test2(eSglSrcBfs, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eSglSrcBfs, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eSglSrcBfs, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eSglSrcBfs, eLstQueAndStk, eLstIdxdQue, true);
  Test2(eSglSrcDfs, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eSglSrcDfs, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eSglSrcDfs, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eSglSrcDfs, eLstQueAndStk, eLstIdxdQue, true);
  Test2(eSglSrcDfsLkhd, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eSglSrcDfsLkhd, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eSglSrcDfsLkhd, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eSglSrcDfsLkhd, eLstQueAndStk, eLstIdxdQue, true);
  Test2(eMplSrcSglPath, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eMplSrcSglPath, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eMplSrcSglPath, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eMplSrcSglPath, eLstQueAndStk, eLstIdxdQue, true);
  Test2(eMplPathDfs, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eMplPathDfs, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eMplPathDfs, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eMplPathDfs, eLstQueAndStk, eLstIdxdQue, true);
  Test2(eMplPathDfsLkhd, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eMplPathDfsLkhd, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eMplPathDfsLkhd, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eMplPathDfsLkhd, eLstQueAndStk, eLstIdxdQue, true);
  Test2(eMplPathBfsDfs, eVecQueAndStk, eLstIdxdQue, false);
  Test2(eMplPathBfsDfs, eVecQueAndStk, eLstIdxdQue, true);
  Test2(eMplPathBfsDfs, eLstQueAndStk, eLstIdxdQue, false);
  Test2(eMplPathBfsDfs, eLstQueAndStk, eLstIdxdQue, true);
  Test3();
  cout << argv[0] << ": all tests passed" << endl;
  return 0;
}
