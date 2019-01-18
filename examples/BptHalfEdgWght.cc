#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "Timer.h"

using namespace std;
using namespace Matchbox;

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
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
  // work variables.
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card;
  Val edgWght;
  Timer timer;
  BptMatchingEngine matchingEngine;
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeHalfEdgWghtMatching
    (graph, &sMateVec, &tMateVec, &card, &edgWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time, weight and cardinality
  timer.Print();
  cout << "weight: " <<fixed <<edgWght <<endl;
  cout << "card: " << card <<endl;
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
	
  // check matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, sMateVec, tMateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
