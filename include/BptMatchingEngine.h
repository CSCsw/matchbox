#ifndef BPT_MATCHING_ENGINE_H
#define BPT_MATCHING_ENGINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm> // for fill, find, sort.
#include <numeric> // for accumulate.
#include <utility> // for pair.
#include <cassert>
#include <functional>

#include "Types.h"
#include "BptGraph.h"
#include "Utility.h" // for ResizeVector.
#include "Functional.h" // for ValGreater.
#include "VecItmQue.h"
#include "LstItmQue.h"
#include "VecItmStk.h"
#include "LstItmStk.h"
#include "LstItmIdxdQue.h"
#include "LstItmAndValIdxdMinPriQue.h"
#include "BhpItmAndValIdxdMinPriQue.h"
#include "LstItmAndValIdxdMaxPriQue.h"
#include "BhpItmAndValIdxdMaxPriQue.h"
#include "Stats.h"
#include "Timer.h"

namespace Matchbox {

class BptMatchingEngine {
public:
  // through restriction, direct bipartite vertex-weight computations can be
  // performed using either a global choice for an augmenting source or a local
  // choice for an augmenting destination.
  enum DrctVtxWghtAlgType {
    eGbl = 0,
    eLcl
  };

  /// Constructor.
  BptMatchingEngine():
      mInlz(true), mQueAndStkType(eVecQueAndStk), mIdxdQueType(eLstIdxdQue),
      mIdxdPriQueType(eBhpIdxdPriQue), mCardGraphSrchType(eMplPathDfsLkhd),
      mEdgWghtGraphSrchType(eSglSrcBfs), mVtxWghtAlgType(eDrct),
      mDrctVtxWghtAlgType(eGbl), mPrcmptdMaxCard(false),
      mPrecision(cMaxPrecision), mFullPrint(false), mStatsPrint(false) {}

  /// Destructor.
  ~BptMatchingEngine() {}

  ///
  void ComputeMxmlMatching(const BptGraph& graph,
                           std::vector<Size>* sMateVec,
                           std::vector<Size>* tMateVec,
                           Size* card,
                           bool rvrs) const;

  ///
  void ComputeMxmlMatching(const BptGraph& graph,
                           std::vector<Size>* sMateVec,
                           std::vector<Size>* tMateVec,
                           Size* card) const;

  ///
  /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  void ComputeMaxCardMatching(const BptGraph& graph,
                              std::vector<Size>* sMateVec,
                              std::vector<Size>* tMateVec,
                              Size* card,
                              bool rvrs) const;

  ///
  /// automatic direction. if |S| <= |T| then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  void ComputeMaxCardMatching(const BptGraph& graph,
                              std::vector<Size>* sMateVec,
                              std::vector<Size>* tMateVec,
                              Size* card) const;


  ///
  /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  void ComputeMaxEdgWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* edgWght,
                                 bool maxCard,
                                 bool rvrs) const;

  ///
  /// automatic direction. if |S| <= |T| then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  void ComputeMaxEdgWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* edgWght,
                                 bool maxCard) const;

  ///
  /// forced direction. the computation is not performed if |S| and |T| are not
  /// equal, otherwise if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  Err ComputePrfMaxEdgWghtMatching(const BptGraph& graph,
                                   std::vector<Size>* sMateVec,
                                   std::vector<Size>* tMateVec,
                                   Size* card,
                                   Val* edgWght,
                                   bool rvrs) const;

  ///
  /// automatic direction. the computation is not performed if |S| and |T| are
  /// not equal, otherwise the computation is performed from the S-side.
  Err ComputePrfMaxEdgWghtMatching(const BptGraph& graph,
                                   std::vector<Size>* sMateVec,
                                   std::vector<Size>* tMateVec,
                                   Size* card,
                                   Val* edgWght) const;

  ///
  /// forced direction. the computation is not performed if |S| > |T| and rvrs
  /// is false or if |S| < |T| and rvrs is true. otherwise if rvrs is false
  /// then the computation is performed from the S-side, otherwise the
  /// computation is performed from the T-side.
  Err ComputeSemiPrfMaxEdgWghtMatching(const BptGraph& graph,
                                       std::vector<Size>* sMateVec,
                                       std::vector<Size>* tMateVec,
                                       Size* card,
                                       Val* edgWght,
                                       bool rvrs) const;

  ///
  /// automatic direction. if |S| <= |T| then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  Err ComputeSemiPrfMaxEdgWghtMatching(const BptGraph& graph,
                                       std::vector<Size>* sMateVec,
                                       std::vector<Size>* tMateVec,
                                       Size* card,
                                       Val* edgWght) const;

  ///
  /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  void ComputeMaxVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght,
                                 bool rvrs) const;

  ///
  void ComputeMaxVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght) const;
	////
	  /// forced direction. if rvrs is false then the computation is performed from
	  /// the S-side, otherwise the computation is performed from the T-side.
	  ///
	  /// graph searches are performed:
	  /// - during the computation of the matching.
	void ComputeApproxMaxVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght,
                                 bool rvrs,
								 Size bnd) const;

  ///
  void ComputeApproxMaxVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght,
								 Size bnd) const;
  ////
    /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  	void ComputeHalfVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght,
                                 bool rvrs) const;
                                 
    ////
  	void ComputeHalfVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght) const;
    ////
   /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  	void ComputeTwoThirdVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght,
                                 bool rvrs) const;
	////
		void ComputeTwoThirdVtxWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght) const;
  
  /////
    /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.
  void ComputeMaxVtxWghtMatchingSuitor(const BptGraph& graph,
    								std::vector<Size>* sMateVec,
									std::vector<Size>* tMateVec,
									Size* card,
									Val* vtxWght,
    								bool rvrs) const;
    /////
    void ComputeMaxVtxWghtMatchingSuitor(const BptGraph& graph,
    									std::vector<Size>* sMateVec,
										std::vector<Size>* tMateVec, 
										Size* card, 
										Val* vtxWght) const;
    /////
  void ComputeMaxVtxWghtMatchingLocal(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* vtxWght) const;
  /////////
  void ComputeHalfEdgWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* edgWght) const;
   ////////               
   /// forced direction. if rvrs is false then the computation is performed from
  /// the S-side, otherwise the computation is performed from the T-side.
  ///
  /// graph searches are performed:
  /// - during the computation of the matching.               
    void ComputeHalfEdgWghtMatching(const BptGraph& graph,
                                 std::vector<Size>* sMateVec,
                                 std::vector<Size>* tMateVec,
                                 Size* card,
                                 Val* edgWght, 
								 bool rvrs) const;
  /////////

  Err GetMatchedEdgWght(const BptGraph& graph,
                        const std::vector<Size>& sMateVec,
                        const std::vector<Size>& tMateVec,
                        Size card,
                        Val *edgWght) const;

  ///
  Err GetMatchedVtxWght(const BptGraph& graph,
                        const std::vector<Size>& sMateVec,
                        const std::vector<Size>& tMateVec,
                        Size card,
                        Val *sVtxWght,
                        Val *tVtxWght,
                        Val *edgWght) const;

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
  Err SetDrctVtxWghtAlgType(DrctVtxWghtAlgType drctVtxWghtAlgType) {
    switch (drctVtxWghtAlgType) {
    case eGbl:
    case eLcl:
      mDrctVtxWghtAlgType = drctVtxWghtAlgType;
      return eErrNone;
    default:
      return eErrInvType;
    }
  }

  ///
  void SetPrcmptdMaxCard(bool prcmptdMaxCard) {
    mPrcmptdMaxCard = prcmptdMaxCard;
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
  bool CheckMatching(const BptGraph& graph,
                     const std::vector<Size>& sMateVec,
                     const std::vector<Size>& tMateVec,
                     Size card) const;

  ///
  void PrintMatching(const std::vector<Size>& sMateVec,
                     const std::vector<Size>& tMateVec,
                     Size card) const;

  ///
  void PrintMatching(const std::vector<Size>& sMateVec,
                     const std::vector<Size>& tMateVec,
                     Size card,
                     Val wght) const;

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
  DrctVtxWghtAlgType mDrctVtxWghtAlgType;
  // TODO: add comment that explains why mutable.
  // controls the precomputation of a maximum cardinality matching for the
  // speculative computation of a maximum vertex-weight matching.
  mutable bool mPrcmptdMaxCard;
  // precision used for printing floating point numbers.
  Size mPrecision;
  // controls the amount of printing: if false then print less information,
  // if true then print more information.
  bool mFullPrint;
  // controls the printing of computation statistics: if false then do not
  // print computation statistics, if true then print computation statistics.
  bool mStatsPrint;
#ifdef STATS
  // statistics.
  mutable Stats mStats;
#endif

  // forbid the copy constructor and the assignment operator.
  BptMatchingEngine(const BptMatchingEngine&);
  BptMatchingEngine& operator=(const BptMatchingEngine&);

  // loose dual initialization functor, with the S-duals equal to the maximum
  // weight of an adjacent edge and the T-duals equal to zero. used for
  // nonperfect and semiperfect maximum edge-weight computations, where there
  // are duals that are constrained to be nonnegative, some of them being
  // actually required to be equal to zero at the end of a computation.
  class rInlzDualsLoose {
  public:
    rInlzDualsLoose(const BptGraph& graph): mGraph(graph) {}
    void operator()(Val* sDualArr,
                    Val* tDualArr,
                    bool rvrs) const;
  private:
    const BptGraph& mGraph;
  };

  // tight dual initialization functor, with the S-duals equal to the maximum
  // weight of an adjacent edge and the T-duals equal to the maximum difference
  // between the weight of an adjacent edge and the dual of its other endpoint.
  // used for perfect maximum edge-weight computations, where the duals are
  // free.
  class rInlzDualsTight {
  public:
    rInlzDualsTight(const BptGraph& graph): mGraph(graph) {}
    void operator()(Val* sDualArr,
                    Val* tDualArr,
                    bool rvrs) const;
  private:
    const BptGraph& mGraph;
  };
  
  ////////
  
  void rInlzGrdyForCard(const BptGraph& graph,
                        Size* sMateArr,
                        Size* tMateArr,
                        Size* card,
                        bool rvrs) const;

  ///
  void rInlzGrdyForEdgWght(const BptGraph& graph,
                           Size* sMateArr,
                           Size* tMateArr,
                           Val* sDualArr,
                           Val* tDualArr,
                           Size* card,
                           Val* edgWght,
                           bool rvrs) const;
                           
    void rInlzGrdyForVtxWght(const BptGraph& graph,
                           Size* sMateArr,
                           Size* tMateArr,
                           std::pair<Size,Val>* sortedArr,
                           Size* card,
                           bool rvrs) const;

    void rInlzRefinedForEdgWght(const BptGraph& graph,
    						Size* sMateArr, 
							Size* tMateArr, 
							Val* sDualArr, 
							Val* tDualArr, 
							Size* card,
    						Val* edgWght, 
							bool rvrs) const;
  ///
  /// used in single source computations:
  /// - maximum cardinality computations
  /// - maximum edge-weight computations
  /// - maximum vertex-weight computations.
  Size rAugment(Size* sMateArr,
                Size* tMateArr,
                Size* sPtrArr,
                Size sLast,
                Size tLast) const;

  ///
  /// used in multiple source computations:
  /// - maximum cardinality computations
  /// - maximum edge-weight computations.
  template<class ItmIdxdQue>
  Size rAugment(Size* sMateArr,
                Size* tMateArr,
                Size* sPtrArr,
                ItmIdxdQue& sExpsdQue,
                Size sLast,
                Size tLast) const;

  ///
  /// used in single source computations:
  /// - maximum edge-weight computations
  /// - maximum vertex-weight computations.
  Size rReverse(Size* sMateArr,
                Size* tMateArr,
                Size* sPtrArr,
                Size sLast) const;

  ///
  /// implicitly breadth-first.
  /// the path length is not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rProcessCardSglPath(const BptGraph& graph,
                           Size* sMateArr,
                           Size* tMateArr,
                           Size* sPtrArr,
                           Stt* sSttArr,
                           ItmQue& sPrcsbQue,
                           ItmQue& sPrcsdQue,
                           Size* sLast,
                           Size* tLast,
                           bool rvrs/*,Size* ecount*/) const;
   /* template<class ItmQue>
  void rProcessCardSglPath(const BptGraph& graph,
                           Size* sMateArr,
                           Size* tMateArr,
                           Size* sPtrArr,
                           Stt* sSttArr,
                           ItmQue& sPrcsbQue,
                           ItmQue& sPrcsdQue,
                           Size* sLast,
                           Size* tLast,
                           bool rvrs) const;*/

  ///
  /// the path length is not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rFindAugPathCardSglSrcBfs(const BptGraph& graph,
                                 Size* sMateArr,
                                 Size* tMateArr,
                                 Size* sPtrArr,
                                 Stt* sSttArr,
                                 ItmQue& sPrcsbQue,
                                 ItmQue& sPrcsdQue,
                                 Size sFirst,
                                 Size* sLast,
                                 Size* tLast,
                                 bool rvrs/*, Size* ecount*/) const;

