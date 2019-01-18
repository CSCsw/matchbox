#ifndef BPT_CANONICAL_ENGINE_H
#define BPT_CANONICAL_ENGINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm> // for min, fill, copy.
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "Utility.h" // for ResizeVector.
#include "VecItmQue.h"
#include "LstItmQue.h"

namespace Matchbox {

class BptCanonicalEngine {
public:
  enum CoarseType {
    eHrz = 0,
    eSqr,
    eVrt
  };

  /// Constructor.
  BptCanonicalEngine():
      mInlz(true), mQueAndStkType(eVecQueAndStk), mIdxdQueType(eLstIdxdQue),
      mIdxdPriQueType(eBhpIdxdPriQue), mCardGraphSrchType(eMplPathDfsLkhd),
      mEdgWghtGraphSrchType(eSglSrcBfs), mVtxWghtAlgType(eSpcl),
      mDrctVtxWghtAlgType(BptMatchingEngine::eGbl), mPrecision(cMaxPrecision),
      mFullPrint(false), mStatsPrint(false) {}

  /// Destructor.
  ~BptCanonicalEngine() {}

  ///
  /// a maximum cardinality matching is available.
  void PartitionCoarse(const BptGraph& graph,
                       const std::vector<Size>& sMateVec,
                       const std::vector<Size>& tMateVec,
                       std::vector<CoarseType>* sCoarseVec,
                       std::vector<CoarseType>* tCoarseVec,
                       Size* sNumHrzVtxs,
                       Size* tNumHrzVtxs,
                       Size* sNumSqrVtxs,
                       Size* tNumSqrVtxs,
                       Size* sNumVrtVtxs,
                       Size* tNumVrtVtxs) const;

  ///
  /// a maximum cardinality matching already is not available.
  void PartitionCoarse(const BptGraph& graph,
                       std::vector<CoarseType>* sCoarseVec,
                       std::vector<CoarseType>* tCoarseVec,
                       Size* sNumHrzVtxs,
                       Size* tNumHrzVtxs,
                       Size* sNumSqrVtxs,
                       Size* tNumSqrVtxs,
                       Size* sNumVrtVtxs,
                       Size* tNumVrtVtxs) const;

  ///
  /// connected components within each coarse component.
  void PartitionMedium(const BptGraph& graph,
                       const std::vector<CoarseType>& sCoarseVec,
                       const std::vector<CoarseType>& tCoarseVec,
                       std::vector<Size>* sMediumVec,
                       std::vector<Size>* tMediumVec,
                       Size* numHrzMediumCmpnts,
                       Size* numSqrMediumCmpnts,
                       Size* numVrtMediumCmpnts) const;

  ///
  /// strongly connected components within the square coarse component.
  /// TODO: explain direction with respect to strong connectivity.
  void PartitionFine(const BptGraph& graph,
                     const std::vector<Size>& tMateVec,
                     const std::vector<CoarseType>& tCoarseVec,
                     const std::vector<Size>& tMediumVec,
                     Size numSqrMediumCmpnts,
                     std::vector<Size>* sFineVec,
                     std::vector<Size>* tFineVec,
                     Size* numSqrFineCmpnts) const;

  ///
  /// TODO: have just one input/output card argument. no need for two.
  void ComputeMaxCardMaxEdgWghtMatching(const BptGraph& graph,
                                        const std::vector<Size>& sInMateVec,
                                        const std::vector<Size>& tInMateVec,
                                        Size inCard,
                                        const std::vector<CoarseType>&
                                          sCoarseVec,
                                        const std::vector<CoarseType>&
                                          tCoarseVec,
                                        Size sNumHrzVtxs,
                                        Size tNumHrzVtxs,
                                        Size sNumSqrVtxs,
                                        Size tNumSqrVtxs,
                                        Size sNumVrtVtxs,
                                        Size tNumVrtVtxs,
                                        std::vector<Size>* sOutMateVec,
                                        std::vector<Size>* tOutMateVec,
                                        Size* outCard,
                                        Val* edgWght) const;

