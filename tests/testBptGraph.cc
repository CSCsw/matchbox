#include <iostream>
#include <vector>
#include <cassert>

#include "BptGraph.h"

using namespace std;
using namespace Matchbox;

void Test1(void) {
  // create an empty graph.
  BptGraph g;
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrNone);
}

void Test2(void) {
  // create a nonempty graph.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 2);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 2);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 2);
  assert(tNumVtxs == 2);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 3);
  g.GetInitErr(&err);
  assert(err == eErrNone);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 2.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrInvVtx);
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 3.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrInvVtx);
  // clear the graph.
  g.Clear();
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrNone);
}

void Test3(void) {
  // create a nonempty graph.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  // modify the graph.
  sVtxVec.clear();
  tVtxVec.clear();
  edgWghtVec.clear();
  sVtxVec.push_back(0);
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  sVtxVec.push_back(2);
  sVtxVec.push_back(2);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  tVtxVec.push_back(3);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  edgWghtVec.push_back(4.0);
  edgWghtVec.push_back(5.0);
  edgWghtVec.push_back(6.0);
  g.Set(3, 4, 6, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 3);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 4);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 3);
  assert(tNumVtxs == 4);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 6);
  g.GetInitErr(&err);
  assert(err == eErrNone);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 4.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 2);
  assert(adjEdgWghtVec[0] == 5.0);
  assert(adjVtxVec[1] == 3);
  assert(adjEdgWghtVec[1] == 6.0);
  err = g.GetAdj(3, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrInvVtx);
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 2.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 4.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 5.0);
  err = g.GetAdj(3, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 2);
  assert(adjEdgWghtVec[0] == 6.0);
  err = g.GetAdj(4, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrInvVtx);
}

void Test4(void) {
  // create a graph with an invalid vertex (sVtxVec).
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(2);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvVtx);
}

void Test5(void) {
  // create a graph with an invalid vertex (tVtxVec).
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(2);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvVtx);
}

void Test6(void) {
  // create a graph with an invalid edge weight.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(-2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvWght);
}

void Test7(void) {
  // create a graph using input vectors of different sizes (sVtxVec).
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvInput);
}

void Test8(void) {
  // create a graph using input vectors of different sizes (tVtxVec).
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvInput);
}

void Test9(void) {
  // create a graph using input vectors of different sizes (edgWghtVec).
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 0);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 0);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 0);
  assert(tNumVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvInput);
}

void Test10(void) {
  // create a nonempty graph with duplicate edges.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  BptGraph g(2, 2, 4, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  // test the graph.
  g.GetSNumVtxs(&sNumVtxs);
  assert(sNumVtxs == 2);
  g.GetTNumVtxs(&tNumVtxs);
  assert(tNumVtxs == 2);
  g.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 2);
  assert(tNumVtxs == 2);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 3);
  g.GetInitErr(&err);
  assert(err == eErrNone);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 2.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrInvVtx);
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 3.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrInvVtx);
}

void Test11(void) {
  // create a graph that is symmetrizable, without common original edges.
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
  // test the symmetrization of the graph.
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  err = graph.Symmetrize();
  assert(err == eErrNone);
  graph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 3);
  assert(tNumVtxs == 3);
  graph.GetNumEdgs(&numEdgs);
  assert(numEdgs == 6);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
}

void Test12(void) {
  // create a graph that is symmetrizable, with common original edges.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(2);
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(0);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  edgWghtVec.push_back(3.0);
  BptGraph graph(3, 3, 4, sVtxVec, tVtxVec, edgWghtVec);
  // test the symmetrization of the graph.
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  err = graph.Symmetrize();
  assert(err == eErrNone);
  graph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 3);
  assert(tNumVtxs == 3);
  graph.GetNumEdgs(&numEdgs);
  assert(numEdgs == 6);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
}

void Test13(void) {
  // create a graph that is not symmetrizable because |S| and |T| are not
  // equal.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  BptGraph graph(1, 2, 2, sVtxVec, tVtxVec, edgWghtVec);
  // test the symmetrization of the graph.
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  err = graph.Symmetrize();
  assert(err == eErrInvNumVtxs);
  graph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 1);
  assert(tNumVtxs == 2);
  graph.GetNumEdgs(&numEdgs);
  assert(numEdgs == 2);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 2.0);
}

void Test14(void) {
  // create a graph that is not symmetrizable because two common edges have
  // different weights.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(2);
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(0);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  edgWghtVec.push_back(4.0);
  BptGraph graph(3, 3, 4, sVtxVec, tVtxVec, edgWghtVec);
  // test the symmetrization of the graph.
  Err err;
  Size sNumVtxs;
  Size tNumVtxs;
  Size numEdgs;
  err = graph.Symmetrize();
  assert(err == eErrNotSymmetrizable);
  graph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  assert(sNumVtxs == 3);
  assert(tNumVtxs == 3);
  graph.GetNumEdgs(&numEdgs);
  assert(numEdgs == 4);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 4.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 2);
  assert(adjEdgWghtVec[0] == 2.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, false);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 2);
  assert(adjEdgWghtVec[0] == 3.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec, true);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 4.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
}

int main(int argc, char** argv) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();
  Test8();
  Test9();
  Test10();
  Test11();
  Test12();
  Test13();
  Test14();
  cout << argv[0] << ": all tests passed" << endl;
  return 0;
}