/*template<class ItmQue>
  void rFindAugPathCardSglSrcBfs(const BptGraph& graph,
                                 Size* sMateArr,
                                 Size* tMateArr,
                                 Size* sPtrArr,
                                 Stt* sSttArr,
                                 ItmQue& sPrcsbQue,
                                 ItmQue& sPrcsdQue,
                                 Size sFirst,
                                 Size* sLast,
                                 Size* tLast,
                                 bool rvrs) const;*/
  ///
  /// the path length in not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmStk>
  void rFindAugPathCardSglSrcDfs(const BptGraph& graph,
                                 Size* sMateArr,
                                 Size* tMateArr,
                                 Size* sPtrArr,
                                 Stt* sSttArr,
                                 Size* sIdxArr,
                                 ItmStk& sPrcsbStk,
                                 ItmQue& sPrcsdQue,
                                 Size sFirst,
                                 Size* sLast,
                                 Size* tLast,
                                 bool rvrs) const;

  ///
  /// with lookahead (one step of breadth-first).
  /// the path length in not bounded.
  /// the path length in not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmStk>
  void rFindAugPathCardSglSrcDfsLkhd(const BptGraph& graph,
                                     Size* sMateArr,
                                     Size* tMateArr,
                                     Size* sPtrArr,
                                     Stt* sSttArr,
                                     Size* sIdxArr,
                                     ItmStk& sPrcsbStk,
                                     ItmQue& sPrcsdQue,
                                     Size sFirst,
                                     Size* sLast,
                                     Size* tLast,
                                     bool rvrs) const;

  ///
  /// implicitly breadth-first.
  /// the path length is not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmIdxdQue>
  void rFindAugPathCardMplSrcSglPath(const BptGraph& graph,
                                     Size* sMateArr,
                                     Size* tMateArr,
                                     Size* sPtrArr,
                                     Stt* sSttArr,
                                     ItmQue& sPrcsbQue,
                                     ItmQue& sPrcsdQue,
                                     ItmIdxdQue& sExpsdQue,
                                     Size* sLast,
                                     Size* tLast,
                                     bool rvrs) const;

  ///
  /// implicitly breadth-first.
  /// the path length is bounded.
  ///
  /// used in:
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rProcessCardSglPathBnd(const BptGraph& graph,
                              Size* sMateArr,
                              Size* tMateArr,
                              Size* sPtrArr,
                              Size* sLenArr,
                              Stt* sSttArr,
                              ItmQue& sPrcsbQue,
                              ItmQue& sPrcsdQue,
                              Size* sLast,
                              Size* tLast,
                              Size augPathLenBnd,
                              bool rvrs) const;

  ///
  /// the path length is bounded.
  ///
  /// used in:
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rFindAugPathCardSglSrcBfsBnd(const BptGraph& graph,
                                    Size* sMateArr,
                                    Size* tMateArr,
                                    Size* sPtrArr,
                                    Size* sLenArr,
                                    Stt* sSttArr,
                                    ItmQue& sPrcsbQue,
                                    ItmQue& sPrcsdQue,
                                    Size sFirst,
                                    Size* sLast,
                                    Size* tLast,
                                    Size augPathLenBnd,
                                    bool rvrs) const;

  ///
  /// implicitly breadth-first.
  /// the path length is bounded.
  ///
  /// currently not used.
  template<class ItmQue,
           class ItmIdxdQue>
  void rFindAugPathCardMplSrcSglPathBnd(const BptGraph& graph,
                                        Size* sMateArr,
                                        Size* tMateArr,
                                        Size* sPtrArr,
                                        Size* sLenArr,
                                        Stt* sSttArr,
                                        ItmQue& sPrcsbQue,
                                        ItmQue& sPrcsdQue,
                                        ItmIdxdQue& sExpsdQue,
                                        Size* sLast,
                                        Size* tLast,
                                        Size augPathLenBnd,
                                        bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// alternatives:
  /// - returned sLast not equal to cNullItm and returned tLast not equal to
  /// cNullItm: this means that an augmenting path is returned
  /// - returned sLast not equal to cNullItm and returned tLast equal to
  /// cNullItm: this means that a reversing path is returned.
  ///
  /// used in:
  /// - nonperfect maximum edge-weight computations.
  template<class ItmQue,
           class ItmAndValIdxdPriQue>
  void rProcessEdgWghtSglPath(const BptGraph& graph,
                              Size* sMateArr,
                              Size* tMateArr,
                              Val* sDualArr,
                              Val* tDualArr,
                              Size* sPtrArr,
                              Size* tPtrArr,
                              Val* sDistArr,
                              Val* tDistArr,
                              Stt* sSttArr,
                              Stt* tSttArr,
                              ItmQue& sPrcsbQue,
                              ItmQue& sPrcsdQue,
                              ItmAndValIdxdPriQue& tPrcsbQue,
                              ItmQue& tPrcsdQue,
                              Size sMinFirst,
                              Size* sLast,
                              Size* tLast,
                              Val* dualShift,
                              bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// alternatives:
  /// - returned sLast not equal to cNullItm and returned tLast not equal to
  /// cNullItm: this means that an augmenting path is returned
  /// - returned sLast not equal to cNullItm and returned tLast equal to
  /// cNullItm: this means that a reversing path is returned.
  ///
  /// used in:
  /// - nonperfect maximum edge-weight computations.
  template<class ItmQue,
           class ItmAndValIdxdPriQue>
  void rFindAugPathEdgWghtSglSrc(const BptGraph& graph,
                                 Size* sMateArr,
                                 Size* tMateArr,
                                 Val* sDualArr,
                                 Val* tDualArr,
                                 Size* sPtrArr,
                                 Size* tPtrArr,
                                 Val* sDistArr,
                                 Val* tDistArr,
                                 Stt* sSttArr,
                                 Stt* tSttArr,
                                 ItmQue& sPrcsbQue,
                                 ItmQue& sPrcsdQue,
                                 ItmAndValIdxdPriQue& tPrcsbQue,
                                 ItmQue& tPrcsdQue,
                                 Size sFirst,
                                 Size* sLast,
                                 Size* tLast,
                                 Val* dualShift,
                                 bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// alternatives:
  /// - returned sLast not equal to cNullItm and returned tLast not equal to
  /// cNullItm: this means that an augmenting path is returned
  /// - returned sLast not equal to cNullItm and returned tLast equal to
  /// cNullItm: this means that a reversing path is returned.
  ///
  /// currently not used.
  /// TODO: add multiple source edge-weight computations.
  template<class ItmQue,
           class ItmIdxdQue,
           class ItmAndValIdxdPriQue>
  void rFindAugPathEdgWghtMplSrc(const BptGraph& graph,
                                 Size* sMateArr,
                                 Size* tMateArr,
                                 Val* sDualArr,
                                 Val* tDualArr,
                                 Size* sPtrArr,
                                 Size* tPtrArr,
                                 Val* sDistArr,
                                 Val* tDistArr,
                                 Stt* sSttArr,
                                 Stt* tSttArr,
                                 ItmQue& sPrcsbQue,
                                 ItmQue& sPrcsdQue,
                                 ItmAndValIdxdPriQue& tPrcsbQue,
                                 ItmQue& tPrcsdQue,
                                 ItmIdxdQue& sExpsdQue,
                                 Size* sLast,
                                 Size* tLast,
                                 Val* dualShift,
                                 bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// alternatives:
  /// - returned sLast not equal to cNullItm and returned tLast not equal to
  /// cNullItm: this means that an augmenting path is returned
  /// - returned sLast equal to cNullItm and returned tLast equal to cNullItm:
  /// this means that no path is returned.
  ///
  /// used in:
  /// - perfect and semiperfect maximum edge-weight computations.
  template<class ItmQue,
           class ItmAndValIdxdPriQue>
  void rProcessPrfEdgWghtSglPath(const BptGraph& graph,
                                 Size* sMateArr,
                                 Size* tMateArr,
                                 Val* sDualArr,
                                 Val* tDualArr,
                                 Size* sPtrArr,
                                 Size* tPtrArr,
                                 Val* sDistArr,
                                 Val* tDistArr,
                                 Stt* sSttArr,
                                 Stt* tSttArr,
                                 ItmQue& sPrcsbQue,
                                 ItmQue& sPrcsdQue,
                                 ItmAndValIdxdPriQue& tPrcsbQue,
                                 ItmQue& tPrcsdQue,
                                 Size* sLast,
                                 Size* tLast,
                                 Val* dualShift,
                                 bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// alternatives:
  /// - returned sLast not equal to cNullItm and returned tLast not equal to
  /// cNullItm: this means that an augmenting path is returned
  /// - returned sLast equal to cNullItm and returned tLast equal to cNullItm:
  /// this means that no path is returned.
  ///
  /// used in:
  /// - perfect and semiperfect maximum edge-weight computations.
  template<class ItmQue,
           class ItmAndValIdxdPriQue>
  void rFindAugPathPrfEdgWghtSglSrc(const BptGraph& graph,
                                    Size* sMateArr,
                                    Size* tMateArr,
                                    Val* sDualArr,
                                    Val* tDualArr,
                                    Size* sPtrArr,
                                    Size* tPtrArr,
                                    Val* sDistArr,
                                    Val* tDistArr,
                                    Stt* sSttArr,
                                    Stt* tSttArr,
                                    ItmQue& sPrcsbQue,
                                    ItmQue& sPrcsdQue,
                                    ItmAndValIdxdPriQue& tPrcsbQue,
                                    ItmQue& tPrcsdQue,
                                    Size sFirst,
                                    Size* sLast,
                                    Size* tLast,
                                    Val* dualShift,
                                    bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// alternatives:
  /// - returned sLast not equal to cNullItm and returned tLast not equal to
  /// cNullItm: this means that an augmenting path is returned
  /// - returned sLast equal to cNullItm and returned tLast equal to cNullItm:
  /// this means that no path is returned.
  ///
  /// currently not used.
  /// TODO: add multiple source edge-weight computations.
  template<class ItmQue,
           class ItmIdxdQue,
           class ItmAndValIdxdPriQue>
  void rFindAugPathPrfEdgWghtMplSrc(const BptGraph& graph,
                                    Size* sMateArr,
                                    Size* tMateArr,
                                    Val* sDualArr,
                                    Val* tDualArr,
                                    Size* sPtrArr,
                                    Size* tPtrArr,
                                    Val* sDistArr,
                                    Val* tDistArr,
                                    Stt* sSttArr,
                                    Stt* tSttArr,
                                    ItmQue& sPrcsbQue,
                                    ItmQue& sPrcsdQue,
                                    ItmAndValIdxdPriQue& tPrcsbQue,
                                    ItmQue& tPrcsdQue,
                                    ItmIdxdQue& sExpsdQue,
                                    Size* sLast,
                                    Size* tLast,
                                    Val* dualShift,
                                    bool rvrs) const;

  ///
  /// implicitly depth-first.
  /// the path length in not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue>
  void rFindMxmlSetAugPathsCard(const BptGraph& graph,
                                Size* sMateArr,
                                Size* tMateArr,
                                Size* sPtrArr,
                                Stt* sSttArr,
                                Stt* tSttArr,
                                Size* sIdxArr,
                                ItmStk& sPrcsbStk,
                                ItmQue& sPrcsdQue,
                                ItmIdxdQue& sExpsdQue,
                                ItmQue& sLastQue,
                                ItmQue& tLastQue,
                                bool rvrs) const;

  ///
  /// implicitly depth-first, with lookahead (one step of breadth-first).
  /// the path length in not bounded.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue>
  void rFindMxmlSetAugPathsCardLkhd(const BptGraph& graph,
                                    Size* sMateArr,
                                    Size* tMateArr,
                                    Size* sPtrArr,
                                    Stt* sSttArr,
                                    Stt* tSttArr,
                                    Size* sIdxArr,
                                    Size* sLkhdArr,
                                    ItmStk& sPrcsbStk,
                                    ItmQue& sPrcsdQue,
                                    ItmIdxdQue& sExpsdQue,
                                    ItmQue& sLastQue,
                                    ItmQue& tLastQue,
                                    bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmIdxdQue>
  void rComputeShrtstAugPathLenCard(const BptGraph& graph,
                                    Size* sMateArr,
                                    Size* tMateArr,
                                    Size* sLenArr,
                                    Size* tLenArr,
                                    Stt* sSttArr,
                                    Stt* tSttArr,
                                    ItmQue& sPrcsbQue,
                                    ItmQue& sPrcsdQue,
                                    ItmQue& tPrcsdQue,
                                    ItmIdxdQue& sExpsdQue,
                                    Size* shrtstAugPathLen,
                                    bool rvrs) const;

  ///
  /// implicitly breadth-first driven depth-first.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue>
  void rFindMxmlSetShrtstAugPathsCard(const BptGraph& graph,
                                      Size* sMateArr,
                                      Size* tMateArr,
                                      Size* sPtrArr,
                                      Size* sLenArr,
                                      Size* tLenArr,
                                      Stt* sSttArr,
                                      Stt* tSttArr,
                                      Size* sIdxArr,
                                      ItmStk& sPrcsbStk,
                                      ItmIdxdQue& sExpsdQue,
                                      Size shrtstAugPathLen,
                                      ItmQue& sLastQue,
                                      ItmQue& tLastQue,
                                      bool rvrs) const;

  ///
  /// implicitly breadth-first.
  ///
  /// used in:
  /// - nonperfect, perfect and semiperfect maximum edge-weight computations.
  template<class ItmQue,
           class ItmIdxdQue>
  void rComputeShrtstAugPathLenEdgWght(const BptGraph& graph,
                                       Size* sMateArr,
                                       Size* tMateArr,
                                       Val* sDualArr,
                                       Val* tDualArr,
                                       Size* sLenArr,
                                       Size* tLenArr,
                                       Stt* sSttArr,
                                       Stt* tSttArr,
                                       ItmQue& sPrcsbQue,
                                       ItmQue& sPrcsdQue,
                                       ItmQue& tPrcsdQue,
                                       ItmIdxdQue& sExpsdQue,
                                       Size* shrtstAugPathLen,
                                       bool rvrs) const;

  ///
  /// implicitly breadth-first driven depth-first.
  ///
  /// used in:
  /// - nonperfect, perfect and semiperfect maximum edge-weight computations.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue>
  void rFindMxmlSetShrtstAugPathsEdgWght(const BptGraph& graph,
                                         Size* sMateArr,
                                         Size* tMateArr,
                                         Val* sDualArr,
                                         Val* tDualArr,
                                         Size* sPtrArr,
                                         Size* sLenArr,
                                         Size* tLenArr,
                                         Stt* sSttArr,
                                         Stt* tSttArr,
                                         Size* sIdxArr,
                                         ItmStk& sPrcsbStk,
                                         ItmIdxdQue& sExpsdQue,
                                         Size shrtstAugPathLen,
                                         ItmQue& sLastQue,
                                         ItmQue& tLastQue,
                                         bool rvrs) const;

  ///
  /// implicitly single source.
  /// the path length is not bounded.
  ///
  /// used in:
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rFindBestAugPathVtxWghtBfs(const BptGraph& graph,
                                  Size* sMateArr,
                                  Size* tMateArr,
                                  Size* sPtrArr,
                                  Stt* sSttArr,
                                  ItmQue& sPrcsbQue,
                                  ItmQue& sPrcsdQue,
                                  Size sFirst,
                                  Size* sLast,
                                  Size* tLast,
                                  bool rvrs) const;

  ///
  /// implicitly single source.
  /// the path length is bounded.
  ///
  /// used in:
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rFindBestAugPathVtxWghtBfsBnd(const BptGraph& graph,
                                     Size* sMateArr,
                                     Size* tMateArr,
                                     Size* sPtrArr,
                                     Size* sLengthArr,
                                     Stt* sSttArr,
                                     ItmQue& sPrcsbQue,
                                     ItmQue& sPrcsdQue,
                                     Size sFirst,
                                     Size* sLast,
                                     Size* tLast,
                                     Size augPathLenBnd,
                                     bool rvrs) const;

  ///
  /// implicitly single source.
  ///
  /// used in:
  /// - maximum vertex-weight computations.
  template<class ItmQue>
  void rFindRevPathVtxWghtBfs(const BptGraph& graph,
                              Size* sMateArr,
                              Size* tMateArr,
                              Size* sPtrArr,
                              Stt* sSttArr,
                              ItmQue& sPrcsbQue,
                              ItmQue& sPrcsdQue,
                              Size sFirst,
                              Size* sLast,
                              bool rvrs) const;

  ///
  /// merge two matchings according to the mendelsohn-dulmage theorem.
  void rMergeMatchings(const BptGraph& graph,
                       const Size* sMateSArr,
                       const Size* tMateSArr,
                       const Size* sMateTArr,
                       const Size* tMateTArr,
                       Size* sMateArr,
                       Size* tMateArr,
                       Size* card) const;

  ///
  /// the core of the single source, breadth-first search, maximum cardinality
  /// matching computation.
  template<class ItmQue>
  void rComputeMaxCardMatchingSglSrcBfs(const BptGraph& graph,
                                        Size* sMateArr,
                                        Size* tMateArr,
                                        Size* card,
                                        bool rvrs) const;

  ///
  /// the core of the single source, depth-first search, maximum cardinality
  /// matching computation.
  template<class ItmQue,
           class ItmStk>
  void rComputeMaxCardMatchingSglSrcDfs(const BptGraph& graph,
                                        Size* sMateArr,
                                        Size* tMateArr,
                                        Size* card,
                                        bool lkhd,
                                        bool rvrs) const;

  ///
  /// the core of the multiple source, single augmenting path, maximum
  /// cardinality matching computation.
  template<class ItmQue,
           class ItmIdxdQue>
  void rComputeMaxCardMatchingMplSrcSglPath(const BptGraph& graph,
                                            Size* sMateArr,
                                            Size* tMateArr,
                                            Size* card,
                                            bool rvrs) const;

  ///
  /// the core of the multiple path, depth-first search, maximum cardinality
  /// matching computation.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue>
  void rComputeMaxCardMatchingMplPathDfs(const BptGraph& graph,
                                      Size* sMateArr,
                                      Size* tMateArr,
                                      Size* card,
                                      bool lkhd,
                                      bool rvrs) const;

  ///
  /// the core of the mltiple path, breadth-first search and depth-first
  /// search (shortest path), maximum cardinality matching computation.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue>
  void rComputeMaxCardMatchingMplPathBfsDfs(const BptGraph& graph,
                                            Size* sMateArr,
                                            Size* tMateArr,
                                            Size* card,
                                            bool rvrs) const;

  ///
  /// the core of the single source maximum edge-weight matching computation.
  ///
  /// nonperfect computations.
  /// pure maximum edge-weight and maximum cardinality maximum edge-weight.
  template<class ItmQue,
           class ItmStk,
           class ItmIdxdQue,
           class ItmAndValIdxdPriQue>
  void rComputeMaxEdgWghtMatchingSglSrc(const BptGraph& graph,
                                        Size* sMateArr,
                                        Size* tMateArr,
                                        Size* card,
                                        Val* edgWght,
                                        bool maxCard,
                                        bool rvrs) const;

  ///
  /// the core of the single source perfect maximum edge-weight matching
  /// computation.
  ///
  /// perfect and semiperfect computations.
  /// maximum edge-weight implies maximum cardinality as well (zero weight
  /// edges are always included, if possible).
  template<class InlzDualsFunctor,
           class ItmQue,
           class ItmStk,
           class ItmIdxdQue,
           class ItmAndValIdxdPriQue>
  Err rComputePrfMaxEdgWghtMatchingSglSrc(const BptGraph& graph,
                                          Size* sMateArr,
                                          Size* tMateArr,
                                          Size* card,
                                          Val* edgWght,
                                          bool rvrs,
                                          InlzDualsFunctor inlzDualsFunctor)
                                          const;

  ///
  /// the core of the direct global maximum vertex-weight matching computation.
  ///
  /// implicitly single source.
  /// returns the weight on one side (S if rvrs is false, T if rvrs is true).
  template<class ItmQue>
  void rComputeMaxVtxWghtMatchingDrctGbl(const BptGraph& graph,
                                         Size* sMateArr,
                                         Size* tMateArr,
                                         Size* card,
                                         Val* vtxWght,
                                         Size augPathLenBnd,
                                         bool rvrs) const;

  ///
  /// the core of the direct local maximum vertex-weight matching computation.
  ///
  /// implicitly single source.
  /// returns the weight on one side (T if rvrs is false, S if rvrs is true).
  template<class ItmQue>
  void rComputeMaxVtxWghtMatchingDrctLcl(const BptGraph& graph,
                                         Size* sMateArr,
                                         Size* tMateArr,
                                         Size* card,
                                         Val* vtxWght,
                                         Size augPathLenBnd,
                                         bool rvrs) const;
                                         
/////////////////////////////
  /// the core of the approximate maximum vertex-weight matching computation using the Suitor 1/2-approx. algorithm.
  ///
  /// returns the weight on one side (T if rvrs is false, S if rvrs is true).
template<class ItmQue>
void rComputeMaxVtxWghtMatchingSuitor(const BptGraph& graph,
 									Size* sMateArr,
									Size* tMateArr,
									Size* card,
    								Val* vtxWght,
									bool rvrs) const;
///////////////////
 /// the core of the approximate maximum vertex-weight matching computation using the greedy 1/2-approx. algorithm.
  ///
  /// returns the weight on one side (T if rvrs is false, S if rvrs is true).
template<class ItmQue>
void rComputeHalfVtxWghtMatchingDrctGbl(const BptGraph& graph,
										Size* sMateArr, 
										Size* tMateArr, 
										Size* card,
    									Val* vtxWght,
										bool rvrs) const;
/////////
/// the core of the approximate maximum vertex-weight matching computation using the greedy 2/3-approx. algorithm.
  ///
  /// returns the weight on one side (T if rvrs is false, S if rvrs is true).
template<class ItmQue>
void rComputeTwoThirdVtxWghtMatchingDrctGbl(const BptGraph& graph,
											Size* sMateArr,
											Size* tMateArr,
											Size* card, 
											Val* vtxWght,  
											bool rvrs) const;
    
/////////////////////////////
/// the core of the approximate maximum edge-weight matching computation using the greedy 1/2-approx. algorithm.
//////
template<class ItmQue>
void rComputeHalfEdgWghtMatching(const BptGraph& graph,
 								Size* sMateArr,
								Size* tMateArr, 
								Size* card,
    							Val* edgWght,
								bool rvrs) const;
///////////
/////////////////////////////
/// the core of the approximate maximum edge-weight matching computation using the locally dominante 1/2-approx. algorithm.
//////
template<class ItmQue>
  void rComputeMaxVtxWghtMatchingLocal(const BptGraph& graph,
                                         Size* sMateArr,
                                         Size* tMateArr,
                                         Size* card,
                                         Val* vtxWght) const;

//////////////////////////////

  ///
  /// the core of the speculative maximum vertex-weight matching computation.
  ///
  /// implicitly single source.
  /// returns the weight on one side (S if rvrs is false, T if rvrs is true).
  template<class ItmQue,
           class ItmAndValIdxdPriQue>
  void rComputeMaxVtxWghtMatchingSpcl(const BptGraph& graph,
                                      Size* sMateArr,
                                      Size* tMateArr,
                                      Size card,
                                      Val* vtxWght,
                                      bool rvrs) const;
}; // class BptMatchingEngine

template <typename Container>
struct compare_indirect_index
  {
  const Container* container;
  compare_indirect_index( const Container* container ): container( container ) { }
  bool operator () ( Size lindex, Size rindex ) const
    {
    return (container[ lindex ] > container[ rindex ]) || (container[ lindex ] == container[ rindex ] && lindex < rindex) ;
    }
  };

template<class ItmIdxdQue>
Size BptMatchingEngine::rAugment(Size* sMateArr, Size* tMateArr, Size* sPtrArr,
    ItmIdxdQue& sExpsdQue, Size sLast, Size tLast) const {
  Size s = sLast;
  Size t = tLast;
  Size k = 0;
  while (s != cNullItm) {
    Size tt = sMateArr[s];
    sMateArr[s] = t;
    tMateArr[t] = s;
    if (sPtrArr[s] == cNullItm) {
      sExpsdQue.Erase(s);
    }
    s = sPtrArr[s];
    t = tt;
    ++k;
  }
  assert(k > 0);
  return 2 * k - 1;
}

template<class ItmQue>
void BptMatchingEngine::rProcessCardSglPath(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size* sLast, Size* tLast, bool rvrs/*, Size* ecount*/)
    const {
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :	
	((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
	
   /*const Val* tVtxWghtArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]); */
    
   // Val maxVtxWght = cNegInfVal;
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
    //	(*ecount)++;
      Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
     // (*ecount)++;
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        continue;
      }
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
      if (ss == cNullItm) {

        *sLast = s;
        *tLast = t;
        return;
      }
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
      ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
      sPtrArr[ss] = s;
      sPrcsbQue.Push(ss);
      sSttArr[ss] = eSttBfsPrcsb;
    }
  }
}

template<class ItmQue>
void BptMatchingEngine::rFindAugPathCardSglSrcBfs(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size sFirst, Size* sLast,
    Size* tLast, bool rvrs/*,Size* ecount*/) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  rProcessCardSglPath<ItmQue>
    (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue, sLast,
     tLast, rvrs/*,ecount*/);
}

template<class ItmQue, class ItmStk>
void BptMatchingEngine::rFindAugPathCardSglSrcDfs(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr, Size* sIdxArr,
    ItmStk& sPrcsbStk, ItmQue& sPrcsdQue, Size sFirst, Size* sLast,
    Size* tLast, bool rvrs) const {
#ifdef STATS
  mStats.mNumDfsVstdVtxs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  sPrcsbStk.Push(sFirst);
  sSttArr[sFirst] = eSttDfsPrcsb;
  while (sPrcsbStk.Empty() == false) {
    Size s = sPrcsbStk.Top();
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    while (sIdxArr[s] < sNumEdgs) {
      Size t = sVtxArr[sIdxArr[s]];
#ifdef STATS
      ++(mStats.mNumDfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        ++(sIdxArr[s]);
      } else {
        break;
      }
    }
    if (sIdxArr[s] < sNumEdgs) {
      Size t = sVtxArr[sIdxArr[s]];
      Size ss = tMateArr[t];
#ifdef STATS
      ++(mStats.mNumDfsVstdVtxs); // visit t.
#endif
      if (ss == cNullItm) {
        *sLast = s;
        *tLast = t;
        return;
      }
#ifdef STATS
      ++(mStats.mNumDfsVstdEdgs); // visit (t,ss).
      ++(mStats.mNumDfsVstdVtxs); // visit ss.
#endif
      sPtrArr[ss] = s;
      sPrcsbStk.Push(ss);
      sSttArr[ss] = eSttDfsPrcsb;
      ++(sIdxArr[s]);
    } else {
      sPrcsbStk.Pop();
      sPrcsdQue.Push(s);
      sSttArr[s] = eSttDfsPrcsd;
    }
  }
}

template<class ItmQue, class ItmStk>
void BptMatchingEngine::rFindAugPathCardSglSrcDfsLkhd(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr, Size* sIdxArr,
    ItmStk& sPrcsbStk, ItmQue& sPrcsdQue, Size sFirst, Size* sLast,
    Size* tLast, bool rvrs) const {
#ifdef STATS
  mStats.mNumDfsVstdVtxs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  sPrcsbStk.Push(sFirst);
  sSttArr[sFirst] = eSttDfsPrcsb;
  while (sPrcsbStk.Empty() == false) {
    Size s = sPrcsbStk.Top();
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    while (sIdxArr[s] < sNumEdgs) {
      Size t = sVtxArr[sIdxArr[s]];
#ifdef STATS
      ++(mStats.mNumDfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        ++(sIdxArr[s]);
      } else {
        break;
      }
    }
    if (sIdxArr[s] < sNumEdgs) {
      Size t = sVtxArr[sIdxArr[s]];
      Size ss = tMateArr[t];
#ifdef STATS
      ++(mStats.mNumDfsVstdVtxs); // visit t.
#endif
      if (ss == cNullItm) {
        *sLast = s;
        *tLast = t;
        return;
      }
#ifdef STATS
      ++(mStats.mNumDfsVstdEdgs); // visit (t,ss).
      ++(mStats.mNumDfsVstdVtxs); // visit ss.
#endif
      sPtrArr[ss] = s;
      sPrcsbStk.Push(ss);
      sSttArr[ss] = eSttDfsPrcsb;
      ++(sIdxArr[s]);
    } else {
      sPrcsbStk.Pop();
      sPrcsdQue.Push(s);
      sSttArr[s] = eSttDfsPrcsd;
    }
  }
}

template<class ItmQue, class ItmIdxdQue>
void BptMatchingEngine::rFindAugPathCardMplSrcSglPath(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, ItmIdxdQue& sExpsdQue, Size* sLast,
    Size* tLast, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumBfsVstdVtxs); // visit sFirst.
#endif
    sPrcsbQue.Push(sFirst);
    sSttArr[sFirst] = eSttBfsPrcsb;
    sFirst = sExpsdQue.Next(sFirst);
  }
  /*rProcessCardSglPath<ItmQue>
    (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue, sLast,
     tLast, rvrs);*/
}

template<class ItmQue>
void BptMatchingEngine::rProcessCardSglPathBnd(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Size* sLenArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size* sLast, Size* tLast,
    Size augPathLenBnd, bool rvrs) const {
  assert(augPathLenBnd > 0);
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        continue;
      }
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
      if (ss == cNullItm) {
        *sLast = s;
        *tLast = t;
        return;
      }
      sLenArr[ss] = sLenArr[s] + 2;
      if (sLenArr[ss] < augPathLenBnd) {
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        sPtrArr[ss] = s;
        sPrcsbQue.Push(ss);
        sSttArr[ss] = eSttBfsPrcsb;
      }
    }
  }
}

