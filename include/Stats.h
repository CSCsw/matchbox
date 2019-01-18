#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <vector>
#include <algorithm> // for fill.
#include <numeric> // for accumulate.
#include <cassert>

#include "Types.h"
#include "Utility.h" // for ReserveVector, ResizeVector.

namespace Matchbox {

class Stats {
public:
  /// Constructor.
  Stats():
      mNumGraphSrchs(0), mNumBfsVstdVtxs(0), mNumDfsVstdVtxs(0),
      mNumBfsVstdEdgs(0), mNumDfsVstdEdgs(0),
      mAggNumBfsVstdVtxs(static_cast<LSize>(0)),
      mAggNumDfsVstdVtxs(static_cast<LSize>(0)),
      mAggNumBfsVstdEdgs(static_cast<LSize>(0)),
      mAggNumDfsVstdEdgs(static_cast<LSize>(0)), mNumAugOps(0),
      mNumRevOps(0), mAggAugPathLen(static_cast<LSize>(0)),
      mAggRevPathLen(static_cast<LSize>(0)), mMinAugPathLen(0),
      mMinRevPathLen(0), mMaxAugPathLen(0), mMaxRevPathLen(0),
      mNumAugPathLens(0), mNumRevPathLens(0), mRvrs(false),
      mComputationType(eCard) {}

  /// Destructor.
  ~Stats() {}

  ///
  void Print(const std::string& caller) const;

  ///
  void Resize(Size maxNumPhases);

  ///
  void Reset(Size maxNumPathLens);

  ///
  void ComputePathStats(Size* numAugPathLens,
                        Size* minAugPathLen,
                        Size* maxAugPathLen,
                        Size* numRevPathLens,
                        Size* minRevPathLen,
                        Size* maxRevPathLen) const;

public:
  Size mNumGraphSrchs;
  Size mNumBfsVstdVtxs;
  Size mNumDfsVstdVtxs;
  Size mNumBfsVstdEdgs;
  Size mNumDfsVstdEdgs;
  LSize mAggNumBfsVstdVtxs;
  LSize mAggNumDfsVstdVtxs;
  LSize mAggNumBfsVstdEdgs;
  LSize mAggNumDfsVstdEdgs;
  Size mNumAugOps;
  Size mNumRevOps;
  LSize mAggAugPathLen;
  LSize mAggRevPathLen;
  Size mMinAugPathLen;
  Size mMinRevPathLen;
  Size mMaxAugPathLen;
  Size mMaxRevPathLen;
  Size mNumAugPathLens;
  Size mNumRevPathLens;
  std::vector<Size> mNumAugsPerAugPathLenVec;
  Size* mNumAugsPerAugPathLenArr;
  std::vector<Size> mNumRevsPerRevPathLenVec;
  Size* mNumRevsPerRevPathLenArr;
  bool mRvrs;
  ComputationType mComputationType;
  std::vector<Size> mCardVec;
  std::vector<Val> mWghtVec;
  std::vector<Size> mNumGraphSrchsVec;
  std::vector<LSize> mAggNumBfsVstdVtxsVec;
  std::vector<LSize> mAggNumDfsVstdVtxsVec;
  std::vector<LSize> mAggNumBfsVstdEdgsVec;
  std::vector<LSize> mAggNumDfsVstdEdgsVec;
  std::vector<Size> mNumAugOpsVec;
  std::vector<Size> mNumRevOpsVec;
  std::vector<LSize> mAggAugPathLenVec;
  std::vector<LSize> mAggRevPathLenVec;
  std::vector<Size> mMinAugPathLenVec;
  std::vector<Size> mMinRevPathLenVec;
  std::vector<Size> mMaxAugPathLenVec;
  std::vector<Size> mMaxRevPathLenVec;
  std::vector<Size> mNumAugPathLensVec;
  std::vector<Size> mNumRevPathLensVec;
}; // class Stats

} // namespace Matchbox

#endif // STATS_H
