// Vector implementation of a stack of items.

#ifndef VEC_ITM_STK_H
#define VEC_ITM_STK_H

#include <vector>
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ResizeVector.

namespace Matchbox {

class VecItmStk {
public:
  explicit VecItmStk(Size maxSize = 0): mMaxSize(maxSize), mSize(0),
      mItmArr(NULL) {
    assert(mMaxSize < cInfSize);
    std::vector<Size> tmpItmVec;
    ResizeVector<Size>(&tmpItmVec, mMaxSize);
    mItmVec.swap(tmpItmVec);
    if (mMaxSize > 0) {
      mItmArr = &mItmVec[0];
    }
  }

  ~VecItmStk() {}

  Size GetMaxSize(void) const { return mMaxSize; };

  Size GetSize(void) const { return mSize; };

  bool Empty(void) const { return (mSize == 0); };

  bool Full(void) const { return (mSize == mMaxSize); };

  void Push(const Size& itm) {
  	if(itm >= mMaxSize)
  	{
  		std::cout << "itm ="<<itm << " max size= "<<mMaxSize<<std::endl;
	  }
	  
	  if(mSize >= mMaxSize)
  	{
  		std::cout << "itm ="<<itm << " max size= "<<mMaxSize<<" msize "<<mSize<<std::endl;
	  }
    assert(itm < mMaxSize);
    assert(mSize < mMaxSize);
    mItmArr[mSize] = itm;
    ++mSize;
  }

  void Pop(void) {
    assert(mSize > 0);
    --mSize;
  }

  const Size& Top(void) const {
    assert(mSize > 0);
    return mItmArr[mSize - 1];
  }

  void Clear(void) {
    mSize = 0;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::vector<Size> mItmVec;
  Size* mItmArr;
}; // class VecItmStk

} // namespace Matchbox

#endif // VEC_ITM_STK_H
