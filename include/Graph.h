#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm> // for fill, copy, find_if, adjacent_find.
#include <functional> // for less, greater_equal, bind2nd.
#include <cassert>
#include <sstream>

#include "Functional.h"
#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class Graph {
public:
  /// Constructor.
  Graph():
      mInitErr(eErrNone), mNumVtxs(0), mNumEdgs(0), mPrecision(cMaxPrecision),
      mFullPrint(false) {}

  /// Constructor.
  /// loop and duplicate edges allowed in the input, they are removed
  /// internally. duplicate removal is performed by preserving the first edge
  /// out of a group.
  Graph(Size numVtxs,
        Size numEdgs,
        const std::vector<Size>& sVtxVec,
        const std::vector<Size>& tVtxVec,
        const std::vector<Val>& edgWghtVec):
      mInitErr(eErrNone), mNumVtxs(0), mNumEdgs(0), mPrecision(cMaxPrecision),
      mFullPrint(false) {
    mInitErr = Set(numVtxs, numEdgs, sVtxVec, tVtxVec, edgWghtVec);
  }

  /// Destructor.
  ~Graph() {}

  ///
  void GetInitErr(Err* initErr) const { *initErr = mInitErr; }

  ///
  void GetNumVtxs(Size* numVtxs) const { *numVtxs = mNumVtxs; }

  ///
  void GetNumEdgs(Size* numEdgs) const { *numEdgs = mNumEdgs; }

  ///
  void GetSize(Size* numVtxs,
               Size* numEdgs) const {
    *numVtxs = mNumVtxs;
    *numEdgs = mNumEdgs;
  }

  ///
  void GetEdgs(std::vector<Size>* sVtxVec,
               std::vector<Size>* tVtxVec,
               std::vector<Val>* edgWghtVec) const;

  ///
  Err GetAdj(Size vtx,
             Size* numEdgs,
             std::vector<Size>* vtxVec,
             std::vector<Val>* edgWghtVec) const;

  ///
  void GetVtxWghts(std::vector<Val>* vtxWghtVec) const;

  ///
  void GetVtxDgrs(std::vector<Size>* vtxDgrVec) const;

  ///
  void Get(Size* numVtxs,
           Size* numEdgs,
           std::vector<Size>* sVtxVec,
           std::vector<Size>* tVtxVec,
           std::vector<Val>* edgWghtVec) const {
    GetSize(numVtxs, numEdgs);
    GetEdgs(sVtxVec, tVtxVec, edgWghtVec);
  }

  ///
  void Print(void) const;

  ///
  void Clear(void) {
    mNumVtxs = 0;
    mNumEdgs = 0;
    ResizeVector<std::vector<Size> >(&mVtxVecVec, 0);
    ResizeVector<std::vector<Val> >(&mEdgWghtVecVec, 0);
    ResizeVector<Val>(&mVtxWghtVec, 0);
  }

  ///
  /// loop and duplicate edges allowed in the input, they are removed
  /// internally. duplicate removal is performed by preserving the first edge
  /// out of a group.
  Err Set(Size numVtxs,
          Size numEdgs,
          const std::vector<Size>& sVtxVec,
          const std::vector<Size>& tVtxVec,
          const std::vector<Val>& edgWghtVec);

  ///
  Err SetVtxWghts(const std::vector<Val>& vtxWghtVec);

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
  Err ReadWeights(const std::string& fileName,
           bool zeroBased = false);
   

	void SortAdjByVtxWghts(void);
private:
  // stores constructor errors.
  Err mInitErr;
  // the number of vertices.
  Size mNumVtxs;
  // the number of edges.
  Size mNumEdgs;
  // the adjacencies: the vertices.
  mutable std::vector<std::vector<Size> > mVtxVecVec;
  // TODO: add comment that explains why mutable.
  // the adjacencies: the edge weights.
  mutable std::vector<std::vector<Val> > mEdgWghtVecVec;
  // the vertex weights.
  std::vector<Val> mVtxWghtVec;
  // the precision used for printing floating point numbers.
  Size mPrecision;
  // controls the amount of printing: if false then print less information,
  // if true then print more information.
  bool mFullPrint;

  // forbid the copy constructor and the assignment operator.
  Graph(const Graph&);
  Graph& operator=(const Graph&);

  // sort the adjacencies.
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // postconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  ///
  void rSortAdjs(Size numVtxs,
                 std::vector<std::vector<Size> >* vtxVecVec,
                 std::vector<std::vector<Val> >* edgWghtVecVec,
                 bool doubleStorage) const;

	
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // postconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // - the adjacencies do not store duplicate edges
  ///
  void rRemoveDupEdgs(Size numVtxs,
                      Size* numEdgs,
                      std::vector<std::vector<Size> >* vtxVecVec,
                      std::vector<std::vector<Val> >* edgWghtVecVec) const;

  // check if there are no duplicate edges.
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // returns success value:
  // - true if the adjacencies do not store duplicate edges.
  // - false otherwise.
  ///
  bool rCheckNoDupEdgs(Size numVtxs,
                       const std::vector<std::vector<Size> >& vtxVecVec) const;

  // form the adjacencies from the set of edges.
  // preconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // postconditions:
  // - the number of vertices and the number of edges are within the allowed
  // range
  // - every vertex is within the allowed range
  // - every edge weight is within the allowed range
  // - the adjacencies are sorted
  // - the adjacencies do not store duplicate edges
  // - the adjacencies double store edges correctly
  ///
  void rFormAdjs(Size* numVtxs,
                 Size* numEdgs,
                 const std::vector<Size>& sVtxVec,
                 const std::vector<Size>& tVtxVec,
                 const std::vector<Val>& edgWghtVec,
                 std::vector<std::vector<Size> >* vtxVecVec,
                 std::vector<std::vector<Val> >* edgWghtVecVec) const;
  ///
  /// TODO: add code.
  //Val rGetMatchedEdgWghtBnd(void) const;

  ///
  /// TODO: add code.
  //void rShiftEdgWghts(Val edgWghtShift) const;

friend class MatchingEngine;
}; // class Graph

} // namespace Matchbox

#endif // GRAPH_H
