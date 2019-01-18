#include "BptIndSetEngine.h"

using namespace std;
using namespace Matchbox;

void BptIndSetEngine::ComputeMaxCardIndSet(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size inCard,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* outCard, bool rvrs)
    const {
  // reset output.
  ResizeVector<Size>(sMarkVec, 0);
  ResizeVector<Size>(tMarkVec, 0);
  *outCard = 0;
  BptVtxCovEngine vtxCovEngine;
  vtxCovEngine.SetInlz(mInlz);
  vtxCovEngine.SetQueAndStkType(mQueAndStkType);
  vtxCovEngine.SetIdxdQueType(mIdxdQueType);
  vtxCovEngine.SetCardGraphSrchType(mCardGraphSrchType);
  vtxCovEngine.SetPrecision(mPrecision);
  vtxCovEngine.SetStatsPrint(mStatsPrint);
  vector<Size> tmpSMarkVec;
  ResizeVector<Size>(&tmpSMarkVec, graph.mSNumVtxs);
  vector<Size> tmpTMarkVec;
  ResizeVector<Size>(&tmpTMarkVec, graph.mTNumVtxs);
  Size vtxCovCard = 0;
  vtxCovEngine.ComputeMinCardVtxCov
    (graph, sMateVec, tMateVec, inCard, &tmpSMarkVec, &tmpTMarkVec,
     &vtxCovCard, rvrs);
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  Size* tmpSMarkArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMarkVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMarkVec[0]);
  Size* tmpTMarkArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMarkVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMarkVec[0]);
  for (Size s = 0; s < sNumVtxs; ++s) {
    tmpSMarkArr[s] = 1 - tmpSMarkArr[s];
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    tmpTMarkArr[t] = 1 - tmpTMarkArr[t];
  }
  // set output.
  sMarkVec->swap(tmpSMarkVec);
  tMarkVec->swap(tmpTMarkVec);
  *outCard = sNumVtxs + tNumVtxs - vtxCovCard;
}

void BptIndSetEngine::ComputeMaxCardIndSet(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size inCard,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* outCard) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMaxCardIndSet
      (graph, sMateVec, tMateVec, inCard, sMarkVec, tMarkVec, outCard, false);
  } else {
    ComputeMaxCardIndSet
      (graph, sMateVec, tMateVec, inCard, sMarkVec, tMarkVec, outCard, true);
  }
}

void BptIndSetEngine::ComputeMaxCardIndSet(const BptGraph& graph,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* card, bool rvrs)
    const {
  BptMatchingEngine matchingEngine;
  matchingEngine.SetInlz(mInlz);
  matchingEngine.SetQueAndStkType(mQueAndStkType);
  matchingEngine.SetIdxdQueType(mIdxdQueType);
  matchingEngine.SetCardGraphSrchType(mCardGraphSrchType);
  matchingEngine.SetPrecision(mPrecision);
  matchingEngine.SetStatsPrint(mStatsPrint);
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size matchingCard = 0;
  matchingEngine.ComputeMaxCardMatching
    (graph, &sMateVec, &tMateVec, &matchingCard);
  ComputeMaxCardIndSet
    (graph, sMateVec, tMateVec, matchingCard, sMarkVec, tMarkVec, card, rvrs);
}

void BptIndSetEngine::ComputeMaxCardIndSet(const BptGraph& graph,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* card) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMaxCardIndSet(graph, sMarkVec, tMarkVec, card, false);
  } else {
    ComputeMaxCardIndSet(graph, sMarkVec, tMarkVec, card, true);
  }
}
