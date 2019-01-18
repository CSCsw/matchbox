#include <iostream>
#include <vector>
#include <cassert>

#include "Graph.h"

using namespace std;
using namespace Matchbox;

void Test1(void) {
  // create an empty graph.
  Graph g;
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 3);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 3);
  g.GetInitErr(&err);
  assert(err == eErrNone);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(3, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrInvVtx);
  // clear the graph.
  g.Clear();
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  // modify the graph.
  sVtxVec.clear();
  tVtxVec.clear();
  edgWghtVec.clear();
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(2);
  sVtxVec.push_back(1);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(3);
  tVtxVec.push_back(3);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  edgWghtVec.push_back(4.0);
  g.Set(4, 4, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 4);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 4);
  g.GetInitErr(&err);
  assert(err == eErrNone);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 3);
  assert(adjVtxVec.size() == 3);
  assert(adjEdgWghtVec.size() == 3);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  assert(adjVtxVec[2] == 3);
  assert(adjEdgWghtVec[2] == 4.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 2.0);
  assert(adjVtxVec[1] == 3);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(3, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 4.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(4, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrInvVtx);
}

void Test4(void) {
  // create a graph with an invalid vertex (sVtxVec).
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(3);
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(3);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(-2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
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
  sVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 3, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 0);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 0);
  g.GetInitErr(&err);
  assert(err == eErrInvInput);
}

void Test10(void) {
  // create a nonempty graph with loop and duplicate edges.
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  sVtxVec.push_back(0);
  sVtxVec.push_back(0);
  sVtxVec.push_back(1);
  sVtxVec.push_back(1);
  sVtxVec.push_back(0);
  tVtxVec.push_back(0);
  tVtxVec.push_back(1);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  tVtxVec.push_back(2);
  edgWghtVec.push_back(0.0);
  edgWghtVec.push_back(1.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(2.0);
  edgWghtVec.push_back(3.0);
  Graph g(3, 5, sVtxVec, tVtxVec, edgWghtVec);
  Err err;
  Size numVtxs;
  Size numEdgs;
  // test the graph.
  g.GetNumVtxs(&numVtxs);
  assert(numVtxs == 3);
  g.GetNumEdgs(&numEdgs);
  assert(numEdgs == 3);
  g.GetInitErr(&err);
  assert(err == eErrNone);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = g.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 3.0);
  err = g.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  assert(adjVtxVec[1] == 2);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 2);
  assert(adjVtxVec.size() == 2);
  assert(adjEdgWghtVec.size() == 2);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 3.0);
  assert(adjVtxVec[1] == 1);
  assert(adjEdgWghtVec[1] == 2.0);
  err = g.GetAdj(3, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrInvVtx);
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
  cout << argv[0] << ": all tests passed" << endl;
  return 0;
}