  ///
  /// TODO: have just one input/output card argument. no need for two.
  void ComputeMaxVtxWghtMatching(const BptGraph& graph,
                                 const std::vector<Size>& sInMateVec,
                                 const std::vector<Size>& tInMateVec,
                                 Size inCard,
                                 const std::vector<CoarseType>&
                                   sCoarseVec,
                                 const std::vector<CoarseType>&
                                   tCoarseVec,
                                 Size sNumHrzVtxs,
                                 Size tNumHrzVtxs,
                                 Size sNumSqrVtxs,
                                 Size tNumSqrVtxs,
                                 Size sNumVrtVtxs,
                                 Size tNumVrtVtxs,
                                 std::vector<Size>* sOutMateVec,
                                 std::vector<Size>* tOutMateVec,
                                 Size* outCard,
                                 Val* vtxWght) const;

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
  Err SetIdxdPriQueType(IdxdPriQueType idxdPriQueType) {
    switch (idxdPriQueType) {
    case eLstIdxdPriQue:
    case eBhpIdxdPriQue:
      mIdxdPriQueType = idxdPriQueType;
      return eErrNone;
    case eFhpIdxdPriQue:
      // TODO: add fibonacci heap indexed priority queue data structure.
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
  Err SetEdgWghtGraphSrchType(GraphSrchType edgWghtGraphSrchType) {
    switch (edgWghtGraphSrchType) {
    case eSglSrcBfs:
      mEdgWghtGraphSrchType = edgWghtGraphSrchType;
      return eErrNone;
    case eMplSrcSglPath:
      // TODO: add multiple source edge-weight computations.
    default:
      // TODO: reformulate the comment below in the context of more algorithms.
      // multiple path edge-weight computations are not implemented since they
      // are generally not expected to improve the performance, given the fact
      // that it is generally unlikely to find a significant number of
      // augmenting paths in the tight graph during a particular iteration.
      return eErrInvType;
    }
  }

  ///
  Err SetVtxWghtAlgType(VtxWghtAlgType vtxWghtAlgType) {
    switch (vtxWghtAlgType) {
    case eDrct:
    case eSpcl:
      mVtxWghtAlgType = vtxWghtAlgType;
      return eErrNone;
    default:
      return eErrInvType;
    }
  }

  ///
  Err SetDrctVtxWghtAlgType(
      BptMatchingEngine::DrctVtxWghtAlgType drctVtxWghtAlgType) {
    switch (drctVtxWghtAlgType) {
    case BptMatchingEngine::eGbl:
    case BptMatchingEngine::eLcl:
      mDrctVtxWghtAlgType = drctVtxWghtAlgType;
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

  ///
  void PrintCoarse(const std::vector<CoarseType>& sCoarseVec,
                   const std::vector<CoarseType>& tCoarseVec,
                   Size sNumHrzVtxs,
                   Size tNumHrzVtxs,
                   Size sNumSqrVtxs,
                   Size tNumSqrVtxs,
                   Size sNumVrtVtxs,
                   Size tNumVrtVtxs) const;

  ///
  void PrintMedium(const std::vector<Size>& sMediumVec,
                   const std::vector<Size>& tMediumVec,
                   Size numHrzMediumCmpnts,
                   Size numSqrMediumCmpnts,
                   Size numVrtMediumCmpnts) const;

  ///
  void PrintFine(const std::vector<Size>& sFineVec,
                 const std::vector<Size>& tFineVec,
                 Size numSqrFineCmpnts) const;

private:
  // controls the greedy initialization of a matching: if false then do not
  // perform greedy initialization, if true then perform greedy initialization.
  bool mInlz;
  // type of queue and stack used for vertex processing.
  QueAndStkType mQueAndStkType;
  // type of indexed queue used for vertex and weight processing.
  IdxdQueType mIdxdQueType;
  // type of indexed priority queue used for vertex and weight processing.
  IdxdPriQueType mIdxdPriQueType;
  // type of graph search used for the computation of a maximum cardinality
  // matching.
  GraphSrchType mCardGraphSrchType;
  // type of graph search used for the computation of a maximum edge-weight
  // matching.
  GraphSrchType mEdgWghtGraphSrchType;
  // type of algorithm used for the computation of a maximum vertex-weight
  // matching.
  VtxWghtAlgType mVtxWghtAlgType;
  // type of algorithm used for the direct computation of a maximum
  // vertex-weight matching.
  BptMatchingEngine::DrctVtxWghtAlgType mDrctVtxWghtAlgType;
  // precision used for printing floating point numbers.
  Size mPrecision;
  // controls the amount of printing: if false then print less information,
  // if true then print more information.
  bool mFullPrint;
  // controls the printing of computation statistics: if false then do not
  // print computation statistics, if true then print computation statistics.
  bool mStatsPrint;

  //
  static const Size cNumCoarseCmpnts;

  // forbid the copy constructor and the assignment operator.
  BptCanonicalEngine(const BptCanonicalEngine&);
  BptCanonicalEngine& operator=(const BptCanonicalEngine&);

  ///
  template<class ItmQue>
  void rProcessMedium(const BptGraph& graph,
                      const CoarseType* sCoarseArr,
                      const CoarseType* tCoarseArr,
                      const std::list<Size>* sVtxLstArr,
                      Stt* sSttArr,
                      Stt* tSttArr,
                      ItmQue& sPrcsbQue,
                      ItmQue& tPrcsbQue,
                      Size* sMediumArr,
                      Size* tMediumArr,
                      Size* numMediumCmpnts,
                      CoarseType coarse) const;

  ///
  template<class ItmQue>
  void rPartitionCoarse(const BptGraph& graph,
                        const Size* sMateArr,
                        const Size* tMateArr,
                        CoarseType* sCoarseArr,
                        CoarseType* tCoarseArr,
                        Size* sNumHrzVtxs,
                        Size* tNumHrzVtxs,
                        Size* sNumSqrVtxs,
                        Size* tNumSqrVtxs,
                        Size* sNumVrtVtxs,
                        Size* tNumVrtVtxs) const;

  ///
  template<class ItmQue>
  void rPartitionMedium(const BptGraph& graph,
                        const CoarseType* sCoarseArr,
                        const CoarseType* tCoarseArr,
                        Size* sMediumArr,
                        Size* tMediumArr,
                        Size* numHrzMediumCmpnts,
                        Size* numSqrMediumCmpnts,
                        Size* numVrtMediumCmpnts) const;

  ///
  template<class ItmQue,
           class ItmStk>
  void rPartitionFine(const BptGraph& graph,
                      const Size* tMateArr,
                      const CoarseType* tCoarseArr,
                      const Size* tMediumarr,
                      Size numSqrMediumCmpnts,
                      Size* sFineArr,
                      Size* tFineArr,
                      Size* numSqrFineCmpnts) const;

  ///
  void rComputeMaxCardMaxWghtMatching(const BptGraph& graph,
                                      const Size* sInMateArr,
                                      const Size* tInMateArr,
                                      Size inCard,
                                      const CoarseType* sCoarseArr,
                                      const CoarseType* tCoarseArr,
                                      Size sNumHrzVtxs,
                                      Size tNumHrzVtxs,
                                      Size sNumSqrVtxs,
                                      Size tNumSqrVtxs,
                                      Size sNumVrtVtxs,
                                      Size tNumVrtVtxs,
                                      Size* sOutMateArr,
                                      Size* tOutMateArr,
                                      Size* outCard,
                                      Val* wght,
                                      bool vtxWght) const;
}; // class BptCanonicalEngine

template<class ItmQue>
void BptCanonicalEngine::rProcessMedium(const BptGraph& graph,
    const CoarseType* sCoarseArr, const CoarseType* tCoarseArr,
    const std::list<Size>* sVtxLstArr, Stt* sSttArr, Stt* tSttArr,
    ItmQue& sPrcsbQue, ItmQue& tPrcsbQue, Size* sMediumArr, Size* tMediumArr,
    Size* numMediumCmpnts, CoarseType coarse) const {
  const std::vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
  const std::vector<Size>*
    tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];
  for (std::list<Size>::const_iterator it = sVtxLstArr[coarse].begin();
       it != sVtxLstArr[coarse].end(); ++it) {
    Size sRoot = *it;
    if (sSttArr[sRoot] != eSttIdle) {
      continue;
    }
    if (sVtxVecArr[sRoot].empty() == true) {
      continue;
    }
    sMediumArr[sRoot] = *numMediumCmpnts;
    sPrcsbQue.Push(sRoot);
    sSttArr[sRoot] = eSttBfsPrcsb;
    while (sPrcsbQue.Empty() == false) {
      while (sPrcsbQue.Empty() == false) {
        Size s = sPrcsbQue.Front();
        sPrcsbQue.Pop();
        sSttArr[s] = eSttBfsPrcsd;
        Size sNumEdgs = sVtxVecArr[s].size();
        const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
        for (Size i = 0; i < sNumEdgs; ++i) {
          Size t = sVtxArr[i];
          if (tCoarseArr[t] != coarse) {
            // confine the graph search to the current coarse component.
            continue;
          }
          if (tSttArr[t] != eSttIdle) {
            continue;
          }
          tMediumArr[t] = *numMediumCmpnts;
          tPrcsbQue.Push(t);
          tSttArr[t] = eSttBfsPrcsb;
        }
      }
      while (tPrcsbQue.Empty() == false) {
        Size t = tPrcsbQue.Front();
        tPrcsbQue.Pop();
        tSttArr[t] = eSttBfsPrcsd;
        Size tNumEdgs = tVtxVecArr[t].size();
        const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
        for (Size j = 0; j < tNumEdgs; ++j) {
          Size s = tVtxArr[j];
          if (sCoarseArr[s] != coarse) {
            // confine the graph search to the current coarse component.
            continue;
          }
          if (sSttArr[s] != eSttIdle) {
            continue;
          }
          sMediumArr[s] = *numMediumCmpnts;
          sPrcsbQue.Push(s);
          sSttArr[s] = eSttBfsPrcsb;
        }
      }
    }
    ++(*numMediumCmpnts);
  }
}

template<class ItmQue>
void BptCanonicalEngine::rPartitionCoarse(const BptGraph& graph,
    const Size* sMateArr, const Size* tMateArr, CoarseType* sCoarseArr,
    CoarseType* tCoarseArr, Size* sNumHrzVtxs, Size* tNumHrzVtxs,
    Size* sNumSqrVtxs, Size* tNumSqrVtxs, Size* sNumVrtVtxs, Size* tNumVrtVtxs)
    const {
  // TODO: return an error if the matching does not have maximum cardinality.
  // TODO: make the function more modular, call another function with reverse
  // common for the vertical/horizontal parts.
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, graph.mSNumVtxs);
  Stt* sSttArr = (graph.mSNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[graph.mSNumVtxs], eSttIdle);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, graph.mTNumVtxs);
  Stt* tSttArr = (graph.mTNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[graph.mTNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(graph.mSNumVtxs);
  ItmQue tPrcsbQue(graph.mTNumVtxs);
  // square partition. mark all vertices as belonging to the square partition,
  // then overwrite for those belonging to the horizontal and vertical
  // partitions.
  *sNumHrzVtxs = 0;
  *tNumHrzVtxs = 0;
  *sNumSqrVtxs = graph.mSNumVtxs;
  *tNumSqrVtxs = graph.mTNumVtxs;
  *sNumVrtVtxs = 0;
  *tNumVrtVtxs = 0;
  if (sCoarseArr != NULL) {
    std::fill(&sCoarseArr[0], &sCoarseArr[graph.mSNumVtxs], eSqr);
  }
  if (tCoarseArr != NULL) {
    std::fill(&tCoarseArr[0], &tCoarseArr[graph.mTNumVtxs], eSqr);
  }
  // horizontal partition. mark all vertices on alternating paths starting at
  // exposed T-vertices.
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    if (tMateArr[t] == cNullItm) {
      tCoarseArr[t] = eHrz;
      --(*tNumSqrVtxs);
      ++(*tNumHrzVtxs);
      tPrcsbQue.Push(t);
      tSttArr[t] = eSttBfsPrcsb;
    }
  }
  const std::vector<Size>*
    tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];
  while (tPrcsbQue.Empty() == false) {
    Size t = tPrcsbQue.Front();
    tPrcsbQue.Pop();
    tSttArr[t] = eSttBfsPrcsd;
    Size tNumEdgs = tVtxVecArr[t].size();
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tVtxArr[j];
      Size tt = sMateArr[s];
      if (tSttArr[tt] != eSttIdle) {
        continue;
      }
      sCoarseArr[s] = eHrz;
      --(*sNumSqrVtxs);
      ++(*sNumHrzVtxs);
      tCoarseArr[tt] = eHrz;
      --(*tNumSqrVtxs);
      ++(*tNumHrzVtxs);
      tPrcsbQue.Push(tt);
      tSttArr[tt] = eSttBfsPrcsb;
    }
  }
  // vertical partition. mark all vertices on alternating paths starting at
  // exposed S-vertices.
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sCoarseArr[s] = eVrt;
      --(*sNumSqrVtxs);
      ++(*sNumVrtVtxs);
      sPrcsbQue.Push(s);
      sSttArr[s] = eSttBfsPrcsb;
    }
  }
  const std::vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
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
      tCoarseArr[t] = eVrt;
      --(*tNumSqrVtxs);
      ++(*tNumVrtVtxs);
      sCoarseArr[ss] = eVrt;
      --(*sNumSqrVtxs);
      ++(*sNumVrtVtxs);
      sPrcsbQue.Push(ss);
      sSttArr[ss] = eSttBfsPrcsb;
    }
  }
  assert(*sNumHrzVtxs <= *tNumHrzVtxs);
  assert(*sNumSqrVtxs == *tNumSqrVtxs);
  assert(*sNumVrtVtxs >= *tNumVrtVtxs);
}

