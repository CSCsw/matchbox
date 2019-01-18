#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#define EPS 0.0000001

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for fill, find, sort.
#include <numeric> // for accumulate.
#include <cassert>
#include <cmath>  
#include <queue>
#include <stack>
#include <omp.h>

#include "Functional.h" // for ValGreater.
#include "Types.h"
#include "Graph.h"
#include "Utility.h" // for ResizeVector.
#include "VecItmQue.h"
#include "LstItmQue.h"


#include "VecItmStk.h"
#include "LstItmStk.h"
#include "LstItmIdxdQue.h"
#include "LstItmAndValIdxdMinPriQue.h"
#include "BhpItmAndValIdxdMinPriQue.h"
#include "LstItmAndValIdxdMaxPriQue.h"
#include "BhpItmAndValIdxdMaxPriQue.h"
#include "Timer.h"

namespace Matchbox {

class MatchingEngine {
public:
  /// Constructor.
  MatchingEngine():
      mInlz(false), mQueAndStkType(eVecQueAndStk), mIdxdQueType(eLstIdxdQue),
      mIdxdPriQueType(eBhpIdxdPriQue), mCardGraphSrchType(eSglSrcBfs),
      mEdgWghtGraphSrchType(eSglSrcBfs), mVtxWghtAlgType(eDrct),
      mPrcmptdMaxCard(false), mPrecision(cMaxPrecision), mFullPrint(false),
      mStatsPrint(false) {}

  /// Destructor.
  ~MatchingEngine() {}

  ///
  void ComputeMxmlMatching(const Graph& graph,
                           std::vector<Size>* mateVec,
                           Size* card) const;

  ///
  void ComputeMaxCardMatching(const Graph& graph,
                              std::vector<Size>* mateVec,
                              Size* card) const;

  ///
  void ComputeAprxMaxEdgWghtMatching4(const Graph& graph,
                                      std::vector<Size>* mateVec,
                                      Size* card,
                                      Val* edgWght) const;
  ///
  void ComputeMaxVtxWghtMatching(const Graph& graph,
                                      std::vector<Size>* mateVec,
                                      Size* card,
                                      Val* vtxWght, Size augPathLenBnd) const;

  ///
  void ComputeHalfVtxWghtMatching(const Graph& graph,
                                      std::vector<Size>* mateVec,
                                      Size* card,
                                      Val* vtxWght) const;
  ///
  void ComputeTwoThirdVtxWghtMatching(const Graph& graph,
                                      std::vector<Size>* mateVec,
                                      Size* card,
                                      Val* vtxWght) const;
  /////
  void SuitorVtxWghtMatching(const Graph& graph,
     							std::vector<Size>* mateVec, 
								 Size* card, 
								 Val* vtxWght) const;
  ///
  void ParSuitorVtxWghtMatching(const Graph& graph,
     								std::vector<Size>* mateVec, 
									 Size* card, 
									 Val* vtxWght) const;
  ///
  void PGVtxWghtMatching(const Graph& graph,
     						std::vector<Size>* mateVec,
							Size* card, 
							Val* vtxWght) const;  
	///
  void PGDPVtxWght(const Graph& graph,
     					std::vector<Size>* mateVec, 
						Size* card, 
						Val* vtxWght) const;
	////
	void LocallyDominantVtxWght(const Graph& graph, 
									std::vector<Size>* mateVec, 
									Size* card, 
									Val* vtxWght)  const;
	///
	void ScaleOneMinusEpsVtxWght(const Graph& graph,
     							std::vector<Size>* mateVec, 
								Size* card, 
								Val* vtxWght, 
								Val ep) const;
     ////
	void ComputeHalfEdgWghtMatching(const Graph& graph, 
									std::vector<Size>* mateVec, 
									Size* card, 
									Val* edgWght) const;
  //////////
  Err GetMatchedEdgWght(const Graph& graph,
                        const std::vector<Size>& mateVec,
                        Size card,
                        Val *edgWght) const;

  ///
  Err GetMatchedVtxWght(const Graph& graph,
                        const std::vector<Size>& mateVec,
                        Size card,
                        Val *vtxWght,
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
      mCardGraphSrchType = cardGraphSrchType;
      return eErrNone;
    default:
      // TODO: add other cardinality computations, especially multiple path.
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
  bool CheckMatching(const Graph& graph,
                     const std::vector<Size>& mateVec,
                     Size card) const;

  ///
  void PrintMatching(const std::vector<Size>& mateVec,
                     Size card) const;

  ///
  void PrintMatching(const std::vector<Size>& mateVec,
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

  // forbid the copy constructor and the assignment operator.
  MatchingEngine(const MatchingEngine&);
  MatchingEngine& operator=(const MatchingEngine&);

  ///
  void rInlzGrdyForCard(const Graph& graph,
                        Size* mateArr,
                        Size* card) const;
  ///
  void rAugment(Size* mateArr,
                Size* ptr1Arr,
                Size* ptr2Arr,
                Size sLast,
                Size tLast) const;
  ///       
  void rAugment(Size* mateArr,
                Size* ptr1Arr,
                Size* ptr2Arr,
                Size sLast,
                Size tLast,
				Val* auglen) const;
				////////      
  void fix(Size* mateArr,
                Size* ptr1Arr,
                Size* ptr2Arr,
                Size sLast,
                Size tLast) const;
  ///
  Size rFind(Size* linkArr,
             Size u) const;

  ///
  void rUnion(Size* linkArr,
              Size* rankArr,
              Size u,
              Size v) const;

  ///
  void rLink(Size* linkArr,
             Size* rankArr,
             Size u,
             Size v) const;

  ///
  /// without disjoint set support.
  template<class ItmQue>
  void rProcessBlsm1(const Graph& graph,
                     Size* mateArr,
                     Size* ptr1Arr,
                     Size* ptr2Arr,
                     Size* blsmArr,
                     Size* rprsArr,
                     Stt* sttArr,
                     ItmQue& prcsbQue,
                     Size s1,
                     Size s2,
                     Size blsm) const;

  ///
  /// witho disjoint set support.
  template<class ItmQue>
  void rProcessBlsm2(const Graph& graph,
                     Size* mateArr,
                     Size* ptr1Arr,
                     Size* ptr2Arr,
                     Size* blsmArr,
                     Size* rprsArr,
                     Size* linkArr,
                     Size* rankArr,
                     Stt* sttArr,
                     ItmQue& prcsbQue,
                     Size s1,
                     Size s2,
                     Size blsm) const;
///
///used by speculative MVM  
template<class ItmQue>
void rProcessBlsm6(const Graph& graph, 
				Size* mateArr,
    			Size* ptr1Arr, 
				Size* ptr2Arr, 
				Size* blsmArr, 
				Size* rprsArr, 
				Size* linkArr,
    			Size* rankArr, 
				Stt* sttArr, 
				ItmQue& prcsbQue, 
				Size s1, 
				Size s2, 
				Size blsm, 
				Val* minVtxWght, 
				Size* sLast, 
				Size* tLast) const;
	////
  ///
  /// implicitly breadth-first.
  /// without disjoint set support.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue>
  void rFindAugPathCardSglSrc1(const Graph& graph,
                               Size* mateArr,
                               Size* ptr1Arr,
                               Size* ptr2Arr,
                               Size* blsmArr,
                               Size* rprsArr,
                               Stt* sttArr,
                               ItmQue& prcsbQue,
                               ItmQue& prcsdQue,
                               Size sFirst,
                               Size* sLast,
                               Size* tLast) const;

  ///
  /// implicitly breadth-first.
  /// with disjoint set support.
  ///
  /// used in:
  /// - maximum cardinality computations.
  template<class ItmQue>
  void rFindAugPathCardSglSrc2(const Graph& graph,
                               Size* mateArr,
                               Size* ptr1Arr,
                               Size* ptr2Arr,
                               Size* blsmArr,
                               Size* rprsArr,
                               Size* linkArr,
                               Size* rankArr,
                               Stt* sttArr,
                               ItmQue& prcsbQue,
                               ItmQue& prcsdQue,
                               Size sFirst,
                               Size* sLast,
                               Size* tLast) const;

  ///
  ///used by MVM  
	template<class ItmQue>
	void rFindAugPathCardSglSrc3(const Graph& graph, 
								Size* mateArr,
    							Size* ptr1Arr, 
								Size* ptr2Arr, 
								Size* blsmArr, 
								Size* rprsArr, 
								Size* linkArr,
    							Size* rankArr, 
								Stt* sttArr, 
								ItmQue& prcsbQue, 
								ItmQue& prcsdQue,
    							Size sFirst, 
								Size* sLast, 
								Size* tLast,
								Val w2)const;
    ///
	///
	///used in restricted augmenting paths MVM  
  	template<class ItmQue>
	void rFindAugPathCardSglSrc1Bnd(const Graph& graph, 
									Size* mateArr,
    								Size* ptr1Arr, 
									Size* ptr2Arr, 
									Size* rprsArr, 
									Stt* sttArr, 
									Size* sLenArr,
    								ItmQue& prcsbQue, 
									ItmQue& prcsdQue, 
									Size sFirst, 
									Size* sLast, 
									Size* tLast,
									Size augPathLenBnd)const;
  ///
  /// the core of the single source maximum cardinality matching computation.
  /// without disjoint set support.
  template<class ItmQue>
  void rComputeMaxCardMatchingSglSrc1(const Graph& graph,
                                      Size* mateArr,
                                      Size* card) const;

  ///
  /// the core of the single source maximum cardinality matching computation.
  /// with disjoint set support.
  template<class ItmQue>
  void rComputeMaxCardMatchingSglSrc2(const Graph& graph,
                                      Size* mateArr,
                                      Size* card) const;
    ///  
	/// 
	/// the core of the single source maximum cardinality matching computation.                              
	template<class ItmQue>
  	void rComputeMaxCardMatchingSglSrc3(const Graph& graph,
                                      Size* mateArr,
                                      Size* card,
									  std::pair<Size,Val>* sortedArr) const;
  ///
  /// the core of the single source approximate maximum weighted matching computation.
  template<class Que>
  void rComputeAprxMaxEdgWghtMatching4(const Graph& graph,
                                       Size* mateArr,
                                       Size* card,
                                       Val* edgWght) const;
  ///
  ///Find increasing paths it used in Specluative MVM                                     
  template<class ItmQue> void rFindIncPathCardSglSrc3(const Graph& graph, 
  													Size* mateArr,
    												Size* ptr1Arr, 
													Size* ptr2Arr, 
													Size* blsmArr, 
													Size* rprsArr, 
													Size* linkArr,
    												Size* rankArr, 
													Stt* sttArr, 
													ItmQue& prcsbQue, 
													ItmQue& prcsdQue,
    												Size sFirst, 
													Size* sLast, 
													Size* tLast) const;
	////
	/// the core of the single source maximum vertex weighted matching computation.
  template<class ItmQue, class ItmStk>
  void rComputeMaxVtxWght(const Graph& graph,
    					  Size* mateArr, 
						  Size* card, 
						  Val* vtxWght, 
						  Size augPathLenBnd) const;
    ///
    /// the core of the single source greedy 1/2-approx. vertex weighted matching computation.
	template<class ItmQue>
  	void rComputeHalfVtxWghtMatching(const Graph& graph,
    					  			Size* mateArr, 
						  			Size* card, 
						  			Val* vtxWght) const;
    ///
    /// the core of the single source greedy 2/3-approx. vertex weighted matching computation.
   	template<class ItmQue>
  	void rComputeTwoThirdVtxWghtMatching(const Graph& graph,
    					  				Size* mateArr, 
						  				Size* card, 
						  				Val* vtxWght) const;
    ///
    /// the core of the single source Suitor 1/2-approx. vertex weighted matching computation.
    template<class ItmQue>
    void rSuitorVtxWght(const Graph& graph,
    					   Size* mateArr, 
						   Size* card, 
						   Val* vtxWght) const;
  ///
 	template<class ItmQue>
 	/// the core of the single source locally dominant 1/2-approx. vertex weighted matching computation.
	void rLocallyDominantVtxWght(const Graph& graph,
    								Size* mateArr, 
									Size* card, 
									Val* vtxWght) const;
  	///
  	/// the core of the shared memory parallel Suitor 1/2-approx. vertex weighted matching computation.
  	template<class ItmQue>
	void rParSuitorVtxWght(const Graph& graph,
    						Size* mateArr, 
							Size* card, 
							Val* vtxWght) const;
  	///
  	/// the core of the single source path growing 1/2-approx. vertex weighted matching computation.
  	template<class ItmQue>
   	void rPGPVtxWght(const Graph& graph,
    					Size* mateArr, 
						Size* card, 
						Val* vtxWght) const;
    ////
    /// the core of the single source path growing and DP 1/2-approx. vertex weighted matching computation.
	template<class ItmQue>
	void rPGDPVtxWght(const Graph& graph,
    					Size* mateArr, 
						Size* card, 
						Val* vtxWght) const;
	///
	///Scaling approx. algorithm functions
	/// the core of multiple source Scaling 1-eps -approx. vertex weighted matching computation.
	template<class ItmQue, class ItmStk, class ItmIdxdQue>
	void rScaleOneMinusEpsVtxWght(const Graph& graph, 
								Size* mateArr, 
								Size* card, 
								Val* vtxWght, 
								Val ep) const;
    ///
    // augment augemnting path 
    // used in Scaling approximation algorithm
    template<class ItmIdxdQue,class ItmQue>
  	void rAugment(Size* mateArr, 
	  			Size* ptrArr, 
				ItmIdxdQue& expsdQue, 
				Size sLast,
                Size tLast,
				Size* blsmArr, 
				Size* rprsArr, 
				Size* blsmParent, 
				std::vector<Size>* blsmChildren,
				std::vector<Size>* blsmL,
				Size num, 
				Size* label,
				Size* blsmin) const;
	///
	// augment through blossoms
    // used in Scaling approximation algorithm
	template<class ItmQue>
	void augmentBlsm(Size b,
					Size s,
					Size* mateArr,
					Size* blsmArr, 
					Size* rprsArr, 
					Size* blsmParent, 
					std::vector<Size>* blsmChildren,
					std::vector<Size>* blsmL,
					Size num) const;
	///
	// find which blossom a vertex belong to
    // used in Scaling approximation algorithm
	template<class ItmQue>	
	Size rFindblsm(Size* p,
					Size* blsm, 
					Size* rprs, 
					Size v) const;
	///
	// dissolve a blossom
    // used in Scaling approximation algorithm
	template<class ItmQue>
	void rDissolveBlsm3(const Graph& graph, 
						Size* blsmArr,
						Size* blsmParentArr, 
						std::vector<Size>* blsmChildren, 
						Size b) const;
	///
	// create and process a blossom
    // used in Scaling approximation algorithm
	template<class ItmQue,class ItmStk>
	void rProcessBlsm3(const Graph& graph, 
						Size* mateArr,
    					Size* ptr1Arr, 
						Size* blsmArr, 
						Size* rprsArr, 
						Size* blsmParent, 
						std::vector<Size>* blsmChildren,
						std::vector<Size>* blsmL,
						Size* label,
    					Stt* sttArr, 
						ItmStk& prcsbStk, 
						Size s1, 
						Size s2, 
						Size* blsm, 
						Val* dualArr,
						Size* blsmin, 
						Size* treeNumArr) const;
    ///
    // find a maximal vertex disjoint augmenting paths 
    // used in Scaling approximation algorithm
	template<class ItmQue, class ItmStk, class ItmIdxdQue>
	void rFindMxmlSetAugPathsCard(const Graph& graph,
    							Size* mateArr, 
								Size* ptrArr, 
								Stt* sttArr,
    							Size* idxArr, 
								ItmStk& prcsbStk, 
								ItmQue& prcsdQue, 
								ItmIdxdQue& expsdQue,
    							ItmQue& sLastQue, 
								ItmQue& tLastQue, 
								Size* blsmArr,
								Size* rprsArr, 
								Size* blsmParent,
								std::vector<Size>* blsmChildren,
								std::vector<Size>* blsmL,
								Size* label, 
								Val* dualArr, 
								Size* blsm, 
								Val delta, 
								Size* blsmin, 
								Size* treeNumArr, 
								Size iter, 
								Val ep) const;
	///
	/// the core of the single source greedy 1/2-approx. edge weighted matching computation.
	template<class ItmQue>
	void rComputeHalfEdgWghtMatching(const Graph& graph, 
									Size* mateArr, 
									Size* card, 
									Val* edgWght) const;
	/// 
	Size logbase2(Val x) const;
	///////////
}; // class MatchingEngine
  ///

	

template<class ItmQue>
void MatchingEngine::rComputeHalfEdgWghtMatching(
    const Graph& graph, Size* mateArr,Size* card, Val* edgWght) const {
  	
	Size numVtxs =graph.mNumVtxs;
	Size numEdgs =graph.mNumEdgs;
	const std::vector<Size>* vtxVecArr = (numVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
    const std::vector<Val>* edgWghtVecArr = (numVtxs == 0) ? NULL : &graph.mEdgWghtVecVec[0];
  	std::vector<std::pair<std::pair<Size,Size>, Val> > sExpsdLst2;
  	ResizeVector<std::pair<std::pair<Size,Size>, Val> >(&sExpsdLst2, numEdgs);
  	std::pair<std::pair<Size,Size>,Val> * sExpsdLst2Arr=  (numEdgs == 0) ? NULL : &sExpsdLst2[0];
	if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[numVtxs], cNullItm);
    }
	
  	*card = 0; 
    *edgWght=0.0;
	
  	Size edgeCounter =0;
  	// list of edges and their weights
  	for (Size sFirst = 0; sFirst < numVtxs; ++sFirst) {
  	   	Size numEdgs = vtxVecArr[sFirst].size();  	   
    	const Size* vtxArr = (numEdgs == 0) ? NULL : &vtxVecArr[sFirst][0];
    	const Val* edgWghtArr = (numEdgs == 0) ? NULL : &edgWghtVecArr[sFirst][0];
   	 	for (Size i = 0; i < numEdgs; ++i) {
      		Size t = vtxArr[i];
	  		Val wgt = edgWghtArr[i];
	  		if(sFirst>t)
	  		 continue;
	  		std::pair<Size,Size> p (sFirst,t);
      		sExpsdLst2Arr[edgeCounter]=std::pair<std::pair<Size,Size>, Val>(p, wgt);
      		edgeCounter++;
		}
     
  	}
  	// sort the edges
	std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreaterPairs<std::pair<std::pair<Size,Size>, Val> >());

