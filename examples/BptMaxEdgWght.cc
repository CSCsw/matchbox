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
  if (argc != 6) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << " symmetrize[no/yes]"
         << " idxdPriQueType[lst/bhp]"
         << " maxCard[no/yes]"
         << " statsPrint[no/yes]"
         << endl;
    return 1;
  }
  // get the symmetrization condition.
  map<string, bool> symmetrizeMap;
  symmetrizeMap["no"] = false;
  symmetrizeMap["yes"] = true;
  map<string, bool>::const_iterator it1 = symmetrizeMap.find(argv[2]);
  if (it1 == symmetrizeMap.end()) {
    cout << "invalid symmetrization condition" << endl;
    return 1;
  }
  bool symmetrize = it1->second;
  // get the indexed priority queue type.
  map<string, IdxdPriQueType> priQueMap;
  priQueMap["lst"] = eLstIdxdPriQue;
  priQueMap["bhp"] = eBhpIdxdPriQue;
  map<string, IdxdPriQueType>::const_iterator it2 = priQueMap.find(argv[3]);
  if (it2 == priQueMap.end()) {
    cout << "invalid indexed priority queue type" << endl;
    return 1;
  }
  IdxdPriQueType idxdPriQueType = it2->second;
  // get the maximum cardinality condition.
  map<string, bool> maxCardMap;
  maxCardMap["no"] = false;
  maxCardMap["yes"] = true;
  map<string, bool>::const_iterator it3 = maxCardMap.find(argv[4]);
  if (it3 == maxCardMap.end()) {
    cout << "invalid maximum cardinality condition" << endl;
    return 1;
  }
  bool maxCard = it3->second;
  // get the computation statistics printing condition.
  map<string, bool> statsPrintMap;
  statsPrintMap["no"] = false;
  statsPrintMap["yes"] = true;
  map<string, bool>::const_iterator it4 = statsPrintMap.find(argv[5]);
  if (it4 == statsPrintMap.end()) {
    cout << "invalid computation statistics printing condition" << endl;
    return 1;
  }
  bool statsPrint = it4->second;
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
  Size card=0;
  Val edgWght=0.0;
  Timer timer;
  BptMatchingEngine matchingEngine;
  // compute a maximum edge-weight matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  switch (idxdPriQueType) {
  case eLstIdxdPriQue:
    cout << "bipartite maximum edge-weight matching, single source, "
         << "single augmenting path, list indexed priority queue:"
         << endl;
    break;
  case eBhpIdxdPriQue:
    cout << "bipartite maximum edge-weight matching, single source, "
         << "single augmenting path, binary heap indexed priority queue:"
         << endl;
    break;
  default:
    assert(false);
  }
  matchingEngine.SetInlz(false);
  matchingEngine.SetIdxdPriQueType(idxdPriQueType);
  matchingEngine.SetStatsPrint(statsPrint);
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeMaxEdgWghtMatching
    (graph, &sMateVec, &tMateVec, &card, &edgWght, maxCard);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time, weight an cardinality.
  timer.Print();
  cout << "weight: " <<fixed << edgWght <<endl;
  cout << "card: " << card <<endl;
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  // get the matched edge-weight.
  //matchingEngine.GetMatchedEdgWght(graph, sMateVec, tMateVec, card, &edgWght);
  // print the graph.
  //graph.Print();
  // print the maximum edge-weight matching.
  //matchingEngine.PrintMatching(sMateVec, tMateVec, card, edgWght); 
  // check the maximum edge-weight matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, sMateVec, tMateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