template<class ItmQue>
void BptMatchingEngine::rFindAugPathCardSglSrcBfsBnd(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Size* sLenArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size sFirst, Size* sLast,
    Size* tLast, Size augPathLenBnd, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  sLenArr[sFirst] = 0;
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  rProcessCardSglPathBnd<ItmQue>
    (graph, sMateArr, tMateArr, sPtrArr, sLenArr, sSttArr, sPrcsbQue,
     sPrcsdQue, sLast, tLast, augPathLenBnd, rvrs);
}

template<class ItmQue, class ItmIdxdQue>
void BptMatchingEngine::rFindAugPathCardMplSrcSglPathBnd(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Size* sLenArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, ItmIdxdQue& sExpsdQue, Size* sLast,
    Size* tLast, Size augPathLenBnd, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumBfsVstdVtxs); // visit sFirst.
#endif
    sLenArr[sFirst] = 0;
    sPrcsbQue.Push(sFirst);
    sSttArr[sFirst] = eSttBfsPrcsb;
    sFirst = sExpsdQue.Next(sFirst);
  }
  rProcessCardSglPathBnd<ItmQue>
    (graph, sMateArr, tMateArr, sPtrArr, sLenArr, sSttArr, sPrcsbQue,
     sPrcsdQue, sLast, tLast, augPathLenBnd, rvrs);
}

