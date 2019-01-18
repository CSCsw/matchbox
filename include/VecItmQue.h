// Vector implementation of a queue of items.

#ifndef VEC_ITM_QUE_H
#define VEC_ITM_QUE_H

#include <vector>
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class VecItmQue {
public:
  explicit VecItmQue(Size maxSize = 0): mMaxSize(maxSize), mSize(0), mFront(0),
      mBack(0), mItmArr(NULL) {
    assert(mMaxSize < cInfSize);
    std::vector<Size> tmpItmVec;
    ResizeVector<Size>(&tmpItmVec, mMaxSize);
    mItmVec.swap(tmpItmVec);
    if (mMaxSize > 0) {
      mItmArr = &mItmVec[0];
    }
  }

  ~VecItmQue() {}

  Size GetMaxSize(void) const { return mMaxSize; };

  Size GetSize(void) const { return mSize; };

  bool Empty(void) const { return (mSize == 0); };

  bool Full(void) const { return (mSize == mMaxSize); };

  void Push(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mSize < mMaxSize);
    mItmArr[mBack] = itm;
    if (mBack < mMaxSize - 1) {
      ++mBack;
    } else {
      mBack = 0;
    }
    ++mSize;
  }

  void Pop(void) {
    assert(mSize > 0);
    if (mFront < mMaxSize - 1) {
      ++mFront;
    } else {
      mFront = 0;
    }
    --mSize;
  }

  const Size& Front(void) const {
    assert(mSize > 0);
    return mItmArr[mFront];
  }

  void Clear(void) {
    mFront = 0;
    mBack = 0;
    mSize = 0;
  }
  
  Size getmBack(void) {
    return mBack;
  }
  
   Size getmFront(void) {
    return mFront;
  }
  
  Size At(Size i)
  {
  	return mItmArr[i];
  }
   
private:
  Size mMaxSize;
  Size mSize;
  Size mFront;
  Size mBack;
  std::vector<Size> mItmVec;
  Size* mItmArr;
}; // class VecItmQue

} // namespace Matchbox

#endif // VEC_ITM_QUE_H
