#include <iostream>
#include <vector>
#include <map>
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "Graph.h"
#include "ConvertEngine.h"
#include "AdjGraphEngine.h"
#include "MatchingEngine.h"
#include "Timer.h"

using namespace std;
using namespace Matchbox;

int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
		 << " vertexWeightsFile"
         << endl;
    return 1;
  }
  
  Graph graph;
  cout << "reading graph file ..." << endl;
  if (graph.Read(argv[1]) != eErrNone) {
      cout << "graph file reading error" << endl;
      return 1;
  }
  cout << "done reading graph file" << endl;
  cout << "reading vertex weights file ..." << endl;
  if (graph.ReadWeights(argv[2]) != eErrNone) {
      cout << "vertex weights file reading error: " << endl;
      return 1;
  }
  cout << "done reading vertex weights file" << endl;

  // work variables.
  vector<Size> mateVec;
  Size card;
  Val vtxWght;
  Timer timer;
  MatchingEngine matchingEngine;
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.PGVtxWghtMatching(graph, &mateVec, &card, &vtxWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time, weight and cardinality.
  timer.Print();
  cout << "weight: " <<fixed << vtxWght <<endl;
  cout << "card: " << card <<endl;
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  //graph.Print();
  //matchingEngine.SetFullPrint(true);
  //matchingEngine.PrintMatching(mateVec, card);
  // check the maximum cardinality matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, mateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