template<class ItmQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rProcessEdgWghtSglPath(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr, 
    Size* sPtrArr, Size* tPtrArr, Val* sDistArr, Val* tDistArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue,
    ItmAndValIdxdPriQue& tPrcsbQue, ItmQue& tPrcsdQue, Size sMinFirst,
    Size* sLast, Size* tLast, Val* dualShift, bool rvrs) const {
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const std::vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);
  Size sMin = sMinFirst;
  Val sMinDualAndDist = cPosInfVal;
  if (sMin != cNullItm) {
    sMinDualAndDist = sDualArr[sMin];
  }
  Val crtDist = 0.0;
  while (true) {
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPrcsdQue.Push(s);
      sSttArr[s] = eSttBfsPrcsd;
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
#ifdef STATS
          ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        if (tSttArr[t] == eSttBfsPrcsd) {
          continue;
        }
        Val stEdgWght = sEdgWghtArr[i];
        Val slack = (sDualArr[s] + tDualArr[t]) - stEdgWght;
        if (slack <= 0) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
          if (tSttArr[t] == eSttBfsPrcsb) {
            tPrcsbQue.Erase(t);
          }
          tDistArr[t] = crtDist;
          tPrcsdQue.Push(t);
          tSttArr[t] = eSttBfsPrcsd;
          Size ss = tMateArr[t];
          if (ss == cNullItm) {
            *sLast = s;
            *tLast = t;
            *dualShift = crtDist;
            return;
          }
#ifdef STATS
          ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
          ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
          Val sCrtDualAndDist = sDualArr[ss] + crtDist;
          if (sCrtDualAndDist < sMinDualAndDist) {
            sMin = ss;
            sMinDualAndDist = sCrtDualAndDist;
          }
          sDistArr[ss] = crtDist;
          sPtrArr[ss] = s;
          sPrcsbQue.Push(ss);
          sSttArr[ss] = eSttBfsPrcsb;
        } else {
          Val newDist = crtDist + slack;
          if (tDistArr[t] > newDist) {
            tDistArr[t] = newDist;
            tPtrArr[t] = s;
            if (tSttArr[t] == eSttIdle) {
              tPrcsbQue.Push(t, tDistArr[t]);
              tSttArr[t] = eSttBfsPrcsb;
            } else {
              tPrcsbQue.IncreasePriority(t, tDistArr[t]);
            }
          }
        }
      }
    }
    {
      Size tMin = cNullItm;
      Val tMinDist = cPosInfVal;
      if (tPrcsbQue.Empty() == false) {
        tMin = tPrcsbQue.Top();
        tMinDist = tDistArr[tMin];
      }
      if ((sMin == cNullItm) && (tMin == cNullItm)) {
        return;
      } else if (sMinDualAndDist < tMinDist) {
        *sLast = sMin;
        *dualShift = sMinDualAndDist;
        return;
      } else {
#ifdef STATS
        ++(mStats.mNumBfsVstdVtxs); // visit tMin.
#endif
        tPrcsbQue.Erase(tMin);
        tPrcsdQue.Push(tMin);
        tSttArr[tMin] = eSttBfsPrcsd;
        Size ss = tMateArr[tMin];
        if (ss == cNullItm) {
          *sLast = tPtrArr[tMin];
          *tLast = tMin;
          *dualShift = tMinDist;
          return;
        }
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        crtDist = tMinDist;
        Val sCrtDualAndDist = sDualArr[ss] + crtDist;
        if (sCrtDualAndDist < sMinDualAndDist) {
          sMin = ss;
          sMinDualAndDist = sCrtDualAndDist;
        }
        sDistArr[ss] = crtDist;
        sPtrArr[ss] = tPtrArr[tMin];
        sPrcsbQue.Push(ss);
        sSttArr[ss] = eSttBfsPrcsb;
      }
    }
  }
}

template<class ItmQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rFindAugPathEdgWghtSglSrc(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr,
    Size* sPtrArr, Size* tPtrArr, Val* sDistArr, Val* tDistArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue,
    ItmAndValIdxdPriQue& tPrcsbQue, ItmQue& tPrcsdQue, Size sFirst,
    Size* sLast, Size* tLast, Val* dualShift, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  *dualShift = cPosInfVal;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  Size sMinFirst = sFirst;
  sDistArr[sFirst] = 0.0;
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  rProcessEdgWghtSglPath<ItmQue, ItmAndValIdxdPriQue>
    (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, tPtrArr, sDistArr,
     tDistArr, sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsbQue, tPrcsdQue,
     sMinFirst, sLast, tLast, dualShift, rvrs);
}

template<class ItmQue, class ItmIdxdQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rFindAugPathEdgWghtMplSrc(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr,
    Size* sPtrArr, Size* tPtrArr, Val* sDistArr, Val* tDistArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue,
    ItmAndValIdxdPriQue& tPrcsbQue, ItmQue& tPrcsdQue, ItmIdxdQue& sExpsdQue,
    Size* sLast, Size* tLast, Val* dualShift, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  *dualShift = cPosInfVal;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  Size sMinFirst = cNullItm;
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumBfsVstdVtxs); // visit sFirst.
#endif
    if (sDualArr[sFirst] < sDualArr[sMinFirst]) {
      sMinFirst = sFirst;
    }
    sDistArr[sFirst] = 0.0;
    sPrcsbQue.Push(sFirst);
    sSttArr[sFirst] = eSttBfsPrcsb;
    sFirst = sExpsdQue.Next(sFirst);
  }
  rProcessEdgWghtSglPath<ItmQue, ItmAndValIdxdPriQue>
    (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, tPtrArr, sDistArr,
     tDistArr, sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsbQue, tPrcsdQue,
     sMinFirst, sLast, tLast, dualShift, rvrs);
}

template<class ItmQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rProcessPrfEdgWghtSglPath(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr,
    Size* sPtrArr, Size* tPtrArr, Val* sDistArr, Val* tDistArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue,
    ItmAndValIdxdPriQue& tPrcsbQue, ItmQue& tPrcsdQue, Size* sLast,
    Size* tLast, Val* dualShift, bool rvrs) const {
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const std::vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);
  Val crtDist = 0.0;
  while (true) {
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPrcsdQue.Push(s);
      sSttArr[s] = eSttBfsPrcsd;
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
#ifdef STATS
          ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        if (tSttArr[t] == eSttBfsPrcsd) {
          continue;
        }
        Val stEdgWght = sEdgWghtArr[i];
        Val slack = (sDualArr[s] + tDualArr[t]) - stEdgWght;
        if (slack <= 0) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
          if (tSttArr[t] == eSttBfsPrcsb) {
            tPrcsbQue.Erase(t);
          }
          tDistArr[t] = crtDist;
          tPrcsdQue.Push(t);
          tSttArr[t] = eSttBfsPrcsd;
          Size ss = tMateArr[t];
          if (ss == cNullItm) {
            *sLast = s;
            *tLast = t;
            *dualShift = crtDist;
            return;
          }
#ifdef STATS
          ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
          ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
          sDistArr[ss] = crtDist;
          sPtrArr[ss] = s;
          sPrcsbQue.Push(ss);
          sSttArr[ss] = eSttBfsPrcsb;
        } else {
          Val newDist = crtDist + slack;
          if (tDistArr[t] > newDist) {
            tDistArr[t] = newDist;
            tPtrArr[t] = s;
            if (tSttArr[t] == eSttIdle) {
              tPrcsbQue.Push(t, tDistArr[t]);
              tSttArr[t] = eSttBfsPrcsb;
            } else {
              tPrcsbQue.IncreasePriority(t, tDistArr[t]);
            }
          }
        }
      }
    }
    {
      Size tMin = cNullItm;
      Val tMinDist = cPosInfVal;
      if (tPrcsbQue.Empty() == false) {
        tMin = tPrcsbQue.Top();
        tMinDist = tDistArr[tMin];
      }
      if (tMin == cNullItm) {
        return;
      } else {
#ifdef STATS
        ++(mStats.mNumBfsVstdVtxs); // visit tMin.
#endif
        tPrcsbQue.Erase(tMin);
        tPrcsdQue.Push(tMin);
        tSttArr[tMin] = eSttBfsPrcsd;
        Size ss = tMateArr[tMin];
        if (ss == cNullItm) {
          *sLast = tPtrArr[tMin];
          *tLast = tMin;
          *dualShift = tMinDist;
          return;
        }
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        crtDist = tMinDist;
        sDistArr[ss] = crtDist;
        sPtrArr[ss] = tPtrArr[tMin];
        sPrcsbQue.Push(ss);
        sSttArr[ss] = eSttBfsPrcsb;
      }
    }
  }
}

template<class ItmQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rFindAugPathPrfEdgWghtSglSrc(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr,
    Size* sPtrArr, Size* tPtrArr, Val* sDistArr, Val* tDistArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue,
    ItmAndValIdxdPriQue& tPrcsbQue, ItmQue& tPrcsdQue, Size sFirst,
    Size* sLast, Size* tLast, Val* dualShift, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  *dualShift = cPosInfVal;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  sDistArr[sFirst] = 0.0;
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  rProcessPrfEdgWghtSglPath<ItmQue, ItmAndValIdxdPriQue>
    (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, tPtrArr, sDistArr,
     tDistArr, sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsbQue, tPrcsdQue,
     sLast, tLast, dualShift, rvrs);
}

template<class ItmQue, class ItmIdxdQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rFindAugPathPrfEdgWghtMplSrc(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr,
    Size* sPtrArr, Size* tPtrArr, Val* sDistArr, Val* tDistArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue,
    ItmAndValIdxdPriQue& tPrcsbQue, ItmQue& tPrcsdQue, ItmIdxdQue& sExpsdQue,
    Size* sLast, Size* tLast, Val* dualShift, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  *dualShift = cPosInfVal;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumBfsVstdVtxs); // visit sFirst.
#endif
    sDistArr[sFirst] = 0.0;
    sPrcsbQue.Push(sFirst);
    sSttArr[sFirst] = eSttBfsPrcsb;
    sFirst = sExpsdQue.Next(sFirst);
  }
  rProcessPrfEdgWghtSglPath<ItmQue, ItmAndValIdxdPriQue>
    (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, tPtrArr, sDistArr,
     tDistArr, sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsbQue, tPrcsdQue,
     sLast, tLast, dualShift, rvrs);
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void BptMatchingEngine::rFindMxmlSetAugPathsCard(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr, Stt* tSttArr,
    Size* sIdxArr, ItmStk& sPrcsbStk, ItmQue& sPrcsdQue, ItmIdxdQue& sExpsdQue,
    ItmQue& sLastQue, ItmQue& tLastQue, bool rvrs) const {
#ifdef STATS
  mStats.mNumDfsVstdVtxs = 0;
  mStats.mNumDfsVstdEdgs = 0;
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumDfsVstdVtxs); // visit sFirst.
#endif
    sPrcsbStk.Push(sFirst);
    sSttArr[sFirst] = eSttDfsPrcsb;
    while (sPrcsbStk.Empty() == false) {
      Size s = sPrcsbStk.Top();
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      while (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (s,t).
#endif
        Size ss = tMateArr[t];
        if (((ss == cNullItm) && (tSttArr[t] != eSttIdle)) ||
            ((ss != cNullItm) && (sSttArr[ss] != eSttIdle))) {
          ++(sIdxArr[s]);
        } else {
          break;
        }
      }
      if (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
        Size ss = tMateArr[t];
#ifdef STATS
        ++(mStats.mNumDfsVstdVtxs); // visit t.
#endif
        if (ss == cNullItm) {
          sLastQue.Push(s);
          tLastQue.Push(t);
          tSttArr[t] = eSttLast;
          while (sPrcsbStk.Empty() == false) {
            Size sss = sPrcsbStk.Top();
            sPrcsbStk.Pop();
            sPrcsdQue.Push(sss);
            sSttArr[sss] = eSttDfsPrcsd;
          }
          break;
        }
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumDfsVstdVtxs); // visit ss.
#endif
        sPtrArr[ss] = s;
        sPrcsbStk.Push(ss);
        sSttArr[ss] = eSttDfsPrcsb;
        ++(sIdxArr[s]);
      } else {
        sPrcsbStk.Pop();
        sPrcsdQue.Push(s);
        sSttArr[s] = eSttDfsPrcsd;
      }
    }
    sFirst = sExpsdQue.Next(sFirst);
  }
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void BptMatchingEngine::rFindMxmlSetAugPathsCardLkhd(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr, Stt* tSttArr,
    Size* sIdxArr, Size* sLkhdArr, ItmStk& sPrcsbStk, ItmQue& sPrcsdQue,
    ItmIdxdQue& sExpsdQue, ItmQue& sLastQue, ItmQue& tLastQue, bool rvrs)
    const {
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumDfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumDfsVstdEdgs = 0;
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumDfsVstdVtxs); // visit sFirst.
#endif
    sPrcsbStk.Push(sFirst);
    sSttArr[sFirst] = eSttDfsPrcsb;
    while (sPrcsbStk.Empty() == false) {
      Size s = sPrcsbStk.Top();
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      while (sLkhdArr[s] < sNumEdgs) {
        Size t = sVtxArr[sLkhdArr[s]];
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        Size ss = tMateArr[t];
        if (((ss == cNullItm) && (tSttArr[t] != eSttIdle)) ||
            (ss != cNullItm)) {
          ++(sLkhdArr[s]);
        } else {
          break;
        }
      }
      if (sLkhdArr[s] < sNumEdgs) {
        Size t = sVtxArr[sLkhdArr[s]];
#ifdef STATS
        ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
        sLastQue.Push(s);
        tLastQue.Push(t);
        tSttArr[t] = eSttLast;
        while (sPrcsbStk.Empty() == false) {
          Size sss = sPrcsbStk.Top();
          sPrcsbStk.Pop();
          sPrcsdQue.Push(sss);
          sSttArr[sss] = eSttDfsPrcsd;
        }
        ++(sLkhdArr[s]);
        break;
      }
      while (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (s,t).
#endif
        Size ss = tMateArr[t];
        if ((ss == cNullItm) ||
            ((ss != cNullItm) && (sSttArr[ss] != eSttIdle))) {
          ++(sIdxArr[s]);
        } else {
          break;
        }
      }
      if (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
        Size ss = tMateArr[t];
#ifdef STATS
        ++(mStats.mNumDfsVstdVtxs); // visit t.
        ++(mStats.mNumDfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumDfsVstdVtxs); // visit ss.
#endif
        sPtrArr[ss] = s;
        sPrcsbStk.Push(ss);
        sSttArr[ss] = eSttDfsPrcsb;
        ++(sIdxArr[s]);
      } else {
        sPrcsbStk.Pop();
        sPrcsdQue.Push(s);
        sSttArr[s] = eSttDfsPrcsd;
      }
    }
    sFirst = sExpsdQue.Next(sFirst);
  }
}

template<class ItmQue, class ItmIdxdQue>
void BptMatchingEngine::rComputeShrtstAugPathLenCard(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sLenArr, Size* tLenArr, Stt* sSttArr,
    Stt* tSttArr, ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, ItmQue& tPrcsdQue,
    ItmIdxdQue& sExpsdQue, Size* shrtstAugPathLen, bool rvrs) const {
  *shrtstAugPathLen = cInfSize;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumBfsVstdVtxs); // visit sFirst.
