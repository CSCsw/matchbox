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
  if (argc != 5) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << " bipartite[no/yes]"
         << " symmetrize[no/yes]"
         << " adjacency[no/yes]"
         << endl;
    return 1;
  }
  // get the bipartite condition.
  map<string, bool> bipartiteMap;
  bipartiteMap["no"] = false;
  bipartiteMap["yes"] = true;
  map<string, bool>::const_iterator it1 = bipartiteMap.find(argv[2]);
  if (it1 == bipartiteMap.end()) {
    cout << "invalid symmetrization condition" << endl;
    return 1;
  }
  bool bipartite = it1->second;
  // get the symmetrization condition.
  map<string, bool> symmetrizeMap;
  symmetrizeMap["no"] = false;
  symmetrizeMap["yes"] = true;
  map<string, bool>::const_iterator it2 = symmetrizeMap.find(argv[3]);
  if (it2 == symmetrizeMap.end()) {
    cout << "invalid symmetrization condition" << endl;
    return 1;
  }
  bool symmetrize = it2->second;
  // get the adjacency condition.
  map<string, bool> adjacencyMap;
  adjacencyMap["no"] = false;
  adjacencyMap["yes"] = true;
  map<string, bool>::const_iterator it3 = adjacencyMap.find(argv[4]);
  if (it3 == adjacencyMap.end()) {
    cout << "invalid symmetrization condition" << endl;
    return 1;
  }
  bool adjacency = it3->second;
  // get the graph.
  Graph graph;
  if (bipartite == true) {
    BptGraph bptGraph;
    cout << "reading graph file ..." << endl;
    if (bptGraph.Read(argv[1]) != eErrNone) {
      cout << "graph file reading error" << endl;
      return 1;
    }
    cout << "done reading graph file" << endl;
    if (symmetrize == true) {
      cout << "symmetrizing graph ..." << endl;
      if (bptGraph.Symmetrize() != eErrNone) {
        cout << "graph symmetrization error" << endl;
        return 1;
      }
      cout << "done symmetrizing graph" << endl;
    }
    if (adjacency == false) {
      ConvertEngine convertEngine;
      // convert the bipartite graph into a graph.
      cout << "converting graph ..." << endl;
      if (convertEngine.Convert(bptGraph, &graph) != eErrNone) {
        cout << "graph conversion error" << endl;
        return 1;
      }
      cout << "done converting graph" << endl;
    } else {
      AdjGraphEngine adjGraphEngine;
      // compute the adjacency graph from the bipartite graph.
      cout << "computing adjacency graph ..." << endl;
      if (adjGraphEngine.GetAdjGraph(bptGraph, &graph) != eErrNone) {
        cout << "adjacency graph computation error" << endl;
        return 1;
      }
      cout << "done computing adjacency graph" << endl;
    }
  } else {
    cout << "reading graph file ..." << endl;
    if (graph.Read(argv[1]) != eErrNone) {
      cout << "graph file reading error" << endl;
      return 1;
    }
    cout << "done reading graph file" << endl;
  }
  // work variables.
  vector<Size> mateVec;
  Size card;
  Val edgWght;
  Timer timer;
  MatchingEngine matchingEngine;
  // compute an approximate maximum edge-weight matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeAprxMaxEdgWghtMatching4
    (graph, &mateVec, &card, &edgWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time to compute the approximate maximum edge-weight matching.
  timer.Print();
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  // get the matched edge-weight.
  matchingEngine.GetMatchedEdgWght(graph, mateVec, card, &edgWght);
  // print the graph.
  graph.Print();
  // print the approximate maximum edge-weight matching.
  matchingEngine.PrintMatching(mateVec, card, edgWght);
  // check the approximate maximum edge-weight matching.
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, mateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
