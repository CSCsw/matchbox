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
  if (argc != 2) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << endl;
    return 1;
  }
  Graph graph;
  cout << "reading graph file ..." << endl;
  if (graph.Read(argv[1])) {
      cout << "graph file reading error" << endl;
      return 1;
  }
  cout << "done reading graph file" << endl;
  
  // work variables.
  vector<Size> mateVec;
  Size card;
  Timer timer;
  MatchingEngine matchingEngine;
  // compute a maximum cardinality matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeMaxCardMatching(graph, &mateVec, &card);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time and cardinality.
  timer.Print();
  cout << "card: " << card <<endl;
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  // print the graph.
  //graph.SetFullPrint(alse);
  //graph.Print();
  // print the maximum cardinality matching.
  //matchingEngine.PrintMatching(mateVec, card);
  // check the maximum cardinality matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, mateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
