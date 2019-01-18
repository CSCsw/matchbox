#include "Stats.h"

using namespace std;
using namespace Matchbox;

void Stats::Print(const string& caller) const {
  assert(mCardVec.size() == mWghtVec.size());
  assert(mCardVec.size() == mNumGraphSrchsVec.size());
  assert(mCardVec.size() == mAggNumBfsVstdVtxsVec.size());
  assert(mCardVec.size() == mAggNumDfsVstdVtxsVec.size());
  assert(mCardVec.size() == mAggNumBfsVstdEdgsVec.size());
  assert(mCardVec.size() == mAggNumDfsVstdEdgsVec.size());
  assert(mCardVec.size() == mNumAugOpsVec.size());
  assert(mCardVec.size() == mNumRevOpsVec.size());
  assert(mCardVec.size() == mAggAugPathLenVec.size());
  assert(mCardVec.size() == mAggRevPathLenVec.size());
  assert(mCardVec.size() == mMinAugPathLenVec.size());
  assert(mCardVec.size() == mMinRevPathLenVec.size());
  assert(mCardVec.size() == mMaxAugPathLenVec.size());
  assert(mCardVec.size() == mMaxRevPathLenVec.size());
  assert(mCardVec.size() == mNumAugPathLensVec.size());
  assert(mCardVec.size() == mNumRevPathLensVec.size());
  cout << "((((((((((((((((((((((((((((((((((((((((((((((((((" << endl;
  cout << "Stats (begin)" << endl;
  cout << "caller = " << caller << endl;
  cout << "source side = " << ((mRvrs == false) ? "S" : "T") << endl;
  switch (mComputationType) {
  case eCard:
    cout << "computation type = cardinality" << endl;
    break;
  case eEdgWght:
    cout << "computation type = edge-weight" << endl;
    break;
  case eVtxWght:
    cout << "computation type = vertex-weight" << endl;
    break;
  default:
    assert(false);
  }
  Size numPhases = mCardVec.size();
  cout << "number of phases: " << numPhases << endl;
  for (Size i = 0; i < numPhases; ++i) {
    cout << "--------------------------------------------------" << endl;
    cout << "phase " << i + 1 << ":" << endl;
    cout << "cardinality = " << mCardVec[i] << endl;
    if (mComputationType != eCard) {
      //cout.setf(ios::left | ios::scientific | ios::showpoint);
      //cout.precision(16);
      cout << "weight = " << mWghtVec[i] << endl;
      //cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    }
    cout << "number of graph searches = " << mNumGraphSrchsVec[i] << endl;
    if (mNumGraphSrchsVec[i] > 0) {
      //cout.setf(ios::left | ios::scientific | ios::showpoint);
      //cout.precision(1);
      cout << "aggregated number of bfs visited vertices = "
           << mAggNumBfsVstdVtxsVec[i] << endl;
      cout << "aggregated number of dfs visited vertices = "
           << mAggNumDfsVstdVtxsVec[i] << endl;
      cout << "aggregated number of visited vertices = "
           << mAggNumBfsVstdVtxsVec[i] + mAggNumDfsVstdVtxsVec[i] << endl;
      cout << "average number of visited vertices per graph search = "
           << (mAggNumBfsVstdVtxsVec[i] + mAggNumDfsVstdVtxsVec[i]) /
              static_cast<LSize>(mNumGraphSrchsVec[i]) << endl;

      cout << "aggregated number of bfs visited edges = "
           << mAggNumBfsVstdEdgsVec[i] << endl;
      cout << "aggregated number of dfs visited edges = "
           << mAggNumDfsVstdEdgsVec[i] << endl;
      cout << "aggregated number of visited edges = "
           << mAggNumBfsVstdEdgsVec[i] + mAggNumDfsVstdEdgsVec[i] << endl;
      cout << "average number of visited edges per graph search = "
           << (mAggNumBfsVstdEdgsVec[i] + mAggNumDfsVstdEdgsVec[i]) /
              static_cast<LSize>(mNumGraphSrchsVec[i]) << endl;
      //cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    }
    cout << "number of augmenting operations = " << mNumAugOpsVec[i] << endl;
    if (mNumAugOpsVec[i] > 0) {
      cout << "aggregated augmenting path length = "
           << mAggAugPathLenVec[i] << endl;
      cout << "minimum augmenting path length = " << mMinAugPathLenVec[i]
           << endl;
      cout << "maximum augmenting path length = " << mMaxAugPathLenVec[i]
           << endl;
      cout << "number of distinct augmenting path lengths = "
           << mNumAugPathLensVec[i] << endl;
      //cout.setf(ios::left | ios::scientific | ios::showpoint);
      //cout.precision(1);
      cout << "average augmenting path length = "
           << mAggAugPathLenVec[i] / static_cast<LSize>(mNumAugOpsVec[i])
           << endl;
      cout << "average number of augmenting operations per distinct "
           << "augmenting path length = "
           << static_cast<LSize>(mNumAugOpsVec[i]) /
              static_cast<LSize>(mNumAugPathLensVec[i]) << endl;
      //cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    }
    cout << "number of reversing operations = " << mNumRevOpsVec[i] << endl;
    if (mNumRevOpsVec[i] > 0) {
      cout << "aggregated reversing path length = "
           << mAggRevPathLenVec[i] << endl;
      cout << "minimum reversing path length = " << mMinRevPathLenVec[i]
           << endl;
      cout << "maximum reversing path length = " << mMaxRevPathLenVec[i]
           << endl;
      cout << "number of distinct reversing path lengths = "
           << mNumRevPathLensVec[i] << endl;
      //cout.setf(ios::left | ios::scientific | ios::showpoint);
      //cout.precision(1);
      cout << "average reversing path length = "
           << mAggRevPathLenVec[i] / static_cast<LSize>(mNumRevOpsVec[i])
           << endl;
      cout << "average number of reversing operations per distinct "
           << "reversing path length = "
           << static_cast<LSize>(mNumRevOpsVec[i]) /
              static_cast<LSize>(mNumRevPathLensVec[i]) << endl;
      //cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    }
  }
  if (numPhases > 0) {
    cout << "--------------------------------------------------" << endl;
    cout << "overall:" << endl;
    Size numGraphSrchs =
      accumulate(mNumGraphSrchsVec.begin(), mNumGraphSrchsVec.end(), 0);
    LSize aggNumBfsVstdVtxs =
      accumulate(mAggNumBfsVstdVtxsVec.begin(), mAggNumBfsVstdVtxsVec.end(),
                 static_cast<LSize>(0));
    LSize aggNumDfsVstdVtxs =
      accumulate(mAggNumDfsVstdVtxsVec.begin(), mAggNumDfsVstdVtxsVec.end(),
                 static_cast<LSize>(0));
    LSize aggNumBfsVstdEdgs =
      accumulate(mAggNumBfsVstdEdgsVec.begin(), mAggNumBfsVstdEdgsVec.end(),
                 static_cast<LSize>(0));
    LSize aggNumDfsVstdEdgs =
      accumulate(mAggNumDfsVstdEdgsVec.begin(), mAggNumDfsVstdEdgsVec.end(),
                 static_cast<LSize>(0));
    cout << "number of graph searches = " << numGraphSrchs << endl;
    if (numGraphSrchs > 0) {
     // cout.setf(ios::left | ios::scientific | ios::showpoint);
     // cout.precision(1);
      cout << "aggregated number of bfs visited vertices = "
           << aggNumBfsVstdVtxs << endl;
      cout << "aggregated number of dfs visited vertices = "
           << aggNumDfsVstdVtxs << endl;
      cout << "aggregated number of visited vertices = "
           << aggNumBfsVstdVtxs + aggNumDfsVstdVtxs << endl;
      cout << "average number of visited vertices per graph search = "
           << (aggNumBfsVstdVtxs + aggNumDfsVstdVtxs) /
              static_cast<LSize>(numGraphSrchs) << endl;
      cout << "aggregated number of bfs visited edges = "
           << aggNumBfsVstdEdgs << endl;
      cout << "aggregated number of dfs visited edges = "
           << aggNumDfsVstdEdgs << endl;
      cout << "aggregated number of visited edges = "
           << aggNumBfsVstdEdgs + aggNumDfsVstdEdgs << endl;
      cout << "average number of visited edges per graph search = "
           << (aggNumBfsVstdEdgs + aggNumDfsVstdEdgs) /
              static_cast<LSize>(numGraphSrchs) << endl;
      //cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    }
    cout << "--------------------------------------------------" << endl;
  }
  cout << "Stats (end)" << endl;
  cout << "))))))))))))))))))))))))))))))))))))))))))))))))))" << endl;
}

void Stats::Resize(Size maxNumPhases) {
  ReserveVector<Size>(&mCardVec, maxNumPhases);
  ReserveVector<Val>(&mWghtVec, maxNumPhases);
  ReserveVector<Size>(&mNumGraphSrchsVec, maxNumPhases);
  ReserveVector<LSize>(&mAggNumBfsVstdVtxsVec, maxNumPhases);
  ReserveVector<LSize>(&mAggNumDfsVstdVtxsVec, maxNumPhases);
  ReserveVector<LSize>(&mAggNumBfsVstdEdgsVec, maxNumPhases);
  ReserveVector<LSize>(&mAggNumDfsVstdEdgsVec, maxNumPhases);
  ReserveVector<Size>(&mNumAugOpsVec, maxNumPhases);
  ReserveVector<Size>(&mNumRevOpsVec, maxNumPhases);
  ReserveVector<LSize>(&mAggAugPathLenVec, maxNumPhases);
  ReserveVector<LSize>(&mAggRevPathLenVec, maxNumPhases);
  ReserveVector<Size>(&mMinAugPathLenVec, maxNumPhases);
  ReserveVector<Size>(&mMinRevPathLenVec, maxNumPhases);
  ReserveVector<Size>(&mMaxAugPathLenVec, maxNumPhases);
  ReserveVector<Size>(&mMaxRevPathLenVec, maxNumPhases);
  ReserveVector<Size>(&mNumAugPathLensVec, maxNumPhases);
  ReserveVector<Size>(&mNumRevPathLensVec, maxNumPhases);
}

void Stats::Reset(Size maxNumPathLens) {
  mNumGraphSrchs = 0;
  mNumBfsVstdVtxs = 0;
  mNumDfsVstdVtxs = 0;
  mNumBfsVstdEdgs = 0;
  mNumDfsVstdEdgs = 0;
  mAggNumBfsVstdVtxs = static_cast<LSize>(0);
  mAggNumDfsVstdVtxs = static_cast<LSize>(0);
  mAggNumBfsVstdEdgs = static_cast<LSize>(0);
  mAggNumDfsVstdEdgs = static_cast<LSize>(0);
  mNumAugOps = 0;
  mNumRevOps = 0;
  mAggAugPathLen = static_cast<LSize>(0);
  mAggRevPathLen = static_cast<LSize>(0);
  mMinAugPathLen = 0;
  mMinRevPathLen = 0;
  mMaxAugPathLen = 0;
  mMaxRevPathLen = 0;
  mNumAugPathLens = 0;
  mNumRevPathLens = 0;
  ResizeVector<Size>(&mNumAugsPerAugPathLenVec, maxNumPathLens);
  fill(mNumAugsPerAugPathLenVec.begin(), mNumAugsPerAugPathLenVec.end(), 0);
  mNumAugsPerAugPathLenArr =
    (mNumAugsPerAugPathLenVec.empty() == true) ? NULL :
    &mNumAugsPerAugPathLenVec[0];
  ResizeVector<Size>(&mNumRevsPerRevPathLenVec, maxNumPathLens);
  fill(mNumRevsPerRevPathLenVec.begin(), mNumRevsPerRevPathLenVec.end(), 0);
  mNumRevsPerRevPathLenArr =
    (mNumRevsPerRevPathLenVec.empty() == true) ? NULL :
    &mNumRevsPerRevPathLenVec[0];
}

void Stats::ComputePathStats(Size* numAugPathLens, Size* minAugPathLen,
    Size* maxAugPathLen, Size* numRevPathLens, Size* minRevPathLen,
    Size* maxRevPathLen) const {
  *numAugPathLens = 0;
  *minAugPathLen = 0;
  *maxAugPathLen = 0;
  *numRevPathLens = 0;
  *minRevPathLen = 0;
  *maxRevPathLen = 0;
  for (Size l = 0; l < mNumAugsPerAugPathLenVec.size(); ++l) {
    if (mNumAugsPerAugPathLenArr[l] > 0) {
      ++(*numAugPathLens);
    }
  }
  for (Size l = 0; l < mNumAugsPerAugPathLenVec.size(); ++l) {
    if ((*minAugPathLen == 0) && (mNumAugsPerAugPathLenArr[l] > 0)) {
      *minAugPathLen = 2 * l + 1;
      break;
    }
  }
  for (Size lDmy = mNumAugsPerAugPathLenVec.size(); lDmy > 0; --lDmy) {
    Size l = lDmy - 1;
    if ((*maxAugPathLen == 0) && (mNumAugsPerAugPathLenArr[l] > 0)) {
      *maxAugPathLen = 2 * l + 1;
      break;
    }
  }
  for (Size l = 0; l < mNumRevsPerRevPathLenVec.size(); ++l) {
    if (mNumRevsPerRevPathLenArr[l] > 0) {
      ++(*numRevPathLens);
    }
  }
  for (Size l = 0; l < mNumRevsPerRevPathLenVec.size(); ++l) {
    if ((*minRevPathLen == 0) && (mNumRevsPerRevPathLenArr[l] > 0)) {
      *minRevPathLen = 2 * l;
      break;
    }
  }
  for (Size lDmy = mNumRevsPerRevPathLenVec.size(); lDmy > 0; --lDmy) {
    Size l = lDmy - 1;
    if ((*maxRevPathLen == 0) && (mNumRevsPerRevPathLenArr[l] > 0)) {
      *maxRevPathLen = 2 * l + 1;
      break;
    }
  }
}
