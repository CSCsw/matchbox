#ifndef BPT_GRAPH_H
#define BPT_GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm> // for min, fill, copy, find_if, adjacent_find, sort.
#include <numeric> // for accumulate.
#include <functional> // for less, greater_equal, bind2nd.
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector, CanAdd.

// the graph validity conditions:
// - the number of vertices and the number of edges are within the allowed
// range: [0, cInfSize)
// - every S-vertex is within the allowed range: [0, mSNumVtxs)
// - every T-vertex is within the allowed range: [0, mTNumVtxs)
// - every edge weight is within the allowed range: [cZeroVal, cPosInfVal)
// - every vertex weight is within the allowed range: [cZeroVal, cPosInfVal)
// - the adjacencies do not store duplicate edges: a vertex appears at most
// once in an adjacency
// - the adjacencies double store the edges correctly: if s is an S-vertex and
// t is a T-vertex and (s,t) is is an edge then (s,t) is stored twice, once in
// the adjacency of s and once in the adjacency of t; in other words s appears
// in the adjacency of t if and only if t appears in the adjacency of t and the
// corresponding edges weigths from the two adjacencies are identical.

// the graph validity conditions do not require sorted adjacencies.
// however, keeping the adjacencies sorted is helpful in guaranteeing two of
// the validity conditions:
// - by keeping the adjacencies sorted it is easy to find and remove duplicate
// edges; allowing such duplication in the user input provides a more forgiving
// behavior
// - by keeping the adjacencies sorted it is easy to determine if they double
// store the edges correctly

// the validation procedure when the graph is formed at once from its set of
// edges:
// - determine if the number of vertices and the number of edges are within the
// allowed range
// - determine if every S-vertex is within the allowed range
// - determine if every T-vertex is within the allowed range
// - determine if every edge weight is within the allowed range
// - sort the adjacencies
// - find and remove duplicate edges

// the validation procedure when the graph is formed one adjacency at a time:
// - same steps as above
// - determine if the adjacencies double store the edges correctly

// note that when the graph is formed at once from its set of edges then it is
// not possible for the user to violate the correct double storage of the edges
// and therefore this condition does not need to be checked during the
// validation procedure. in this case the sort procedure is shorter, requiring
// just one bucket sort step. if adj represents the original, not necessarily
// sorted adjacencies and adj' represents the output of a bucket sort step with
// adj as the input, then adj' is the sorted version of adj.

// on the other hand, when the graph is formed one adjacency at a time then it
// is possible for the user to violate the correct double storage of the edges
// and therefore this condition needs to be checked during the validation
// procedure. in this case the sort procedure is longer, requiring two bucket
// sort steps. if adj and adj' are as above then adj' is not necessarily the
// sorted version of adj. the second bucket sort step takes adj' as input and
// produces adj'' as output and adj'' is the sorted version of adj. the
// adjacencies double store the edges correctly if and only if adj' and adj''
// are identical.

namespace Matchbox {

class BptGraph {
public:
  /// Constructor.
  BptGraph():
      mInitErr(eErrNone), mSNumVtxs(0), mTNumVtxs(0), mNumEdgs(0),
      mPrecision(cMaxPrecision), mFullPrint(false) {}

  /// Constructor.
  /// duplicate edges allowed in the input, they are removed internally.
  /// duplicate removal is performed by preserving the first edge out of a
  /// group.
  BptGraph(Size sNumVtxs,
           Size tNumVtxs,
           Size numEdgs,
           const std::vector<Size>& sVtxVec,
           const std::vector<Size>& tVtxVec,
           const std::vector<Val>& edgWghtVec):
      mInitErr(eErrNone), mSNumVtxs(0), mTNumVtxs(0), mNumEdgs(0),
      mPrecision(cMaxPrecision), mFullPrint(false) {
    mInitErr = Set(sNumVtxs, tNumVtxs, numEdgs, sVtxVec, tVtxVec, edgWghtVec);
  }