	std::pair<Size,Size> sedge;

    for (Size current = 0; current < numEdgs; ++current) {
    	sedge =  sExpsdLst2Arr[current].first;
    	Size s = sedge.first;
    	Size t = sedge.second;
    	if(mateArr[s]!=cNullItm || mateArr[t]!=cNullItm)
    	 continue;
    	else
    	{
    		// match an edge and udate the cardinality the weight
    		mateArr[t]=s;
			mateArr[s]=t;
			++(*card);
			*edgWght += sExpsdLst2Arr[current].second;			
		}
	}
}



template<class ItmQue>
void MatchingEngine::rProcessBlsm1(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr,
    Stt* sttArr, ItmQue& prcsbQue, Size s1, Size s2, Size blsm) const {
  // find vertex rprs, the representative of the blossom. search alternatively
  // along both paths toward the base of the blossom, instead of searching
  // along one path first and then along the other one, in order for the number
  // of steps in the search to be proportional to the number of vertices in the
  // blossom rather than being bounded by the number of vertices in the graph.
  // for a graph G = (V,E) the former approach would determine a complexity of
  // O(|V|) per augmenting path search, as opposed to the O(|V|^2) complexity
  // determined by the latter. the number of blossoms discovered during an
  // augmenting path search is O(|V|). the number of vertices "shrunk" into
  // blossoms during an augmenting path search is also O(|V|).
  Size rprs(cNullItm);
  Size tmpRprsArr[2];
  tmpRprsArr[0] = rprsArr[s1];
  tmpRprsArr[1] = rprsArr[s2];
  blsmArr[tmpRprsArr[0]] = blsm;
  blsmArr[tmpRprsArr[1]] = blsm;
  bool done = false;
  do {
    for (Size k = 0; k < 2; ++k) {
      Size r = tmpRprsArr[k];
      Size s = ptr1Arr[r];
      if (s != cNullItm) {
        r = rprsArr[s];
        if (blsmArr[r] == blsm) {
          rprs = r;
          done = true;
          break;
        }
        blsmArr[r] = blsm;
        tmpRprsArr[k] = r;
      }
    }
  } while (done == false);
  // make every T-vertex in the blossom an S-vertex and make vertex rprs the
  // representative of such a T-vertex that becomes an S-vertex. this time
  // separately along both paths toward the base of the blossom since it is
  // easy now to prevent the procedure from continuing beyond the base. for a
  // graph G = (V,E), for the reasons stated above, the complexity of this task
  // is O(|V|) per augmenting path search.
  tmpRprsArr[0] = rprsArr[s1];
  tmpRprsArr[1] = rprsArr[s2];
  for (Size k = 0; k < 2; ++k) {
    Size r = tmpRprsArr[k];
    while (r != rprs) {
      Size t = mateArr[r];
      ptr1Arr[t] = s1;
      ptr2Arr[t] = s2;
      rprsArr[t] = rprs;
      prcsbQue.Push(t);
      sttArr[t] = eSttBfsPrcsb;
      Size s = ptr1Arr[r];
      r = rprsArr[s];
    }
  }
  // update the representative of every S-vertex (original S-vertex or T-vertex
  // that later became S-vertex) whose representative is supposed to become
  // rprs, the representative of the new blossom. this is the most
  // expensive part of the blossom processing task because it visits every
  // vertex in the graph. since, for a graph G = (V,E), the number of blossoms
  // discovered during an augmenting path search is O(|V|), this determines a
  // complexity of O(|V|^2) per augmenting path search.
  for (Size s = 0; s < graph.mNumVtxs; ++s) {
    Size r = rprsArr[s];
    // check if rprs is already the representative of s or if r was involved
    // in the task of determining rprs.
    if ((r == rprs) || (blsmArr[r] != blsm)) {
      continue;
    }
    Size t = mateArr[r];
    // check if r is actually inside the new blossom. it could have been
    // involved in the task of determining rprs, but it could still be
    // outside the blossom (beyond the blossom's base).
    if ((t == cNullItm) || (rprsArr[t] != rprs)) {
      continue;
    }
    rprsArr[s] = rprs;
  }
}

template<class ItmQue>
void MatchingEngine::rProcessBlsm2(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr, Size* linkArr,
    Size* rankArr, Stt* sttArr, ItmQue& prcsbQue, Size s1, Size s2, Size blsm)
    const {
  // find vertex rprs, the representative of the blossom. search alternatively
  // along both paths toward the base of the blossom, instead of searching
  // along one path first and then along the other one, in order for the number
  // of steps in the search to be proportional to the number of vertices in the
  // blossom rather than being bounded by the number of vertices in the graph.
  // for a graph G = (V,E) the former approach would determine a complexity of
  // O(|V|) per augmenting path search, as opposed to the O(|V|^2) complexity
  // determined by the latter. the number of blossoms discovered during an
  // augmenting path search is O(|V|). the number of vertices "shrunk" into
  // blossoms during an augmenting path search is also O(|V|).
  Size rprs(cNullItm);
  Size tmpRprsArr[2];
  tmpRprsArr[0] = rprsArr[rFind(linkArr, s1)];
  tmpRprsArr[1] = rprsArr[rFind(linkArr, s2)];
  blsmArr[tmpRprsArr[0]] = blsm;
  blsmArr[tmpRprsArr[1]] = blsm;
  bool done = false;
  do {
    for (Size k = 0; k < 2; ++k) {
      Size r = tmpRprsArr[k];
      Size s = ptr1Arr[r];
      if (s != cNullItm) {
        r = rprsArr[rFind(linkArr, s)];
        if (blsmArr[r] == blsm) {
          rprs = r;
          done = true;
          break;
        }
        blsmArr[r] = blsm;
        tmpRprsArr[k] = r;
      }
    }
  } while (done == false);
  // make every T-vertex in the blossom an S-vertex and make vertex rprs the
  // representative of such a T-vertex that becomes an S-vertex. this time
  // separately along both paths toward the base of the blossom since it is
  // easy now to prevent the procedure from continuing beyond the base. for a
  // graph G = (V,E), for the reasons stated above, the complexity of this task
  // is O(|V|) per augmenting path search.
  tmpRprsArr[0] = rprsArr[rFind(linkArr, s1)];
  tmpRprsArr[1] = rprsArr[rFind(linkArr, s2)];
  for (Size k = 0; k < 2; ++k) {
    Size r = tmpRprsArr[k];
    while (r != rprs) {
      rUnion(linkArr, rankArr, r, rprs);
      Size t = mateArr[r];
      ptr1Arr[t] = s1;
      ptr2Arr[t] = s2;
      rUnion(linkArr, rankArr, t, rprs);
      	prcsbQue.Push(t);
      	sttArr[t] = eSttBfsPrcsb;
      rprsArr[rFind(linkArr, rprs)] = rprs;
      Size s = ptr1Arr[r];
      r = rprsArr[rFind(linkArr, s)];
    }
  }
}

template<class ItmQue>
void MatchingEngine::rProcessBlsm6(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr, Size* linkArr,
    Size* rankArr, Stt* sttArr, ItmQue& prcsbQue, Size s1, Size s2, Size blsm, Val* minVtxWght, Size* sLast, Size* tLast)
    const {
  // find vertex rprs, the representative of the blossom. search alternatively
  // along both paths toward the base of the blossom, instead of searching
  // along one path first and then along the other one, in order for the number
  // of steps in the search to be proportional to the number of vertices in the
  // blossom rather than being bounded by the number of vertices in the graph.
  // for a graph G = (V,E) the former approach would determine a complexity of
  // O(|V|) per augmenting path search, as opposed to the O(|V|^2) complexity
  // determined by the latter. the number of blossoms discovered during an
  // augmenting path search is O(|V|). the number of vertices "shrunk" into
  // blossoms during an augmenting path search is also O(|V|).
  // Also return the lightest vertex in the blossom which is used by the speculative MVM
  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  Size rprs(cNullItm);
  Size tmpRprsArr[2];
  tmpRprsArr[0] = rprsArr[rFind(linkArr, s1)];
  tmpRprsArr[1] = rprsArr[rFind(linkArr, s2)];
  blsmArr[tmpRprsArr[0]] = blsm;
  blsmArr[tmpRprsArr[1]] = blsm;
  bool done = false;
  do {
    for (Size k = 0; k < 2; ++k) {
      Size r = tmpRprsArr[k];
      Size s = ptr1Arr[r];
      if (s != cNullItm) {
        r = rprsArr[rFind(linkArr, s)];
        if (blsmArr[r] == blsm) {
          rprs = r;
          done = true;
          break;
        }
        blsmArr[r] = blsm;
        tmpRprsArr[k] = r;
      }
    }
  } while (done == false);
  // make every T-vertex in the blossom an S-vertex and make vertex rprs the
  // representative of such a T-vertex that becomes an S-vertex. this time
  // separately along both paths toward the base of the blossom since it is
  // easy now to prevent the procedure from continuing beyond the base. for a
  // graph G = (V,E), for the reasons stated above, the complexity of this task
  // is O(|V|) per augmenting path search.
  tmpRprsArr[0] = rprsArr[rFind(linkArr, s1)];
  tmpRprsArr[1] = rprsArr[rFind(linkArr, s2)];
  for (Size k = 0; k < 2; ++k) {
    Size r = tmpRprsArr[k];
    while (r != rprs) {
      rUnion(linkArr, rankArr, r, rprs);
      Size t = mateArr[r];
      ptr1Arr[t] = s1;
      ptr2Arr[t] = s2;
      rUnion(linkArr, rankArr, t, rprs);
      	prcsbQue.Push(t);
      	sttArr[t] = eSttBfsPrcsb;
      	if (*minVtxWght > vtxWghtArr[t]) {
          *sLast = r;
          *tLast = r;
          *minVtxWght = vtxWghtArr[t];
        }
      
      rprsArr[rFind(linkArr, rprs)] = rprs;
      Size s = ptr1Arr[r];
      r = rprsArr[rFind(linkArr, s)];
    }
  }
}

template<class ItmQue>
void MatchingEngine::rFindAugPathCardSglSrc1(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr, Stt* sttArr,
    ItmQue& prcsbQue, ItmQue& prcsdQue, Size sFirst, Size* sLast, Size* tLast)
    const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  Size blsm = 0;
  prcsbQue.Push(sFirst);
  sttArr[sFirst] = eSttBfsPrcsb;
  while (prcsbQue.Empty() == false) {
    Size s = prcsbQue.Front();
    prcsbQue.Pop();
    prcsdQue.Push(s);
    sttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      assert(s != t);
      // if t is an outer vertex and s and t are in different blossoms then creat a blossom
      if (sttArr[t] == eSttBfsPrcsb) {
        if (rprsArr[s] != rprsArr[t]) {
          rProcessBlsm1(graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr,
                        sttArr, prcsbQue, s, t, blsm);
        }
        ++blsm;
        continue;
      } else if (sttArr[t] == eSttBfsPrcsd) {
        continue;
      }
      Size ss = mateArr[t];
      if ((ss != cNullItm) && (sttArr[ss] != eSttIdle)) {
        continue;
      }
      if (ss == cNullItm) {
      	// an unmatched vertex is found
        *sLast = s;
        *tLast = t;
        return;
      }
      if (sttArr[ss] != eSttIdle) {
        continue;
      }
      ptr1Arr[ss] = s;
      prcsbQue.Push(ss);
      sttArr[ss] = eSttBfsPrcsb;
    }
  }
}

