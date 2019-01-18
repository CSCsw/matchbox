#include "BptEdgCovEngine.h"

using namespace std;
using namespace Matchbox;

void BptEdgCovEngine::ComputeMinCardEdgCov(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size inCard,
    vector<list<Size> >* sMateLstVec, vector<list<Size> >* tMateLstVec,
    Size* outCard) const {
  // TODO: check validity of matching.
  // reset output.
  ResizeVector<list<Size> >(sMateLstVec, 0);
  ResizeVector<list<Size> >(tMateLstVec, 0);
  *outCard = 0;
  const Size* sMateArr = (graph.mSNumVtxs == 0) ? NULL : &sMateVec[0];
  const Size* tMateArr = (graph.mTNumVtxs == 0) ? NULL : &tMateVec[0];
  vector<list<Size> > tmpSMateLstVec;
  ResizeVector<list<Size> >(&tmpSMateLstVec, graph.mSNumVtxs);
  list<Size>*
    tmpSMateLstArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMateLstVec[0];
  vector<list<Size> > tmpTMateLstVec;
  ResizeVector<list<Size> >(&tmpTMateLstVec, graph.mTNumVtxs);
  list<Size>*
    tmpTMateLstArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMateLstVec[0];
  Size tmpOutCard = 0;
  rComputeMinCardEdgCov
    (graph, sMateArr, tMateArr, inCard, tmpSMateLstArr, tmpTMateLstArr,
     &tmpOutCard);
  // set output.
  sMateLstVec->swap(tmpSMateLstVec);
  tMateLstVec->swap(tmpTMateLstVec);
  *outCard = tmpOutCard;
}

void BptEdgCovEngine::ComputeMinCardEdgCov(const BptGraph& graph,
    vector<list<Size> >* sMateLstVec, vector<list<Size> >* tMateLstVec,
    Size* card, bool rvrs) const {
  BptMatchingEngine matchingEngine;
  matchingEngine.SetInlz(mInlz);
  matchingEngine.SetQueAndStkType(mQueAndStkType);
  matchingEngine.SetIdxdQueType(mIdxdQueType);
  matchingEngine.SetCardGraphSrchType(mCardGraphSrchType);
  matchingEngine.SetPrecision(mPrecision);
  matchingEngine.SetStatsPrint(mStatsPrint);
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size matchingCard;
  matchingEngine.ComputeMaxCardMatching
    (graph, &sMateVec, &tMateVec, &matchingCard, rvrs);
  ComputeMinCardEdgCov
    (graph, sMateVec, tMateVec, matchingCard, sMateLstVec, tMateLstVec, card);
}

void BptEdgCovEngine::ComputeMinCardEdgCov(const BptGraph& graph,
    vector<list<Size> >* sMateLstVec, vector<list<Size> >* tMateLstVec,
    Size* card) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMinCardEdgCov(graph, sMateLstVec, tMateLstVec, card, false);
  } else {
    ComputeMinCardEdgCov(graph, sMateLstVec, tMateLstVec, card, true);
  }
}

void BptEdgCovEngine::rComputeMinCardEdgCov(const BptGraph& graph,
    const Size* sMateArr, const Size* tMateArr, Size inCard,
    list<Size>* sMateLstArr, list<Size>* tMateLstArr, Size* outCard) const {
  *outCard = inCard;
  const vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
  const vector<Size>*
    tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    Size t = sMateArr[s];
    if (t != cNullItm) {
      // matched edge, covers its two matched endpoints.
      sMateLstArr[s].push_back(t);
      tMateLstArr[t].push_back(s);
    } else if (sVtxVecArr[s].size() > 0) {
      // arbitrary edge to cover exposed S-vertex.
      Size tt = sVtxVecArr[s][0];
      sMateLstArr[s].push_back(tt);
      tMateLstArr[tt].push_back(s);
      ++(*outCard);
    }
  }
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    Size s = tMateArr[t];
    if ((s == cNullItm) && (tVtxVecArr[t].size() > 0)) {
      // arbitrary edge to cover exposed T-vertex.
      Size ss = tVtxVecArr[t][0];
      tMateLstArr[t].push_back(ss);
      sMateLstArr[ss].push_back(t);
      ++(*outCard);
    }
  }
}