#endif
    sLenArr[sFirst] = 0;
    sPrcsbQue.Push(sFirst);
    sSttArr[sFirst] = eSttBfsPrcsb;
    sFirst = sExpsdQue.Next(sFirst);
  }
  Size sCrtLvl = 0;
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    if (sCrtLvl < sLenArr[s] / 2) {
      if (*shrtstAugPathLen != cInfSize) {
        break;
      }
      ++sCrtLvl;
    }
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      if (tSttArr[t] == eSttBfsPrcsd) {
        continue;
      }
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
      tLenArr[t] = sLenArr[s] + 1;
      tPrcsdQue.Push(t);
      tSttArr[t] = eSttBfsPrcsd;
      Size ss = tMateArr[t];
      if (ss == cNullItm) {
        *shrtstAugPathLen = tLenArr[t];
      } else {
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        sLenArr[ss] = tLenArr[t] + 1;
        sPrcsbQue.Push(ss);
        sSttArr[ss] = eSttBfsPrcsb;
      }
    }
  }
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void BptMatchingEngine::rFindMxmlSetShrtstAugPathsCard(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Size* sLenArr,
    Size* tLenArr, Stt* sSttArr, Stt* tSttArr, Size* sIdxArr,
    ItmStk& sPrcsbStk, ItmIdxdQue& sExpsdQue, Size shrtstAugPathLen,
    ItmQue& sLastQue, ItmQue& tLastQue, bool rvrs) const {
#ifdef STATS
  mStats.mNumDfsVstdVtxs = 0;
  mStats.mNumDfsVstdEdgs = 0;
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumDfsVstdVtxs); // visit sFirst.
#endif
    sPrcsbStk.Push(sFirst);
    sSttArr[sFirst] = eSttDfsPrcsb;
    while (sPrcsbStk.Empty() == false) {
      Size s = sPrcsbStk.Top();
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      while (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (s,t).
#endif
        Size ss = tMateArr[t];
        if ((tLenArr[t] != sLenArr[s] + 1) ||
            ((ss == cNullItm) && (tSttArr[t] == eSttLast)) ||
            ((ss != cNullItm) && ((sLenArr[s] + 1 == shrtstAugPathLen) ||
                                  (sSttArr[ss] == eSttDfsPrcsb) ||
                                  (sSttArr[ss] == eSttDfsPrcsd)))) {
          ++(sIdxArr[s]);
        } else {
          break;
        }
      }
      if (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
        Size ss = tMateArr[t];
#ifdef STATS
        ++(mStats.mNumDfsVstdVtxs); // visit t.
#endif
        if (ss == cNullItm) {
          sLastQue.Push(s);
          tLastQue.Push(t);
          tSttArr[t] = eSttLast;
          while (sPrcsbStk.Empty() == false) {
            Size sss = sPrcsbStk.Top();
            sPrcsbStk.Pop();
            sSttArr[sss] = eSttDfsPrcsd;
          }
          break;
        }
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumDfsVstdVtxs); // visit ss.
#endif
        sPtrArr[ss] = s;
        sPrcsbStk.Push(ss);
        sSttArr[ss] = eSttDfsPrcsb;
        ++(sIdxArr[s]);
      } else {
        sPrcsbStk.Pop();
        sSttArr[s] = eSttDfsPrcsd;
      }
    }
    sFirst = sExpsdQue.Next(sFirst);
  }
}

template<class ItmQue, class ItmIdxdQue>
void BptMatchingEngine::rComputeShrtstAugPathLenEdgWght(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr,
    Size* sLenArr, Size* tLenArr, Stt* sSttArr, Stt* tSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, ItmQue& tPrcsdQue,
    ItmIdxdQue& sExpsdQue, Size* shrtstAugPathLen, bool rvrs) const {
  *shrtstAugPathLen = cInfSize;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const std::vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumBfsVstdVtxs); // visit sFirst.
#endif
    sLenArr[sFirst] = 0;
    sPrcsbQue.Push(sFirst);
    sSttArr[sFirst] = eSttBfsPrcsb;
    sFirst = sExpsdQue.Next(sFirst);
  }
  Size sCrtLvl = 0;
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    if (sCrtLvl < sLenArr[s] / 2) {
      if (*shrtstAugPathLen != cInfSize) {
        break;
      }
      ++sCrtLvl;
    }
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      Val stEdgWght = sEdgWghtArr[i];
      Val slack = (sDualArr[s] + tDualArr[t]) - stEdgWght;
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      if ((slack > 0) || (tSttArr[t] == eSttBfsPrcsd)) {
        continue;
      }
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
      tLenArr[t] = sLenArr[s] + 1;
      tPrcsdQue.Push(t);
      tSttArr[t] = eSttBfsPrcsd;
      Size ss = tMateArr[t];
      if (ss == cNullItm) {
        *shrtstAugPathLen = tLenArr[t];
      } else {
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        sLenArr[ss] = tLenArr[t] + 1;
        sPrcsbQue.Push(ss);
        sSttArr[ss] = eSttBfsPrcsb;
      }
    }
  }
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void BptMatchingEngine::rFindMxmlSetShrtstAugPathsEdgWght(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Val* sDualArr,
    Val* tDualArr, Size* sPtrArr, Size* sLenArr, Size* tLenArr, Stt* sSttArr,
    Stt* tSttArr, Size* sIdxArr, ItmStk& sPrcsbStk, ItmIdxdQue& sExpsdQue,
    Size shrtstAugPathLen, ItmQue& sLastQue, ItmQue& tLastQue, bool rvrs)
    const {
#ifdef STATS
  mStats.mNumDfsVstdVtxs = 0;
  mStats.mNumDfsVstdEdgs = 0;
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const std::vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);
  Size sFirst = sExpsdQue.First();
  while (sFirst != cNullItm) {
#ifdef STATS
    ++(mStats.mNumDfsVstdVtxs); // visit sFirst.
#endif
    sPrcsbStk.Push(sFirst);
    sSttArr[sFirst] = eSttDfsPrcsb;
    while (sPrcsbStk.Empty() == false) {
      Size s = sPrcsbStk.Top();
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      while (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
        Val stEdgWght = sEdgWghtArr[sIdxArr[s]];
        Val slack = (sDualArr[s] + tDualArr[t]) - stEdgWght;
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (s,t).
#endif
        Size ss = tMateArr[t];
        if ((tLenArr[t] != sLenArr[s] + 1) || (slack > 0) ||
            ((ss == cNullItm) && (tSttArr[t] == eSttLast)) ||
            ((ss != cNullItm) && ((sLenArr[s] + 1 == shrtstAugPathLen) ||
                                  (sSttArr[ss] == eSttDfsPrcsb) ||
                                  (sSttArr[ss] == eSttDfsPrcsd)))) {
          ++(sIdxArr[s]);
        } else {
          break;
        }
      }
      if (sIdxArr[s] < sNumEdgs) {
        Size t = sVtxArr[sIdxArr[s]];
        Size ss = tMateArr[t];
#ifdef STATS
        ++(mStats.mNumDfsVstdVtxs); // visit t.
#endif
        if (ss == cNullItm) {
          sLastQue.Push(s);
          tLastQue.Push(t);
          tSttArr[t] = eSttLast;
          while (sPrcsbStk.Empty() == false) {
            Size sss = sPrcsbStk.Top();
            sPrcsbStk.Pop();
            sSttArr[sss] = eSttDfsPrcsd;
          }
          break;
        }
#ifdef STATS
        ++(mStats.mNumDfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumDfsVstdVtxs); // visit ss.
#endif
        sPtrArr[ss] = s;
        sPrcsbStk.Push(ss);
        sSttArr[ss] = eSttDfsPrcsb;
        ++(sIdxArr[s]);
      } else {
        sPrcsbStk.Pop();
        sSttArr[s] = eSttDfsPrcsd;
      }
    }
    sFirst = sExpsdQue.Next(sFirst);
  }
}

template<class ItmQue>
void BptMatchingEngine::rFindBestAugPathVtxWghtBfs(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size sFirst, Size* sLast,
    Size* tLast, bool rvrs) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const Val* tVtxWghtArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]);
  Val maxVtxWght = cNegInfVal;
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        continue;
      }
#ifdef STATS
      if (ss != cNullItm) {
        ++(mStats.mNumBfsVstdVtxs); // visit t.
      }
#endif
      if (ss == cNullItm) {
        if (maxVtxWght < tVtxWghtArr[t]) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
          *sLast = s;
          *tLast = t;
          maxVtxWght = tVtxWghtArr[t];
        }
        continue;
      }
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
      ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
      sPtrArr[ss] = s;
      sPrcsbQue.Push(ss);
      sSttArr[ss] = eSttBfsPrcsb;
    }
  }
}

template<class ItmQue>
void BptMatchingEngine::rFindBestAugPathVtxWghtBfsBnd(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Size* sLenArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size sFirst, Size* sLast,
    Size* tLast, Size augPathLenBnd, bool rvrs) const {
  assert(augPathLenBnd > 0);
  *sLast = cNullItm;
  *tLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const Val* tVtxWghtArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]);
  Val maxVtxWght = cNegInfVal;
  sLenArr[sFirst] = 0;
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        continue;
      }
#ifdef STATS
      if (ss != cNullItm) {
        ++(mStats.mNumBfsVstdVtxs); // visit t.
      }
#endif
      if (ss == cNullItm) {
        if (maxVtxWght < tVtxWghtArr[t]) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
          *sLast = s;
          *tLast = t;
          maxVtxWght = tVtxWghtArr[t];
        }
        continue;
      }
      sLenArr[ss] = sLenArr[s] + 2;
      if (sLenArr[ss] < augPathLenBnd) {
#ifdef STATS
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        sPtrArr[ss] = s;
        sPrcsbQue.Push(ss);
        sSttArr[ss] = eSttBfsPrcsb;
      }
    }
  }
}

template<class ItmQue>
void BptMatchingEngine::rFindRevPathVtxWghtBfs(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* sPtrArr, Stt* sSttArr,
    ItmQue& sPrcsbQue, ItmQue& sPrcsdQue, Size sFirst, Size* sLast, bool rvrs)
    const {
  *sLast = cNullItm;
#ifdef STATS
  mStats.mNumBfsVstdEdgs = 0;
  mStats.mNumBfsVstdVtxs = 1; // visit sFirst.
#endif
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const Val* sVtxWghtArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);
  sPrcsbQue.Push(sFirst);
  sSttArr[sFirst] = eSttBfsPrcsb;
  while (sPrcsbQue.Empty() == false) {
    Size s = sPrcsbQue.Front();
    sPrcsbQue.Pop();
    sPrcsdQue.Push(s);
    sSttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
      Size ss = tMateArr[t];
      if ((ss != cNullItm) && (sSttArr[ss] != eSttIdle)) {
        continue;
      }
      if (ss == cNullItm) {
        continue;
      } else {
#ifdef STATS
        ++(mStats.mNumBfsVstdVtxs); // visit t.
        ++(mStats.mNumBfsVstdEdgs); // visit (t,ss).
        ++(mStats.mNumBfsVstdVtxs); // visit ss.
#endif
        if (sVtxWghtArr[ss] < sVtxWghtArr[sFirst]) {
          sPtrArr[ss] = s;
          *sLast = ss;
          return;
        }
      }
      sPtrArr[ss] = s;
      sPrcsbQue.Push(ss);
      sSttArr[ss] = eSttBfsPrcsb;
    }
  }
}