  /// Destructor.
  ~BptGraph() {}

  ///
  void GetInitErr(Err* initErr) const { *initErr = mInitErr; }

  ///
  void GetSNumVtxs(Size* sNumVtxs) const { *sNumVtxs = mSNumVtxs; }

  ///
  void GetTNumVtxs(Size* tNumVtxs) const { *tNumVtxs = mTNumVtxs; }

  ///
  void GetNumVtxs(Size* sNumVtxs,
                  Size* tNumVtxs) const {
    *sNumVtxs = mSNumVtxs;
    *tNumVtxs = mTNumVtxs;
  }

  ///
  void GetNumEdgs(Size* numEdgs) const { *numEdgs = mNumEdgs; }

  ///
  void GetSize(Size* sNumVtxs,
               Size* tNumVtxs,
               Size* numEdgs) const {
    *sNumVtxs = mSNumVtxs;
    *tNumVtxs = mTNumVtxs;
    *numEdgs = mNumEdgs;
  }

  ///
  void GetEdgs(std::vector<Size>* sVtxVec,
               std::vector<Size>* tVtxVec,
               std::vector<Val>* edgWghtVec) const;

  ///
  Err GetAdj(Size sVtx,
             Size* sNumEdgs,
             std::vector<Size>* sVtxVec,
             std::vector<Val>* sEdgWghtVec,
             bool rvrs) const;

  ///
  void GetVtxWghts(std::vector<Val>* sVtxWghtVec,
                   std::vector<Val>* tVtxWghtVec) const;

  ///
  void GetVtxDgrs(std::vector<Size>* sVtxDgrVec,
                  std::vector<Size>* tVtxDgrVec) const;

  ///
  void Get(Size* sNumVtxs,
           Size* tNumVtxs,
           Size* numEdgs,
           std::vector<Size>* sVtxVec,
           std::vector<Size>* tVtxVec,
           std::vector<Val>* edgWghtVec) const {
    GetSize(sNumVtxs, tNumVtxs, numEdgs);
    GetEdgs(sVtxVec, tVtxVec, edgWghtVec);
  }

  ///
  void Print(void) const;

  ///
  void Clear(void) {
    mSNumVtxs = 0;
    mTNumVtxs = 0;
    mNumEdgs = 0;
    ResizeVector<std::vector<Size> >(&mSVtxVecVec, 0);
    ResizeVector<std::vector<Size> >(&mTVtxVecVec, 0);
    ResizeVector<std::vector<Val> >(&mSEdgWghtVecVec, 0);
    ResizeVector<std::vector<Val> >(&mTEdgWghtVecVec, 0);
    ResizeVector<Val>(&mSVtxWghtVec, 0);
    ResizeVector<Val>(&mTVtxWghtVec, 0);
  }

  ///
  /// duplicate edges allowed in the input, they are removed internally.
  /// duplicate removal is performed by preserving the first edge out of a
  /// group.
  Err Set(Size sNumVtxs,
          Size tNumVtxs,
          Size numEdgs,
          const std::vector<Size>& sVtxVec,
          const std::vector<Size>& tVtxVec,
          const std::vector<Val>& edgWghtVec);

  ///
  Err SetVtxWghts(const std::vector<Val>& sVtxWghtVec,
                  const std::vector<Val>& tVtxWghtVec);

  ///
  void SetEdgWghtsFromVtxWghts(void);

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
  Err Read(const std::string& fileName,
           bool zeroBased = false);

Err ReadWeights(const std::string& fileName, bool zeroBased =false) ;

