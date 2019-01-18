#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib> // for srand, rand, RAND_MAX.
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "BptCanonicalEngine.h"
#include "Timer.h"

using namespace std;
using namespace Matchbox;

int main(int argc, char** argv) {
  if (argc != 7) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << " symmetrize[no/yes]"
         << " cardGraphSrchType[ssbf/ssdf/ssdflk/mssp/mpdf/mpdflk/mpbfdf]"
         << " vtxWghtAlgType[drct/spcl]"
         << " drctVtxWghtAlgType[gbl/lcl]"
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
  // get the vertex-weight algorithm type.
  map<string, VtxWghtAlgType> vtxWghtAlgTypeMap;
  vtxWghtAlgTypeMap["drct"] = eDrct;
  vtxWghtAlgTypeMap["spcl"] = eSpcl;
  map<string, VtxWghtAlgType>::const_iterator
    it3 = vtxWghtAlgTypeMap.find(argv[4]);
  if (it3 == vtxWghtAlgTypeMap.end()) {
    cout << "invalid vertex-weight algorithm type" << endl;
    return 1;
  }
  VtxWghtAlgType vtxWghtAlgType = it3->second;
  // get the direct vertex-weight algorithm type.
  map<string, BptMatchingEngine::DrctVtxWghtAlgType> drctVtxWghtAlgTypeMap;
  drctVtxWghtAlgTypeMap["gbl"] = BptMatchingEngine::eGbl;
  drctVtxWghtAlgTypeMap["lcl"] = BptMatchingEngine::eLcl;
  map<string, BptMatchingEngine::DrctVtxWghtAlgType>::const_iterator
    it4 = drctVtxWghtAlgTypeMap.find(argv[5]);
  if (it4 == drctVtxWghtAlgTypeMap.end()) {
    cout << "invalid direct vertex-weight algorithm type" << endl;
    return 1;
  }
  BptMatchingEngine::DrctVtxWghtAlgType drctVtxWghtAlgType = it4->second;
  // get the computation statistics printing condition.
  map<string, bool> statsPrintMap;
  statsPrintMap["no"] = false;
  statsPrintMap["yes"] = true;
  map<string, bool>::const_iterator it5 = statsPrintMap.find(argv[6]);
  if (it5 == statsPrintMap.end()) {
    cout << "invalid computation statistics printing condition" << endl;
    return 1;
  }
  bool statsPrint = it5->second;
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
  Size sNumVtxs;
  Size tNumVtxs;
  vector<Val> sVtxWghtVec;
  vector<Val> tVtxWghtVec;
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
  Val vtxWght;
  Val sVtxWght;
  Val tVtxWght;
  Timer timer;
  BptMatchingEngine matchingEngine;
  BptCanonicalEngine canonicalEngine;
  // initialize the vertex weights.
  graph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  ResizeVector<Val>(&sVtxWghtVec, sNumVtxs);
  ResizeVector<Val>(&tVtxWghtVec, tNumVtxs);
  srand(13);
  for (Size s = 0; s < sNumVtxs; ++s) {
    sVtxWghtVec[s] = 10e6 * rand() / RAND_MAX;
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    tVtxWghtVec[t] = 10e6 * rand() / RAND_MAX;
  }
  graph.SetVtxWghts(sVtxWghtVec, tVtxWghtVec);
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
  canonicalEngine.SetVtxWghtAlgType(vtxWghtAlgType);
  canonicalEngine.SetDrctVtxWghtAlgType(drctVtxWghtAlgType);
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
  // compute a maximum vertex-weight matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "bipartite maximum vertex-weight matching through "
       << "the canonical decomposition:" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  canonicalEngine.ComputeMaxVtxWghtMatching
    (graph, sMate1Vec, tMate1Vec, card1, sCoarseVec, tCoarseVec, sNumHrzVtxs,
     tNumHrzVtxs, sNumSqrVtxs, tNumSqrVtxs, sNumVrtVtxs, tNumVrtVtxs,
     &sMate2Vec, &tMate2Vec, &card2, &vtxWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time to compute the maximum vertex-weight matching.
  timer.Print();
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;
  // get the matched vertex-weight.
  matchingEngine.GetMatchedVtxWght
    (graph, sMate2Vec, tMate2Vec, card2, &sVtxWght, &tVtxWght, &edgWght);
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
  // print the maximum vertex-weight matching.
  matchingEngine.PrintMatching
    (sMate2Vec, tMate2Vec, card2, sVtxWght + tVtxWght);
  // check the maximum vertex-weight matching.
  cout << "checking matching ..." << endl;
  bool
    valid2 = matchingEngine.CheckMatching(graph, sMate2Vec, tMate2Vec, card2);
  assert(valid2 == true);
  cout << "done checking matching" << endl;
  return 0;
}