template<class ItmQue>
void BptMatchingEngine::rComputeMaxCardMatchingSglSrcBfs(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* card, bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eCard;
  mStats.Resize(2);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    rInlzGrdyForCard(graph, sMateArr, tMateArr, &iniCard, rvrs);
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(0.0);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(iniCard);
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    if (sMateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    rFindAugPathCardSglSrcBfs<ItmQue>
      (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue,
       sFirst, &sLast, &tLast, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (tLast != cNullItm) {
#ifndef STATS
      rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
#else
      Size augPathLen = rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#endif
      ++(*card);
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue, class ItmStk>
void BptMatchingEngine::rComputeMaxCardMatchingSglSrcDfs(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* card, bool lkhd, bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eCard;
  mStats.Resize(2);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    rInlzGrdyForCard(graph, sMateArr, tMateArr, &iniCard, rvrs);
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(0.0);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(iniCard);
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  std::vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    std::fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  ItmStk sPrcsbStk(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    if (sMateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    if (lkhd == false) {
      rFindAugPathCardSglSrcDfs<ItmQue, ItmStk>
        (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sIdxArr, sPrcsbStk,
         sPrcsdQue, sFirst, &sLast, &tLast, rvrs);
    } else {
      rFindAugPathCardSglSrcDfsLkhd<ItmQue, ItmStk>
        (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sIdxArr, sPrcsbStk,
         sPrcsdQue, sFirst, &sLast, &tLast, rvrs);
    }
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumDfsVstdVtxs += static_cast<LSize>(mStats.mNumDfsVstdVtxs);
    mStats.mAggNumDfsVstdEdgs += static_cast<LSize>(mStats.mNumDfsVstdEdgs);
#endif
    if (tLast != cNullItm) {
#ifndef STATS
      rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
#else
      Size augPathLen = rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#endif
      ++(*card);
    }
    while (sPrcsbStk.Empty() == false) {
      Size s = sPrcsbStk.Top();
      sPrcsbStk.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue, class ItmIdxdQue>
void BptMatchingEngine::rComputeMaxCardMatchingMplSrcSglPath(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eCard;
  mStats.Resize(2);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    rInlzGrdyForCard(graph, sMateArr, tMateArr, &iniCard, rvrs);
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(0.0);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(static_cast<Size>(iniCard));
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
  ItmIdxdQue sExpsdQue(sNumVtxs);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sExpsdQue.Push(s);
    }
  }
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  do {
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    rFindAugPathCardMplSrcSglPath<ItmQue, ItmIdxdQue>
      (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue,
       sExpsdQue, &sLast, &tLast, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (tLast == cNullItm) {
      break;
    }
#ifndef STATS
    rAugment<ItmIdxdQue>(sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
#else
    Size augPathLen = rAugment<ItmIdxdQue>
      (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
    mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
    ++(mStats.mNumAugOps);
    ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#endif
    ++(*card);
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
  } while (true);
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void BptMatchingEngine::rComputeMaxCardMatchingMplPathDfs(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    bool lkhd, bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eCard;
  mStats.Resize(2);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    rInlzGrdyForCard(graph, sMateArr, tMateArr, &iniCard, rvrs);
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(0.0);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(static_cast<Size>(iniCard));
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, tNumVtxs);
  Stt* tSttArr = (tNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[tNumVtxs], eSttIdle);
  }
  std::vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    std::fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  std::vector<Size> sLkhdVec;
  if (lkhd == true) {
    ResizeVector<Size>(&sLkhdVec, sNumVtxs);
  }
  Size* sLkhdArr = (sNumVtxs == 0) ? NULL : &sLkhdVec[0];
  if (sLkhdArr != NULL) {
    std::fill(&sLkhdArr[0], &sLkhdArr[sNumVtxs], 0);
  }
  ItmStk sPrcsbStk(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
  ItmIdxdQue sExpsdQue(sNumVtxs);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sExpsdQue.Push(s);
    }
  }
  ItmQue sLastQue(sNumVtxs);
  ItmQue tLastQue(tNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  do {
    if (lkhd == false) {
      rFindMxmlSetAugPathsCard<ItmQue, ItmStk, ItmIdxdQue>
        (graph, sMateArr, tMateArr, sPtrArr, sSttArr, tSttArr, sIdxArr,
         sPrcsbStk, sPrcsdQue, sExpsdQue, sLastQue, tLastQue, rvrs);
    } else {
      rFindMxmlSetAugPathsCardLkhd<ItmQue, ItmStk, ItmIdxdQue>
        (graph, sMateArr, tMateArr, sPtrArr, sSttArr, tSttArr, sIdxArr,
         sLkhdArr, sPrcsbStk, sPrcsdQue, sExpsdQue, sLastQue, tLastQue, rvrs);
    }
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumDfsVstdVtxs += static_cast<LSize>(mStats.mNumDfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
    mStats.mAggNumDfsVstdEdgs += static_cast<LSize>(mStats.mNumDfsVstdEdgs);
#endif
    if (tLastQue.Empty() == true) {
      break;
    }
    while (tLastQue.Empty() == false) {
      Size sLast = sLastQue.Front();
      sLastQue.Pop();
      Size tLast = tLastQue.Front();
      tLastQue.Pop();
      tSttArr[tLast] = eSttIdle;
#ifndef STATS
      rAugment<ItmIdxdQue>
        (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
#else
      Size augPathLen = rAugment<ItmIdxdQue>
        (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#endif
      ++(*card);
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
  } while (true);
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void BptMatchingEngine::rComputeMaxCardMatchingMplPathBfsDfs(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eCard;
  mStats.Resize(2);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    rInlzGrdyForCard(graph, sMateArr, tMateArr, &iniCard, rvrs);
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(0.0);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(static_cast<Size>(iniCard));
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Size> sLenVec;
  ResizeVector<Size>(&sLenVec, sNumVtxs);
  Size* sLenArr = (sNumVtxs == 0) ? NULL : &sLenVec[0];
  if (sLenArr != NULL) {
    std::fill(&sLenArr[0], &sLenArr[sNumVtxs], cInfSize);
  }
  std::vector<Size> tLenVec;
  ResizeVector<Size>(&tLenVec, tNumVtxs);
  Size* tLenArr = (tNumVtxs == 0) ? NULL : &tLenVec[0];
  if (tLenArr != NULL) {
    std::fill(&tLenArr[0], &tLenArr[tNumVtxs], cInfSize);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, tNumVtxs);
  Stt* tSttArr = (tNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[tNumVtxs], eSttIdle);
  }
  std::vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    std::fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
  ItmQue tPrcsdQue(tNumVtxs);
  ItmStk sPrcsbStk(sNumVtxs);
  ItmIdxdQue sExpsdQue(sNumVtxs);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sExpsdQue.Push(s);
    }
  }
  ItmQue sLastQue(sNumVtxs);
  ItmQue tLastQue(tNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  do {
    Size shrtstAugPathLen;
    rComputeShrtstAugPathLenCard<ItmQue, ItmIdxdQue>
      (graph, sMateArr, tMateArr, sLenArr, tLenArr, sSttArr, tSttArr,
       sPrcsbQue, sPrcsdQue, tPrcsdQue, sExpsdQue, &shrtstAugPathLen, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (shrtstAugPathLen == cInfSize) {
      break;
    }
    rFindMxmlSetShrtstAugPathsCard<ItmQue, ItmStk, ItmIdxdQue>
      (graph, sMateArr, tMateArr, sPtrArr, sLenArr, tLenArr, sSttArr, tSttArr,
       sIdxArr, sPrcsbStk, sExpsdQue, shrtstAugPathLen, sLastQue, tLastQue,
       rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumDfsVstdVtxs += static_cast<LSize>(mStats.mNumDfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
    mStats.mAggNumDfsVstdEdgs += static_cast<LSize>(mStats.mNumDfsVstdEdgs);
#endif
    while (tLastQue.Empty() == false) {
      Size sLast = sLastQue.Front();
      sLastQue.Pop();
      Size tLast = tLastQue.Front();
      tLastQue.Pop();
#ifndef STATS
      rAugment<ItmIdxdQue>
        (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
#else
      Size augPathLen = rAugment<ItmIdxdQue>
        (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[shrtstAugPathLen / 2]);
#endif
      ++(*card);
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sLenArr[s] = cInfSize;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sLenArr[s] = cInfSize;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (tPrcsdQue.Empty() == false) {
      Size t = tPrcsdQue.Front();
      tPrcsdQue.Pop();
      tLenArr[t] = cInfSize;
      tSttArr[t] = eSttIdle;
    }
  } while (true);
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue, class ItmStk, class ItmIdxdQue,
    class ItmAndValIdxdPriQue>
void BptMatchingEngine::rComputeMaxEdgWghtMatchingSglSrc(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size* card, Val* edgWght, bool maxCard,
    bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eEdgWght;
  mStats.Resize(3);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  Val edgWghtShift = 0.0;
  // shift weights up only for a maximum cardinality maximum edge-weight
  // computation, do not shift weights for a pure maximum edge-weight
  // computation. it is the presence and absence of the weight shifting task
  // that distinguishes between a maximum cardinality maximum edge-weight
  // computation and a pure maximum edge-weight computation, respectively.
  if (maxCard == true) {
    edgWghtShift = graph.rGetMatchedEdgWghtBnd();
    graph.rShiftEdgWghts(edgWghtShift);
  }
  std::vector<Val> sDualVec;
  ResizeVector<Val>(&sDualVec, sNumVtxs);
  Val* sDualArr = (sNumVtxs == 0) ? NULL : &sDualVec[0];
  std::vector<Val> tDualVec;
  ResizeVector<Val>(&tDualVec, tNumVtxs);
  Val* tDualArr = (tNumVtxs == 0) ? NULL : &tDualVec[0];
  // it is the dual initialization that distinguishes between a nonperfect
  // or semiperfect maximum edge-weight computation on one side (loose dual
  // initialization) and a perfect maximum edge-weight computation on the other
  // side (tight dual initialization).
  
  rInlzDualsLoose inlzDualsFunctor(graph);
  inlzDualsFunctor(sDualArr, tDualArr, rvrs);
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
    
  } else {
    Size iniCard(0);
    Val iniEdgWght(0.0);
    rInlzGrdyForEdgWght
      (graph, sMateArr, tMateArr, sDualArr, tDualArr, &iniCard, &iniEdgWght,
       rvrs);
    if (maxCard == true) {
      iniEdgWght -= iniCard * edgWghtShift;
    }
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(iniEdgWght);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(static_cast<Size>(iniCard));
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Size> tPtrVec;
  ResizeVector<Size>(&tPtrVec, tNumVtxs);
  Size* tPtrArr = (tNumVtxs == 0) ? NULL : &tPtrVec[0];
  if (tPtrArr != NULL) {
    std::fill(&tPtrArr[0], &tPtrArr[tNumVtxs], cNullItm);
  }
  std::vector<Size> sLenVec;
  ResizeVector<Size>(&sLenVec, sNumVtxs);
  Size* sLenArr = (sNumVtxs == 0) ? NULL : &sLenVec[0];
  if (sLenArr != NULL) {
    std::fill(&sLenArr[0], &sLenArr[sNumVtxs], cInfSize);
  }
  std::vector<Size> tLenVec;
  ResizeVector<Size>(&tLenVec, tNumVtxs);
  Size* tLenArr = (tNumVtxs == 0) ? NULL : &tLenVec[0];
  if (tLenArr != NULL) {
    std::fill(&tLenArr[0], &tLenArr[tNumVtxs], cInfSize);
  }
  std::vector<Val> sDistVec;
  ResizeVector<Val>(&sDistVec, sNumVtxs);
  Val* sDistArr = (sNumVtxs == 0) ? NULL : &sDistVec[0];
  if (sDistArr != NULL) {
    std::fill(&sDistArr[0], &sDistArr[sNumVtxs], cPosInfVal);
  }
  std::vector<Val> tDistVec;
  ResizeVector<Val>(&tDistVec, tNumVtxs);
  Val* tDistArr = (tNumVtxs == 0) ? NULL : &tDistVec[0];
  if (tDistArr != NULL) {
    std::fill(&tDistArr[0], &tDistArr[tNumVtxs], cPosInfVal);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, tNumVtxs);
  Stt* tSttArr = (tNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[tNumVtxs], eSttIdle);
  }
  std::vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    std::fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
  ItmAndValIdxdPriQue tPrcsbQue(tNumVtxs);
  ItmQue tPrcsdQue(tNumVtxs);
  ItmStk sPrcsbStk(sNumVtxs);
  ItmIdxdQue sExpsdQue(sNumVtxs);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sExpsdQue.Push(s);
    }
  }
  ItmQue sLastQue(sNumVtxs);
  ItmQue tLastQue(tNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  do {
    Size shrtstAugPathLen;
    rComputeShrtstAugPathLenEdgWght<ItmQue, ItmIdxdQue>
      (graph, sMateArr, tMateArr, sDualArr, tDualArr, sLenArr, tLenArr,
       sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsdQue, sExpsdQue,
       &shrtstAugPathLen, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (shrtstAugPathLen != cInfSize) {
      rFindMxmlSetShrtstAugPathsEdgWght<ItmQue, ItmStk, ItmIdxdQue>
        (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, sLenArr,
         tLenArr, sSttArr, tSttArr, sIdxArr, sPrcsbStk, sExpsdQue,
         shrtstAugPathLen, sLastQue, tLastQue, rvrs);
#ifdef STATS
      ++(mStats.mNumGraphSrchs);
      mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
      mStats.mAggNumDfsVstdVtxs += static_cast<LSize>(mStats.mNumDfsVstdVtxs);
      mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
      mStats.mAggNumDfsVstdEdgs += static_cast<LSize>(mStats.mNumDfsVstdEdgs);
#endif
      while (tLastQue.Empty() == false) {
        Size sLast = sLastQue.Front();
        sLastQue.Pop();
        Size tLast = tLastQue.Front();
        tLastQue.Pop();
#ifndef STATS
        rAugment<ItmIdxdQue>
          (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
#else
        Size augPathLen = rAugment<ItmIdxdQue>
          (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
        mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
        ++(mStats.mNumAugOps);
        ++(mStats.mNumAugsPerAugPathLenArr[shrtstAugPathLen / 2]);
#endif
        ++(*card);
      }
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sLenArr[s] = cInfSize;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sLenArr[s] = cInfSize;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (tPrcsdQue.Empty() == false) {
      Size t = tPrcsdQue.Front();
      tPrcsdQue.Pop();
      tLenArr[t] = cInfSize;
      tSttArr[t] = eSttIdle;
    }
    if (shrtstAugPathLen == cInfSize) {
      break;
    }
  } while (true);
  sExpsdQue.Clear();
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif

  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    if (sMateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    Val dualShift;
    rFindAugPathEdgWghtSglSrc<ItmQue, ItmAndValIdxdPriQue>
      (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, tPtrArr,
       sDistArr, tDistArr, sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsbQue,
       tPrcsdQue, sFirst, &sLast, &tLast, &dualShift, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    // adjustments (reversing operations) are required for a nonperfect maximum
    // edge-weight computation, in order to correctly handle the duals.
    // generally, such a computation does not match all vertices, therefore the
    // duals are constrained to be nonnegative. in addition, the duals of the
    // vertices that are not matched must be equal to zero, in order for the
    // complementary slackness conditions to be satisfied. without corrections
    // it is not possible to guarantee that at the end of the computation the
    // duals of the vertices that are not matched are equal to zero.
    // it is the presence and absence of adjustments that distinguishes between
    // a nonperfect maximum edge-weight computation on one side and a perfect
    // or semiperfect maximum edge-weight computation on the other side,
    // respectively.
    if (tLast != cNullItm) {
#ifndef STATS
rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);

	
      
#else
      Size augPathLen = rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
      
#endif
      ++(*card);
    } else {
#ifndef STATS
      rReverse(sMateArr, tMateArr, sPtrArr, sLast);
#else
      Size revPathLen = rReverse(sMateArr, tMateArr, sPtrArr, sLast);
      mStats.mAggRevPathLen += static_cast<LSize>(revPathLen);
      ++(mStats.mNumRevOps);
      ++(mStats.mNumRevsPerRevPathLenArr[revPathLen / 2]);
#endif
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sDistArr[s] = cPosInfVal;
      sSttArr[s] = eSttIdle;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sDualArr[s] -= dualShift - sDistArr[s];
      sPtrArr[s] = cNullItm;
      sDistArr[s] = cPosInfVal;
      sSttArr[s] = eSttIdle;
    }
    while (tPrcsbQue.Empty() == false) {
      Size t = tPrcsbQue.Top();
      tPrcsbQue.Erase(t);
      tPtrArr[t] = cNullItm;
      tDistArr[t] = cPosInfVal;
      tSttArr[t] = eSttIdle;
    }
    while (tPrcsdQue.Empty() == false) {
      Size t = tPrcsdQue.Front();
      tPrcsdQue.Pop();
      tDualArr[t] += dualShift - tDistArr[t];
      tPtrArr[t] = cNullItm;
      tDistArr[t] = cPosInfVal;
      tSttArr[t] = eSttIdle;
    }
  }
  *edgWght = 0.0;
  {
    for (Size s = 0; s < sNumVtxs; ++s) {
      *edgWght += sDualArr[s];
    }
    for (Size t = 0; t < tNumVtxs; ++t) {
      *edgWght += tDualArr[t];
    }
  }
  if (maxCard == true) {
    *edgWght -= *card * edgWghtShift;
  }
  // shift weights back down only for a maximum cardinality maximum edge-weight
  // computation, do not shift weights for a pure maximum edge-weight
  // computation. it is the presence and absence of the weight shifting task
  // that distinguishes between a maximum cardinality maximum edge-weight
  // computation and a pure maximum edge-weight computation, respectively.
  if (maxCard == true) {
    graph.rShiftEdgWghts(-edgWghtShift);
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(*edgWght);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(mStats.mNumRevOps);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(mStats.mAggRevPathLen);
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(mStats.mMinRevPathLen);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(mStats.mMaxRevPathLen);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(mStats.mNumRevPathLens);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class InlzDualsFunctor, class ItmQue, class ItmStk, class ItmIdxdQue,
    class ItmAndValIdxdPriQue>
Err BptMatchingEngine::rComputePrfMaxEdgWghtMatchingSglSrc(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* edgWght, bool rvrs, InlzDualsFunctor inlzDualsFunctor) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eEdgWght;
  mStats.Resize(3);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  std::vector<Val> sDualVec;
  ResizeVector<Val>(&sDualVec, sNumVtxs);
  Val* sDualArr = (sNumVtxs == 0) ? NULL : &sDualVec[0];
  std::vector<Val> tDualVec;
  ResizeVector<Val>(&tDualVec, tNumVtxs);
  Val* tDualArr = (tNumVtxs == 0) ? NULL : &tDualVec[0];
  // it is the dual initialization that distinguishes between a nonperfect
  // or semiperfect maximum edge-weight computation on one side (loose dual
  // initialization) and a perfect maximum edge-weight computation on the other
  // side (tight dual initialization).
  inlzDualsFunctor(sDualArr, tDualArr, rvrs);
  if (mInlz == false) {
    if (sMateArr != NULL) {
      std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
    }
    if (tMateArr != NULL) {
      std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    Val iniEdgWght(0.0);
    rInlzGrdyForEdgWght
      (graph, sMateArr, tMateArr, sDualArr, tDualArr, &iniCard, &iniEdgWght,
       rvrs);
#ifdef STATS
    mStats.mCardVec.push_back(iniCard);
    mStats.mWghtVec.push_back(iniEdgWght);
    mStats.mNumGraphSrchsVec.push_back(1);
    mStats.mAggNumBfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdVtxs));
    mStats.mAggNumDfsVstdVtxsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdVtxs));
    mStats.mAggNumBfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumBfsVstdEdgs));
    mStats.mAggNumDfsVstdEdgsVec.push_back
      (static_cast<LSize>(mStats.mNumDfsVstdEdgs));
    mStats.mNumAugOpsVec.push_back(static_cast<Size>(iniCard));
    mStats.mNumRevOpsVec.push_back(0);
    mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(iniCard));
    mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
    mStats.mMinAugPathLenVec.push_back(1);
    mStats.mMinRevPathLenVec.push_back(0);
    mStats.mMaxAugPathLenVec.push_back(1);
    mStats.mMaxRevPathLenVec.push_back(0);
    mStats.mNumAugPathLensVec.push_back(1);
    mStats.mNumRevPathLensVec.push_back(0);
#endif
    *card = iniCard;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Size> tPtrVec;
  ResizeVector<Size>(&tPtrVec, tNumVtxs);
  Size* tPtrArr = (tNumVtxs == 0) ? NULL : &tPtrVec[0];
  if (tPtrArr != NULL) {
    std::fill(&tPtrArr[0], &tPtrArr[tNumVtxs], cNullItm);
  }
  std::vector<Size> sLenVec;
  ResizeVector<Size>(&sLenVec, sNumVtxs);
  Size* sLenArr = (sNumVtxs == 0) ? NULL : &sLenVec[0];
  if (sLenArr != NULL) {
    std::fill(&sLenArr[0], &sLenArr[sNumVtxs], cInfSize);
  }
  std::vector<Size> tLenVec;
  ResizeVector<Size>(&tLenVec, tNumVtxs);
  Size* tLenArr = (tNumVtxs == 0) ? NULL : &tLenVec[0];
  if (tLenArr != NULL) {
    std::fill(&tLenArr[0], &tLenArr[tNumVtxs], cInfSize);
  }
  std::vector<Val> sDistVec;
  ResizeVector<Val>(&sDistVec, sNumVtxs);
  Val* sDistArr = (sNumVtxs == 0) ? NULL : &sDistVec[0];
  if (sDistArr != NULL) {
    std::fill(&sDistArr[0], &sDistArr[sNumVtxs], cPosInfVal);
  }
  std::vector<Val> tDistVec;
  ResizeVector<Val>(&tDistVec, tNumVtxs);
  Val* tDistArr = (tNumVtxs == 0) ? NULL : &tDistVec[0];
  if (tDistArr != NULL) {
    std::fill(&tDistArr[0], &tDistArr[tNumVtxs], cPosInfVal);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  std::vector<Stt> tSttVec;
  ResizeVector<Stt>(&tSttVec, tNumVtxs);
  Stt* tSttArr = (tNumVtxs == 0) ? NULL : &tSttVec[0];
  if (tSttArr != NULL) {
    std::fill(&tSttArr[0], &tSttArr[tNumVtxs], eSttIdle);
  }
  std::vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    std::fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
  ItmAndValIdxdPriQue tPrcsbQue(tNumVtxs);
  ItmQue tPrcsdQue(tNumVtxs);
  ItmStk sPrcsbStk(sNumVtxs);
  ItmIdxdQue sExpsdQue(sNumVtxs);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
      sExpsdQue.Push(s);
    }
  }
  ItmQue sLastQue(sNumVtxs);
  ItmQue tLastQue(tNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  do {
    Size shrtstAugPathLen;
    rComputeShrtstAugPathLenEdgWght<ItmQue, ItmIdxdQue>
      (graph, sMateArr, tMateArr, sDualArr, tDualArr, sLenArr, tLenArr,
       sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsdQue, sExpsdQue,
       &shrtstAugPathLen, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (shrtstAugPathLen != cInfSize) {
      rFindMxmlSetShrtstAugPathsEdgWght<ItmQue, ItmStk, ItmIdxdQue>
        (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, sLenArr,
         tLenArr, sSttArr, tSttArr, sIdxArr, sPrcsbStk, sExpsdQue,
         shrtstAugPathLen, sLastQue, tLastQue, rvrs);
#ifdef STATS
      ++(mStats.mNumGraphSrchs);
      mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
      mStats.mAggNumDfsVstdVtxs += static_cast<LSize>(mStats.mNumDfsVstdVtxs);
      mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
      mStats.mAggNumDfsVstdEdgs += static_cast<LSize>(mStats.mNumDfsVstdEdgs);
#endif
      while (tLastQue.Empty() == false) {
        Size sLast = sLastQue.Front();
        sLastQue.Pop();
        Size tLast = tLastQue.Front();
        tLastQue.Pop();
#ifndef STATS
        rAugment<ItmIdxdQue>
          (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
#else
        Size augPathLen = rAugment<ItmIdxdQue>
          (sMateArr, tMateArr, sPtrArr, sExpsdQue, sLast, tLast);
        mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
        ++(mStats.mNumAugOps);
        ++(mStats.mNumAugsPerAugPathLenArr[shrtstAugPathLen / 2]);
#endif
        ++(*card);
      }
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sLenArr[s] = cInfSize;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sLenArr[s] = cInfSize;
      sSttArr[s] = eSttIdle;
      sIdxArr[s] = 0;
    }
    while (tPrcsdQue.Empty() == false) {
      Size t = tPrcsdQue.Front();
      tPrcsdQue.Pop();
      tLenArr[t] = cInfSize;
      tSttArr[t] = eSttIdle;
    }
    if (shrtstAugPathLen == cInfSize) {
      break;
    }
  } while (true);
  sExpsdQue.Clear();
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(0.0);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    if (sMateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    Val dualShift;
    rFindAugPathPrfEdgWghtSglSrc<ItmQue, ItmAndValIdxdPriQue>
      (graph, sMateArr, tMateArr, sDualArr, tDualArr, sPtrArr, tPtrArr,
       sDistArr, tDistArr, sSttArr, tSttArr, sPrcsbQue, sPrcsdQue, tPrcsbQue,
       tPrcsdQue, sFirst, &sLast, &tLast, &dualShift, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    // adjustments (reversing ops) are not required for a perfect or
    // semiperfect maximum edge-weight computation. such a computation matches
    // all vertices of interest, therefore the corresponding duals are free.
    // it is the presence and absence of adjustments that distinguishes between
    // a nonperfect maximum edge-weight computation on one side and a perfect
    // or semiperfect maximum edge-weight computation on the other side,
    // respectively.
    if (tLast != cNullItm) {
#ifndef STATS
      rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
#else
      Size augPathLen = rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#endif
      ++(*card);
    } else {
      return eErrNoPrfMatching;
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sDistArr[s] = cPosInfVal;
      sSttArr[s] = eSttIdle;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sDualArr[s] -= dualShift - sDistArr[s];
      sPtrArr[s] = cNullItm;
      sDistArr[s] = cPosInfVal;
      sSttArr[s] = eSttIdle;
    }
    while (tPrcsbQue.Empty() == false) {
      Size t = tPrcsbQue.Top();
      tPrcsbQue.Erase(t);
      tPtrArr[t] = cNullItm;
      tDistArr[t] = cPosInfVal;
      tSttArr[t] = eSttIdle;
    }
    while (tPrcsdQue.Empty() == false) {
      Size t = tPrcsdQue.Front();
      tPrcsdQue.Pop();
      tDualArr[t] += dualShift - tDistArr[t];
      tPtrArr[t] = cNullItm;
      tDistArr[t] = cPosInfVal;
      tSttArr[t] = eSttIdle;
    }
  }
  *edgWght = 0.0;
  {
    for (Size s = 0; s < sNumVtxs; ++s) {
      *edgWght += sDualArr[s];
    }
    for (Size t = 0; t < tNumVtxs; ++t) {
      *edgWght += tDualArr[t];
    }
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(*edgWght);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
  return eErrNone;
}

template<class ItmQue>
void BptMatchingEngine::rComputeMaxVtxWghtMatchingDrctGbl(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* vtxWght, Size augPathLenBnd, bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eVtxWght;
  mStats.Resize(1);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
  if (augPathLenBnd == 0) {
    return;
  }
  
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Size> sLenVec;
  ResizeVector<Size>(&sLenVec, sNumVtxs);
  Size* sLenArr = (sNumVtxs == 0) ? NULL : &sLenVec[0];
  if (sLenArr != NULL) {
    std::fill(&sLenArr[0], &sLenArr[sNumVtxs], cInfSize);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  const Val* sVtxWghtArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);
 std::vector<std::pair<Size, Val> > sExpsdLst2;
  ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, sNumVtxs);
  std::pair<Size,Val> * sExpsdLst2Arr=  (sNumVtxs == 0) ? NULL : &sExpsdLst2[0]; 
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    sExpsdLst2Arr[sFirst]=std::pair<Size, Val>(sFirst, sVtxWghtArr[sFirst]); 
  } 

  std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater<std::pair<Size, Val> >());
  
  for (Size current = 0; current < sNumVtxs; ++current) {
    	Size sFirst =  sExpsdLst2Arr[current].first;
    	if(sMateArr[sFirst] !=cNullItm)
    	continue;
    Size sLast(cNullItm);
    Size tLast(cNullItm);
      rFindAugPathCardSglSrcBfs<ItmQue>
        (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue,
         sFirst, &sLast, &tLast, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (tLast != cNullItm) {
#ifndef STATS
      Size augPathLen = rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#else
		rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
#endif
      ++(*card);
    }
	sPrcsbQue.Clear();
	sPrcsdQue.Clear();
	
  }
  
  *vtxWght = 0.0;
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] != cNullItm) {
      *vtxWght += sVtxWghtArr[s];
    }
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(*vtxWght);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue>
void BptMatchingEngine::rComputeMaxVtxWghtMatchingDrctLcl(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* vtxWght, Size augPathLenBnd, bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eVtxWght;
  mStats.Resize(1);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
  if (augPathLenBnd == 0) {
    return;
  }
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Size> sLenVec;
  ResizeVector<Size>(&sLenVec, sNumVtxs);
  Size* sLenArr = (sNumVtxs == 0) ? NULL : &sLenVec[0];
  if (sLenArr != NULL) {
    std::fill(&sLenArr[0], &sLenArr[sNumVtxs], cInfSize);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    if (augPathLenBnd == cInfSize) {
      rFindBestAugPathVtxWghtBfs<ItmQue>
        (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue,
         sFirst, &sLast, &tLast, rvrs);
    } else {
      rFindBestAugPathVtxWghtBfsBnd<ItmQue>
        (graph, sMateArr, tMateArr, sPtrArr, sLenArr, sSttArr, sPrcsbQue,
         sPrcsdQue, sFirst, &sLast, &tLast, augPathLenBnd, rvrs);
    }
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (tLast != cNullItm) {
#ifndef STATS
      rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
#else
      Size augPathLen = rAugment(sMateArr, tMateArr, sPtrArr, sLast, tLast);
      mStats.mAggAugPathLen += static_cast<LSize>(augPathLen);
      ++(mStats.mNumAugOps);
      ++(mStats.mNumAugsPerAugPathLenArr[augPathLen / 2]);
#endif
      ++(*card);
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
  }
  const Val* tVtxWghtArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]);
  *vtxWght = 0.0;
  for (Size t = 0; t < tNumVtxs; ++t) {
    if (tMateArr[t] != cNullItm) {
      *vtxWght += tVtxWghtArr[t];
    }
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(*card);
  mStats.mWghtVec.push_back(*vtxWght);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(mStats.mNumAugOps);
  mStats.mNumRevOpsVec.push_back(0);
  mStats.mAggAugPathLenVec.push_back(mStats.mAggAugPathLen);
  mStats.mAggRevPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mMinAugPathLenVec.push_back(mStats.mMinAugPathLen);
  mStats.mMinRevPathLenVec.push_back(0);
  mStats.mMaxAugPathLenVec.push_back(mStats.mMaxAugPathLen);
  mStats.mMaxRevPathLenVec.push_back(0);
  mStats.mNumAugPathLensVec.push_back(mStats.mNumAugPathLens);
  mStats.mNumRevPathLensVec.push_back(0);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue, class ItmAndValIdxdPriQue>
void BptMatchingEngine::rComputeMaxVtxWghtMatchingSpcl(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Size card, Val* vtxWght, bool rvrs) const {
#ifdef STATS
  mStats.mRvrs = rvrs;
  mStats.mComputationType = eVtxWght;
  mStats.Resize(1);
#endif
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
#ifdef STATS
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
#endif
  std::vector<Size> sPtrVec;
  ResizeVector<Size>(&sPtrVec, sNumVtxs);
  Size* sPtrArr = (sNumVtxs == 0) ? NULL : &sPtrVec[0];
  if (sPtrArr != NULL) {
    std::fill(&sPtrArr[0], &sPtrArr[sNumVtxs], cNullItm);
  }
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  ItmQue sPrcsbQue(sNumVtxs);
  ItmQue sPrcsdQue(sNumVtxs);
#ifdef STATS
  mStats.Reset((sNumVtxs + tNumVtxs) / 2);
#endif
  const Val* sVtxWghtArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);
  ItmAndValIdxdPriQue sExpsdQue(sNumVtxs);
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    if (sMateArr[sFirst] == cNullItm) {
      sExpsdQue.Push(sFirst, sVtxWghtArr[sFirst]);
    }
  }
  while (sExpsdQue.Empty() == false) {
    Size sFirst = sExpsdQue.Top();
    sExpsdQue.Erase(sFirst);
    Size sLast(cNullItm);
    rFindRevPathVtxWghtBfs<ItmQue>
      (graph, sMateArr, tMateArr, sPtrArr, sSttArr, sPrcsbQue, sPrcsdQue,
       sFirst, &sLast, rvrs);
#ifdef STATS
    ++(mStats.mNumGraphSrchs);
    mStats.mAggNumBfsVstdVtxs += static_cast<LSize>(mStats.mNumBfsVstdVtxs);
    mStats.mAggNumBfsVstdEdgs += static_cast<LSize>(mStats.mNumBfsVstdEdgs);
#endif
    if (sLast != cNullItm) {
#ifndef STATS
      rReverse(sMateArr, tMateArr, sPtrArr, sLast);
#else
      Size revPathLen = rReverse(sMateArr, tMateArr, sPtrArr, sLast);
      mStats.mAggRevPathLen += static_cast<LSize>(revPathLen);
      ++(mStats.mNumRevOps);
      ++(mStats.mNumRevsPerRevPathLenArr[revPathLen / 2]);
#endif
      sExpsdQue.Push(sLast, sVtxWghtArr[sLast]);
    }
    while (sPrcsbQue.Empty() == false) {
      Size s = sPrcsbQue.Front();
      sPrcsbQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
    if (sLast != cNullItm) {
      sPtrArr[sLast] = cNullItm;
    }
    while (sPrcsdQue.Empty() == false) {
      Size s = sPrcsdQue.Front();
      sPrcsdQue.Pop();
      sPtrArr[s] = cNullItm;
      sSttArr[s] = eSttIdle;
    }
  }
  *vtxWght = 0.0;
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] != cNullItm) {
      *vtxWght += sVtxWghtArr[s];
    }
  }
#ifdef STATS
  mStats.ComputePathStats
    (&mStats.mNumAugPathLens, &mStats.mMinAugPathLen, &mStats.mMaxAugPathLen,
     &mStats.mNumRevPathLens, &mStats.mMinRevPathLen, &mStats.mMaxRevPathLen);
  mStats.mCardVec.push_back(card);
  mStats.mWghtVec.push_back(*vtxWght);
  mStats.mNumGraphSrchsVec.push_back(mStats.mNumGraphSrchs);
  mStats.mAggNumBfsVstdVtxsVec.push_back(mStats.mAggNumBfsVstdVtxs);
  mStats.mAggNumDfsVstdVtxsVec.push_back(mStats.mAggNumDfsVstdVtxs);
  mStats.mAggNumBfsVstdEdgsVec.push_back(mStats.mAggNumBfsVstdEdgs);
  mStats.mAggNumDfsVstdEdgsVec.push_back(mStats.mAggNumDfsVstdEdgs);
  mStats.mNumAugOpsVec.push_back(0);
  mStats.mNumRevOpsVec.push_back(mStats.mNumRevOps);
  mStats.mAggAugPathLenVec.push_back(static_cast<LSize>(0));
  mStats.mAggRevPathLenVec.push_back(mStats.mAggRevPathLen);
  mStats.mMinAugPathLenVec.push_back(0);
  mStats.mMinRevPathLenVec.push_back(mStats.mMinRevPathLen);
  mStats.mMaxAugPathLenVec.push_back(0);
  mStats.mMaxRevPathLenVec.push_back(mStats.mMaxRevPathLen);
  mStats.mNumAugPathLensVec.push_back(0);
  mStats.mNumRevPathLensVec.push_back(mStats.mNumRevPathLens);
  if (mStatsPrint == true) {
    mStats.Print(std::string(__PRETTY_FUNCTION__));
  }
#endif
}

template<class ItmQue>
void BptMatchingEngine::rComputeMaxVtxWghtMatchingLocal(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* vtxWght) const {
	Size sNumVtxs = graph.mSNumVtxs;
	Size tNumVtxs = graph.mTNumVtxs;
	if (sMateArr != NULL) {
		std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
	}
	if (tMateArr != NULL) {
		std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
	}
	*card = 0;
  
	std::vector<Size> sAliveVec;
  	ResizeVector<Size>(&sAliveVec, sNumVtxs);

  	Size* sAlive = (sNumVtxs == 0) ? NULL : &sAliveVec[0];

  	if (sAlive != NULL) {
    	std::fill(&sAlive[0], &sAlive[sNumVtxs], 1);
  	}

   	std::vector<Size> tAliveVec;

  	ResizeVector<Size>(&tAliveVec, tNumVtxs);

  	Size* tAlive = (tNumVtxs == 0) ? NULL : &tAliveVec[0];

  	if (tAlive != NULL) {
    	std::fill(&tAlive[0], &tAlive[tNumVtxs], 1);
  	}

	const std::vector<Size>* sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
	const std::vector<Size>* tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];

	const Val* sVtxWghtArr =((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) ;
	const Val* tVtxWghtArr = ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);

  	bool done = false;

	while(!done)
	{	  
		for (Size first = 0; first < sNumVtxs; ++first)
   		{
	   		Val heaviest=0.0;
	    	if(sAlive[first]==0 || sMateArr[first]!=cNullItm)
	    		continue;	
	    	Size t = -1;
	    	Size sNumEdgs = sVtxVecArr[first].size();
	        const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[first][0];
		    for (Size i = 0; i < sNumEdgs; ++i) {
		    	//nedges_profile++;
		      	Size tempT = currentVtxArr[i];
		      	if(tAlive[tempT]==0)
			   		continue;
		      	if(tVtxWghtArr[tempT] > heaviest ||(tVtxWghtArr[tempT]==heaviest && tempT > t)) {
		        	t= tempT;
	    			heaviest = tVtxWghtArr[tempT];
		      		}
		    	}
				done =true;
				if(heaviest >0.0)
				   	sMateArr[first]=t;
				else
				  	sAlive[first]=0;
		}
	
		for (Size first = 0; first < tNumVtxs; ++first)
	   	{
	   		Val heaviest=0.0;
	    	if(tAlive[first]==0 || tMateArr[first]!=cNullItm)
	    		continue;
	    	Size s = -1;
	    	Size tNumEdgs = tVtxVecArr[first].size();
	        const Size* currentVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[first][0];
		    for (Size i = 0; i < tNumEdgs; ++i) {
		    	Size tempS = currentVtxArr[i];
		      	if(sAlive[tempS]==0)
			   		continue;
		      	if(sVtxWghtArr[tempS] > heaviest ||(sVtxWghtArr[tempS]==heaviest && tempS>s)) {
		        	s= tempS;
	    			heaviest = sVtxWghtArr[tempS];
		      	}
		    }
			done =true;
			if(heaviest >0.0)
			   	tMateArr[first]=s;
			else
			   	tAlive[first]=0;
		}
	
		for(Size first = 0; first < tNumVtxs; ++first){
			if(tAlive[first]==0)
	            continue;
	        Size curr =tMateArr[first];
	        if(sMateArr[curr]!= first)
	        {
	           	tMateArr[first]=cNullItm;
	           	done=false;
			}
			else
			{
				tAlive[first]=0;
				sAlive[curr]=0;
			}   
		}
		for (Size first = 0; first < sNumVtxs; ++first){
			if(sAlive[first]==0)
	            continue;            
	        Size curr =sMateArr[first];
	        if(tMateArr[curr]!= first)
	        {
	           	sMateArr[first]=cNullItm;
	           	done=false;
			}
		}

	}//end while
	
	  *vtxWght = 0.0;
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] != cNullItm) {
      *vtxWght = *vtxWght + sVtxWghtArr[s];
      *card = *card + 1;
    }
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    if (tMateArr[t] != cNullItm) {
      *vtxWght = *vtxWght + tVtxWghtArr[t];
    }
  }

}

template<class ItmQue>
void BptMatchingEngine::rComputeMaxVtxWghtMatchingSuitor(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* vtxWght, bool rvrs) const {

  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  
  if (tMateArr != NULL) {
    std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
 std::vector<Val> tWs;
  ResizeVector<Val>(&tWs, tNumVtxs);
  Val* tws = (tNumVtxs == 0) ? NULL : &tWs[0];
  if (tws != NULL) {
    std::fill(&tws[0], &tws[tNumVtxs], cZeroVal);
  }
  
  const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
    
    
  const Val* sVtxWghtArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);
  
  for (Size first = 0; first < sNumVtxs; ++first)
   {
    Size current = first;
    bool done = false;
    while(!done)
    {  	
    	 Size partner = sMateArr[current];
    	Val heaviest = 0;
    	 Size sNumEdgs = sVtxVecArr[current].size();
         const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[current][0];
         
	    for (Size i = 0; i < sNumEdgs; ++i) {
	      Size t = currentVtxArr[i];	   
				if((sVtxWghtArr[current] > tws[t]) /*|| (sVtxWghtArr[current] == tws[t] && tMateArr[t]>current)*/)
	            	{
					partner = t;
    				heaviest = sVtxWghtArr[current];
    				break;
					}
					else if (tMateArr[t] !=cNullItm && sVtxWghtArr[current] == tws[t] && tMateArr[t]>current)
					{
						partner = t;
    				    heaviest = sVtxWghtArr[current];
						break;   
					}
	    }
	    done = true;
	    if(heaviest > 0)
	    {
	    	Size y = tMateArr[partner];
	    	tMateArr[partner]=current;
	    	tws[partner]=heaviest;
	    	if(y != cNullItm)
	    	{
	    		current = y;
	    		done= false;
			}
		}	
	}
}
  *vtxWght = 0.0;
  Size mate =-1;
  for (Size t = 0; t < tNumVtxs; ++t) {
    if (tMateArr[t] != cNullItm) {
    	++(*card);
    	mate= tMateArr[t];
    	sMateArr[mate]=t;
      *vtxWght += sVtxWghtArr[mate];
    }
  }
}


template<class ItmQue>
void BptMatchingEngine::rComputeHalfVtxWghtMatchingDrctGbl(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* vtxWght, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
  
   const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
 
  ItmQue sPrcsbQue(sNumVtxs);

   const Val* sVtxWghtArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);
 
  std::vector<std::pair<Size, Val> > sExpsdLst2;
  ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, sNumVtxs);
  std::pair<Size,Val> * sExpsdLst2Arr=  (sNumVtxs == 0) ? NULL : &sExpsdLst2[0]; 

  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    sExpsdLst2Arr[sFirst]=std::pair<Size, Val>(sFirst, sVtxWghtArr[sFirst]); 
  } 

	std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater<std::pair<Size, Val> >());
	Size sFirst=0;
    for (Size current = 0; current < sNumVtxs; ++current) {
    	sFirst =  sExpsdLst2Arr[current].first;
		Size sNumEdgs = sVtxVecArr[sFirst].size();
		const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[sFirst][0];
		for (Size i = 0; i < sNumEdgs; ++i) {
		  Size t = sVtxArr[i];
		  if(tMateArr[t]== cNullItm)
		  {
			tMateArr[t]=sFirst;
			sMateArr[sFirst]=t;		
			break;
		  }
	}
  }
  *vtxWght = 0.0;
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] != cNullItm) {
    	++(*card);
      *vtxWght += sVtxWghtArr[s];
    }
  }
}


template<class ItmQue>
void BptMatchingEngine::rComputeTwoThirdVtxWghtMatchingDrctGbl(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* vtxWght, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;

   const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
 
  std::deque<Size> sPrcsbQue;
  std::deque<Size> sPrcsdQue;
  
  std::vector<Stt> sSttVec;
  ResizeVector<Stt>(&sSttVec, sNumVtxs);
  Stt* sSttArr = (sNumVtxs == 0) ? NULL : &sSttVec[0];
  if (sSttArr != NULL) {
    std::fill(&sSttArr[0], &sSttArr[sNumVtxs], eSttIdle);
  }
  
  const Val* sVtxWghtArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]);
  
  std::vector<std::pair<Size, Val> > sExpsdLst2;
  ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, sNumVtxs);
  std::pair<Size,Val> * sExpsdLst2Arr=  (sNumVtxs == 0) ? NULL : &sExpsdLst2[0]; 

  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
    sExpsdLst2Arr[sFirst]=std::pair<Size, Val>(sFirst, sVtxWghtArr[sFirst]); 
  } 

  std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater<std::pair<Size, Val> >());

    for (Size current = 0; current < sNumVtxs; ++current) {
    	Size sFirst =  sExpsdLst2Arr[current].first;
    Size sNumEdgs = sVtxVecArr[sFirst].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[sFirst][0];
	bool found=false;
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
	  if(tMateArr[t]== cNullItm)
	  {
		tMateArr[t]=sFirst;
		sMateArr[sFirst]=t;
		while (sPrcsdQue.empty() == false) {
	      Size s = sPrcsdQue.front();
	      sPrcsdQue.pop_front();
	      sSttArr[s] = eSttIdle;
	    }
		++(*card);
		found=true;
		break;
	  }
	  else if(sSttArr[tMateArr[t]]==eSttIdle)
	  {
		sPrcsbQue.push_back(tMateArr[t]);
		sPrcsdQue.push_back(tMateArr[t]);
	  }
	}
	if(!found)
	{
		while (sPrcsbQue.empty() == false) {
			bool found2=false;
		  Size s = sPrcsbQue.front();
		  sPrcsbQue.pop_front();
		  sSttArr[s]=eSttBfsPrcsd;
		  Size sNumEdgs = sVtxVecArr[s].size();
			const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
			for (Size i = 0; i < sNumEdgs; ++i) {
			  Size t = sVtxArr[i];
			  if(tMateArr[t]== cNullItm)
			  {
				Size tempMate=sMateArr[s];
				tMateArr[t]=s;
				sMateArr[s]=t;
				tMateArr[tempMate]=sFirst;
				sMateArr[sFirst]=tempMate;
				while (sPrcsdQue.empty() == false) {
		      Size s = sPrcsdQue.front();
		      sPrcsdQue.pop_front();
		      sSttArr[s] = eSttIdle;
		    }
				++(*card);
				found2=true;
				break;
			  }
			  }
			  if(found2)
			  break;
			  
		  
		}
	}
	sPrcsbQue.clear();
	sPrcsdQue.clear();
}
  *vtxWght = 0.0;
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] != cNullItm) {
      *vtxWght += sVtxWghtArr[s];
    }
  }
}

