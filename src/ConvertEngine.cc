#include "ConvertEngine.h"

using namespace std;
using namespace Matchbox;

Err ConvertEngine::Convert(const BptGraph& bptGraph, Graph* graph) {
  Size sNumVtxs;
  Size tNumVtxs;
  bptGraph.GetNumVtxs(&sNumVtxs, &tNumVtxs);
  if (CanAdd(sNumVtxs, tNumVtxs) == false) {
    return eErrInvNumVtxs;
  }
  Size numEdgs;
  bptGraph.GetNumEdgs(&numEdgs);
  vector<Size> sVtxVec;
  vector<Size> tVtxVec;
  vector<Val> edgWghtVec;
  bptGraph.GetEdgs(&sVtxVec, &tVtxVec, &edgWghtVec);
  assert(sVtxVec.size() == numEdgs);
  assert(tVtxVec.size() == numEdgs);
  assert(edgWghtVec.size() == numEdgs);
  Size* tVtxArr = (numEdgs == 0) ? NULL : &tVtxVec[0];
  for (Size k = 0; k < numEdgs; ++k) {
    tVtxArr[k] += sNumVtxs;
  }
  graph->Set(sNumVtxs + tNumVtxs, numEdgs, sVtxVec, tVtxVec, edgWghtVec);
  graph->GetNumEdgs(&numEdgs);
  assert(sVtxVec.size() == numEdgs);
  assert(tVtxVec.size() == numEdgs);
  assert(edgWghtVec.size() == numEdgs);
  return eErrNone;
}
