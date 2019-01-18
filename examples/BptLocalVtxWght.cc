#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib> // for srand, rand, RAND_MAX.
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "Utility.h" // for ResizeVector.
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
  
  // get the graph.
  BptGraph graph;
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
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card;
  Val vtxWght=0.0;
  Timer timer;
  BptMatchingEngine matchingEngine;

  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeMaxVtxWghtMatchingLocal
    (graph, &sMateVec, &tMateVec, &card, &vtxWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time, weight and cardinality.
  timer.Print();
  cout << "weight: " <<fixed << vtxWght <<endl;
  cout << "card: " << card <<endl;
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  
  //graph.Print();
  //matchingEngine.PrintMatching(sMateVec, tMateVec, card, vtxWght);
  // check matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, sMateVec, tMateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