template<class ItmQue>
void BptCanonicalEngine::rPartitionMedium(const BptGraph& graph,
    const CoarseType* sCoarseArr, const CoarseType* tCoarseArr,
    Size* sMediumArr, Size* tMediumArr, Size* numHrzMediumCmpnts,
    Size* numSqrMediumCmpnts, Size* numVrtMediumCmpnts) const {
  *numHrzMediumCmpnts = 0;
  *numSqrMediumCmpnts = 0;
  *numVrtMediumCmpnts = 0;
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, graph.mSNumVtxs);
  Stt* sSttArr = (graph.mSNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[graph.mSNumVtxs], eSttIdle);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, graph.mTNumVtxs);
  Stt* tSttArr = (graph.mTNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[graph.mTNumVtxs], eSttIdle);
  }
  // use a vector of lists in order to group the S-vertices within the coarse
  // components. the processing is performed from the S-side. the side choice
  // does not matter since the processing traverses all edges.
  std::vector<std::list<Size> > sVtxLstVec;
  ResizeVector<std::list<Size> >(&sVtxLstVec, cNumCoarseCmpnts);
  assert(cNumCoarseCmpnts > 0);
  std::list<Size>* sVtxLstArr = &sVtxLstVec[0];
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    sVtxLstArr[sCoarseArr[s]].push_back(s);
  }
  ItmQue sPrcsbQue(graph.mSNumVtxs);
  ItmQue tPrcsbQue(graph.mTNumVtxs);
  // handle trivial horizontal medium components represented by isolated
  // T-vertices.
  const std::vector<Size>*
    tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    if (tVtxVecArr[t].empty() == true) {
      tMediumArr[t] = *numHrzMediumCmpnts;
      ++(*numHrzMediumCmpnts);
    }
  }
  // handle nontrivial (not corresponding to isolated vertices) horizontal,
  // square and vertical medium components by searching from S. process the
  // coarse components sequentially. this guarantees that the medium components
  // are considered consecutively within the coarse components.
  rProcessMedium<ItmQue>
    (graph, sCoarseArr, tCoarseArr, sVtxLstArr, sSttArr, tSttArr, sPrcsbQue,
     tPrcsbQue, sMediumArr, tMediumArr, numHrzMediumCmpnts, eHrz);
  rProcessMedium<ItmQue>
    (graph, sCoarseArr, tCoarseArr, sVtxLstArr, sSttArr, tSttArr, sPrcsbQue,
     tPrcsbQue, sMediumArr, tMediumArr, numSqrMediumCmpnts, eSqr);
  rProcessMedium<ItmQue>
    (graph, sCoarseArr, tCoarseArr, sVtxLstArr, sSttArr, tSttArr, sPrcsbQue,
     tPrcsbQue, sMediumArr, tMediumArr, numVrtMediumCmpnts, eVrt);
  // handle trivial vertical medium components represented by isolated
  // S-vertices.
  const std::vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    if (sVtxVecArr[s].empty() == true) {
      sMediumArr[s] = *numVrtMediumCmpnts;
      ++(*numVrtMediumCmpnts);
    }
  }
}

