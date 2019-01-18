// List implementation of a queue of items.

#ifndef LST_ITM_QUE_H
#define LST_ITM_QUE_H

#include <list>
#include <cassert>

#include "Types.h"

namespace Matchbox {

class LstItmQue {
public:
  explicit LstItmQue(Size maxSize = 0): mMaxSize(maxSize), mSize(0) {
    assert(mMaxSize < cInfSize);
  }

  ~LstItmQue() {}

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
    mItmLst.pop_front();
    --mSize;
  }

  const Size& Front(void) const {
    assert(mSize > 0);
    return mItmLst.front();
  }

  void Clear(void) {
    mItmLst.clear();
    mSize = 0;
  }

private:
  Size mMaxSize;
  Size mSize;
  std::list<Size> mItmLst;
}; // class LstItmQue

} // namespace Matchbox

#endif // LST_ITM_QUE_H
