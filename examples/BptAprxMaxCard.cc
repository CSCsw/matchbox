#include <iostream>
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
  if (argc != 3) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << " symmetrize[no/yes]"
         << endl;
    return 1;
  }
  // get the symmetrization condition.
  map<string, bool> symmetrizeMap;
  symmetrizeMap["no"] = false;
  symmetrizeMap["yes"] = true;
  map<string, bool>::const_iterator it = symmetrizeMap.find(argv[2]);
  if (it == symmetrizeMap.end()) {
    cout << "invalid symmetrization condition" << endl;
    return 1;
  }
  bool symmetrize = it->second;
  // get the graph.
  BptGraph graph;
  cout << "reading graph file ..." << endl;
  if (graph.Read(argv[1]) != eErrNone) {
    cout << "graph file reading error" << endl;
    return 1;
  }
  cout << "done reading graph file" << endl;
  if (symmetrize == true) {
    cout << "symmetrizing graph ..." << endl;
    if (graph.Symmetrize() != eErrNone) {
      cout << "graph symmetrization error" << endl;
      return 1;
    }
    cout << "done symmetrizing graph" << endl;
  }
  // work variables.
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card;
  Timer timer;
  BptMatchingEngine matchingEngine;
  // compute a maximal matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeMxmlMatching(graph, &sMateVec, &tMateVec, &card);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time to compute the maximal matching.
  timer.Print();
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  // print the graph.
  graph.Print();
  // print the maximal matching.
  matchingEngine.PrintMatching(sMateVec, tMateVec, card);
  // check the maximal matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, sMateVec, tMateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
