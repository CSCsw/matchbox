#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "BptCanonicalEngine.h"
#include "Timer.h"

using namespace std;
using namespace Matchbox;

int main(int argc, char** argv) {
  if (argc != 5) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << " symmetrize[no/yes]"
         << " cardGraphSrchType[ssbf/ssdf/ssdflk/mssp/mpdf/mpdflk/mpbfdf]"
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
  // get the cardinality graph search type.
  map<string, GraphSrchType> cardGraphSrchTypeMap;
  cardGraphSrchTypeMap["ssbf"] = eSglSrcBfs;
  cardGraphSrchTypeMap["ssdf"] = eSglSrcDfs;
  cardGraphSrchTypeMap["ssdflk"] = eSglSrcDfsLkhd;
  cardGraphSrchTypeMap["mssp"] = eMplSrcSglPath;
  cardGraphSrchTypeMap["mpdf"] = eMplPathDfs;
  cardGraphSrchTypeMap["mpdflk"] = eMplPathDfsLkhd;
  cardGraphSrchTypeMap["mpbfdf"] = eMplPathBfsDfs;
  map<string, GraphSrchType>::const_iterator
    it2 = cardGraphSrchTypeMap.find(argv[3]);
  if (it2 == cardGraphSrchTypeMap.end()) {
    cout << "invalid cardinality graph search type" << endl;
    return 1;
  }
  GraphSrchType cardGraphSrchType = it2->second;
  // get the computation statistics printing condition.
  map<string, bool> statsPrintMap;
  statsPrintMap["no"] = false;
  statsPrintMap["yes"] = true;
  map<string, bool>::const_iterator it3 = statsPrintMap.find(argv[4]);
  if (it3 == statsPrintMap.end()) {
    cout << "invalid computation statistics printing condition" << endl;
    return 1;
  }
  bool statsPrint = it3->second;
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
  vector<Size> sMate1Vec;
  vector<Size> tMate1Vec;
  Size card1;
  vector<BptCanonicalEngine::CoarseType> sCoarseVec;
  vector<BptCanonicalEngine::CoarseType> tCoarseVec;
  Size sNumHrzVtxs;
  Size tNumHrzVtxs;
  Size sNumSqrVtxs;
  Size tNumSqrVtxs;
  Size sNumVrtVtxs;
  Size tNumVrtVtxs;
  vector<Size> sMate2Vec;
  vector<Size> tMate2Vec;
  Size card2;
  Val edgWght;
  Timer timer;
  BptMatchingEngine matchingEngine;
  BptCanonicalEngine canonicalEngine;
  // compute a maximum cardinality matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  switch (cardGraphSrchType) {
  case eSglSrcBfs:
    cout << "bipartite maximum cardinality matching, single source, bfs:"
         << endl;
    break;
  case eSglSrcDfs:
    cout << "bipartite maximum cardinality matching, single source, dfs:"
         << endl;
    break;
  case eSglSrcDfsLkhd:
    cout << "bipartite maximum cardinality matching, single source, dfs, "
         << "with lookahead:" << endl;
    break;
  case eMplSrcSglPath:
    cout << "bipartite maximum cardinality matching, multiple source, "
         << "single augmenting path:" << endl;
    break;
  case eMplPathDfs:
    cout << "bipartite maximum cardinality matching, "
         << "multiple augmenting path, dfs:" << endl;
    break;
  case eMplPathDfsLkhd:
    cout << "bipartite maximum cardinality matching, "
         << "multiple augmenting path, dfs, with lookahead:" << endl;
    break;
  case eMplPathBfsDfs:
    cout << "bipartite maximum cardinality matching, "
         << "multiple augmenting path, bfs + dfs (shortest path):" << endl;
    break;
  default:
    assert(false);
  }
  matchingEngine.SetCardGraphSrchType(cardGraphSrchType);
  matchingEngine.SetStatsPrint(statsPrint);
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeMaxCardMatching(graph, &sMate1Vec, &tMate1Vec, &card1);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time to compute the maximum cardinality matching.
  timer.Print();
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  // compute the coarse canonical decomposition.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  canonicalEngine.SetStatsPrint(statsPrint);
  cout << "computing coarse canonical decomposition ..." << endl;
  timer.Start();
  canonicalEngine.PartitionCoarse
    (graph, sMate1Vec, tMate1Vec, &sCoarseVec, &tCoarseVec, &sNumHrzVtxs,
     &tNumHrzVtxs, &sNumSqrVtxs, &tNumSqrVtxs, &sNumVrtVtxs, &tNumVrtVtxs);
  timer.Stop();
  cout << "done computing coarse canonical decomposition" << endl;
  // print the time to compute the coarse canonical decomposition.
  timer.Print();
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  // compute a maximum cardinality maximum edge-weight matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "bipartite maximum cardinality maximum edge-weight matching through "
       << "the canonical decomposition:" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  canonicalEngine.ComputeMaxCardMaxEdgWghtMatching
    (graph, sMate1Vec, tMate1Vec, card1, sCoarseVec, tCoarseVec, sNumHrzVtxs,
     tNumHrzVtxs, sNumSqrVtxs, tNumSqrVtxs, sNumVrtVtxs, tNumVrtVtxs,
     &sMate2Vec, &tMate2Vec, &card2, &edgWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time to compute the maximum cardinality maximum edge-weight
  // matching.
  timer.Print();
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  // get the matched edge-weight.
  matchingEngine.GetMatchedEdgWght
    (graph, sMate2Vec, tMate2Vec, card2, &edgWght);
  // print the graph.
  graph.Print();
  // print the maximum cardinality matching.
  matchingEngine.PrintMatching(sMate1Vec, tMate1Vec, card1);
  // check the maximum cardinality matching.
  cout << "checking matching ..." << endl;
  bool
    valid1 = matchingEngine.CheckMatching(graph, sMate1Vec, tMate1Vec, card1);
  assert(valid1 == true);
  cout << "done checking matching" << endl;
  // print the coarse canonical decomposition.
  canonicalEngine.PrintCoarse
    (sCoarseVec, tCoarseVec, sNumHrzVtxs, tNumHrzVtxs, sNumSqrVtxs,
     tNumSqrVtxs, sNumVrtVtxs, tNumVrtVtxs);
  // print the maximum cardinality maximum edge-weight matching.
  matchingEngine.PrintMatching(sMate2Vec, tMate2Vec, card2, edgWght);
  // check the maximum cardinality maximum edge-weight matching.
  cout << "checking matching ..." << endl;
  bool
    valid2 = matchingEngine.CheckMatching(graph, sMate2Vec, tMate2Vec, card2);
  assert(valid2 == true);
  cout << "done checking matching" << endl;
  return 0;
}