template<class ItmQue>
void MatchingEngine::rFindAugPathCardSglSrc2(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr, Size* linkArr,
    Size* rankArr, Stt* sttArr, ItmQue& prcsbQue, ItmQue& prcsdQue,
    Size sFirst, Size* sLast, Size* tLast) const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  Size blsm = graph.mNumVtxs;
  prcsbQue.Push(sFirst);
  sttArr[sFirst] = eSttBfsPrcsb;
  while (prcsbQue.Empty() == false) {
    Size s = prcsbQue.Front();
    prcsbQue.Pop();
    prcsdQue.Push(s);
    sttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      assert(s != t);
      // if t is an outer vertex and s and t are in different blossoms then creat a blossom
      if (sttArr[t] != eSttIdle) {
      	Size b1 =rprsArr[rFind(linkArr, s)] ;
      	Size b2 = rprsArr[rFind(linkArr, t)];
        if (b1!= b2) {
          rProcessBlsm2(graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr,
                        linkArr, rankArr, sttArr, prcsbQue, s, t, blsm);
        }
        ++blsm;
        continue;
      } else if (sttArr[t] == eSttBfsPrcsd) {
        continue;
      }
      Size ss = mateArr[t];
      
      if ((ss != cNullItm) && (sttArr[ss] != eSttIdle)) {
        continue;
      }
      if (ss == cNullItm) {
      	// an unmatched vertex is found
        *sLast = s;
        *tLast = t;
       
        return;
      }
      if (sttArr[ss] != eSttIdle) {
        continue;
      }
      ptr1Arr[ss] = s;
      prcsbQue.Push(ss);
      sttArr[ss] = eSttBfsPrcsb;
    }
  }
}
//////////////////////////////////////////////

template<class ItmQue>
void MatchingEngine::rFindAugPathCardSglSrc3(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr, Size* linkArr,
    Size* rankArr, Stt* sttArr, ItmQue& prcsbQue, ItmQue& prcsdQue,
    Size sFirst, Size* sLast, Size* tLast, Val w2)
    const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  const std::vector<Size>* vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  Size blsm = graph.mNumVtxs;
  Val maxVtxWght = cNegInfVal;
  prcsbQue.Push(sFirst);
  sttArr[sFirst] = eSttBfsPrcsb;

  while (prcsbQue.Empty() == false) {
    Size s = prcsbQue.Front();
    prcsbQue.Pop();
    prcsdQue.Push(s);
    sttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      assert(s != t);
      // if t is an outer vertex and s and t are in different blossoms then creat a blossom
      if (sttArr[t] == eSttBfsPrcsd || sttArr[t] == eSttBfsPrcsb) {
        if (rprsArr[rFind(linkArr, s)] != rprsArr[rFind(linkArr, t)]) {
          rProcessBlsm2(graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr,
                        linkArr, rankArr, sttArr, prcsbQue, s, t, blsm);                     
                        ++blsm;               
        }

        continue;
      } else if (sttArr[t] == eSttLast) {
        continue;
      }
      Size ss = mateArr[t];
      if ((ss != cNullItm) && (sttArr[ss] != eSttIdle)) {
        continue;
      }
      if (ss == cNullItm) {
      if (maxVtxWght < vtxWghtArr[t]) {
      	  // a heavier unmatched vertex is found
          *sLast = s;
          *tLast = t;
          maxVtxWght = vtxWghtArr[t];
          if(fabs(w2 - maxVtxWght) <= 0.00001)
           return;
        }
        continue;
      }
      if (sttArr[ss] != eSttIdle) {
        continue;
      }
      
      ptr1Arr[ss] = s;
      prcsbQue.Push(ss);
      sttArr[ss] = eSttBfsPrcsb;
    }
  }
}
      
template<class ItmQue>
void MatchingEngine::rFindIncPathCardSglSrc3(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* ptr2Arr, Size* blsmArr, Size* rprsArr, Size* linkArr,
    Size* rankArr, Stt* sttArr, ItmQue& prcsbQue, ItmQue& prcsdQue,
    Size sFirst, Size* sLast, Size* tLast)
    const {
  *sLast = cNullItm;
  *tLast = cNullItm;
  const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  Size blsm = graph.mNumVtxs;
  Val minVtxWght= vtxWghtArr[sFirst];
  prcsbQue.Push(sFirst);
  sttArr[sFirst] = eSttBfsPrcsb;

  while (prcsbQue.Empty() == false) {
    Size s = prcsbQue.Front();
    prcsbQue.Pop();
    prcsdQue.Push(s);
    sttArr[s] = eSttBfsPrcsd;
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
	
	
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      assert(s != t);
      // if t is an outer vertex and s and t are in different blossoms then creat a blossom
      if (sttArr[t] == eSttBfsPrcsd || sttArr[t] == eSttBfsPrcsb) {
        if (rprsArr[rFind(linkArr, s)] != rprsArr[rFind(linkArr, t)]) {
          rProcessBlsm6<ItmQue>(graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr,
                        linkArr, rankArr, sttArr, prcsbQue, s, t, blsm, &minVtxWght,sLast,tLast);
                        ++blsm;
        }
        
        continue;
      } else if (sttArr[t] == eSttBfsPrcsd) {
        continue;
      }
      Size ss = mateArr[t];
      if ((ss != cNullItm) && (sttArr[ss] != eSttIdle)) {
        continue;
      }
      if (minVtxWght > vtxWghtArr[ss]) {
      	// a lighter matched vertex is found
          *sLast = s;
          *tLast = t;
          minVtxWght = vtxWghtArr[ss];
          ptr1Arr[ss] = s;
          prcsbQue.Push(ss);
          sttArr[ss] = eSttBfsPrcsb;
          continue;
        }
        
      if (sttArr[ss] != eSttIdle) {
        continue;
      }
      ptr1Arr[ss] = s;
      prcsbQue.Push(ss);
      sttArr[ss] = eSttBfsPrcsb;
    }
  }
}

/////////////// Scaling approximation Algorithm functions////
template<class ItmQue>
Size MatchingEngine::rFindblsm(Size* p ,Size* blsm, Size* rprs, Size v) const 
{
   Size vblsm=blsm[v];
	if(rprs[vblsm] != cNullItm)
	{
		if(p[vblsm] == cNullItm)
		{
			return vblsm;
		}			
		else
		{
			// if the blossom tree was updated then find the root blossom by climbing the blossom tree
			while(p[vblsm] != cNullItm)
			{
			    vblsm = p[vblsm];    
			}
			blsm[v]=vblsm;
			return vblsm;
		}
	}
	else
	{
		// if the blossom has been dissolved then move up the tree until the root is found
		Size newBlsm = v;
		while(p[newBlsm] != cNullItm)
		{
			newBlsm = p[newBlsm];
		}
		blsm[v]=newBlsm;
		return newBlsm;
	}
}

template<class ItmQue>
void MatchingEngine::augmentBlsm(Size b,Size s,Size* mateArr,Size* blsmArr, Size* rprsArr, 
Size* blsmParent, std::vector<Size>* blsmChildren,std::vector<Size>* blsmL,Size num) const{
	
	std::stack<Size> tempS;
	tempS.push(b);
	tempS.push(s);
	
	while(tempS.empty()==false)
	{
		s= tempS.top();
		tempS.pop();
		b = tempS.top();
		tempS.pop();
		Size t = s;
		//find the root blossom
		while(blsmParent[t]!=b)
		{
			t = blsmParent[t];
		}
		
		if(t >= num)
		{
			tempS.push(t);
			tempS.push(s);
		}
		Size shiftB =b-num;
		// find the index of t in the order list of blossom children
		Size idx = std::find(blsmChildren[shiftB].begin(), blsmChildren[shiftB].end(), t) - blsmChildren[shiftB].begin();
		Size idx2 =idx*2;

		int inc=1;
		if(idx%2==0)
		 inc=-1;
		while(idx != 0)
		{
			idx+=inc;
			idx2+=2*inc;
			t = blsmChildren[shiftB][idx];
			Size a1 =t;
			if(t >= num)
			{
				if(idx%2==0)
					a1 = blsmL[shiftB][idx2];
				else
					a1 = blsmL[shiftB][idx2-1];
				tempS.push(t);
				tempS.push(a1);
			}	
			idx+=inc;
			idx2+=2*inc;
			if(idx >= blsmChildren[shiftB].size())
			{
				idx = 0;
				idx2--;
			}
			t = blsmChildren[shiftB][idx];
			Size a2 =t;
			if(t >= num)
			{
				if(idx%2==0)
				 a2 = blsmL[shiftB][idx2];	
				else
				 a2 = blsmL[shiftB][idx2-1];
				tempS.push(t);
				tempS.push(a2);
			}
			mateArr[a1] = a2;
    		mateArr[a2] = a1;
		}
		//change the order of the blossom children so it begins from the base and update the base
		std::rotate(blsmChildren[shiftB].begin(),blsmChildren[shiftB].begin()+idx2,blsmChildren[shiftB].end());
		std::rotate(blsmL[shiftB].begin(),blsmL[shiftB].begin()+(idx2*2),blsmL[shiftB].end());
		rprsArr[b] = s;
	}
}


template<class ItmIdxdQue,class ItmQue>
void MatchingEngine::rAugment(Size* mateArr,Size* ptrArr,
    ItmIdxdQue& expsdQue, Size sLast, Size tLast, Size* blsmArr, 
	Size* rprsArr, Size* blsmParent, std::vector<Size>* blsmChildren,std::vector<Size>* blsmL,Size num, Size* label, Size* blsmin) const {
  
  Size s = sLast;
  Size t = tLast;
  expsdQue.Erase(t);
  while (s != cNullItm) {
    Size blsmt=t;
    if(blsmParent[t]!=cNullItm)
   		blsmt = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, t);
    label[blsmt]=0;
   	if(blsmt >= num && blsmin[blsmt-num]!= cNullItm)
    {	
     	Size tempT =blsmin[blsmt-num];
     	//augment the blossom
		augmentBlsm<ItmQue>(blsmArr[t],tempT,mateArr,blsmArr, rprsArr, blsmParent, blsmChildren,blsmL,num);
		t= tempT;
    }
    
    Size blsms=s;
    if(blsmParent[s]!=cNullItm)
	 blsms =rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, s);
    if(blsms >= num && rprsArr[blsms]!=s)
    {	
		//if s is in a blossom 
    	label[blsms]=0;
		Size base = rprsArr[blsms];
		Size mateBase = mateArr[base];
		//augment the blossom
    	augmentBlsm<ItmQue>(blsms,s,mateArr,blsmArr, rprsArr, blsmParent, blsmChildren,blsmL,num);
    	
    	label[s]=0;
		label[t]=0;
		mateArr[s] = t;
    	mateArr[t] = s;
    	s=base;
    	if(ptrArr[s] == cNullItm || mateBase ==cNullItm )
    	{
    		expsdQue.Erase(s);
		}
    	s = ptrArr[s];
    	t=mateBase;	
	}
	else
	{
		//if s is not in blossom
		Size tt = mateArr[s];
		label[s]=0;
		label[t]=0;
		mateArr[s] = t;
    	mateArr[t] = s;
    	if(ptrArr[s] == cNullItm)
    	{
    		expsdQue.Erase(s);
		}
    	s = ptrArr[s];
    	t=tt;
	}
  }
}

template<class ItmQue>
void MatchingEngine::rDissolveBlsm3(const Graph& graph, Size* blsmArr,Size* blsmParent , std::vector<Size>* blsmChildren, Size b) const {

    for(Size i=0; i < blsmChildren[b-graph.mNumVtxs].size();i++)
    {
        Size child = blsmChildren[b-graph.mNumVtxs][i];
        blsmParent[child] = cNullItm;
        if( child < graph.mNumVtxs)
		{
			blsmArr[child]= child;	
		}
	}
}

