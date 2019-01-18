// List implementation of an indexed queue of items and values.

#ifndef LST_ITM_AND_VAL_IDXD_QUE_H
#define LST_ITM_AND_VAL_IDXD_QUE_H

#include <vector>
#include <list>
#include <algorithm> // for fill.
#include <utility> // for pair.
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class LstItmAndValIdxdQue {
public:
  explicit LstItmAndValIdxdQue(Size maxSize = 0): mMaxSize(maxSize), mSize(0),
      mItArr(NULL) {
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

  ~LstItmAndValIdxdQue() {}

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
    mItArr[mItmAndValLst.front()] = mItmAndValLst.end();
    mItmAndValLst.pop_front();
    --mSize;
  }

  void Erase(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmAndValLst.end());
    mItmAndValLst.erase(mItArr[itm]);
    mItArr[itm] = mItmAndValLst.end();
    --mSize;
  }

  const Size& Front(void) const {
    assert(mSize > 0);
    return mItmAndValLst.front().first;
  }

  const Size& Front(Val* val) const {
    assert(mSize > 0);
    *val = mItmAndValLst.front().second;
    return mItmAndValLst.front().first;
  }

  const Val& GetVal(const Size& itm) const {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmAndValLst.end());
    return mItArr[itm]->second;
  }

  void Clear(void) {
    for (std::list<std::pair<Size, Val> >::iterator
         it = mItmAndValLst.begin(); it != mItmAndValLst.end(); ++it) {
      mItArr[it->first] = mItmAndValLst.end();
    }
    mItmAndValLst.clear();
    mSize = 0;
  }

  Size First(void) const {
    if (mSize == 0) {
      return cNullItm;
    }
    return mItmAndValLst.front().first;
  }

  Size Next(Size itm) const {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmAndValLst.end());
    std::list<std::pair<Size, Val> >::const_iterator it = mItArr[itm];
    if (++it == mItmAndValLst.end()) {
      return cNullItm;
    }
    return it->first;
  }

  Size Last(void) const {
    if (mSize == 0) {
      return cNullItm;
    }
    return mItmAndValLst.back().first;
  }

  Size Previous(Size itm) const {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmAndValLst.end());
    std::list<std::pair<Size, Val> >::const_reverse_iterator it(mItArr[itm]);
    if (it == mItmAndValLst.rend()) {
      return cNullItm;
    }
    return it->first;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::vector<std::list<std::pair<Size, Val> >::iterator> mItVec;
  std::list<std::pair<Size, Val> >::iterator* mItArr;
  std::list<std::pair<Size, Val> > mItmAndValLst;
}; // class LstItmAndValIdxdQue

} // namespace Matchbox

#endif // LST_ITM_AND_VAL_IDXD_QUE_H
