// List implementation of an indexed priority queue of items and values.

#ifndef LST_ITM_AND_VAL_IDXD_MIN_PRI_QUE_H
#define LST_ITM_AND_VAL_IDXD_MIN_PRI_QUE_H

#include <vector>
#include <list>
#include <algorithm> // for fill.
#include <utility> // for pair.
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class LstItmAndValIdxdMinPriQue {
public:
  explicit LstItmAndValIdxdMinPriQue(Size maxSize = 0): mMaxSize(maxSize),
      mSize(0), mItArr(NULL) {
    assert(mMaxSize < cInfSize);
    std::vector<std::list<std::pair<Size, Val> >::iterator> tmpItVec;
    ResizeVector<std::list<std::pair<Size, Val> >::iterator>
      (&tmpItVec, mMaxSize);
    mItVec.swap(tmpItVec);
    if (mMaxSize > 0) {
      mItArr = &mItVec[0];
    }
    if (mItArr != NULL) {
      std::fill(&mItArr[0], &mItArr[mMaxSize], mItmAndValLst.end());
    }
  }

  ~LstItmAndValIdxdMinPriQue() {}

  Size GetMaxSize(void) const { return mMaxSize; };

  Size GetSize(void) const { return mSize; };

  bool Empty(void) const { return (mSize == 0); };

  bool Full(void) const { return (mSize == mMaxSize); };

  void Push(const Size& itm, const Val& val) {
    assert(itm < mMaxSize);
    assert(mItArr[itm] == mItmAndValLst.end());
    mItArr[itm] = mItmAndValLst.insert(mItmAndValLst.end(),
                                       std::pair<Size, Val>(itm, val));
    ++mSize;
  }

  void Pop(void) {
    assert(mSize > 0);
    std::list<std::pair<Size, Val> >::iterator topIt = mItmAndValLst.begin();
    std::list<std::pair<Size, Val> >::iterator it = topIt;
    for (++it; it != mItmAndValLst.end(); ++it) {
      if (it->second < topIt->second) {
        topIt = it;
      }
    }
    mItArr[topIt->first] = mItmAndValLst.end();
    mItmAndValLst.erase(topIt);
    --mSize;
  }

  void Erase(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmAndValLst.end());
    mItmAndValLst.erase(mItArr[itm]);
    mItArr[itm] = mItmAndValLst.end();
    --mSize;
  }

  void IncreasePriority(const Size& itm, const Val& val) {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmAndValLst.end());
    std::list<std::pair<Size, Val> >::iterator it = mItArr[itm];
    // relaxation from strict inequality assertion because, due to compiler
    // optimizations, the priority may not change at all if the difference
    // between the old and the new priority is very small.
    assert(val <= it->second);
    it->second = val;
  }

  const Size& Top(void) const {
    assert(mSize > 0);
    std::list<std::pair<Size, Val> >::const_iterator
      topIt = mItmAndValLst.begin();
    std::list<std::pair<Size, Val> >::const_iterator it = topIt;
    for (++it; it != mItmAndValLst.end(); ++it) {
      if (it->second < topIt->second) {
        topIt = it;
      }
    }
    return topIt->first;
  }

  const Size& Top(Val* val) const {
    assert(mSize > 0);
    std::list<std::pair<Size, Val> >::const_iterator
      topIt = mItmAndValLst.begin();
    std::list<std::pair<Size, Val> >::const_iterator it = topIt;
    for (++it; it != mItmAndValLst.end(); ++it) {
      if (it->second < topIt->second) {
        topIt = it;
      }
    }
    *val = topIt->second;
    return topIt->first;
  }

  void Clear(void) {
    for (std::list<std::pair<Size, Val> >::iterator
         it = mItmAndValLst.begin(); it != mItmAndValLst.end(); ++it) {
      mItArr[it->first] = mItmAndValLst.end();
    }
    mItmAndValLst.clear();
    mSize = 0;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::vector<std::list<std::pair<Size, Val> >::iterator> mItVec;
  std::list<std::pair<Size, Val> >::iterator* mItArr;
  std::list<std::pair<Size, Val> > mItmAndValLst;
}; // class LstItmAndValIdxdMinPriQue

} // namespace Matchbox

#endif // LST_ITM_AND_VAL_IDXD_MIN_PRI_QUE_H
