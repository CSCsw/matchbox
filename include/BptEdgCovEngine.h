#ifndef BPT_EDG_COV_ENGINE_H
#define BPT_EDG_COV_ENGINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "Types.h"
#include "BptGraph.h"
#include "BptMatchingEngine.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class BptEdgCovEngine {
public:
  /// Constructor.
  BptEdgCovEngine():
      mInlz(true), mQueAndStkType(eVecQueAndStk), mIdxdQueType(eLstIdxdQue),
      mCardGraphSrchType(eMplPathDfsLkhd), mPrecision(cMaxPrecision),
      mFullPrint(false), mStatsPrint(false) {}

  /// Destructor.
  ~BptEdgCovEngine() {}

  // a maximum cardinality matching is provided.
  // the edge covering is computed from the matching.
  //
  // no graph searches are performed:
  // - during the computation of the edge covering.
  void ComputeMinCardEdgCov(const BptGraph& graph,
                            const std::vector<Size>& sMateVec,
                            const std::vector<Size>& tMateVec,
                            Size inCard,
                            std::vector<std::list<Size> >* sMateLstVec,
                            std::vector<std::list<Size> >* tMateLstVec,
                            Size* outCard) const;

  // a maximum cardinality matching is computed.
  // the edge covering is computed from the matching.
  //
  // forced direction of graph searches. if rvrs is false then the direction of
  // graph searches is from S to T, otherwise it is from T to S.
  //
  // graph searches are performed:
  // - during the computation of the matching.
  // no graph searches are performed:
  // - during the computation of the edge covering.
  void ComputeMinCardEdgCov(const BptGraph& graph,
                            std::vector<std::list<Size> >* sMateLstVec,
                            std::vector<std::list<Size> >* tMateLstVec,
                            Size* card,
                            bool rvrs) const;

  // a maximum cardinality matching is computed.
  // the edge covering is computed from the matching.
  //
  // automatic direction of graph searches. if |S| <= |T| then the direction of
  // graph searches is from S to T, otherwise it is from T to S.
  //
  // graph searches are performed:
  // - during the computation of the matching.
  // no graph searches are performed:
  // - during the computation of the edge covering.
  void ComputeMinCardEdgCov(const BptGraph& graph,
                            std::vector<std::list<Size> >* sMateLstVec,
                            std::vector<std::list<Size> >* tMateLstVec,
                            Size* cardinality) const;

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
  BptEdgCovEngine(const BptEdgCovEngine&);
  BptEdgCovEngine& operator=(const BptEdgCovEngine&);

  void rComputeMinCardEdgCov(const BptGraph& graph,
                             const Size* sMateArr,
                             const Size* tMateArr,
                             Size inCard,
                             std::list<Size>* sMateLstArr,
                             std::list<Size>* tMateLstArr,
                             Size* outCard) const;
}; // class BptEdgCovEngine

} // namespace Matchbox

#endif // BPT_EDG_COV_ENGINE_H
