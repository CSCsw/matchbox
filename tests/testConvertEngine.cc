#include <iostream>
#include <vector>
#include <cassert>

#include "BptGraph.h"
#include "Graph.h"
#include "ConvertEngine.h"

using namespace std;
using namespace Matchbox;

void Test1(void) {
  Err err;
  // create a bipartite graph.
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
  BptGraph bptGraph(3, 3, 3, sVtxVec, tVtxVec, edgWghtVec);
  // convert the bipartite graph into a graph.
  Graph graph;
  ConvertEngine convertEngine;
  err = convertEngine.Convert(bptGraph, &graph);
  assert(err == eErrNone);
  // test the conversion.
  Size numVtxs;
  Size numEdgs;
  graph.GetNumVtxs(&numVtxs);
  assert(numVtxs == 6);
  graph.GetNumEdgs(&numEdgs);
  assert(numEdgs == 3);
  Size adjNumEdgs;
  vector<Size> adjVtxVec;
  vector<Val> adjEdgWghtVec;
  err = graph.GetAdj(0, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 4);
  assert(adjEdgWghtVec[0] == 1.0);
  err = graph.GetAdj(1, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 5);
  assert(adjEdgWghtVec[0] == 2.0);
  err = graph.GetAdj(2, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 3);
  assert(adjEdgWghtVec[0] == 3.0);
  err = graph.GetAdj(3, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 2);
  assert(adjEdgWghtVec[0] == 3.0);
  err = graph.GetAdj(4, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 0);
  assert(adjEdgWghtVec[0] == 1.0);
  err = graph.GetAdj(5, &adjNumEdgs, &adjVtxVec, &adjEdgWghtVec);
  assert(err == eErrNone);
  assert(adjNumEdgs == 1);
  assert(adjVtxVec.size() == 1);
  assert(adjEdgWghtVec.size() == 1);
  assert(adjVtxVec[0] == 1);
  assert(adjEdgWghtVec[0] == 2.0);
}

int main(int argc, char** argv) {
  Test1();
  cout << argv[0] << ": all tests passed" << endl;
  return 0;
}