template <class ItmQue,class ItmStk>
void MatchingEngine::rProcessBlsm3(const Graph& graph, Size* mateArr,
    Size* ptr1Arr, Size* blsmArr, Size* rprsArr, Size* blsmParent, std::vector<Size>* blsmChildren,std::vector<Size>* blsmL, Size* label,
    Stt* sttArr, ItmStk& prcsbStk, Size s1, Size s2, Size* blsm, Val* dualArr, Size* blsmin, Size* treeNumArr) const {
  
  	std::queue<Size> tempQ; 
  	Size numVtxs = graph.mNumVtxs;
  	Size bs1=s1;
  	Size bs2=s2;
  	if(blsmParent[s1]!=cNullItm)	
  	 bs1 = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, s1);
	if(blsmParent[s2]!=cNullItm)
	 bs2 = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, s2);
    Size base =rprsArr[bs2];      
    // Create blossom.
    Size b = *blsm;
    Size shiftB =b-numVtxs;
    rprsArr[b] = base;
    treeNumArr[b]=treeNumArr[bs2];
    blsmParent[b] = cNullItm;
    blsmParent[bs2] = b;
    blsmChildren[shiftB].push_back(bs2);
    blsmL[shiftB].push_back(s2);
    blsmL[shiftB].push_back(s1);
    // iterate over the vertices in backward order until the base is reached
    while (bs1 != b)
    {	
		Size tempS1 = s1;
    	blsmParent[bs1] = b;
    	blsmChildren[shiftB].push_back(bs1);
		Size mates1;
		if(bs1 < numVtxs)
		{
			blsmL[shiftB].push_back(bs1);
			mates1 = mateArr[bs1];
		}		
		else
		{
			Size rprsbs1 = rprsArr[bs1];
			if(tempS1 != rprsbs1)
			{
				ptr1Arr[tempS1]= ptr1Arr[base];
				s1= rprsbs1;
				tempS1 = rprsbs1;
			}
			
			blsmL[shiftB].push_back(rprsbs1);
			mates1 = mateArr[rprsbs1];
		}
		blsmL[shiftB].push_back(mates1);
		bs1= mates1;
		if(blsmParent[mates1]!=cNullItm)
		 bs1 = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, mates1);
		blsmParent[bs1] = b;
    	blsmChildren[shiftB].push_back(bs1);
    	
		if(bs1 < numVtxs)
		{
			blsmL[shiftB].push_back(mates1);
			if(sttArr[bs1] == eSttIdle || (label[bs1]== 2 || label[bs1]== 0)) 
			{
				prcsbStk.Push(bs1);
      			sttArr[bs1] = eSttDfsPrcsb;
      			ptr1Arr[bs1]= ptr1Arr[base];
			}	
		}		
		else
		{	
			if(blsmin[bs1-numVtxs]==cNullItm || blsmin[bs1-numVtxs]==rprsArr[bs1])
			{
				blsmL[shiftB].push_back(mates1);
				ptr1Arr[mates1]= ptr1Arr[base];
			}	
			else
			{
				ptr1Arr[blsmin[bs1-numVtxs]]= ptr1Arr[base];
				blsmL[shiftB].push_back(blsmin[bs1-numVtxs]);	
			}
	
			if(sttArr[rprsArr[bs1]] == eSttIdle)
			{	
				tempQ.push(bs1-numVtxs);					
				while (tempQ.empty() == false) 
				{     	
					Size tempB = tempQ.front();
					tempQ.pop();
					for(Size i=0; i < blsmChildren[tempB].size();i++)
					{
						Size child = blsmChildren[tempB][i];
						if( child < numVtxs)
						{
							if(sttArr[child] == eSttIdle)
							{
								prcsbStk.Push(child);
								sttArr[child] = eSttDfsPrcsb;
								ptr1Arr[child] = ptr1Arr[base];
							}
						}
						else											
						{
							tempQ.push(child-numVtxs);
						} 
					}
				}
			}
			label[bs1] = 1;
		}	
		s1 = ptr1Arr[s1];
		ptr1Arr[tempS1]= ptr1Arr[base];
		blsmL[shiftB].push_back(s1);
		bs1=s1;
		if(blsmParent[s1]!=cNullItm)
		 bs1 = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, s1);
	}
    label[b] = 1;
    dualArr[b] = 0;
	(*blsm)++;
}


template<class ItmQue, class ItmStk, class ItmIdxdQue>
void MatchingEngine::rFindMxmlSetAugPathsCard(const Graph& graph,
    Size* mateArr, Size* ptrArr, Stt* sttArr,
    Size* idxArr, ItmStk& prcsbStk, ItmQue& prcsdQue, ItmIdxdQue& expsdQue,
    ItmQue& sLastQue, ItmQue& tLastQue, Size* blsmArr,Size* rprsArr, Size* blsmParent,
	std::vector<Size>* blsmChildren,std::vector<Size>* blsmL, Size* label, Val* dualArr,
	 Size* blsm, Val delta, Size* blsmin, Size* treeNumArr,Size iter, Val ep) const {

  	Size numVtxs = graph.mNumVtxs; 
   	Val gamma = logbase2(1.0/ep);
  	const std::vector<Size>* vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  	const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];   
  	std::queue<Size> tempQ;
  	Size sFirst = expsdQue.First();
  	while (sFirst != cNullItm) 
  	{
  		if(sttArr[sFirst] != eSttIdle)
  		{
  			sFirst = expsdQue.Next(sFirst);
  			continue;
	  	}
		prcsbStk.Push(sFirst);
    	sttArr[sFirst] = eSttDfsPrcsb;
    	label[sFirst]=1;
        treeNumArr[sFirst]=sFirst;

    	Size blsmf= sFirst;
		if(blsmParent[sFirst]!=cNullItm)
    	 blsmf = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, sFirst);
    	// if sFirst is in a blosso then add all vertices within the blossom to the search stack
		if(blsmf  >= numVtxs)
		{
			label[blsmf]=1;
			treeNumArr[blsmf]=sFirst; 
			tempQ.push(blsmf-numVtxs);					
			while (tempQ.empty() == false) 
			{     	
				Size tempB = tempQ.front();
				tempQ.pop();
				for(Size i=0; i < blsmChildren[tempB].size();i++)
				{
					Size child = blsmChildren[tempB][i];
					if( child < numVtxs)
					{
						if(sttArr[child] == eSttIdle)
						{
							prcsbStk.Push(child);
							sttArr[child] = eSttDfsPrcsb;
						}
					}
					else
					{
						tempQ.push(child-numVtxs);
					} 
				}
			}
		}
    	while (prcsbStk.Empty() == false) 
		{
			
      		Size s = prcsbStk.Top();
      		Size sNumEdgs = vtxVecArr[s].size();
      		const Size* vtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
      		Size cases = 0;
      		while (idxArr[s] < sNumEdgs) 
			{
        		Size t = vtxArr[idxArr[s]];
        		Val wght = vtxWghtArr[s]+vtxWghtArr[t];
        		Size ss;
        		Size base;
        		/////////
        		if(t == mateArr[s])
        		{
        			++(idxArr[s]);
        			continue;
				}
				
				Size blsmt=t;
				Size blsms =s;
				if(blsmParent[t]!=cNullItm)				
				 blsmt = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, t);
				if(blsmParent[s]!=cNullItm)
				 blsms = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, s);
				
				if(label[blsmt]==1 &&  treeNumArr[blsms] == treeNumArr[blsmt])
				{				
			  		if(fabs((dualArr[s]+dualArr[t] )- ((int)(wght/delta)*delta - delta)) < EPS && blsms != blsmt && sttArr[t] == eSttDfsPrcsd && logbase2(wght)>=iter-gamma)
			  		{
			  			//create a blossom
						rProcessBlsm3<ItmQue, ItmStk>(graph, mateArr,ptrArr,blsmArr, rprsArr, blsmParent,blsmChildren,blsmL,label,sttArr, prcsbStk,t, s, blsm, dualArr,blsmin,treeNumArr);
						break;
					}
			  		++(idxArr[s]);
			  		continue;	
				}
				
        		if(blsmt >=numVtxs)
        		{
        			base = rprsArr[blsmt];
					ss = mateArr[base];
					cases=1;
				}
				else
				{
					ss = mateArr[t];
					if(ss !=cNullItm)
					 cases= 2;
					else
					 cases= 3;
				}
        		if (((ss == cNullItm) && (sttArr[t] != eSttIdle)) || label[blsmt]==2 || (treeNumArr[blsmt] !=cNullItm && treeNumArr[blsms] != treeNumArr[blsmt] )) {
	
          				++(idxArr[s]);
        		} 
				else
				{
					// check if the edge (s,t) is an eligible edge
					if(fabs((dualArr[s]+dualArr[t] )- ((int)(wght/delta)*delta - delta)) <= EPS && logbase2(wght)>=iter-gamma) 
					{
					
						if(ss == cNullItm)
						 break;
						Size tempv = t;
						if(cases == 1 )
						{
							tempv = base;
							if(ss == cNullItm)
							{
								break;
							}
						}
						double result = dualArr[ss]+dualArr[tempv] - (floor((vtxWghtArr[ss]+vtxWghtArr[tempv])/delta)*delta );
						bool eligible = false;
						if(result >= 0)
						{    // check if (t,matet) is an eligble edge                                                                   
							if(fabs(result - floorf(result)) <= EPS  &&  fabs(((round(result/delta)*delta)- result)) <= EPS && logbase2(vtxWghtArr[ss]+vtxWghtArr[tempv])>=iter-gamma)
							{
								eligible = true;
							}
						}
						if(eligible)
						{
							break;
						}			
						else
						{
							label[t]=2;
							++(idxArr[s]);
						}	
					}
					else
					 ++(idxArr[s]);	
        		}
    		}
    		if(idxArr[s] < sNumEdgs) 
			{
        		Size t = vtxArr[idxArr[s]];
        		Size blsmt=t;
				Size blsms =s;
				if(blsmParent[t]!=cNullItm)	
        		 blsmt = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, t);
        		if(blsmParent[s]!=cNullItm)
        		 blsms = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, s);
				if(blsms == blsmt)
				{
					++(idxArr[s]);
					continue;
				}
				Size ss = mateArr[t];
				
				if(ss != cNullItm)
				{
					Size blsmss=ss;
					if(blsmParent[ss]!=cNullItm)
					 blsmss = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, ss);
					if(label[blsmt]==0)
					{
						//if t has not been considered					
						if(blsmt >= numVtxs) 
						{
							// if t is on a blossom
							Size base = rprsArr[blsmt];		
							blsmin[blsmt-numVtxs]=t;	
							label[blsmt]=2;
							treeNumArr[blsmt]=treeNumArr[blsms];
							ss = mateArr[base];
							if(ss == cNullItm)
							{
								// if the base of a blossom is unmatched then an augmenting path is found
								if(sttArr[base] == eSttIdle)
								{
									label[blsmt]=1;
									sLastQue.Push(s);
					          		tLastQue.Push(base);
					          		sttArr[base] = eSttLast;
					          		while (prcsbStk.Empty() == false) 
									{
					            		Size sss = prcsbStk.Top();			
					            		prcsbStk.Pop();
					            		prcsdQue.Push(sss);
					            		sttArr[sss] = eSttDfsPrcsd;	
					          		}
					          		break;
								}
								else
								{
									++(idxArr[s]);
						        	continue;
								}
							}
							// other wise move to the base of a blossom
							ptrArr[ss] = s;	
							blsmss=ss;
							if(blsmParent[ss]!=cNullItm)
							 blsmss = rFindblsm<ItmQue>(blsmParent,blsmArr, rprsArr, ss);
							treeNumArr[blsmss]=treeNumArr[blsms];
							if(blsmss >= numVtxs)
							{
								// if mste of t is in a blosso then add all vertices within the blossom to the search stack
								prcsbStk.Push(ss);
								sttArr[ss] = eSttDfsPrcsb;
								label[blsmss]=1;
								tempQ.push(blsmss-numVtxs);
								while (tempQ.empty() == false) 
								{     	
									Size tempB = tempQ.front();
									tempQ.pop();
									for(Size i=0; i < blsmChildren[tempB].size();i++)
									{
									    Size child = blsmChildren[tempB][i];
									    if( child < numVtxs)
										{
									      	if(sttArr[child] == eSttIdle)
									      	{
									      		prcsbStk.Push(child);
									      		sttArr[child] = eSttDfsPrcsb;
									      		ptrArr[child] = s;
											}
										}
										else
										{
											tempQ.push(child-numVtxs);
										} 
									}
								}
							}
							else
							{
								label[ss]=1;
								prcsbStk.Push(ss);
						        sttArr[ss] = eSttDfsPrcsb;
							}
							++(idxArr[s]);	
						}
						else if(blsmss >= numVtxs)							
						{
							// if mate of t is in a blosso then add all vertices within the blossom to the search stack
							label[blsmt]=2;
							treeNumArr[blsmt]=treeNumArr[blsms];
							ptrArr[ss] = s;
							prcsbStk.Push(ss);
							sttArr[ss] = eSttDfsPrcsb;
							label[blsmss]=1;
							treeNumArr[blsmss]=treeNumArr[blsms];
							tempQ.push(blsmss-numVtxs);
							while (tempQ.empty() == false) 
							{     	
								Size tempB = tempQ.front();
								tempQ.pop();
								for(Size i=0; i < blsmChildren[tempB].size();i++)
								{
									Size child = blsmChildren[tempB][i];
									if( child < numVtxs)
									{					
									    if(sttArr[child] == eSttIdle)
									    {
									      	ptrArr[child] = s;
									      	prcsbStk.Push(child);
									    	sttArr[child] = eSttDfsPrcsb;
										}			
									}
									else
									{
										tempQ.push(child-numVtxs);
									} 
								}
							}
							++(idxArr[s]);
						}
						else
						{
							// add the mate of t to the search stack
							label[blsmt]=2;	
							treeNumArr[blsmt]=treeNumArr[blsms];							
							label[ss]=1;
							treeNumArr[ss]=treeNumArr[blsms];
							ptrArr[ss] = s;
						    prcsbStk.Push(ss);
						    sttArr[ss] = eSttDfsPrcsb;
						    ++(idxArr[s]);
						}	
					}
					else
					 ++(idxArr[s]);
				}
				else 
				{
					// an ugmenting path is found
	          		sLastQue.Push(s);
	          		tLastQue.Push(t);
	          		sttArr[t] = eSttLast;
	          		label[blsmt]=1;
	          		if(blsmt>=numVtxs)	          				
	          		 blsmin[blsmt-numVtxs]=cNullItm;
	          		while (prcsbStk.Empty() == false) 
					{
	            		Size sss = prcsbStk.Top();
	            		prcsbStk.Pop();
	            		prcsdQue.Push(sss);
	            		sttArr[sss] = eSttDfsPrcsd;	
	          		}
	          		break;
	        	}		       
      		} 
	  		else 
	  		{
		        prcsbStk.Pop();
		        prcsdQue.Push(s);
		        sttArr[s] = eSttDfsPrcsd;
      		}
    	}
    	sFirst = expsdQue.Next(sFirst);
  	}
}

