// List implementation of an indexed queue of items.

#ifndef LST_ITM_IDXD_QUE_H
#define LST_ITM_IDXD_QUE_H

#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class LstItmIdxdQue {
public:
  explicit LstItmIdxdQue(Size maxSize = 0): mMaxSize(maxSize), mSize(0),
      mItArr(NULL) {
    assert(mMaxSize < cInfSize);
    std::vector<std::list<Size>::iterator> tmpItVec;
    ResizeVector<std::list<Size>::iterator>(&tmpItVec, mMaxSize);
    mItVec.swap(tmpItVec);
    if (mMaxSize > 0) {
      mItArr = &mItVec[0];
    }
    if (mItArr != NULL) {
      std::fill(&mItArr[0], &mItArr[mMaxSize], mItmLst.end());
    }
  }

  ~LstItmIdxdQue() {}

  Size GetMaxSize(void) const { return mMaxSize; };

  Size GetSize(void) const { return mSize; };

  bool Empty(void) const { return (mSize == 0); };

  bool Full(void) const { return (mSize == mMaxSize); };

  void Push(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mItArr[itm] == mItmLst.end());
    mItArr[itm] = mItmLst.insert(mItmLst.end(), itm);
    ++mSize;
  }

  void Pop(void) {
    assert(mSize > 0);
    mItArr[mItmLst.front()] = mItmLst.end();
    mItmLst.pop_front();
    --mSize;
  }

  void Erase(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmLst.end());
    mItmLst.erase(mItArr[itm]);
    mItArr[itm] = mItmLst.end();
    --mSize;
  }

  const Size& Front(void) const {
    assert(mSize > 0);
    return mItmLst.front();
  }

  void Clear(void) {
    for (std::list<Size>::iterator it = mItmLst.begin(); it != mItmLst.end();
         ++it) {
      mItArr[*it] = mItmLst.end();
    }
    mItmLst.clear();
    mSize = 0;
  }

  Size First(void) const {
    if (mSize == 0) {
      return cNullItm;
    }
    return mItmLst.front();
  }

  Size Next(Size itm) const {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmLst.end());
    std::list<Size>::const_iterator it = mItArr[itm];
    if (++it == mItmLst.end()) {
      return cNullItm;
    }
    return *it;
  }

  Size Last(void) const {
    if (mSize == 0) {
      return cNullItm;
    }
    return mItmLst.back();
  }

  Size Previous(Size itm) const {
    assert(itm < mMaxSize);
    assert(mItArr[itm] != mItmLst.end());
    std::list<Size>::const_reverse_iterator it(mItArr[itm]);
    if (it == mItmLst.rend()) {
      return cNullItm;
    }
    return *it;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::vector<std::list<Size>::iterator> mItVec;
  std::list<Size>::iterator* mItArr;
  std::list<Size> mItmLst;
}; // class LstItmIdxdQue

} // namespace Matchbox

#endif // LST_ITM_IDXD_QUE_H
