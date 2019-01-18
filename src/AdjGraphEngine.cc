#include "AdjGraphEngine.h"

using namespace std;
using namespace Matchbox;

Err AdjGraphEngine::GetAdjGraph(const BptGraph& bptGraph, Graph* adjGraph) {
  Size sNumVtxs(0);
  Size tNumVtxs(0);
  bptGraph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  if (sNumVtxs != tNumVtxs) {
    return eErrNotSymmetrizable;
  }
  Size numEdgs(0);
  bptGraph.GetNumEdgs(&numEdgs);
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  bptGraph.GetEdgs(&sVtxVec, &tVtxVec, &edgWghtVec);
  assert(sVtxVec.size() == numEdgs);
  assert(tVtxVec.size() == numEdgs);
  assert(edgWghtVec.size() == numEdgs);
  Size* sVtxArr = (numEdgs == 0) ? NULL : &sVtxVec[0];
  Size* tVtxArr = (numEdgs == 0) ? NULL : &tVtxVec[0];
  Val* edgWghtArr = (numEdgs == 0) ? NULL : &edgWghtVec[0];
  Size tmpNumVtxs = sNumVtxs;
  Size tmpNumEdgs = 0;
  vector<Size> tmpSVtxVec;
  vector<Size> tmpTVtxVec;
  vector<Val> tmpEdgWghtVec;
  for (Size k = 0; k < numEdgs; ++k) {
    if (sVtxArr[k] != tVtxArr[k]) {
      ++tmpNumEdgs;
      tmpSVtxVec.push_back(sVtxArr[k]);
      tmpTVtxVec.push_back(tVtxArr[k]);
      tmpEdgWghtVec.push_back(edgWghtArr[k]);
    }
  }
  adjGraph->Set(tmpNumVtxs, tmpNumEdgs, tmpTVtxVec, tmpSVtxVec, tmpEdgWghtVec);
  adjGraph->GetNumEdgs(&tmpNumEdgs);
//  assert(tmpSVtxVec.size() == tmpNumEdgs);
//  assert(tmpTVtxVec.size() == tmpNumEdgs);
//  assert(tmpEdgWghtVec.size() == tmpNumEdgs);
  return eErrNone;
}
