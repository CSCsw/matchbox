#ifndef TYPES_H
#define TYPES_H

//#include <vector>
#include <limits>

namespace Matchbox {

// the actual type of size_t is platform-dependent. a common mistake is to
// assume size_t is the same as unsigned int, which can lead to programming
// errors, when moving from a 32-bit to a 64-bit architecture, for example.
// according to the 1999 ISO C standard (C99), size_t is an unsigned integer
// type of at least 16 bits.

// Size is required to be an unsigned integer type. Size it used for sizes as
// well as for items. an item's value can be at most the next to the value of
// the corresponding size.
typedef std::size_t Size;
//typedef std::vector<int>::size_type Size

typedef double LSize;

// Val is required to be a floating point type.
typedef double Val;


enum Err {
  eErrNone = 0,
  eErrInvNumVtxs,
  eErrInvNumEdgs,
  eErrInvVtx,
  eErrInvWght,
  eErrInvMatching,
  eErrInvInput,
  eErrFileOpen,
  eErrInvFile,
  eErrInvType,
  eErrInvPrecision,
  eErrNotSymmetrizable,
  eErrNoPrfMatching
};

enum QueAndStkType {
  eVecQueAndStk = 0,
  eLstQueAndStk
};

enum IdxdQueType {
  eLstIdxdQue = 0
};

enum IdxdPriQueType {
  eLstIdxdPriQue = 0,
  eBhpIdxdPriQue,
  eFhpIdxdPriQue
};

enum ComputationType {
  eCard = 0,
  eEdgWght,
  eVtxWght
};

// TODE: revisit the comment below, as the number of types has increased.
// all three graph search types can be used for cardinality and edge-weight
// matching computations. for vertex-weight matching computations only the
// single source graph search can be used.

enum GraphSrchType {
  eSglSrcBfs = 0,
  eSglSrcDfs,
  eSglSrcDfsLkhd,
  eMplSrcSglPath,
  eMplPathDfs,
  eMplPathDfsLkhd,
  eMplPathBfsDfs
};

enum VtxWghtAlgType {
  eDrct = 0,
  eSpcl
};

enum Stt {
  eSttIdle = 0,
  eSttBfsPrcsb,
  eSttBfsPrcsd,
  eSttDfsPrcsb,
  eSttDfsPrcsd,
  eSttLast
};

// a special Size value cInfSize is required as an exclusive upper bound for
// any value of type Size. cInfSize is set as the maximum value that can be
// represented by Size.
const Size cInfSize = std::numeric_limits<Size>::max();;

// a special value cNullItm is required for any situation in which an item is
// missing. cNullItm is set as the next to the maximum value that can be
// represented by Size.
const Size cNullItm = std::numeric_limits<Size>::max() - 1;

// TODO: describe cZeroVal, cPosOneVal, cPosInfVal, cNegOneVal.
const Val cZeroVal = static_cast<Val>(0.0);
const Val cPosOneVal = static_cast<Val>(1.0);
const Val cPosInfVal = cPosOneVal / cZeroVal;
const Val cNegInfVal = -cPosInfVal;

const Size cMaxPrecision = 16;

} // namespace Matchbox

#endif // TYPES_H