template<class ItmQue, class ItmStk, class ItmIdxdQue>
void MatchingEngine::rScaleOneMinusEpsVtxWght(const Graph& graph, Size* mateArr, Size* card, Val* vtxWght, Val ep) const {

  Size numVtxs = graph.mNumVtxs; 
  if (mInlz == false) {
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[numVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    rInlzGrdyForCard(graph, mateArr, &iniCard);

    *card = iniCard;
  }
  //to store a pointer from an outer vertex to its parent in the search tree
  std::vector<Size> ptrVec;
  ResizeVector<Size>(&ptrVec,numVtxs);
  Size* ptrArr = (numVtxs == 0) ? NULL : &ptrVec[0];
  if (ptrArr != NULL) {
    std::fill(&ptrArr[0], &ptrArr[numVtxs], cNullItm);
  }
  //to store a blossom id for a vertex
  std::vector<Size> blsmVec;
  ResizeVector<Size>(&blsmVec, numVtxs);
  Size* blsmArr = (numVtxs == 0) ? NULL : &blsmVec[0];
   for (Size v = 0; v < graph.mNumVtxs; ++v) {
    blsmArr[v] = v;
  }
  //to store a base vertex for a vertex or a blossom
  std::vector<Size> rprsVec;
  ResizeVector<Size>(&rprsVec, numVtxs*2);
  Size* rprsArr = (numVtxs == 0) ? NULL : &rprsVec[0];
  for (Size v = 0; v < numVtxs; ++v) {
    rprsArr[v] = v;
  }
  std::fill(&rprsArr[numVtxs], &rprsArr[numVtxs*2], cNullItm);
  for (Size v = numVtxs; v < numVtxs*2; ++v) {
    rprsArr[v] = cNullItm;
  }
  //2
  //to store a label for a vertex (0 for unlabelled vertex 1 for inner vertex 2 for an outer vertex)
  std::vector<Size> labelVec;
  ResizeVector<Size>(&labelVec, numVtxs*2);
  Size* label = (numVtxs == 0) ? NULL : &labelVec[0];
  if (label != NULL) {
    std::fill(&label[0], &label[numVtxs], 0);
  }
  
  //to store a blossom parent in a blossom tree
  std::vector<Size> blsmParentVec;
  ResizeVector<Size>(&blsmParentVec, numVtxs*2);
  Size* blsmParentArr = (numVtxs == 0) ? NULL : &blsmParentVec[0];
  if (blsmParentArr != NULL) {
    std::fill(&blsmParentArr[0], &blsmParentArr[numVtxs*2], cNullItm);
   
  }
	
	//to store a blossom children in a blossom tree
  std::vector<std::vector<Size> > blsmChildrenVec;
  ResizeVector<std::vector<Size> >(&blsmChildrenVec, numVtxs);
  std::vector<Size>* blsmChildrenArr = (numVtxs == 0) ? NULL : &blsmChildrenVec[0];
	
	//to store a blossom edges
  std::vector<std::vector<Size> > blsmLVec;
  ResizeVector<std::vector<Size> >(&blsmLVec, numVtxs);
  std::vector<Size>* blsmL = (numVtxs == 0) ? NULL : &blsmLVec[0];
  
  //to store which vertex an augmenting path is using in a blossom
  std::vector<Size> blsminVec;
  ResizeVector<Size>(&blsminVec, numVtxs);
  Size* blsmin = (numVtxs == 0) ? NULL : &blsminVec[0];
  if (blsmin != NULL) {
    std::fill(&blsmin[0], &blsmin[numVtxs], cNullItm);
  }
  //2
  //to store a tree id for each vertex or a blossom
  std::vector<Size> treeNumVec;
  ResizeVector<Size>(&treeNumVec, numVtxs*2);
  Size* treeNumArr = (numVtxs == 0) ? NULL : &treeNumVec[0];
    if (treeNumArr != NULL) {
    std::fill(&treeNumArr[0], &treeNumArr[numVtxs*2], cNullItm);
  }
  
  const std::vector<Size>*
    vtxVecArr = (numVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
   //const std::vector<Val>* edgWghtVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mEdgWghtVecVec[0]; 
   const Val* vtxWghtArr = (numVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];    

  Val maxweight = 0.0;
  // find the max edge weight
  for (Size v = 0; v < numVtxs; ++v) {
    Size sNumEdgs = vtxVecArr[v].size();
    const Size* vtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[v][0];
	 for (Size i = 0; i < sNumEdgs; ++i) {
	      Size t = vtxArr[i];
		      
	      	if(vtxWghtArr[v]+vtxWghtArr[t] > maxweight)
	      	 maxweight = vtxWghtArr[v]+vtxWghtArr[t];
  }
}
  
 
  Val delta = maxweight*ep;
  //2
  //to store dual values for each vertex of a blossom
  std::vector<Val> dualVec;
  ResizeVector<Val>(&dualVec, numVtxs*2);
  Val* dualArr = (numVtxs== 0) ? NULL : &dualVec[0];
  std::fill(&dualArr[0], &dualArr[numVtxs], maxweight/2.0 - delta/2.0);
  std::fill(&dualArr[numVtxs], &dualArr[numVtxs*2], 0);
  
  //to store a status for each vertex or a blossom
  std::vector<Stt> sttVec;
  ResizeVector<Stt>(&sttVec, numVtxs);
  Stt* sttArr = (numVtxs == 0) ? NULL : &sttVec[0];
  if (sttArr != NULL) {
    std::fill(&sttArr[0], &sttArr[numVtxs], eSttIdle);
}
  std::vector<Size> idxVec;
  ResizeVector<Size>(&idxVec, numVtxs);
  Size* idxArr = (numVtxs == 0) ? NULL : &idxVec[0];
  if (idxArr != NULL) {
    std::fill(&idxArr[0], &idxArr[numVtxs], 0);
  }

  	ItmQue sLastQue(numVtxs);
  	ItmQue tLastQue(numVtxs);
  
  	ItmStk prcsbStk(numVtxs);
	ItmQue prcsdQue(numVtxs);
  	ItmIdxdQue expsdQue(numVtxs);
	
	Size blsm = numVtxs;

	for (Size s = 0; s < numVtxs; ++s) 
	{
      	expsdQue.Push(s);
  	}
	
  	for(Size i = 0; i <= logbase2(maxweight) ; i++)
  	{		
  		bool doneScale=true;
  		
  		do
  		{
  			doneScale=true;
  			
  			//maximal set of vertex disjoint augmenting paths
      		rFindMxmlSetAugPathsCard<ItmQue, ItmStk, ItmIdxdQue>
        	(graph, mateArr, ptrArr, sttArr, idxArr,
         	prcsbStk, prcsdQue, expsdQue, sLastQue, tLastQue,blsmArr,rprsArr,blsmParentArr,blsmChildrenArr,blsmL,label,
			  dualArr, &blsm, delta,blsmin,treeNumArr,i,ep);
			
			// augmenting the set of maximal  augmenting paths
    		while (tLastQue.Empty() == false) 
			{
      			Size sLast = sLastQue.Front();
      			sLastQue.Pop();
      			Size tLast = tLastQue.Front();
      			tLastQue.Pop();
      			sttArr[tLast] = eSttIdle;
      			rAugment<ItmIdxdQue,ItmQue>(mateArr, ptrArr, expsdQue, sLast, tLast, blsmArr, rprsArr, blsmParentArr,
				    blsmChildrenArr,blsmL,numVtxs,label,blsmin);
      			
      			++(*card);
    		}
    		// vertices dual updates
  			for (Size v = 0; v < numVtxs; ++v) 
			{
				Size blsmv=v;
				if(blsmParentArr[v]!=cNullItm)
	    		{
				blsmv = rFindblsm<ItmQue>(blsmParentArr,blsmArr, rprsArr, v);
				}
			    if( blsmv>=graph.mNumVtxs && label[blsmv]==1)
				{
					dualArr[v] = fabs(dualArr[v] - delta/2);
				}
				else if(blsmv>=graph.mNumVtxs && label[ blsmv]==2)
				{
					dualArr[v] += delta/2;
				}
  				else if(label[v]==1 || mateArr[v]==cNullItm) 
    				{
    					dualArr[v] = fabs(dualArr[v] - delta/2);
					}
    			else if(label[v]==2)
    			{
    				dualArr[v] += delta/2;
				}
				label[v]=0;
				treeNumArr[v]=cNullItm;
    				
  			}

            //blossoms dual updates
  			for(Size v = numVtxs; v < blsm; ++v) 
			{
  				if(rprsArr[v]!=cNullItm && blsmParentArr[v]==cNullItm)
  				{
  					if(label[v]==1)
		    			{
		    				dualArr[v] += delta;
						}
		    		else if(label[v]==2)
		    			{
		    				dualArr[v] = fabs(dualArr[v]-delta);
						}
	  			}
	  			label[v]=0;
	  			treeNumArr[v]=cNullItm;
  			}
  		
  			//dissolving inner blossoms if the dual becomes zero
  			for (Size v = numVtxs; v < blsm; ++v)
			{
  				if(rprsArr[v]!=cNullItm && blsmParentArr[v]==cNullItm && fabs(dualArr[v]) <= EPS)
  				{
  						rprsArr[v]=cNullItm;
		    			rDissolveBlsm3<ItmQue>(graph, blsmArr,blsmParentArr, blsmChildrenArr, v);		    			
	  			}
  			}
  
  			//check if we reach the limit of iterations within a scale
  			if(i <logbase2(maxweight) )
  			{
  				Size v = expsdQue.First();
				while (v != cNullItm) 
				{
				  	
					if(dualArr[v] > (maxweight/(pow(2,i+2)))-delta/2)
  					{
  						doneScale=false;
  						break;
					}
					v = expsdQue.Next(v);				
				}
			}
			else
			{
				Size v = expsdQue.First();
				while (v != cNullItm) 
				{
				  	
					if(dualArr[v] > EPS)
  					{
  						doneScale=false;
  						break;
					}
					v = expsdQue.Next(v);				
				}
			}
			while (prcsdQue.Empty() == false) 
			{
      			Size s = prcsdQue.Front();
      			prcsdQue.Pop();
      			ptrArr[s] = cNullItm;
     			sttArr[s] = eSttIdle;
      			idxArr[s] = 0;	
    		}
		}while(!doneScale);
  		
  		// update the duals
  		delta = delta/2.0;
  		for (Size v = 0; v < numVtxs; ++v) 
		{
    		dualArr[v] += delta;
		}
	}// main scale loop
	
	*vtxWght = 0.0;
  for (Size s = 0; s < numVtxs; ++s) {
    if (mateArr[s] != cNullItm) {
      *vtxWght += vtxWghtArr[s];
 
    }
   }
}

template<class ItmQue>
void MatchingEngine::rComputeMaxCardMatchingSglSrc1(const Graph& graph,
    Size* mateArr, Size* card) const {
  if (mInlz == false) {
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    //initialize with maximal cardinality
    rInlzGrdyForCard(graph, mateArr, &iniCard);
    *card = iniCard;
  }
  //to store a pointer from an outer vertex to its parent in the search tree
  std::vector<Size> ptr1Vec;
  ResizeVector<Size>(&ptr1Vec, graph.mNumVtxs);
  Size* ptr1Arr = (graph.mNumVtxs == 0) ? NULL : &ptr1Vec[0];
  if (ptr1Arr != NULL) {
    std::fill(&ptr1Arr[0], &ptr1Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a pointer in from an outer vertex to its parent after its status is changed in a blossom
  std::vector<Size> ptr2Vec;
  ResizeVector<Size>(&ptr2Vec, graph.mNumVtxs);
  Size* ptr2Arr = (graph.mNumVtxs == 0) ? NULL : &ptr2Vec[0];
  if (ptr2Arr != NULL) {
    std::fill(&ptr2Arr[0], &ptr2Arr[graph.mNumVtxs], cNullItm);
  }
  
  //to store a blossom id
  std::vector<Size> blsmVec;
  ResizeVector<Size>(&blsmVec, graph.mNumVtxs);
  Size* blsmArr = (graph.mNumVtxs == 0) ? NULL : &blsmVec[0];
  if (blsmArr != NULL) {
    std::fill(&blsmArr[0], &blsmArr[graph.mNumVtxs], cNullItm);
  }
  //to store a base id of a blossom
  std::vector<Size> rprsVec;
  ResizeVector<Size>(&rprsVec, graph.mNumVtxs);
  Size* rprsArr = (graph.mNumVtxs == 0) ? NULL : &rprsVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    rprsArr[v] = v;
  }
  //to store a status of a vertex
  std::vector<Stt> sttVec;
  ResizeVector<Stt>(&sttVec, graph.mNumVtxs);
  Stt* sttArr = (graph.mNumVtxs == 0) ? NULL : &sttVec[0];
  if (sttArr != NULL) {
    std::fill(&sttArr[0], &sttArr[graph.mNumVtxs], eSttIdle);
  }
  ItmQue prcsbQue(graph.mNumVtxs);
  ItmQue prcsdQue(graph.mNumVtxs);
  for (Size sFirst = 0; sFirst < graph.mNumVtxs; ++sFirst) {
    if (mateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    // find an augmenting path
    rFindAugPathCardSglSrc1<ItmQue>
      (graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr, sttArr, prcsbQue,
       prcsdQue, sFirst, &sLast, &tLast);
    if (tLast != cNullItm) {
    	//augment an augmenting path
      rAugment(mateArr, ptr1Arr, ptr2Arr, sLast, tLast);
      ++(*card);
    }
    //reset working variable for visited vertices
    while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      sttArr[v] = eSttIdle;
    }
    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      sttArr[v] = eSttIdle;
    }
  }
}

template<class ItmQue>
void MatchingEngine::rComputeMaxCardMatchingSglSrc2(const Graph& graph,
    Size* mateArr, Size* card) const {
  if (mInlz == false) {
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
    Size iniCard(0);
    //initialize with maximal cardinality
    rInlzGrdyForCard(graph, mateArr, &iniCard);
    *card = iniCard;
  }

  //to store a pointer from an outer vertex to its parent in the search tree
  std::vector<Size> ptr1Vec;
  ResizeVector<Size>(&ptr1Vec, graph.mNumVtxs);
  Size* ptr1Arr = (graph.mNumVtxs == 0) ? NULL : &ptr1Vec[0];
  if (ptr1Arr != NULL) {
    std::fill(&ptr1Arr[0], &ptr1Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a pointer in from an outer vertex to its parent after its status is changed in a blossom
  std::vector<Size> ptr2Vec;
  ResizeVector<Size>(&ptr2Vec, graph.mNumVtxs);
  Size* ptr2Arr = (graph.mNumVtxs == 0) ? NULL : &ptr2Vec[0];
  if (ptr2Arr != NULL) {
    std::fill(&ptr2Arr[0], &ptr2Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a blossom id
  std::vector<Size> blsmVec;
  ResizeVector<Size>(&blsmVec, graph.mNumVtxs);
  Size* blsmArr = (graph.mNumVtxs == 0) ? NULL : &blsmVec[0];
  if (blsmArr != NULL) {
    std::fill(&blsmArr[0], &blsmArr[graph.mNumVtxs], cNullItm);
  }
  //to store a base id of a blossom
  std::vector<Size> rprsVec;
  ResizeVector<Size>(&rprsVec, graph.mNumVtxs);
  Size* rprsArr = (graph.mNumVtxs == 0) ? NULL : &rprsVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    rprsArr[v] = v;
  }
  //to store links between items in union find tree
  std::vector<Size> linkVec;
  ResizeVector<Size>(&linkVec, graph.mNumVtxs);
  Size* linkArr = (graph.mNumVtxs == 0) ? NULL : &linkVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    linkArr[v] = v;
  }
  //to store a rank of an item in union find tree
  std::vector<Size> rankVec;
  ResizeVector<Size>(&rankVec, graph.mNumVtxs);
  Size* rankArr = (graph.mNumVtxs == 0) ? NULL : &rankVec[0];
  if (rankArr != NULL) {
    std::fill(&rankArr[0], &rankArr[graph.mNumVtxs], 0);
  }
  //to store a status of a vertex
  std::vector<Stt> sttVec;
  ResizeVector<Stt>(&sttVec, graph.mNumVtxs);
  Stt* sttArr = (graph.mNumVtxs == 0) ? NULL : &sttVec[0];
  if (sttArr != NULL) {
    std::fill(&sttArr[0], &sttArr[graph.mNumVtxs], eSttIdle);
  }
  ItmQue prcsbQue(graph.mNumVtxs);
  ItmQue prcsdQue(graph.mNumVtxs);
  for (Size sFirst = 0; sFirst < graph.mNumVtxs; ++sFirst) {
    if (mateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    // find an augmenting path
    rFindAugPathCardSglSrc2<ItmQue>
      (graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr, linkArr, rankArr,
       sttArr, prcsbQue, prcsdQue, sFirst, &sLast, &tLast);
    if (tLast != cNullItm) {
    	//augment an augmenting path	
      rAugment(mateArr, ptr1Arr, ptr2Arr, sLast, tLast);
      ++(*card);
      //reset working variable for visited vertices
      while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttIdle;
    }
    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttIdle;
    }
    continue;
    }
    //mark visited vertices so they are not visited again in future searches
    while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttLast;
    }
    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttLast;
    }
  }	
}


template<class ItmQue>
void MatchingEngine::rComputeMaxCardMatchingSglSrc3(const Graph& graph,
    Size* mateArr, Size* card,std::pair<Size,Val>* sortedArr) const {
  if (mInlz == false) {
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
  } else {
  	//initialize with maximal cardinality
    Size iniCard(0);
    rInlzGrdyForCard(graph, mateArr, &iniCard);
    *card = iniCard;
  }
  //Timer timer;
  //timer.Start();
  //to store a pointer from an outer vertex to its parent in the search tree
  std::vector<Size> ptr1Vec;
  ResizeVector<Size>(&ptr1Vec, graph.mNumVtxs);
  Size* ptr1Arr = (graph.mNumVtxs == 0) ? NULL : &ptr1Vec[0];
  if (ptr1Arr != NULL) {
    std::fill(&ptr1Arr[0], &ptr1Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a pointer in from an outer vertex to its parent after its status is changed in a blossom
  std::vector<Size> ptr2Vec;
  ResizeVector<Size>(&ptr2Vec, graph.mNumVtxs);
  Size* ptr2Arr = (graph.mNumVtxs == 0) ? NULL : &ptr2Vec[0];
  if (ptr2Arr != NULL) {
    std::fill(&ptr2Arr[0], &ptr2Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a blossom id
  std::vector<Size> blsmVec;
  ResizeVector<Size>(&blsmVec, graph.mNumVtxs);
  Size* blsmArr = (graph.mNumVtxs == 0) ? NULL : &blsmVec[0];
  if (blsmArr != NULL) {
    std::fill(&blsmArr[0], &blsmArr[graph.mNumVtxs], cNullItm);
  }
  //to store a base id of a blossom
  std::vector<Size> rprsVec;
  ResizeVector<Size>(&rprsVec, graph.mNumVtxs);
  Size* rprsArr = (graph.mNumVtxs == 0) ? NULL : &rprsVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    rprsArr[v] = v;
  }
  //to store links between items in union find tree
  std::vector<Size> linkVec;
  ResizeVector<Size>(&linkVec, graph.mNumVtxs);
  Size* linkArr = (graph.mNumVtxs == 0) ? NULL : &linkVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    linkArr[v] = v;
  }
  //to store a rank of an item in union find tree
  std::vector<Size> rankVec;
  ResizeVector<Size>(&rankVec, graph.mNumVtxs);
  Size* rankArr = (graph.mNumVtxs == 0) ? NULL : &rankVec[0];
  if (rankArr != NULL) {
    std::fill(&rankArr[0], &rankArr[graph.mNumVtxs], 0);
  }
  //to store a status of a vertex
  std::vector<Stt> sttVec;
  ResizeVector<Stt>(&sttVec, graph.mNumVtxs);
  Stt* sttArr = (graph.mNumVtxs == 0) ? NULL : &sttVec[0];
  if (sttArr != NULL) {
    std::fill(&sttArr[0], &sttArr[graph.mNumVtxs], eSttIdle);
  }
  ItmQue prcsbQue(graph.mNumVtxs);
  ItmQue prcsdQue(graph.mNumVtxs);
   for (Size current = 0; current <graph.mNumVtxs; ++current) {
    	Size sFirst =  sortedArr[current].first;
    if (mateArr[sFirst] != cNullItm) {
      continue;
    }
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    // find an augmenting path
    rFindAugPathCardSglSrc2<ItmQue>
      (graph, mateArr, ptr1Arr, ptr2Arr, blsmArr, rprsArr, linkArr, rankArr,
       sttArr, prcsbQue, prcsdQue, sFirst, &sLast, &tLast);
    if (tLast != cNullItm) {
    	//augment an augmenting path
      rAugment(mateArr, ptr1Arr, ptr2Arr, sLast, tLast);
      ++(*card);
      //reset visited vertices working variables
      while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttIdle;
    }
    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttIdle;
    }
    continue;
    }
    //mark visited vertices so they are not visited again in future searches
    while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttLast;
    }
    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      rprsArr[v] = v;
      linkArr[v] = v;
      rankArr[v] = 0;
      sttArr[v] = eSttLast;
    }
  }		
}

