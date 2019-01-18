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
  if (argc != 7) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << " vertexWeightFile"
         << " symmetrize[no/yes]"
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
  map<string, bool>::const_iterator it1 = symmetrizeMap.find(argv[3]);
  if (it1 == symmetrizeMap.end()) {
    cout << "invalid symmetrization condition" << endl;
    return 1;
  }
  bool symmetrize = it1->second;
  // get the vertex-weight algorithm type.
  map<string, VtxWghtAlgType> vtxWghtAlgTypeMap;
  vtxWghtAlgTypeMap["drct"] = eDrct;
  vtxWghtAlgTypeMap["spcl"] = eSpcl;
  map<string, VtxWghtAlgType>::const_iterator
    it2 = vtxWghtAlgTypeMap.find(argv[4]);
  if (it2 == vtxWghtAlgTypeMap.end()) {
    cout << "invalid vertex-weight algorithm type" << endl;
    return 1;
  }
  VtxWghtAlgType vtxWghtAlgType = it2->second;
  // get the direct vertex-weight algorithm type.
  map<string, BptMatchingEngine::DrctVtxWghtAlgType> drctVtxWghtAlgTypeMap;
  drctVtxWghtAlgTypeMap["gbl"] = BptMatchingEngine::eGbl;
  drctVtxWghtAlgTypeMap["lcl"] = BptMatchingEngine::eLcl;
  map<string, BptMatchingEngine::DrctVtxWghtAlgType>::const_iterator
    it3 = drctVtxWghtAlgTypeMap.find(argv[5]);
  if (it3 == drctVtxWghtAlgTypeMap.end()) {
    cout << "invalid direct vertex-weight algorithm type" << endl;
    return 1;
  }
  BptMatchingEngine::DrctVtxWghtAlgType drctVtxWghtAlgType = it3->second;
  // get the computation statistics printing condition.
  map<string, bool> statsPrintMap;
  statsPrintMap["no"] = false;
  statsPrintMap["yes"] = true;
  map<string, bool>::const_iterator it4 = statsPrintMap.find(argv[6]);
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
  cout << "reading vertex weights file ..." << endl;

    if (graph.ReadWeights(argv[2]) != eErrNone) {
      cout << "vertex weights file reading error: "<< endl;
      return 1;
    }
    cout << "done reading vertex weights file" << endl;
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
  Val vtxWght;
  Timer timer;
  BptMatchingEngine matchingEngine;
  
  // compute a maximum vertex-weight matching.
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  matchingEngine.SetVtxWghtAlgType(vtxWghtAlgType);
  matchingEngine.SetDrctVtxWghtAlgType(drctVtxWghtAlgType);
  matchingEngine.SetStatsPrint(statsPrint);
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeMaxVtxWghtMatching
    (graph, &sMateVec, &tMateVec, &card, &vtxWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  // print the time, weight and cardinality.
  timer.Print();
  cout << "weight: " <<fixed << vtxWght <<endl;
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
