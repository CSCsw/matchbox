// List implementation of a stack of items.

#ifndef LST_ITM_STK_H
#define LST_ITM_STK_H

#include <list>
#include <cassert>

#include "Types.h"

namespace Matchbox {

class LstItmStk {
public:
  explicit LstItmStk(Size maxSize = 0): mMaxSize(maxSize), mSize(0) {
    assert(mMaxSize < cInfSize);
  }

  ~LstItmStk() {}

  Size GetMaxSize(void) const { return mMaxSize; };

  Size GetSize(void) const { return mSize; };

  bool Empty(void) const { return (mSize == 0); };

  bool Full(void) const { return (mSize == mMaxSize); };

  void Push(const Size& itm) {
    assert(itm < mMaxSize);
    assert(mSize < mMaxSize);
    mItmLst.push_back(itm);
    ++mSize;
  }

  void Pop(void) {
    assert(mSize > 0);
    mItmLst.pop_back();
    --mSize;
  }

  const Size& Top(void) const {
    assert(mSize > 0);
    return mItmLst.back();
  }

  void Clear(void) {
    mItmLst.clear();
    mSize = 0;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::list<Size> mItmLst;
}; // class LstItmStk

} // namespace Matchbox

#endif // LST_ITM_STK_H
