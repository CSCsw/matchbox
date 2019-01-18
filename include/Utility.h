#ifndef UTILITY_H
#define UTILITY_H

#include <vector>

#include <Types.h>

namespace Matchbox {

template<class T>
inline void ReserveVector(std::vector<T>* vec, Size size) {
  std::vector<T> tmpVec;
  tmpVec.reserve(size);
  vec->swap(tmpVec);
}

template<class T>
inline void ResizeVector(std::vector<T>* vec, Size size) {
  std::vector<T> tmpVec;
  tmpVec.reserve(size);
  tmpVec.resize(size);
  vec->swap(tmpVec);
}

inline bool CanAdd(Size a, Size b) {
 if (a >= cInfSize - b) {
    return false;
  }
  return true;
}

inline bool CanMultiply(Size a, Size b) {
  if ((b > 0) &&
      ((a > cInfSize / b) || ((a == cInfSize / b) && (cInfSize % b == 0)))) {
    return false;
  }
  return true;
}

} // namespace Matchbox

#endif // UTILITY_H