template<class ItmQue>
void MatchingEngine::rComputeAprxMaxEdgWghtMatching4(const Graph& graph,
    Size* mateArr, Size* card, Val* edgWght) const {
  if (mateArr != NULL) {
    std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
  }
  *card = 0;
  *edgWght = 0.0;
  const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  const std::vector<Val>*
    edgWghtVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mEdgWghtVecVec[0];
  // candidates.
  std::vector<Size> cndtMateVec;
  ResizeVector<Size>(&cndtMateVec, graph.mNumVtxs);
  Size* cndtMateArr = (graph.mNumVtxs == 0) ? NULL : &cndtMateVec[0];
  if (cndtMateArr != NULL) {
    std::fill(&cndtMateArr[0], &cndtMateArr[graph.mNumVtxs], cNullItm);
  }
  // queue of matched vertices to be processed.
  ItmQue matchedQue(graph.mNumVtxs);
  // initialize the queue of matched vertices.
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    Size w = cNullItm;
    Val maxEdgWght = cNegInfVal;
    Size vNumEdgs = vtxVecArr[v].size();
    const Size* vVtxArr = (vNumEdgs == 0) ? NULL : &vtxVecArr[v][0];
    const Val* vEdgWghtArr = (vNumEdgs == 0) ? NULL : &edgWghtVecArr[v][0];
    for (Size j = 0; j < vNumEdgs; ++j) {
      Size z = vVtxArr[j];
      Val vzEdgWght = vEdgWghtArr[j];
      if (z == v) {
        continue;
      }
      if (maxEdgWght < vzEdgWght) {
        w = z;
        maxEdgWght = vzEdgWght;
      }
    }
    cndtMateArr[v] = w;
    if ((w != cNullItm) && (cndtMateArr[w] == v)) {
      mateArr[v] = w;
      mateArr[w] = v;
      matchedQue.Push(v);
      ++(*card);
      *edgWght += maxEdgWght;
    }
  }
  // only one vertex out of each matched pair is queued, use an array to
  // process both.
  Size matchedArr[2];
  // process the matched vertices from the queue.
  while (matchedQue.Empty() == false) {
    Size u = matchedQue.Front();
    matchedQue.Pop();
    matchedArr[0] = u;
    matchedArr[1] = mateArr[u];
    for (Size k = 0; k < 2; ++k) {
      u = matchedArr[k];
      Size uNumEdgs = vtxVecArr[u].size();
      const Size* uVtxArr = (uNumEdgs == 0) ? NULL : &vtxVecArr[u][0];
      for (Size i = 0; i < uNumEdgs; ++i) {
        Size v = uVtxArr[i];
        if (v == u) {
          continue;
        }
        if (mateArr[v] != cNullItm) {
          continue;
        }
        if (cndtMateArr[v] != u) {
          continue;
        }
        Size w = cNullItm;
        Val maxEdgWght = cNegInfVal;
        Size vNumEdgs = vtxVecArr[v].size();
        const Size* vVtxArr = (vNumEdgs == 0) ? NULL : &vtxVecArr[v][0];
        const Val* vEdgWghtArr = (vNumEdgs == 0) ? NULL : &edgWghtVecArr[v][0];
        for (Size j = 0; j < vNumEdgs; ++j) {
          Size z = vVtxArr[j];
          Val vzEdgWght = vEdgWghtArr[j];
          if (z == v) {
            continue;
          }
          if (mateArr[z] != cNullItm) {
            continue;
          }
          if (maxEdgWght < vzEdgWght) {
            w = z;
            maxEdgWght = vzEdgWght;
          }
        }
        cndtMateArr[v] = w;
        if ((w != cNullItm) && (cndtMateArr[w] == v)) {
          mateArr[v] = w;
          mateArr[w] = v;
          matchedQue.Push(v);
          ++(*card);
          *edgWght += maxEdgWght;
        }
      }
    }
  }
}

//max vertex weighted matching using augmenting paths that reach a heaviest vertex
template<class ItmQue, class ItmStk>
void MatchingEngine::rComputeMaxVtxWght(const Graph& graph,
    Size* mateArr, Size* card, Val* vtxWght, Size augPathLenBnd) const {

    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
	Size numVtxs = graph.mNumVtxs;
	
  //to store a pointer from an outer vertex to its parent in the search tree
  std::vector<Size> ptr1Vec;
  ResizeVector<Size>(&ptr1Vec, graph.mNumVtxs);
  Size* ptr1Arr = (graph.mNumVtxs == 0) ? NULL : &ptr1Vec[0];
  if (ptr1Arr != NULL) {
    std::fill(&ptr1Arr[0], &ptr1Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a pointer in from an outer vertex to its parent after its status is changed in a blossom
  std::vector<Size> ptr2Vec;
  ResizeVector<Size>(&ptr2Vec, graph.mNumVtxs);
  Size* ptr2Arr = (graph.mNumVtxs == 0) ? NULL : &ptr2Vec[0];
  if (ptr2Arr != NULL) {
    std::fill(&ptr2Arr[0], &ptr2Arr[graph.mNumVtxs], cNullItm);
  }
  //to store a blossom id
  std::vector<Size> blsmVec;
  ResizeVector<Size>(&blsmVec, graph.mNumVtxs);
  Size* blsmArr = (graph.mNumVtxs == 0) ? NULL : &blsmVec[0];
  if (blsmArr != NULL) {
     for (Size v = 0; v < graph.mNumVtxs; ++v) {
    blsmArr[v] = v;
  }
  }
  //to store a base id of a blossom
  std::vector<Size> rprsVec;
  ResizeVector<Size>(&rprsVec, graph.mNumVtxs*2);
  Size* rprsArr = (graph.mNumVtxs == 0) ? NULL : &rprsVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    rprsArr[v] = v;
  }
  std::fill(&rprsArr[numVtxs], &rprsArr[numVtxs*2], cNullItm);
  //to store a status of a vertex
  std::vector<Stt> sttVec;
  ResizeVector<Stt>(&sttVec, graph.mNumVtxs);
  Stt* sttArr = (graph.mNumVtxs == 0) ? NULL : &sttVec[0];
  if (sttArr != NULL) {
    std::fill(&sttArr[0], &sttArr[graph.mNumVtxs], eSttIdle);
  }
  //to store links between items in union find tree
  std::vector<Size> linkVec;
  ResizeVector<Size>(&linkVec, graph.mNumVtxs);
  Size* linkArr = (graph.mNumVtxs == 0) ? NULL : &linkVec[0];
  for (Size v = 0; v < graph.mNumVtxs; ++v) {
    linkArr[v] = v;
  }
  //to store a rank of an item in union find tree
  std::vector<Size> rankVec;
  ResizeVector<Size>(&rankVec, graph.mNumVtxs);
  Size* rankArr = (graph.mNumVtxs == 0) ? NULL : &rankVec[0];
  if (rankArr != NULL) {
    std::fill(&rankArr[0], &rankArr[graph.mNumVtxs], 0);
  }
  

  ItmQue prcsbQue(graph.mNumVtxs);
  ItmQue prcsdQue(graph.mNumVtxs);
  
  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  
  std::vector<std::pair<Size, Val> > sExpsdLst2;
  ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, numVtxs);
  std::pair<Size,Val> * sExpsdLst2Arr=  (numVtxs == 0) ? NULL : &sExpsdLst2[0]; 

  for (Size first = 0; first < numVtxs; ++first) {
    sExpsdLst2Arr[first]=std::pair<Size, Val>(first, vtxWghtArr[first]); 
  } 
  //sort vertices in non-increasing order of their weights
  std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater2<std::pair<Size, Val> >());

   for (Size current = 0; current < numVtxs; ++current) {
    	Size sFirst =  sExpsdLst2Arr[current].first; 
		
    if(mateArr[sFirst]!=cNullItm)
    continue;

    //find the next heaviest vertex
    Val secondWght =sExpsdLst2Arr[current].second;
    
    if(current+1<numVtxs)
    {
    	Size c = current+1;
    	while(c<numVtxs)
    	{
    		if(mateArr[sExpsdLst2Arr[c].first]==cNullItm)
    		{
    			secondWght = sExpsdLst2Arr[c].second;
    			break;
			}
			c++;
		}
	}
    else
    break;
    Size sLast(cNullItm);
    Size tLast(cNullItm);
    
       //find an augmenting path to a heaviest unmatched vertex
      rFindAugPathCardSglSrc3<ItmQue>
        (graph, mateArr, ptr1Arr,  ptr2Arr,blsmArr, rprsArr,linkArr, rankArr,
       sttArr, prcsbQue, prcsdQue, sFirst, &sLast, &tLast,secondWght);
   
    if (tLast != cNullItm) {
       //augment an augmenting path 
      rAugment(mateArr, ptr1Arr, ptr2Arr, sLast, tLast);
      ++(*card);
	  
	//reset visited vertices working variables
	while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      linkArr[v] = v;
      rankArr[v] = 0;
      rprsArr[v] = v;
      sttArr[v] = eSttIdle;
    } 
    
    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      linkArr[v] = v;
      rankArr[v] = 0;
      rprsArr[v] = v;
      sttArr[v] = eSttIdle;
    }
      continue;
    }
    //mark visited vertices so they are not visited again in future searches
    while (prcsbQue.Empty() == false) {
      Size v = prcsbQue.Front();
      prcsbQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      linkArr[v] = v;
      rankArr[v] = 0;
      rprsArr[v] = v;
      sttArr[v] = eSttLast;
    }

    while (prcsdQue.Empty() == false) {
      Size v = prcsdQue.Front();
      prcsdQue.Pop();
      ptr1Arr[v] = cNullItm;
      ptr2Arr[v] = cNullItm;
      blsmArr[v] = cNullItm;
      linkArr[v] = v;
      rankArr[v] = 0;
      rprsArr[v] = v;
      sttArr[v] = eSttLast;
    }
  
  }
  *vtxWght = 0.0;
  for (Size s = 0; s < numVtxs; ++s) {
    if (mateArr[s] != cNullItm) {
      *vtxWght += vtxWghtArr[s];
    }
   }
}

