#ifndef BPT_VTX_COV_ENGINE_H
#define BPT_VTX_COV_ENGINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for fill.
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "Utility.h" // for ResizeVector.
#include "VecItmQue.h"
#include "LstItmQue.h"

namespace Matchbox {

class BptVtxCovEngine {
public:
  /// Constructor.
  BptVtxCovEngine():
      mInlz(true), mQueAndStkType(eVecQueAndStk), mIdxdQueType(eLstIdxdQue),
      mCardGraphSrchType(eMplPathDfsLkhd), mPrecision(cMaxPrecision),
      mFullPrint(false), mStatsPrint(false) {}

  /// Destructor.
  ~BptVtxCovEngine() {}

  // a maximum cardinality matching is provided.
  // the vertex covering is computed from the matching.
  //
  // forced direction of graph searches. if rvrs is false then the direction of
  // graph searches is from S to T, otherwise it is from T to S.
  //
  // graph searches are performed:
  // - during the computation of the vertex covering.
  void ComputeMinCardVtxCov(const BptGraph& graph,
                            const std::vector<Size>& sMateVec,
                            const std::vector<Size>& tMateVec,
                            Size inCard,
                            std::vector<Size>* sMarkVec,
                            std::vector<Size>* tMarkVec,
                            Size* outCard,
                            bool rvrs) const;

  // a maximum cardinality matching is provided.
  // the vertex covering is computed from the matching.
  //
  // automatic direction of graph searches. if |S| <= |T| then the direction of
  // graph searches is from S to T, otherwise it is from T to S.
  //
  // graph searches are performed:
  // - during the computation of the vertex covering.
  void ComputeMinCardVtxCov(const BptGraph& graph,
                            const std::vector<Size>& sMateVec,
                            const std::vector<Size>& tMateVec,
                            Size inCard,
                            std::vector<Size>* sMarkVec,
                            std::vector<Size>* tMarkVec,
                            Size* outCard) const;

  // a maximum cardinality matching is computed.
  // the vertex covering is computed from the matching.
  //
  // forced direction of graph searches. if rvrs is false then the direction of
  // graph searches is from S to T, otherwise it is from T to S.
  //
  // graph searches are performed:
  // - during the computation of the matching;
  // - during the computation of the vertex covering.
  void ComputeMinCardVtxCov(const BptGraph& graph,
                            std::vector<Size>* sMarkVec,
                            std::vector<Size>* tMarkVec,
                            Size* card,
                            bool rvrs) const;

  // a maximum cardinality matching is computed.
  // the vertex covering is computed from the matching.
  //
  // automatic direction of graph searches. if |S| <= |T| then the direction of
  // graph searches is from S to T, otherwise it is from T to S.
  //
  // graph searches are performed:
  // - during the computation of the matching;
  // - during the computation of the vertex covering.
  void ComputeMinCardVtxCov(const BptGraph& graph,
                            std::vector<Size>* sMarkVec,
                            std::vector<Size>* tMarkVec,
                            Size* card) const;

  ///
  void SetInlz(bool inlz) { mInlz = inlz; }

  ///
  Err SetQueAndStkType(QueAndStkType queAndStkType) {
    switch (queAndStkType) {
    case eVecQueAndStk:
    case eLstQueAndStk:
      mQueAndStkType = queAndStkType;
      return eErrNone;
    default:
      return eErrInvType;
    }
  }

  ///
  Err SetIdxdQueType(IdxdQueType idxdQueType) {
    switch (idxdQueType) {
    case eLstIdxdQue:
      mIdxdQueType = idxdQueType;
      return eErrNone;
    default:
      return eErrInvType;
    }
  }

  ///
  Err SetCardGraphSrchType(GraphSrchType cardGraphSrchType) {
    switch (cardGraphSrchType) {
    case eSglSrcBfs:
    case eSglSrcDfs:
    case eSglSrcDfsLkhd:
    case eMplSrcSglPath:
    case eMplPathDfs:
    case eMplPathDfsLkhd:
    case eMplPathBfsDfs:
      mCardGraphSrchType = cardGraphSrchType;
      return eErrNone;
    default:
      return eErrInvType;
    }
  }

  ///
  Err SetPrecision(Size precision) {
    if (precision > cMaxPrecision) {
      return eErrInvPrecision;
    }
    mPrecision = precision;
    return eErrNone;
  }

  ///
  void SetFullPrint(bool fullPrint) { mFullPrint = fullPrint; }

  ///
  void SetStatsPrint(bool statsPrint) { mStatsPrint = statsPrint; }

private:
  // controls the greedy initialization of a matching: if false then do not
  // perform greedy initialization, if true then perform greedy initialization.
  bool mInlz;
  // type of queue and stack used for vertex processing.
  QueAndStkType mQueAndStkType;
  // type of indexed queue used for vertex and weight processing.
  IdxdQueType mIdxdQueType;
  // type of graph search used for the computation of a maximum cardinality
  // matching.
  GraphSrchType mCardGraphSrchType;
  // precision used for printing floating point numbers.
  Size mPrecision;
  // controls the amount of printing: if false then print less information,
  // if true then print more information.
  bool mFullPrint;
  // controls the printing of computation statistics: if false then do not
  // print computation statistics, if true then print computation statistics.
  bool mStatsPrint;

  // forbid the copy constructor and the assignment operator.
  BptVtxCovEngine(const BptVtxCovEngine&);
  BptVtxCovEngine& operator=(const BptVtxCovEngine&);

  template<class Queue>
  void rComputeMinCardVtxCov(const BptGraph& graph,
                             const Size* sMateArr,
                             const Size* tMateArr,
                             Size* sMarkArr,
                             Size* tMarkArr,
                             bool rvrs) const;
}; // class BptVtxCovEngine

template<class ItmQue>
void BptVtxCovEngine::rComputeMinCardVtxCov(const BptGraph& graph,
    const Size* sMateArr, const Size* tMateArr, Size* sMarkArr, Size* tMarkArr,
    bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMarkArr != NULL) {
    std::fill(&sMarkArr[0], &sMarkArr[sNumVtxs], 0);
  }
  if (tMarkArr != NULL) {
    std::fill(&tMarkArr[0], &tMarkArr[tNumVtxs], 0);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  // pick all matched T-vertices along alternating paths starting at exposed
  // S-vertices.
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sPrcsbQue.Push(s);
      sSttArr[s] = eSttBfsPrcsb;
    }
  }
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sSttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      Size ss = tMateArr[t];
      if (sSttArr[ss] != eSttIdle) {
        continue;
      }
      tMarkArr[t] = 1;
      sPrcsbQue.Push(ss);
      sSttArr[ss] = eSttBfsPrcsb;
    }
  }
  // pick all matched S-vertices whose mates are not already picked.
  for (Size s = 0; s < sNumVtxs; ++s) {
    Size t = sMateArr[s];
    if ((t != cNullItm) && (tMarkArr[t] == 0)) {
      sMarkArr[s] = 1;
    }
  }
}

} // namespace Matchbox

#endif // BPT_VTX_COV_ENGINE_H