template<class ItmQue>
void BptMatchingEngine::rComputeHalfEdgWghtMatching(
    const BptGraph& graph, Size* sMateArr, Size* tMateArr, Size* card,
    Val* edgWght, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  Size numEdgs = graph.mNumEdgs;
  if (sMateArr != NULL) {
    std::fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    std::fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
  *edgWght=0;
  
   const std::vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
   const std::vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);

  std::vector<std::pair<std::pair<Size,Size>, Val> > sExpsdLst2;
  ResizeVector<std::pair<std::pair<Size,Size>, Val> >(&sExpsdLst2, numEdgs);
  std::pair<std::pair<Size,Size>,Val> * sExpsdLst2Arr=  (numEdgs == 0) ? NULL : &sExpsdLst2[0]; 

	Size edgeCounter =0;
  for (Size sFirst = 0; sFirst < sNumVtxs; ++sFirst) {
  	   Size sNumEdgs = sVtxVecArr[sFirst].size();
  	   
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[sFirst][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[sFirst][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
	  Val wgt = sEdgWghtArr[i];
	  std::pair<Size,Size> p (sFirst,t);
      sExpsdLst2Arr[edgeCounter]=std::pair<std::pair<Size,Size>, Val>(p, wgt);
      edgeCounter++;
      }
  } 

	std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreaterPairs< std::pair< std::pair<Size,Size>, Val> >()); 

	std::pair<Size,Size> sedge;
    for (Size current = 0; current < numEdgs; ++current) {
    	sedge =  sExpsdLst2Arr[current].first;
    	
    	Size s = sedge.first;
    	Size t = sedge.second;
       if(sMateArr[s]!=cNullItm || tMateArr[t]!=cNullItm)
       continue;
       else
       {
    	  tMateArr[t]=s;
		  sMateArr[s]=t;
		  ++(*card);
		  *edgWght += sExpsdLst2Arr[current].second;	
	   }
	}
}
////////////////////////////////////////////end///////////////////////////////////////////////////////////////////////

} // namespace Matchbox

#endif // BPT_MATCHING_ENGINE_H