template<class ItmQue>
void MatchingEngine::rSuitorVtxWght(const Graph& graph,
    Size* mateArr, Size* card, Val* vtxWght) const {
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
	Size numVtxs = graph.mNumVtxs;
  
  std::vector<Val> sWs;
  ResizeVector<Val>(&sWs, graph.mNumVtxs);
  Val* ws = (graph.mNumVtxs == 0) ? NULL : &sWs[0];
  if (ws != NULL) {
    std::fill(&ws[0], &ws[graph.mNumVtxs], cZeroVal);
  }

////
  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  
   const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  for (Size first = 0; first < numVtxs; ++first)
   {
    Size current = first;
    bool done = false;
    while(!done)
    {
    	Size partner = cNullItm;
    	Val heaviest = 0.0;
    	
    	Size sNumEdgs = vtxVecArr[current].size();
	    const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[current][0];
	    //find a heaviest neighbor with a lower or no proposal
	    for (Size i = 0; i < sNumEdgs; ++i) {
	      Size t = currentVtxArr[i];

	      if (vtxWghtArr[t] + vtxWghtArr[current] >  heaviest || ((fabs(vtxWghtArr[t] + vtxWghtArr[current] -  heaviest)< EPS) && partner > t)){
				if( vtxWghtArr[t] + vtxWghtArr[current] > ws[t])
	            	{
					partner = t;
    				heaviest = vtxWghtArr[t] + vtxWghtArr[current];
					}
					else if (mateArr[t] !=cNullItm && fabs((vtxWghtArr[t] + vtxWghtArr[current] )- ws[t]) < EPS && mateArr[t]>current)
					{
						partner = t;
    					heaviest = vtxWghtArr[t] + vtxWghtArr[current];  
					}
    			
	      }
	    }
	    done = true;
	    if(heaviest > 0.0)
	    {
	    	//change partner and annul y proposal is any
	    	Size y = mateArr[partner];
	    	mateArr[partner]=current;
	    	ws[partner]=heaviest;
	    	if(y != cNullItm)
	    	{
	    		current = y;
	    		done= false;
			}
		}
	}
}

  *vtxWght = 0.0;
  for (Size s = 0; s < numVtxs; ++s) {
    if (mateArr[s] != cNullItm) {
      *vtxWght += vtxWghtArr[s];
      ++(*card);
    }
   }
   (*card)=(*card)/2;
}

template<class ItmQue>
void MatchingEngine::rParSuitorVtxWght(const Graph& graph,
    Size* mateArr, Size* card, Val* vtxWght) const {
	
	Size numVtxss = graph.mNumVtxs;
  	std::vector<Val> sWs;
  	ResizeVector<Val>(&sWs, graph.mNumVtxs);
  	Val* ws = (graph.mNumVtxs == 0) ? NULL : &sWs[0];
  	const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
   	const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
    Size nlocks[numVtxss];
    Val tempvtxWght = 0.0;
	Size tempcard=0;
  	#pragma omp parallel
  	{
  		Size numVtxs = numVtxss;
  		//setting locks for each vertex in parallel
		#pragma omp for schedule(static,256) 
		for(Size i=0;i<numVtxs;i++)  
    	{
        	nlocks[i]=0;
        	ws[i]=cZeroVal;
        	mateArr[i]=cNullItm;
    	}
    	// in parallel find a heaviest partner with a lower or no proposal
  		#pragma omp for schedule(static,256) 
  		for (Size first = 0; first < numVtxs; ++first)
   		{
    		Size current = first;
    		bool done = false;
    		while(!done)
    		{
    			Size partner = cNullItm;
    			Val heaviest = 0;
    	
    			Size sNumEdgs = vtxVecArr[current].size();
	    		const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[current][0];
	    		for (Size i = 0; i < sNumEdgs; ++i) {
	      		Size t = currentVtxArr[i];
	      		//while(__sync_lock_test_and_set(&nlocks[t], 1));
	      		if (vtxWghtArr[t] + vtxWghtArr[current] >  heaviest || ((fabs(vtxWghtArr[t] + vtxWghtArr[current] -  heaviest)< EPS) && partner > t)){
					if( vtxWghtArr[t] + vtxWghtArr[current] > ws[t])
	            	{
						partner = t;
    					heaviest = vtxWghtArr[t] + vtxWghtArr[current];
					}
					else if (mateArr[t] !=cNullItm && fabs((vtxWghtArr[t] + vtxWghtArr[current] )- ws[t]) < EPS && mateArr[t]>current)
					{
						partner = t;
    					heaviest = vtxWghtArr[t] + vtxWghtArr[current];  
					}
    			
	      		}
	      		//__sync_lock_release(&nlocks[t]);
	    	}
	    	done = true;
	    	if(heaviest > 0.0)
	    	{
	    		//lock partner
	    		while(__sync_lock_test_and_set(&nlocks[partner], 1))
				 ;
				Size y = mateArr[partner];
	    		if(y != cNullItm)
	    		{
					if(vtxWghtArr[y] < vtxWghtArr[current] || (vtxWghtArr[y] == vtxWghtArr[current] && current < y))
					{
						mateArr[partner]=current;
	    				ws[partner]=heaviest;
						current = y;
	    				done= false;
					}
					else
					{
						done =false;
					}	
				}
				else
				{
					mateArr[partner]=current;
	    			ws[partner]=heaviest;	
				}
				//release the lock
				__sync_lock_release(&nlocks[partner]);
			}
		}
	}

	#pragma omp for schedule(static,256) nowait reduction(+:tempvtxWght,tempcard) 
	for (Size s = 0; s < numVtxs; ++s)
	{
 		if (mateArr[s] != cNullItm) {
      	tempvtxWght += vtxWghtArr[s];
      	++(tempcard);
    	}
	}
}
  *vtxWght =tempvtxWght;
   *card=tempcard/2;
}

template<class ItmQue>
void MatchingEngine::rPGPVtxWght(const Graph& graph,
    Size* mateArr, Size* card, Val* vtxWght) const {
  
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
Val vtxWght1=0.0;
Val vtxWght2=0.0;
Size card1=0;
Size card2=0;
Size numVtxs = graph.mNumVtxs;
//paths counter
Size pc=0;
//mates of vertices for M1
std::vector<Size> mateVec1;
  ResizeVector<Size>(&mateVec1, graph.mNumVtxs);
  Size* mateArr1 = (graph.mNumVtxs == 0) ? NULL : &mateVec1[0];
  if (mateArr1 != NULL) {
    std::fill(&mateArr1[0], &mateArr1[graph.mNumVtxs], cNullItm);
  } 
  //mate of vertices for M2
  std::vector<Size> mateVec2;
  ResizeVector<Size>(&mateVec2, graph.mNumVtxs);
  Size* mateArr2 = (graph.mNumVtxs == 0) ? NULL : &mateVec2[0];
  if (mateArr2 != NULL) {
    std::fill(&mateArr2[0], &mateArr2[graph.mNumVtxs], cNullItm);
  } 
  //marking the visitied vertices
  std::vector<Size> markVec;
  ResizeVector<Size>(&markVec, graph.mNumVtxs);
  Size* mark = (graph.mNumVtxs == 0) ? NULL : &markVec[0];
  if (mark != NULL) {
    std::fill(&mark[0], &mark[graph.mNumVtxs], 0);
  }
const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  std::vector<std::vector<Size> > tmpVtxVecVec;
  ResizeVector<std::vector<Size> >(&tmpVtxVecVec, numVtxs);
  std::vector<Size>* tmpVtxVecArr = (numVtxs == 0) ? NULL : &tmpVtxVecVec[0];
  for (Size first = 0; first < numVtxs; ++first){
    	Size sNumEdgs = vtxVecArr[first].size();
	    for (Size i = 0; i < sNumEdgs; ++i)
	    {
	    	tmpVtxVecArr[first].push_back(0);
		}  
	  }
  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  //to alternate between M1 and M2
  bool M1turn =true;
  bool cycle =false;
  //length of the path
  Size lp=0;
  for (Size vfirst = 0; vfirst < numVtxs; ++vfirst){
    Size first = vfirst;
    cycle=false;
    pc++;
    mark[first]=pc;
    lp=0;
    M1turn=true;
    bool done = false;
    // construct a path from first vertex
    while(!done)
    {
    // the path could not be extended
    if(M1turn && mateArr1[first]!=cNullItm)
    break;
    if(!M1turn && mateArr2[first]!=cNullItm)
    break;
    	Size sNumEdgs = vtxVecArr[first].size();
    	Size second=cNullItm;
    	Val heaviest = 0.0;
    	Size eIndex=cNullItm;
	    const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[first][0];
	    // find a heaviest neighbor to extend a path
	    for (Size i = 0; i < sNumEdgs; ++i) {
	      Size tempSecond = currentVtxArr[i];
	      
	      assert(first != tempSecond);
	      // if a vertex is already visited
	      if(mark[tempSecond]==pc)
	      {
	      	if(second==vfirst && lp %2 ==1)
		     cycle=true;
		    else
		    continue;
		  }
		  // already constructed path
		   if(mark[tempSecond]<pc && mark[tempSecond]>0)
		   continue;
		   // save a neighbor if it is heavier than the previous one
	      if (vtxWghtArr[tempSecond]> heaviest && tmpVtxVecArr[first][i] ==0 ) {
	            	second= tempSecond;
    				heaviest = vtxWghtArr[tempSecond];
    				eIndex=i;
	      }
	    }
		
		done =true;
		if(heaviest >0.0)
	    {
	    	mark[second]=pc;
	    	// increment the length
	    	lp++;
	    	if(M1turn)
	    	{
	    		if (mateArr1[second] == cNullItm)
				{
	    		mateArr1[second]=first;
	    		mateArr1[first]=second;
	    		vtxWght1+=vtxWghtArr[first];
	    		vtxWght1+=vtxWghtArr[second];
	    		card1++;
	    		tmpVtxVecArr[first][eIndex]=1;
	    		Size sNumEdgs1 = vtxVecArr[second].size();
	    		 const Size* currentVtxArr1 = (sNumEdgs == 0) ? NULL : &vtxVecArr[second][0];
			    for (Size j = 0; j < sNumEdgs1; ++j) {
			      if(currentVtxArr1[j]==first)
			      {
			      	tmpVtxVecArr[second][j]=1;
			      	break;
				  }
					}
				M1turn=false;
			  }
			}
			else
	    	{
	    	if (mateArr2[second] == cNullItm)
				{
	    		mateArr2[second]=first;
	    		mateArr2[first]=second;
	    		vtxWght2+=vtxWghtArr[first];
	    		vtxWght2+=vtxWghtArr[second];
	    		card2++;
	    		tmpVtxVecArr[first][eIndex]=1;
	    		Size sNumEdgs1 = vtxVecArr[second].size();
	    		 const Size* currentVtxArr1 = (sNumEdgs == 0) ? NULL : &vtxVecArr[second][0];
			    for (Size j = 0; j < sNumEdgs1; ++j) {
			      if(currentVtxArr1[j]==first)
			      {
			      	tmpVtxVecArr[second][j]=1;
			      	break;
				  }
					}
				M1turn=true;
			  }  		
			}
			done= false;
			first=second;
			if(cycle)
			done= true;
		}	
	}
  }

 if(vtxWght1 >= vtxWght2)
 {
 	*vtxWght =vtxWght1;	
 	*card=card1;
 	 for (Size s = 0; s < numVtxs; ++s) {
    	mateArr[s] = mateArr1[s];
   }
 }
 else
 {
 	*vtxWght =vtxWght2;	
 	*card=card2;
 	 for (Size s = 0; s < numVtxs; ++s) {
    	mateArr[s] = mateArr2[s];
   }
 }
}