  ///
  /// adds edges, if necessary, such that (s,t) is an edge, with s an S-vertex
  /// and t a T-vertex, if and only if (s',t') is an edge, with s' an S-vertex
  /// and t' a T-vertex, where s and t' have the same label and t and s' have
  /// the same label, and the corresponding edge weights are identical.
  ///
  /// the symmetrization cannot be performed if either |S| and |T| are not
  /// equal or there is at least a pair of original edges that match the
  /// above characterization except that their weights are not identical.
  Err Symmetrize(void);

private:
  // stores constructor errors.
  Err mInitErr;
  // the number of S-vertices.
  Size mSNumVtxs;
  // the number of T-vertices.
  Size mTNumVtxs;
  // the number of edges.
  Size mNumEdgs;
  // the S-adjacencies: the T-vertices.
  std::vector<std::vector<Size> > mSVtxVecVec;
  // the T-adjacencies: the S-vertices.
  std::vector<std::vector<Size> > mTVtxVecVec;
  // TODO: add comment that explains why mutable.
  // the S-adjacencies: the edge weights.
  mutable std::vector<std::vector<Val> > mSEdgWghtVecVec;
  // the T-adjacencies: the edge weights.
  mutable std::vector<std::vector<Val> > mTEdgWghtVecVec;
  // the S-vertex weights.
  std::vector<Val> mSVtxWghtVec;
  // the T-vertex weights.
  std::vector<Val> mTVtxWghtVec;
  // the precision used for printing floating point numbers.
  Size mPrecision;
  // controls the amount of printing: if false then print less information,
  // if true then print more information.
  bool mFullPrint;

  // forbid the copy constructor and the assignment operator.
  BptGraph(const BptGraph&);
  BptGraph& operator=(const BptGraph&);

  // sort the adjacencies.
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // postconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  ///
  void rSortAdjs(Size sNumVtxs,
                 Size tNumVtxs,
                 std::vector<std::vector<Size> >* sVtxVecVec,
                 std::vector<std::vector<Size> >* tVtxVecVec,
                 std::vector<std::vector<Val> >* sEdgWghtVecVec,
                 std::vector<std::vector<Val> >* tEdgWghtVecVec,
                 bool doubleStorage) const;

  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // postconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // - the adjacencies do not store duplicate edges
  ///
  void rRemoveDupEdgs(Size sNumVtxs,
                      Size tNumVtxs,
                      Size* numEdgs,
                      std::vector<std::vector<Size> >* sVtxVecVec,
                      std::vector<std::vector<Size> >* tVtxVecVec,
                      std::vector<std::vector<Val> >* sEdgWghtVecVec,
                      std::vector<std::vector<Val> >* tEdgWghtVecVec) const;

  // check if there are no duplicate edges.
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // returns success value:
  // - true if the adjacencies do not store duplicate edges.
  // - false otherwise.
  ///
  bool rCheckNoDupEdgs(Size sNumVtxs,
                       Size tNumVtxs,
                       const std::vector<std::vector<Size> >& sVtxVecVec,
                       const std::vector<std::vector<Size> >& tVtxVecVec)
                       const;

  // form the adjacencies from the set of edges.
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // postconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every S-vertex is within the allowed range
  // - every T-vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // - the adjacencies do not store duplicate edges
  // - the adjacencies double store edges correctly
  ///
  void rFormAdjs(Size sNumVtxs,
                 Size tNumVtxs,
                 Size* numEdgs,
                 const std::vector<Size>& sVtxVec,
                 const std::vector<Size>& tVtxVec,
                 const std::vector<Val>& edgWghtVec,
                 std::vector<std::vector<Size> >* sVtxVecVec,
                 std::vector<std::vector<Size> >* tVtxVecVec,
                 std::vector<std::vector<Val> >* sEdgWghtVecVec,
                 std::vector<std::vector<Val> >* tEdgWghtVecVec) const;

  ///
  Val rGetMatchedEdgWghtBnd(void) const;

  ///
  void rShiftEdgWghts(Val edgWghtShift) const;

friend class BptMatchingEngine;
friend class BptCanonicalEngine;
friend class BptEdgCovEngine;
friend class BptIndSetEngine;
friend class BptVtxCovEngine;
}; // class BptGraph

} // namespace Matchbox

#endif // BPT_GRAPH_H
