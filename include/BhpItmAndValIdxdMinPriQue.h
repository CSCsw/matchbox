// Binary heap implementation of an indexed priority queue of items and values.

#ifndef BHP_ITM_AND_VAL_IDXD_MIN_PRI_QUE_H
#define BHP_ITM_AND_VAL_IDXD_MIN_PRI_QUE_H

#include <vector>
#include <algorithm> // for swap, fill.
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class BhpItmAndValIdxdMinPriQue {
public:
  explicit BhpItmAndValIdxdMinPriQue(Size maxSize = 0): mMaxSize(maxSize),
      mSize(0), mIdxArr(NULL), mItmArr(NULL), mValArr(NULL) {
    assert(mMaxSize < cInfSize);
    std::vector<Size> tmpIdxVec;
    ResizeVector<Size>(&tmpIdxVec, mMaxSize);
    mIdxVec.swap(tmpIdxVec);
    if (mMaxSize > 0) {
      mIdxArr = &mIdxVec[0];
    }
    if (mIdxArr != NULL) {
      std::fill(&mIdxArr[0], &mIdxArr[mMaxSize], cNullItm);
    }
    std::vector<Size> tmpItmVec;
    ResizeVector<Size>(&tmpItmVec, mMaxSize);
    mItmVec.swap(tmpItmVec);
    if (mMaxSize > 0) {
      mItmArr = &mItmVec[0];
    }
    std::vector<Val> tmpValVec;
    ResizeVector<Val>(&tmpValVec, mMaxSize);
    mValVec.swap(tmpValVec);
    if (mMaxSize > 0) {
      mValArr = &mValVec[0];
    }
  }

  ~BhpItmAndValIdxdMinPriQue() {}

  Size GetMaxSize(void) const { return mMaxSize; };

  Size GetSize(void) const { return mSize; };

  bool Empty(void) const { return (mSize == 0); };

  bool Full(void) const { return (mSize == mMaxSize); };

  void Push(const Size& itm, const Val& val) {
    assert(itm < mMaxSize);
    assert(mIdxArr[itm] == cNullItm);
    mIdxArr[itm] = mSize;
    mItmArr[mSize] = itm;
    mValArr[mSize] = val;
    ++mSize;
    HeapifyUp(mSize - 1);
  }

  void Pop(void) {
    assert(mSize > 0);
    mIdxArr[mItmArr[0]] = cNullItm;
    --mSize;
    if (mSize > 0) {
      mItmArr[0] = mItmArr[mSize];
      mValArr[0] = mValArr[mSize];
      mIdxArr[mItmArr[0]] = 0;
      HeapifyDown(0);
    }
  }

  void Erase(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mIdxArr[itm] != cNullItm);
    Size idx = mIdxArr[itm];
    mIdxArr[itm] = cNullItm;
    --mSize;
    if (mSize > idx) {
      mItmArr[idx] = mItmArr[mSize];
      mValArr[idx] = mValArr[mSize];
      mIdxArr[mItmArr[idx]] = idx;
      HeapifyDown(idx);
      HeapifyUp(idx);
    }
  }

  void IncreasePriority(const Size& itm, const Val& val) {
    assert(itm < mMaxSize);
    assert(mIdxArr[itm] != cNullItm);
    Size idx = mIdxArr[itm];
    // relaxation from strict inequality assertion because, due to compiler
    // optimizations, the priority may not change at all if the change is very
    // small.
    assert(val <= mValArr[idx]);
    mValArr[idx] = val;
    HeapifyUp(idx);
  }

  const Size& Top(void) const {
    assert(mSize > 0);
    return mItmArr[0];
  }

  const Size& Top(Val* val) const {
    assert(mSize > 0);
    *val = mValArr[0];
    return mItmArr[0];
  }

  void Clear(void) {
    for (Size idx = 0; idx < mSize; ++idx) {
      mIdxArr[mItmArr[idx]] = cNullItm;
    }
    mSize = 0;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::vector<Size> mIdxVec;
  Size* mIdxArr;
  std::vector<Size> mItmVec;
  Size* mItmArr;
  std::vector<Val> mValVec;
  Val* mValArr;

  void HeapifyUp(Size idx) {
    while (idx > 0) {
      Size prntIdx = (idx + 1) / 2 - 1;
      if (mValArr[idx] >= mValArr[prntIdx]) {
        break;
      }
      Size itm = mItmArr[idx];
      Size prntItm = mItmArr[prntIdx];
      std::swap(mIdxArr[itm], mIdxArr[prntItm]);
      std::swap(mItmArr[idx], mItmArr[prntIdx]);
      std::swap(mValArr[idx], mValArr[prntIdx]);
      idx = prntIdx;
    }
  }

  void HeapifyDown(Size idx) {
    do {
      Size bestIdx = idx;
      Size lftChldIdx = 2 * idx + 1;
      Size rgtChldIdx = 2 * idx + 2;
      if ((lftChldIdx < mSize) && (mValArr[lftChldIdx] < mValArr[bestIdx])) {
        bestIdx = lftChldIdx;
      }
      if ((rgtChldIdx < mSize) && (mValArr[rgtChldIdx] < mValArr[bestIdx])) {
        bestIdx = rgtChldIdx;
      }
      if (bestIdx == idx) {
        break;
      }
      Size itm = mItmArr[idx];
      Size bestItm = mItmArr[bestIdx];
      std::swap(mIdxArr[itm], mIdxArr[bestItm]);
      std::swap(mItmArr[idx], mItmArr[bestIdx]);
      std::swap(mValArr[idx], mValArr[bestIdx]);
      idx = bestIdx;
    } while (true);
  }
}; // class BhpItmAndValIdxdMinPriQue

} // namespace Matchbox

#endif // BHP_ITM_AND_VAL_IDXD_MIN_PRI_QUE_H
