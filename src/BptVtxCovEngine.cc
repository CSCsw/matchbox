#include "BptVtxCovEngine.h"

using namespace std;
using namespace Matchbox;

void BptVtxCovEngine::ComputeMinCardVtxCov(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size inCard,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* outCard, bool rvrs)
    const {
  // TODO: check validity of matching.
  // reset output.
  ResizeVector<Size>(sMarkVec, 0);
  ResizeVector<Size>(tMarkVec, 0);
  *outCard = 0;
  const Size* sMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &sMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tMateVec[0]);
  const Size* tMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &sMateVec[0]);
  vector<Size> tmpSMarkVec;
  ResizeVector<Size>(&tmpSMarkVec, graph.mSNumVtxs);
  vector<Size> tmpTMarkVec;
  ResizeVector<Size>(&tmpTMarkVec, graph.mTNumVtxs);
  Size* tmpSMarkArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMarkVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMarkVec[0]);
  Size* tmpTMarkArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMarkVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMarkVec[0]);
  switch (mQueAndStkType) {
  case eVecQueAndStk:
    rComputeMinCardVtxCov<VecItmQue>
      (graph, sMateArr, tMateArr, tmpSMarkArr, tmpTMarkArr, rvrs);
    break;
  case eLstQueAndStk:
    rComputeMinCardVtxCov<LstItmQue>
      (graph, sMateArr, tMateArr, tmpSMarkArr, tmpTMarkArr, rvrs);
    break;
  default:
    assert(false);
  }
  // set output.
  sMarkVec->swap(tmpSMarkVec);
  tMarkVec->swap(tmpTMarkVec);
  *outCard = inCard;
}

void BptVtxCovEngine::ComputeMinCardVtxCov(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size inCard,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* outCard) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMinCardVtxCov
      (graph, sMateVec, tMateVec, inCard, sMarkVec, tMarkVec, outCard, false);
  } else {
    ComputeMinCardVtxCov
      (graph, sMateVec, tMateVec, inCard, sMarkVec, tMarkVec, outCard, true);
  }
}

void BptVtxCovEngine::ComputeMinCardVtxCov(const BptGraph& graph,
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
    (graph, &sMateVec, &tMateVec, &matchingCard, rvrs);
  ComputeMinCardVtxCov
    (graph, sMateVec, tMateVec, matchingCard, sMarkVec, tMarkVec, card, rvrs);
}

void BptVtxCovEngine::ComputeMinCardVtxCov(const BptGraph& graph,
    vector<Size>* sMarkVec, vector<Size>* tMarkVec, Size* card) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMinCardVtxCov(graph, sMarkVec, tMarkVec, card, false);
  } else {
    ComputeMinCardVtxCov(graph, sMarkVec, tMarkVec, card, true);
  }
}