template<class ItmQue, class ItmStk>
void BptCanonicalEngine::rPartitionFine(const BptGraph& graph,
    const Size* tMateArr, const CoarseType* tCoarseArr,
    const Size* tMediumArr, Size numSqrMediumCmpnts, Size* sFineArr,
    Size* tFineArr, Size* numSqrFineCmpnts) const {
  // first phase: determine the fine partitions (only within the square coarse
  // partition).
  // the fine partitions correspond to the strongly connected components of
  // a directed graph obtained by merging the endpoints of the matching edges
  // and assigning direction to the free edges. one can determine the strongly
  // components by assigning direction either from S to T or from T to S but
  // for proper ordering reasons the direction needs to be from T to S. use
  // tarjan's depth first search based algorithm for computing strongly
  // connected components. the depth first search procedure is implemented
  // nonrecursively with an explicit stack.
  *numSqrFineCmpnts = 0;
  std::vector<Size> tPtrVec;
  ResizeVector<Size>(&tPtrVec, graph.mTNumVtxs);
  Size* tPtrArr = (graph.mTNumVtxs == 0) ? NULL : &tPtrVec[0];
  if (tPtrArr != NULL) {
    std::fill(&tPtrArr[0], &tPtrArr[graph.mTNumVtxs], cNullItm);
  }
  std::vector<Size> tSeqNumVec;
  ResizeVector<Size>(&tSeqNumVec, graph.mTNumVtxs);
  Size* tSeqNumArr = (graph.mTNumVtxs == 0) ? NULL : &tSeqNumVec[0];
  if (tSeqNumArr != NULL) {
    std::fill(&tSeqNumArr[0], &tSeqNumArr[graph.mTNumVtxs], 0);
  }
  std::vector<Size> tLowLnkVec;
  ResizeVector<Size>(&tLowLnkVec, graph.mTNumVtxs);
  Size* tLowLnkArr = (graph.mTNumVtxs == 0) ? NULL : &tLowLnkVec[0];
  if (tLowLnkArr != NULL) {
    std::fill(&tLowLnkArr[0], &tLowLnkArr[graph.mTNumVtxs], 0);
  }
  std::vector<Size> tCmpntVec;
  ResizeVector<Size>(&tCmpntVec, graph.mTNumVtxs);
  Size* tCmpntArr = (graph.mTNumVtxs == 0) ? NULL : &tCmpntVec[0];
  if (tCmpntArr != NULL) {
    std::fill(&tCmpntArr[0], &tCmpntArr[graph.mTNumVtxs], 0);
  }
  std::vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, graph.mSNumVtxs);
  Size* sIdxArr = (graph.mSNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    std::fill(&sIdxArr[0], &sIdxArr[graph.mSNumVtxs], 0);
  }
  std::vector<Size> tStkdVec;
  ResizeVector<Size>(&tStkdVec, graph.mTNumVtxs);
  Size* tStkdArr = (graph.mTNumVtxs == 0) ? NULL : &tStkdVec[0];
  if (tStkdArr != NULL) {
    std::fill(&tStkdArr[0], &tStkdArr[graph.mTNumVtxs], 0);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, graph.mTNumVtxs);
  Stt* tSttArr = (graph.mTNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[graph.mTNumVtxs], eSttIdle);
  }
  ItmStk tPrcsbStk(graph.mTNumVtxs);
  ItmStk tCmpntStk(graph.mTNumVtxs);
  Size seqNum = 0;
  Size numCmpnts = 0;
  const std::vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
  for (Size tRoot = 0; tRoot < graph.mTNumVtxs; ++tRoot) {
    if ((tCoarseArr[tRoot] != eSqr) || (tSttArr[tRoot] != eSttIdle)) {
      // confine the graph search to the square coarse partition.
      continue;
    }
    tSeqNumArr[tRoot] = seqNum;
    tLowLnkArr[tRoot] = seqNum;
    ++seqNum;
    tCmpntStk.Push(tRoot);
    tStkdArr[tRoot] = 1;
    tPrcsbStk.Push(tRoot);
    tSttArr[tRoot] = eSttBfsPrcsb;
    while (tPrcsbStk.Empty() == false) {
      Size t = tPrcsbStk.Top();
      Size s = tMateArr[t];
      assert(s != cNullItm);
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      if (sIdxArr[s] < sNumEdgs) {
        // keep traversing the adjacency of s.
        Size tt = sVtxArr[sIdxArr[s]];
        ++(sIdxArr[s]);
        if ((tCoarseArr[tt] == eSqr) && (tt != t)) {
          // confine the graph search to the square coarse partition.
          if (tSttArr[tt] == eSttIdle) {
            // depth first search tree edge (tt not yet visited).
            tPtrArr[tt] = t;
            tSeqNumArr[tt] = seqNum;
            tLowLnkArr[tt] = seqNum;
            ++seqNum;
            tCmpntStk.Push(tt);
            tStkdArr[tt] = 1;
            tPrcsbStk.Push(tt);
            tSttArr[tt] = eSttBfsPrcsb;
          } else if (tSeqNumArr[tt] < tSeqNumArr[t]) {
            // depth first search back or cross edge (tt already visited).
            if (tStkdArr[tt] == 1) {
              tLowLnkArr[t] = std::min(tLowLnkArr[t], tSeqNumArr[tt]);
            }
          }
        }
      } else {
        // done with the adjacency of s.
        if (tLowLnkArr[t] == tSeqNumArr[t]) {
          // t is the root of a strongly connected component.
          Size tt;
          do {
            tt = tCmpntStk.Top();
            tCmpntArr[tt] = numCmpnts;
            tCmpntStk.Pop();
            tStkdArr[tt] = 0;
          } while (tt != t);
          ++numCmpnts;
        }
        if (tPtrArr[t] != cNullItm) {
          tLowLnkArr[tPtrArr[t]] =
            std::min(tLowLnkArr[tPtrArr[t]], tLowLnkArr[t]);
        }
        tPrcsbStk.Pop();
        tSttArr[t] = eSttBfsPrcsd;
      }
    }
  }
  // second phase: order the fine partitions (only within the square coarse
  // partition).
  // the strongly connected components computed in the first phase are not
  // ordered topologically. a topological order is required by the block
  // triangular form, therefore perform a topological sort.
  std::vector<Size> vstdVec;
  ResizeVector<Size>(&vstdVec, numCmpnts);
  Size* vstdArr = (numCmpnts == 0) ? NULL : &vstdVec[0];
  if (vstdArr != NULL) {
    std::fill(&vstdArr[0], &vstdArr[numCmpnts], 0);
  }
  // use a vector of lists in order to group the strongly connected components
  // within the square medium partitions.
  std::vector<std::list<Size> > cmpntLstVec;
  ResizeVector<std::list<Size> >(&cmpntLstVec, numSqrMediumCmpnts);
  std::list<Size>* cmpntLstArr =
    (numSqrMediumCmpnts == 0) ? NULL : &cmpntLstVec[0];
  // use a vector of lists in order to group the vertices within the strongly
  // connected components.
  std::vector<std::list<Size> > tVtxLstVec;
  ResizeVector<std::list<Size> >(&tVtxLstVec, numCmpnts);
  std::list<Size>* tVtxLstArr = (numCmpnts == 0) ? NULL : &tVtxLstVec[0];
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    if (tCoarseArr[t] == eSqr) {
      // confine the graph search to the square coarse partition.
      Size c = tCmpntArr[t];
      tVtxLstArr[c].push_back(t);
      if (vstdArr[c] == 0) {
        cmpntLstArr[tMediumArr[t]].push_back(c);
        vstdArr[c] = 1;
      }
    }
  }
  std::vector<Size> inDgrVec;
  ResizeVector<Size>(&inDgrVec, numCmpnts);
  Size* inDgrArr = (numCmpnts == 0) ? NULL : &inDgrVec[0];
  if (inDgrArr != NULL) {
    std::fill(&inDgrArr[0], &inDgrArr[numCmpnts], 0);
  }
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    if (tCoarseArr[t] != eSqr) {
      // confine the graph search to the square coarse partition.
      continue;
    }
    Size c = tCmpntArr[t];
    Size s = tMateArr[t];
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size tt = sVtxArr[i];
      Size cc = tCmpntArr[tt];
      if ((tCoarseArr[tt] == eSqr) && (cc != c)) {
        // confine the graph search to the square coarse partition.
        ++(inDgrArr[cc]);
      }
    }
  }
  // process the square medium partitions sequentially. this guarantees that
  // the square fine partitions are considered consecutively within the square
  // medium partitions.
  for (Size p = 0; p < numSqrMediumCmpnts; ++p) {
    Size numFineCmpnts = 0;
    ItmQue cmpntQue(numCmpnts);
    for (std::list<Size>::const_iterator it = cmpntLstArr[p].begin();
         it != cmpntLstArr[p].end(); ++it) {
      Size c = *it;
      if (inDgrArr[c] == 0) {
        cmpntQue.Push(c);
      }
    }
    while (cmpntQue.Empty() == false) {
      Size c = cmpntQue.Front();
      cmpntQue.Pop();
      for (std::list<Size>::const_iterator it = tVtxLstArr[c].begin();
           it != tVtxLstArr[c].end(); ++it) {
        Size t = *it;
        Size s = tMateArr[t];
        tFineArr[t] = numFineCmpnts;
        sFineArr[s] = numFineCmpnts;
        Size sNumEdgs = sVtxVecArr[s].size();
        const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
        for (Size i = 0; i < sNumEdgs; ++i) {
          Size tt = sVtxArr[i];
          Size cc = tCmpntArr[tt];
          if ((tCoarseArr[tt] == eSqr) && (cc != c)) {
            // confine the graph search to the square coarse partition.
            --(inDgrArr[cc]);
            if (inDgrArr[cc] == 0) {
              cmpntQue.Push(cc);
            }
          }
        }
      }
      ++numFineCmpnts;
      ++(*numSqrFineCmpnts);
    }
  }
}

} // namespace Matchbox

#endif // BPT_CANONICAL_ENGINE_H