template<class ItmQue>
void MatchingEngine::rPGDPVtxWght(const Graph& graph,
    Size* mateArr, Size* card, Val* vtxWght) const {
  
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
  
Size numVtxs = graph.mNumVtxs;
 
    Size midx1=0;
    Size midx2=0;
    Size pidx=0;
    Val W1=0;
    Val W2=0;
    Val temp;
	Size* tp;
	Size pc=0;
//mates of vertices for M1
std::vector<Size> M1Vec;
  ResizeVector<Size>(&M1Vec, 3*graph.mNumVtxs);
  Size* M1 = (graph.mNumVtxs == 0) ? NULL : &M1Vec[0];
  if (M1 != NULL) {
    std::fill(&M1[0], &M1[3*graph.mNumVtxs], 0);
  }
 //mates of vertices for M2
std::vector<Size> M2Vec;
  ResizeVector<Size>(&M2Vec, 3*graph.mNumVtxs);
  Size* M2 = (graph.mNumVtxs == 0) ? NULL : &M2Vec[0];
  if (M2 != NULL) {
    std::fill(&M2[0], &M2[3*graph.mNumVtxs], 0);
  }
//mark visited vertices
std::vector<Size> markVec;
  ResizeVector<Size>(&markVec, graph.mNumVtxs);
  Size* mark = (graph.mNumVtxs == 0) ? NULL : &markVec[0];
  if (mark != NULL) {
    std::fill(&mark[0], &mark[graph.mNumVtxs], 0);
  }
  
const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];

  std::vector<std::vector<Size> > tmpVtxVecVec;
  ResizeVector<std::vector<Size> >(&tmpVtxVecVec, numVtxs);
  std::vector<Size>* tmpVtxVecArr = (numVtxs == 0) ? NULL : &tmpVtxVecVec[0];
  
  for (Size first = 0; first < numVtxs; ++first){
    	Size sNumEdgs = vtxVecArr[first].size();
	    for (Size i = 0; i < sNumEdgs; ++i)
	    {
	    	tmpVtxVecArr[first].push_back(0);
		}
	      
	  }

  const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
	 
    bool cycle =true;
    //edge number in apth
    Size eNumPath=0;
    //path ength
    Size lp=0;
	
	for (Size vfirst = 0; vfirst < numVtxs; ++vfirst){
    Size first = vfirst;
    
    bool done = false;
    midx1=0;
    midx2=0;
    W1=0;
    W2=0;
    eNumPath=0;
    pc++;
    cycle=false;
    mark[first]=pc;
    lp=0;
    while(!done)
    {
    	if(mateArr[first]!=cNullItm)
    	break;

    	Size sNumEdgs = vtxVecArr[first].size();
    	Size second=cNullItm;
    	Val heaviest = 0.0;
    	Size eIndex=cNullItm;
	    const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[first][0];
	    for (Size i = 0; i < sNumEdgs; ++i) {
	      Size tempSecond = currentVtxArr[i];
	      
	      assert(first != tempSecond);
	      // check if the vertex is already visited
	      if(mark[tempSecond]==pc)
	      {
	      	if(second==vfirst && lp %2 ==1)
		     cycle=true;
		    else
		    continue;
		  }
		   if(mateArr[tempSecond]!=cNullItm)
		   continue;
		   //the vertex belong to different path
		   if(mark[tempSecond]<pc && mark[tempSecond]>0)
		   continue;
	    
	      if (vtxWghtArr[tempSecond]> heaviest && tmpVtxVecArr[first][i] ==0 ) {
	            	second= tempSecond;
    				heaviest = vtxWghtArr[tempSecond];
    				eIndex=i;
	      }
	    }
		
		done =true;
		if(heaviest >0.0)
	    {
	    	mark[second]=pc;
	    	//increment the path length
	    	eNumPath++;
	    	if(eNumPath==1)
	    	{
	    		// the first edge to be included in a path
				W1=heaviest+vtxWghtArr[first];
            	M1[midx1]=first;
            	M1[midx1+1]=second;
            	M1[midx1+2]=heaviest;
            	midx1+=3;
	    		tmpVtxVecArr[first][eIndex]=1;
	    		Size sNumEdgs1 = vtxVecArr[second].size();
	    		const Size* currentVtxArr1 = (sNumEdgs == 0) ? NULL : &vtxVecArr[second][0];
			    for (Size j = 0; j < sNumEdgs1; ++j) {
			      if(currentVtxArr1[j]==first)
			      {
			      	tmpVtxVecArr[second][j]=1;
			      	break;
				  }
				}
			}
			else
	    	{
	    		// using dynamic programming to select the heaviest matching edges in a path
				if(W2 + heaviest+vtxWghtArr[first] > W1)
	            {
	                temp=W2;
	                W2=W1;
	                W1=temp+heaviest+vtxWghtArr[first];
	
	                M2[midx2]=first;
	                M2[midx2+1]=second;
	                M2[midx2+2]=heaviest+vtxWghtArr[first];
	                midx2+=3;
	
	                tp=M2;
	                M2=M1;
	                M1=tp;
	
	                pidx=midx2;
	                midx2=midx1;
	                midx1=pidx;
	
	            }
	            else
	            {
	                W2=W1;
	                for(Size i=0;i<midx1;i++)
	                 M2[i]=M1[i];
	                midx2=midx1;
	            }
	    	
	    		tmpVtxVecArr[first][eIndex]=1;
	    		Size sNumEdgs1 = vtxVecArr[second].size();
	    		 const Size* currentVtxArr1 = (sNumEdgs == 0) ? NULL : &vtxVecArr[second][0];
			    for (Size j = 0; j < sNumEdgs1; ++j) {
			      if(currentVtxArr1[j]==first)
			      {
			      	tmpVtxVecArr[second][j]=1;
			      	break;
				  }
				} 		
			}
			eNumPath++;
			done= false;
			first=second;
			if(cycle)
			done=true;
		}	
	}
  	
  	//matched vertices found by using dynamic programming
  	Size u=0,v=0;
	if(midx1>0)
        {
            *vtxWght+=W1;
           for(Size j=0;j< midx1;j+=3)
           {
               u=M1[j];
               v=M1[j+1];  
                mateArr[u]=v;
                mateArr[v]=u;
                *card=*card+1;
           }
        }	
  }
}

template<class ItmQue>
void MatchingEngine::rLocallyDominantVtxWght(const Graph& graph,
    Size* mateArr, Size* card, Val* vtxWght) const {
    if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    *card = 0;
  
Size numVtxs = graph.mNumVtxs;
 // live vertices are considered (they are not matched)
std::vector<Size> aliveVec;
  ResizeVector<Size>(&aliveVec, graph.mNumVtxs);
  Size* alive = (graph.mNumVtxs == 0) ? NULL : &aliveVec[0];
  if (alive != NULL) {
    std::fill(&alive[0], &alive[graph.mNumVtxs], 1);
  }
  
const std::vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];

   const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];      
   bool done = false;
    
    while(!done)
    {
      
	    for (Size vfirst = 0; vfirst < numVtxs; ++vfirst){
 
    	Val heaviest=0.0;
    	//skip if the vertex is already matched		
    	if(alive[ vfirst]==0 || mateArr[vfirst]!=cNullItm)
    	continue;

    	Size sNumEdgs = vtxVecArr[vfirst].size();
    	Size second = cNullItm;
	    const Size* currentVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[vfirst][0];
	    for (Size i = 0; i < sNumEdgs; ++i) {
	      Size tempSecond = currentVtxArr[i];
	      
	      assert(vfirst != tempSecond);
		   if(alive[tempSecond]==0)
		   continue;
	      if (vtxWghtArr[tempSecond] > heaviest ||(vtxWghtArr[tempSecond]==heaviest && tempSecond>second)) {
	            	second= tempSecond;
    				heaviest = vtxWghtArr[tempSecond];
	      }
	    }
		
		done =true;
		if(heaviest >0.0)
	    { 
	    	mateArr[vfirst]=second;
		}
		else
	    {		
	    	alive[vfirst]=0;
	   	}
		
		}
		
		for (Size vfirst = 0; vfirst < numVtxs; ++vfirst){
			 if(alive[vfirst]==0)
                    continue;
                    
            Size curr =mateArr[vfirst];
            if(mateArr[curr]!= vfirst)
            {
            	//if the edge is not locally dominant then reset mate to be considered in the next iteration
            	mateArr[vfirst]=cNullItm;
            	done=false;
			}
			else
			{
				// match an edge
				*vtxWght+=(vtxWghtArr[vfirst]+vtxWghtArr[curr]);
				*card=*card+1;
				mateArr[vfirst]=curr;
				mateArr[curr]=vfirst;
				alive[vfirst]=0;
				alive[curr]=0;
			}   
		}	
	}
}


template<class ItmQue>
void MatchingEngine::rComputeHalfVtxWghtMatching(
    const Graph& graph, Size* mateArr, Size* card,
    Val* vtxWght) const {
  
	Size numVtxs =graph.mNumVtxs;
	
	if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
	
  	*card = 0; 
   	const std::vector<Size>* vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
    const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  	std::vector<std::pair<Size, Val> > sExpsdLst2;
  	ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, numVtxs);
  	std::pair<Size,Val> * sExpsdLst2Arr=  (numVtxs == 0) ? NULL : &sExpsdLst2[0]; 

  	for (Size first = 0; first < numVtxs; ++first) {
    	sExpsdLst2Arr[first]=std::pair<Size, Val>(first, vtxWghtArr[first]); 
  	} 
  	//sort vertices in non-increasing order of their weights
  	std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater<std::pair<Size, Val> >());

    for (Size current = 0; current < numVtxs; ++current) {
    	Size sFirst =  sExpsdLst2[current].first;
    	if(mateArr[sFirst]!=cNullItm)
    		continue;
    	Val heaviest = 0.0;
    	Size mateT = cNullItm;
    	Size numEdgs = vtxVecArr[sFirst].size();
    	const Size* vtxArr = (numEdgs == 0) ? NULL : &vtxVecArr[sFirst][0];
    	//find  heaviest neighbor
    	for (Size i = 0; i < numEdgs; ++i) {
      		Size t = vtxArr[i];
	  		if(mateArr[t]== cNullItm && vtxWghtArr[t] > heaviest)
	  		{
				heaviest = 	vtxWghtArr[t];
				mateT=t;
	  		}
		}
		if(heaviest > 0.0)
		{
			//match an edge
			mateArr[mateT]=sFirst;
			mateArr[sFirst]=mateT;
			++(*card);	
		}
	
	}
  *vtxWght = 0.0;
  for (Size s = 0; s < numVtxs; ++s) {
    if (mateArr[s] != cNullItm) {
      *vtxWght += vtxWghtArr[s];
    }
  }
}


template<class ItmQue>
void MatchingEngine::rComputeTwoThirdVtxWghtMatching(
    const Graph& graph, Size* mateArr, Size* card,
    Val* vtxWght) const {
 Size numVtxs =graph.mNumVtxs;
 
 if (mateArr != NULL) {
      std::fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
    }
    

  *card = 0;
  
   const std::vector<Size>* vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];

    const Val* vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  
  // a queue to save matched neighbors
  std::deque<Size> sPrcsbQue;
 
  std::vector<std::pair<Size, Val> > sExpsdLst2;
  ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, numVtxs);
  std::pair<Size,Val> * sExpsdLst2Arr=  (numVtxs == 0) ? NULL : &sExpsdLst2[0]; 

  for (Size first = 0; first < numVtxs; ++first) {
    sExpsdLst2Arr[first]=std::pair<Size, Val>(first, vtxWghtArr[first]); 
  } 
  //sort vertices in non-increasing order
  std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater<std::pair<Size, Val> >());
    // for each vertex find an augmenting path of length at most 3 that reach a heaviest unmatched vertex
    for (Size current = 0; current < numVtxs; ++current) {
		Size sFirst =  sExpsdLst2Arr[current].first;    	
		if(mateArr[sFirst]!=cNullItm)
    	continue;
    	Size numEdgs = vtxVecArr[sFirst].size();
    	const Size* vtxArr = (numEdgs == 0) ? NULL : &vtxVecArr[sFirst][0];
		Val heaviest =0;
		Size mateT =cNullItm;
		Size tempMate=cNullItm;
		sPrcsbQue.clear();
    	for (Size i = 0; i < numEdgs; ++i) {
      		Size t = vtxArr[i];
	  		if(mateArr[t]== cNullItm)
	  		{
	  			if(vtxWghtArr[t] > heaviest)
	  			{
	  				heaviest = vtxWghtArr[t];
	  				tempMate=cNullItm;
	  				mateT = t;	
				}
	  		}
	  		else
	  		{
	  			sPrcsbQue.push_back(mateArr[t]);
	  		}
		}
		while (sPrcsbQue.empty() == false) {
		  	Size s = sPrcsbQue.front();
		  	sPrcsbQue.pop_front();
		  	Size numEdgs = vtxVecArr[s].size();
			const Size* vtxArr = (numEdgs == 0) ? NULL : &vtxVecArr[s][0];
			for (Size i = 0; i < numEdgs; ++i) {
				Size t = vtxArr[i];
			  	if(mateArr[t] == cNullItm && t != sFirst)
			  	{
			  		if(vtxWghtArr[t] > heaviest)
			  		{
			  		heaviest = vtxWghtArr[t];
	  				mateT = t;
					tempMate=mateArr[s];
					}
				
			  	}
			}
		}
		if(heaviest > 0)
		{
			//augment an augmenting path
			if(tempMate == cNullItm )
			{
				mateArr[mateT]=sFirst;
				mateArr[sFirst]=mateT;
				++(*card);
			}
			else
			{
				Size tempS = mateArr[tempMate];
				mateArr[mateT]=tempS;
				mateArr[tempS]=mateT;
				mateArr[tempMate]=sFirst;
				mateArr[sFirst]=tempMate;
				++(*card);
			}
		}
		
	}
  	*vtxWght = 0.0;
  	for (Size s = 0; s < numVtxs; ++s) {
    	if (mateArr[s] != cNullItm) {
      	*vtxWght += vtxWghtArr[s];
    	}
  	}
}

} // namespace Matchbox

#endif // MATCHING_ENGINE_H
