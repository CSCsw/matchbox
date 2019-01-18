#include "BptCanonicalEngine.h"

using namespace std;
using namespace Matchbox;

const Size BptCanonicalEngine::cNumCoarseCmpnts = 3;

void BptCanonicalEngine::PartitionCoarse(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec,
    vector<CoarseType>* sCoarseVec, vector<CoarseType>* tCoarseVec,
    Size* sNumHrzVtxs, Size* tNumHrzVtxs, Size* sNumSqrVtxs, Size* tNumSqrVtxs,
    Size* sNumVrtVtxs, Size* tNumVrtVtxs) const {
  // TODO: check validity of matching.
  // reset output.
  ResizeVector<CoarseType>(sCoarseVec, 0);
  ResizeVector<CoarseType>(tCoarseVec, 0);
  *sNumHrzVtxs = 0;
  *tNumHrzVtxs = 0;
  *sNumSqrVtxs = 0;
  *tNumSqrVtxs = 0;
  *sNumVrtVtxs = 0;
  *tNumVrtVtxs = 0;
  const Size* sMateArr = (graph.mSNumVtxs == 0) ? NULL : &sMateVec[0];
  const Size* tMateArr = (graph.mTNumVtxs == 0) ? NULL : &tMateVec[0];
  vector<CoarseType> tmpSCoarseVec;
  ResizeVector<CoarseType>(&tmpSCoarseVec, graph.mSNumVtxs);
  CoarseType*
    tmpSCoarseArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSCoarseVec[0];
  vector<CoarseType> tmpTCoarseVec;
  ResizeVector<CoarseType>(&tmpTCoarseVec, graph.mTNumVtxs);
  CoarseType*
    tmpTCoarseArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTCoarseVec[0];
  Size tmpSNumHrzVtxs = 0;
  Size tmpTNumHrzVtxs = 0;
  Size tmpSNumSqrVtxs = 0;
  Size tmpTNumSqrVtxs = 0;
  Size tmpSNumVrtVtxs = 0;
  Size tmpTNumVrtVtxs = 0;
  switch (mQueAndStkType) {
  case eVecQueAndStk:
    rPartitionCoarse<VecItmQue>
      (graph, sMateArr, tMateArr, tmpSCoarseArr, tmpTCoarseArr,
       &tmpSNumHrzVtxs, &tmpTNumHrzVtxs, &tmpSNumSqrVtxs, &tmpTNumSqrVtxs,
       &tmpSNumVrtVtxs, &tmpTNumVrtVtxs);
    break;
  case eLstQueAndStk:
    rPartitionCoarse<LstItmQue>
      (graph, sMateArr, tMateArr, tmpSCoarseArr, tmpTCoarseArr,
       &tmpSNumHrzVtxs, &tmpTNumHrzVtxs, &tmpSNumSqrVtxs, &tmpTNumSqrVtxs,
       &tmpSNumVrtVtxs, &tmpTNumVrtVtxs);
    break;
  default:
    assert(false);
  }
  // set output.
  sCoarseVec->swap(tmpSCoarseVec);
  tCoarseVec->swap(tmpTCoarseVec);
  *sNumHrzVtxs = tmpSNumHrzVtxs;
  *tNumHrzVtxs = tmpTNumHrzVtxs;
  *sNumSqrVtxs = tmpSNumSqrVtxs;
  *tNumSqrVtxs = tmpTNumSqrVtxs;
  *sNumVrtVtxs = tmpSNumVrtVtxs;
  *tNumVrtVtxs = tmpTNumVrtVtxs;
}

void BptCanonicalEngine::PartitionCoarse(const BptGraph& graph,
    vector<CoarseType>* sCoarseVec, vector<CoarseType>* tCoarseVec,
    Size* sNumHrzVtxs, Size* tNumHrzVtxs, Size* sNumSqrVtxs, Size* tNumSqrVtxs,
    Size* sNumVrtVtxs, Size* tNumVrtVtxs) const {
  BptMatchingEngine matchingEngine;
  matchingEngine.SetInlz(mInlz);
  matchingEngine.SetQueAndStkType(mQueAndStkType);
  matchingEngine.SetIdxdQueType(mIdxdQueType);
  matchingEngine.SetCardGraphSrchType(mCardGraphSrchType);
  matchingEngine.SetPrecision(mPrecision);
  matchingEngine.SetStatsPrint(mStatsPrint);
  vector<Size> sMateVec;
  vector<Size> tMateVec;
  Size card = 0;
  matchingEngine.ComputeMaxCardMatching(graph, &sMateVec, &tMateVec, &card);
  PartitionCoarse
    (graph, sMateVec, tMateVec, sCoarseVec, tCoarseVec, sNumHrzVtxs,
     tNumHrzVtxs, sNumSqrVtxs, tNumSqrVtxs, sNumVrtVtxs, tNumVrtVtxs);
}

void BptCanonicalEngine::PartitionMedium(const BptGraph& graph,
    const vector<CoarseType>& sCoarseVec, const vector<CoarseType>& tCoarseVec,
    vector<Size>* sMediumVec, vector<Size>* tMediumVec,
    Size* numHrzMediumCmpnts, Size* numSqrMediumCmpnts,
    Size* numVrtMediumCmpnts) const {
  // reset output.
  ResizeVector<Size>(sMediumVec, 0);
  ResizeVector<Size>(tMediumVec, 0);
  *numHrzMediumCmpnts = 0;
  *numSqrMediumCmpnts = 0;
  *numVrtMediumCmpnts = 0;
  const CoarseType*
    sCoarseArr = (graph.mSNumVtxs == 0) ? NULL : &sCoarseVec[0];
  const CoarseType*
    tCoarseArr = (graph.mTNumVtxs == 0) ? NULL : &tCoarseVec[0];
  vector<Size> tmpSMediumVec;
  ResizeVector<Size>(&tmpSMediumVec, graph.mSNumVtxs);
  Size* tmpSMediumArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMediumVec[0];
  vector<Size> tmpTMediumVec;
  ResizeVector<Size>(&tmpTMediumVec, graph.mTNumVtxs);
  Size* tmpTMediumArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMediumVec[0];
  Size tmpNumHrzMediumCmpnts = 0;
  Size tmpNumSqrMediumCmpnts = 0;
  Size tmpNumVrtMediumCmpnts = 0;
  switch (mQueAndStkType) {
  case eVecQueAndStk:
    rPartitionMedium<VecItmQue>
      (graph, sCoarseArr, tCoarseArr, tmpSMediumArr, tmpTMediumArr,
       &tmpNumHrzMediumCmpnts, &tmpNumSqrMediumCmpnts, &tmpNumVrtMediumCmpnts);
    break;
  case eLstQueAndStk:
    rPartitionMedium<LstItmQue>
      (graph, sCoarseArr, tCoarseArr, tmpSMediumArr, tmpTMediumArr,
       &tmpNumHrzMediumCmpnts, &tmpNumSqrMediumCmpnts, &tmpNumVrtMediumCmpnts);
    break;
  default:
    assert(false);
  }
  // set output.
  sMediumVec->swap(tmpSMediumVec);
  tMediumVec->swap(tmpTMediumVec);
  *numHrzMediumCmpnts = tmpNumHrzMediumCmpnts;
  *numSqrMediumCmpnts = tmpNumSqrMediumCmpnts;
  *numVrtMediumCmpnts = tmpNumVrtMediumCmpnts;
}

void BptCanonicalEngine::PartitionFine(const BptGraph& graph,
    const vector<Size>& tMateVec, const vector<CoarseType>& tCoarseVec,
    const vector<Size>& tMediumVec, Size numSqrMediumCmpnts,
    vector<Size>* sFineVec, vector<Size>* tFineVec, Size* numSqrFineCmpnts)
    const {
  // reset output.
  ResizeVector<Size>(sFineVec, 0);
  ResizeVector<Size>(tFineVec, 0);
  *numSqrFineCmpnts = 0;
  const Size* tMateArr = (graph.mTNumVtxs == 0) ? NULL : &tMateVec[0];
  const CoarseType*
    tCoarseArr = (graph.mTNumVtxs == 0) ? NULL : &tCoarseVec[0];
  const Size* tMediumArr = (graph.mTNumVtxs == 0) ? NULL : &tMediumVec[0];
  vector<Size> tmpSFineVec;
  ResizeVector<Size>(&tmpSFineVec, graph.mSNumVtxs);
  Size* tmpSFineArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSFineVec[0];
  vector<Size> tmpTFineVec;
  ResizeVector<Size>(&tmpTFineVec, graph.mTNumVtxs);
  Size* tmpTFineArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTFineVec[0];
  Size tmpNumSqrFineCmpnts = 0;
  switch (mQueAndStkType) {
  case eVecQueAndStk:
    rPartitionFine<VecItmQue, VecItmStk>
      (graph, tMateArr, tCoarseArr, tMediumArr, numSqrMediumCmpnts,
       tmpSFineArr, tmpTFineArr, &tmpNumSqrFineCmpnts);
    break;
  case eLstQueAndStk:
    rPartitionFine<VecItmQue, LstItmStk>
      (graph, tMateArr, tCoarseArr, tMediumArr, numSqrMediumCmpnts,
       tmpSFineArr, tmpTFineArr, &tmpNumSqrFineCmpnts);
    break;
  default:
    assert(false);
  }
  // set output.
  sFineVec->swap(tmpSFineVec);
  tFineVec->swap(tmpTFineVec);
  *numSqrFineCmpnts = tmpNumSqrFineCmpnts;
}

void BptCanonicalEngine::ComputeMaxCardMaxEdgWghtMatching(
    const BptGraph& graph, const vector<Size>& sInMateVec,
    const vector<Size>& tInMateVec, Size inCard,
    const vector<CoarseType>& sCoarseVec, const vector<CoarseType>& tCoarseVec,
    Size sNumHrzVtxs, Size tNumHrzVtxs, Size sNumSqrVtxs, Size tNumSqrVtxs,
    Size sNumVrtVtxs, Size tNumVrtVtxs, vector<Size>* sOutMateVec,
    vector<Size>* tOutMateVec, Size* outCard, Val* edgWght) const {
  // reset output.
  ResizeVector<Size>(sOutMateVec, 0);
  ResizeVector<Size>(tOutMateVec, 0);
  *outCard = 0;
  *edgWght = 0;
  // TODO: check validity of matching.
  const Size* sInMateArr = (graph.mSNumVtxs == 0) ? NULL : &sInMateVec[0];
  const Size* tInMateArr = (graph.mTNumVtxs == 0) ? NULL : &tInMateVec[0];
  // TODO: check validity of coarse canonical decomposition.
  const CoarseType*
    sCoarseArr = (graph.mSNumVtxs == 0) ? NULL : &sCoarseVec[0];
  const CoarseType*
    tCoarseArr = (graph.mTNumVtxs == 0) ? NULL : &tCoarseVec[0];
  vector<Size> tmpSOutMateVec;
  ResizeVector<Size>(&tmpSOutMateVec, graph.mSNumVtxs);
  Size* tmpSOutMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSOutMateVec[0];
  vector<Size> tmpTOutMateVec;
  ResizeVector<Size>(&tmpTOutMateVec, graph.mTNumVtxs);
  Size* tmpTOutMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTOutMateVec[0];
  Size tmpOutCard = 0;
  Val tmpEdgWght = 0.0;
  rComputeMaxCardMaxWghtMatching
    (graph, sInMateArr, tInMateArr, inCard, sCoarseArr, tCoarseArr,
     sNumHrzVtxs, tNumHrzVtxs, sNumSqrVtxs, tNumSqrVtxs, sNumVrtVtxs,
     tNumVrtVtxs, tmpSOutMateArr, tmpTOutMateArr, &tmpOutCard, &tmpEdgWght,
     false);
  // set output.
  sOutMateVec->swap(tmpSOutMateVec);
  tOutMateVec->swap(tmpTOutMateVec);
  *outCard = tmpOutCard;
  *edgWght = tmpEdgWght;
}

void BptCanonicalEngine::ComputeMaxVtxWghtMatching(const BptGraph& graph,
    const vector<Size>& sInMateVec, const vector<Size>& tInMateVec,
    Size inCard, const vector<CoarseType>& sCoarseVec,
    const vector<CoarseType>& tCoarseVec, Size sNumHrzVtxs, Size tNumHrzVtxs,
    Size sNumSqrVtxs, Size tNumSqrVtxs, Size sNumVrtVtxs, Size tNumVrtVtxs,
    vector<Size>* sOutMateVec, vector<Size>* tOutMateVec, Size* outCard,
    Val* vtxWght) const {
  // reset output.
  ResizeVector<Size>(sOutMateVec, 0);
  ResizeVector<Size>(tOutMateVec, 0);
  *outCard = 0;
  *vtxWght = 0;
  // TODO: check validity of matching.
  const Size* sInMateArr = (graph.mSNumVtxs == 0) ? NULL : &sInMateVec[0];
  const Size* tInMateArr = (graph.mTNumVtxs == 0) ? NULL : &tInMateVec[0];
  // TODO: check validity of coarse canonical decomposition.
  const CoarseType*
    sCoarseArr = (graph.mSNumVtxs == 0) ? NULL : &sCoarseVec[0];
  const CoarseType*
    tCoarseArr = (graph.mTNumVtxs == 0) ? NULL : &tCoarseVec[0];
  vector<Size> tmpSOutMateVec;
  ResizeVector<Size>(&tmpSOutMateVec, graph.mSNumVtxs);
  Size* tmpSOutMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSOutMateVec[0];
  vector<Size> tmpTOutMateVec;
  ResizeVector<Size>(&tmpTOutMateVec, graph.mTNumVtxs);
  Size* tmpTOutMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTOutMateVec[0];
  Size tmpOutCard = 0;
  Val tmpVtxWght = 0.0;
  rComputeMaxCardMaxWghtMatching
    (graph, sInMateArr, tInMateArr, inCard, sCoarseArr, tCoarseArr,
     sNumHrzVtxs, tNumHrzVtxs, sNumSqrVtxs, tNumSqrVtxs, sNumVrtVtxs,
     tNumVrtVtxs, tmpSOutMateArr, tmpTOutMateArr, &tmpOutCard, &tmpVtxWght,
     true);
  // set output.
  sOutMateVec->swap(tmpSOutMateVec);
  tOutMateVec->swap(tmpTOutMateVec);
  *outCard = tmpOutCard;
  *vtxWght = tmpVtxWght;
}

void BptCanonicalEngine::PrintCoarse(const vector<CoarseType>& sCoarseVec,
    const vector<CoarseType>& tCoarseVec, Size sNumHrzVtxs, Size tNumHrzVtxs,
    Size sNumSqrVtxs, Size tNumSqrVtxs, Size sNumVrtVtxs, Size tNumVrtVtxs)
    const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "CoarseCanonical (begin)" << endl;
  cout << "number of horizontal S-vertices: " << sNumHrzVtxs << endl;
  cout << "number of horizontal T-vertices: " << tNumHrzVtxs << endl;
  cout << "number of square S-vertices: " << sNumSqrVtxs << endl;
  cout << "number of square T-vertices: " << tNumSqrVtxs << endl;
  cout << "number of vertical S-vertices: " << sNumVrtVtxs << endl;
  cout << "number of vertical T-vertices: " << tNumVrtVtxs << endl;
  if (mFullPrint == true) {
    cout << "coarse partition S-membership:";
    for (vector<CoarseType>::const_iterator it = sCoarseVec.begin();
         it != sCoarseVec.end(); ++it) {
      cout << " " ;
      switch (*it) {
      case eHrz:
        cout << "h";
        break;
      case eSqr:
        cout << "s";
        break;
      case eVrt:
        cout << "v";
        break;
      default:
        assert(false);
      }
    }
    cout << endl;
    cout << "coarse partition T-membership:";
    for (vector<CoarseType>::const_iterator it = tCoarseVec.begin();
         it != tCoarseVec.end(); ++it) {
      cout << " " ;
      switch (*it) {
      case eHrz:
        cout << "h";
        break;
      case eSqr:
        cout << "s";
        break;
      case eVrt:
        cout << "v";
        break;
      default:
        assert(false);
      }
    }
    cout << endl;
  }
  cout << "CoarseCanonical (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void BptCanonicalEngine::PrintMedium(const vector<Size>& sMediumVec,
    const vector<Size>& tMediumVec, Size numHrzMediumCmpnts,
    Size numSqrMediumCmpnts, Size numVrtMediumCmpnts) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "MediumCanonical (begin)" << endl;
  cout << "number of horizontal medium components: " << numHrzMediumCmpnts
       << endl;
  cout << "number of square medium components: " << numSqrMediumCmpnts << endl;
  cout << "number of vertical medium components: " << numVrtMediumCmpnts
       << endl;
  if (mFullPrint == true) {
    cout << "medium partition S-membership:";
    for (vector<Size>::const_iterator it = sMediumVec.begin();
         it != sMediumVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
    cout << "medium partition T-membership:";
    for (vector<Size>::const_iterator it = tMediumVec.begin();
         it != tMediumVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
  }
  cout << "MediumCanonical (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void BptCanonicalEngine::PrintFine(const vector<Size>& sFineVec,
    const vector<Size>& tFineVec, Size numSqrFineCmpnts) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "FineCanonical (begin)" << endl;
  cout << "number of square fine components: " << numSqrFineCmpnts << endl;
  if (mFullPrint == true) {
    cout << "fine partition S-membership:";
    for (vector<Size>::const_iterator it = sFineVec.begin();
         it != sFineVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
    cout << "fine partition T-membership:";
    for (vector<Size>::const_iterator it = tFineVec.begin();
         it != tFineVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
  }
  cout << "FineCanonical (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void BptCanonicalEngine::rComputeMaxCardMaxWghtMatching(
    const BptGraph& graph, const Size* sInMateArr, const Size* tInMateArr,
    Size inCard, const CoarseType* sCoarseArr, const CoarseType* tCoarseArr,
    Size sNumHrzVtxs, Size tNumHrzVtxs, Size sNumSqrVtxs, Size tNumSqrVtxs,
    Size sNumVrtVtxs, Size tNumVrtVtxs, Size* sOutMateArr, Size* tOutMateArr,
    Size* outCard, Val* wght, bool vtxWght) const {
  // get the vertex weights of the full graph.
  vector<Val> sVtxWghtVec;
  vector<Val> tVtxWghtVec;
  graph.GetVtxWghts(&sVtxWghtVec, &tVtxWghtVec);
  Val* sVtxWghtArr = (graph.mSNumVtxs == 0) ? NULL : &sVtxWghtVec[0];
  Val* tVtxWghtArr = (graph.mTNumVtxs == 0) ? NULL : &tVtxWghtVec[0];
  // set up the vertex weights of the coarse subgraphs.
  vector<Val> sHrzVtxWghtVec;
  ResizeVector<Val>(&sHrzVtxWghtVec, sNumHrzVtxs);
  Val* sHrzVtxWghtArr = (sNumHrzVtxs == 0) ? NULL : &sHrzVtxWghtVec[0];
  vector<Val> tHrzVtxWghtVec;
  ResizeVector<Val>(&tHrzVtxWghtVec, tNumHrzVtxs);
  Val* tHrzVtxWghtArr = (tNumHrzVtxs == 0) ? NULL : &tHrzVtxWghtVec[0];
  vector<Val> sSqrVtxWghtVec;
  ResizeVector<Val>(&sSqrVtxWghtVec, sNumSqrVtxs);
  Val* sSqrVtxWghtArr = (sNumSqrVtxs == 0) ? NULL : &sSqrVtxWghtVec[0];
  vector<Val> tSqrVtxWghtVec;
  ResizeVector<Val>(&tSqrVtxWghtVec, tNumSqrVtxs);
  Val* tSqrVtxWghtArr = (tNumSqrVtxs == 0) ? NULL : &tSqrVtxWghtVec[0];
  vector<Val> sVrtVtxWghtVec;
  ResizeVector<Val>(&sVrtVtxWghtVec, sNumVrtVtxs);
  Val* sVrtVtxWghtArr = (sNumVrtVtxs == 0) ? NULL : &sVrtVtxWghtVec[0];
  vector<Val> tVrtVtxWghtVec;
  ResizeVector<Val>(&tVrtVtxWghtVec, tNumVrtVtxs);
  Val* tVrtVtxWghtArr = (tNumVrtVtxs == 0) ? NULL : &tVrtVtxWghtVec[0];
  // set up the mapping between the coarse subgraphs and the full graph.
  vector<Size> sHrzToFullVec;
  ResizeVector<Size>(&sHrzToFullVec, sNumHrzVtxs);
  Size* sHrzToFullArr = (sNumHrzVtxs == 0) ? NULL : &sHrzToFullVec[0];
  vector<Size> tHrzToFullVec;
  ResizeVector<Size>(&tHrzToFullVec, tNumHrzVtxs);
  Size* tHrzToFullArr = (tNumHrzVtxs == 0) ? NULL : &tHrzToFullVec[0];
  vector<Size> sSqrToFullVec;
  ResizeVector<Size>(&sSqrToFullVec, sNumSqrVtxs);
  Size* sSqrToFullArr = (sNumSqrVtxs == 0) ? NULL : &sSqrToFullVec[0];
  vector<Size> tSqrToFullVec;
  ResizeVector<Size>(&tSqrToFullVec, tNumSqrVtxs);
  Size* tSqrToFullArr = (tNumSqrVtxs == 0) ? NULL : &tSqrToFullVec[0];
  vector<Size> sVrtToFullVec;
  ResizeVector<Size>(&sVrtToFullVec, sNumVrtVtxs);
  Size* sVrtToFullArr = (sNumVrtVtxs == 0) ? NULL : &sVrtToFullVec[0];
  vector<Size> tVrtToFullVec;
  ResizeVector<Size>(&tVrtToFullVec, tNumVrtVtxs);
  Size* tVrtToFullArr = (tNumVrtVtxs == 0) ? NULL : &tVrtToFullVec[0];
  vector<Size> sFullToCoarseVec;
  ResizeVector<Size>(&sFullToCoarseVec, graph.mSNumVtxs);
  Size*
    sFullToCoarseArr = (graph.mSNumVtxs == 0) ? NULL : &sFullToCoarseVec[0];
  vector<Size> tFullToCoarseVec;
  ResizeVector<Size>(&tFullToCoarseVec, graph.mTNumVtxs);
  Size*
    tFullToCoarseArr = (graph.mTNumVtxs == 0) ? NULL : &tFullToCoarseVec[0];
  // compute the mapping between coarse subgraphs and the full graph and the
  // vertex weights of the coarse subgraphs.
  for (Size s = 0, sHrz = 0; s < graph.mSNumVtxs; ++s) {
    if (sCoarseArr[s] == eHrz) {
      sHrzToFullArr[sHrz] = s;
      sFullToCoarseArr[s] = sHrz;
      sHrzVtxWghtArr[sHrz] = sVtxWghtArr[s];
      ++sHrz;
    }
  }
  for (Size t = 0, tHrz = 0; t < graph.mTNumVtxs; ++t) {
    if (tCoarseArr[t] == eHrz) {
      tHrzToFullArr[tHrz] = t;
      tFullToCoarseArr[t] = tHrz;
      tHrzVtxWghtArr[tHrz] = tVtxWghtArr[t];
      ++tHrz;
    }
  }
  for (Size s = 0, sSqr = 0; s < graph.mSNumVtxs; ++s) {
    if (sCoarseArr[s] == eSqr) {
      sSqrToFullArr[sSqr] = s;
      sFullToCoarseArr[s] = sSqr;
      sSqrVtxWghtArr[sSqr] = sVtxWghtArr[s];
      ++sSqr;
    }
  }
  for (Size t = 0, tSqr = 0; t < graph.mTNumVtxs; ++t) {
    if (tCoarseArr[t] == eSqr) {
      tSqrToFullArr[tSqr] = t;
      tFullToCoarseArr[t] = tSqr;
      tSqrVtxWghtArr[tSqr] = tVtxWghtArr[t];
      ++tSqr;
    }
  }
  for (Size s = 0, sVrt = 0; s < graph.mSNumVtxs; ++s) {
    if (sCoarseArr[s] == eVrt) {
      sVrtToFullArr[sVrt] = s;
      sFullToCoarseArr[s] = sVrt;
      sVrtVtxWghtArr[sVrt] = sVtxWghtArr[s];
      ++sVrt;
    }
  }
  for (Size t = 0, tVrt = 0; t < graph.mTNumVtxs; ++t) {
    if (tCoarseArr[t] == eVrt) {
      tVrtToFullArr[tVrt] = t;
      tFullToCoarseArr[t] = tVrt;
      tVrtVtxWghtArr[tVrt] = tVtxWghtArr[t];
      ++tVrt;
    }
  }
  // explicitly form the coarse subgraphs.
  const vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
  const vector<Val>*
    sEdgWghtVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0];
  Size numEdgs;
  graph.GetNumEdgs(&numEdgs);
  vector<Size> sVtxVec;
  sVtxVec.reserve(numEdgs);
  vector<Size> tVtxVec;
  tVtxVec.reserve(numEdgs);
  vector<Val> edgWghtVec;
  edgWghtVec.reserve(numEdgs);
  Err err;
  Size numHrzEdgs = 0;
  for (Size sHrz = 0; sHrz < sNumHrzVtxs; ++sHrz) {
    Size s = sHrzToFullArr[sHrz];
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      if (tCoarseArr[t] == eHrz) {
        Val stEdgWght = sEdgWghtArr[i];
        Size tHrz = tFullToCoarseArr[t];
        ++numHrzEdgs;
        sVtxVec.push_back(sHrz);
        tVtxVec.push_back(tHrz);
        edgWghtVec.push_back(stEdgWght);
      }
    }
  }
  BptGraph hrzGraph
    (sNumHrzVtxs, tNumHrzVtxs, numHrzEdgs, sVtxVec, tVtxVec, edgWghtVec);
  hrzGraph.GetInitErr(&err);
  assert(err == eErrNone);
  hrzGraph.SetVtxWghts(sHrzVtxWghtVec, tHrzVtxWghtVec);
  sVtxVec.clear();
  tVtxVec.clear();
  edgWghtVec.clear();
  Size numSqrEdgs = 0;
  for (Size sSqr = 0; sSqr < sNumSqrVtxs; ++sSqr) {
    Size s = sSqrToFullArr[sSqr];
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      if (tCoarseArr[t] == eSqr) {
        Val stEdgWght = sEdgWghtArr[i];
        Size tSqr = tFullToCoarseArr[t];
        ++numSqrEdgs;
        sVtxVec.push_back(sSqr);
        tVtxVec.push_back(tSqr);
        edgWghtVec.push_back(stEdgWght);
      }
    }
  }
  BptGraph sqrGraph
    (sNumSqrVtxs, tNumSqrVtxs, numSqrEdgs, sVtxVec, tVtxVec, edgWghtVec);
  sqrGraph.GetInitErr(&err);
  assert(err == eErrNone);
  sqrGraph.SetVtxWghts(sSqrVtxWghtVec, tSqrVtxWghtVec);
  sVtxVec.clear();
  tVtxVec.clear();
  edgWghtVec.clear();
  Size numVrtEdgs = 0;
  for (Size sVrt = 0; sVrt < sNumVrtVtxs; ++sVrt) {
    Size s = sVrtToFullArr[sVrt];
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      if (tCoarseArr[t] == eVrt) {
        Val stEdgWght = sEdgWghtArr[i];
        Size tVrt = tFullToCoarseArr[t];
        ++numVrtEdgs;
        sVtxVec.push_back(sVrt);
        tVtxVec.push_back(tVrt);
        edgWghtVec.push_back(stEdgWght);
      }
    }
  }
  BptGraph vrtGraph
    (sNumVrtVtxs, tNumVrtVtxs, numVrtEdgs, sVtxVec, tVtxVec, edgWghtVec);
  vrtGraph.GetInitErr(&err);
  assert(err == eErrNone);
  vrtGraph.SetVtxWghts(sVrtVtxWghtVec, tVrtVtxWghtVec);
  sVtxVec.clear();
  tVtxVec.clear();
  edgWghtVec.clear();
  // compute perfect and semiperfect maximum weight matchings in the coarse
  // subgraphs.
  BptMatchingEngine matchingEngine;
  matchingEngine.SetInlz(mInlz);
  matchingEngine.SetQueAndStkType(mQueAndStkType);
  matchingEngine.SetIdxdQueType(mIdxdQueType);
  matchingEngine.SetIdxdPriQueType(mIdxdPriQueType);
  matchingEngine.SetCardGraphSrchType(mCardGraphSrchType);
  matchingEngine.SetEdgWghtGraphSrchType(mEdgWghtGraphSrchType);
  matchingEngine.SetVtxWghtAlgType(mVtxWghtAlgType);
  matchingEngine.SetDrctVtxWghtAlgType(mDrctVtxWghtAlgType);
  matchingEngine.SetPrcmptdMaxCard(true);
  matchingEngine.SetStatsPrint(mStatsPrint);
  vector<Size> sHrzMateVec;
  vector<Size> tHrzMateVec;
  Size hrzCard = 0;
  Val hrzWght = 0.0;
  if (vtxWght == false) {
    err = matchingEngine.ComputeSemiPrfMaxEdgWghtMatching
      (hrzGraph, &sHrzMateVec, &tHrzMateVec, &hrzCard, &hrzWght, false);
    assert(err == eErrNone);
  } else {
    bool rvrs = true;
    if ((mVtxWghtAlgType == eDrct) &&
        (mDrctVtxWghtAlgType == BptMatchingEngine::eLcl)) {
      rvrs = !rvrs;
    }
    if (mVtxWghtAlgType == eSpcl) {
      // copy the precomputed horizontal matching.
      ResizeVector<Size>(&sHrzMateVec, sNumHrzVtxs);
      ResizeVector<Size>(&tHrzMateVec, tNumHrzVtxs);
      hrzCard = sNumHrzVtxs;
      Size* sHrzMateArr = (sNumHrzVtxs == 0) ? NULL : &sHrzMateVec[0];
      Size* tHrzMateArr = (tNumHrzVtxs == 0) ? NULL : &tHrzMateVec[0];
      for (Size sHrz = 0; sHrz < sNumHrzVtxs; ++sHrz) {
        Size s = sHrzToFullArr[sHrz];
        Size t = sInMateArr[s];
        if (t == cNullItm) {
          sHrzMateArr[sHrz] = cNullItm;
        } else {
          Size tHrz = tFullToCoarseArr[t];
          sHrzMateArr[sHrz] = tHrz;
        }
      }
      for (Size tHrz = 0; tHrz < tNumHrzVtxs; ++tHrz) {
        Size t = tHrzToFullArr[tHrz];
        Size s = tInMateArr[t];
        if (s == cNullItm) {
          tHrzMateArr[tHrz] = cNullItm;
        } else {
          Size sHrz = sFullToCoarseArr[s];
          tHrzMateArr[tHrz] = sHrz;
        }
      }
    }
    // TODO: the returned weight is only for the T side.
    matchingEngine.ComputeMaxVtxWghtMatching
      (hrzGraph, &sHrzMateVec, &tHrzMateVec, &hrzCard, &hrzWght, rvrs);
  }
  assert(hrzCard == sNumHrzVtxs);
  vector<Size> sSqrMateVec;
  vector<Size> tSqrMateVec;
  Size sqrCard = 0;
  Val sqrWght = 0.0;
  // nothing to do for the square for a maximum vertex-weight computation.
  if (vtxWght == false) {
    err = matchingEngine.ComputePrfMaxEdgWghtMatching
      (sqrGraph, &sSqrMateVec, &tSqrMateVec, &sqrCard, &sqrWght);
    assert(err == eErrNone);
  } else {
    sqrCard = sNumSqrVtxs;
  }
  assert(sqrCard == sNumSqrVtxs);
  assert(sqrCard == tNumSqrVtxs);
  vector<Size> sVrtMateVec;
  vector<Size> tVrtMateVec;
  Size vrtCard = 0;
  Val vrtWght = 0.0;
  if (vtxWght == false) {
    err = matchingEngine.ComputeSemiPrfMaxEdgWghtMatching
      (vrtGraph, &sVrtMateVec, &tVrtMateVec, &vrtCard, &vrtWght, true);
    assert(err == eErrNone);
  } else {
    bool rvrs = false;
    if ((mVtxWghtAlgType == eDrct) &&
        (mDrctVtxWghtAlgType == BptMatchingEngine::eLcl)) {
      rvrs = !rvrs;
    }
    if (mVtxWghtAlgType == eSpcl) {
      // copy the precomputed vertical matching.
      ResizeVector<Size>(&sVrtMateVec, sNumVrtVtxs);
      ResizeVector<Size>(&tVrtMateVec, tNumVrtVtxs);
      vrtCard = tNumVrtVtxs;
      Size* sVrtMateArr = (sNumVrtVtxs == 0) ? NULL : &sVrtMateVec[0];
      Size* tVrtMateArr = (tNumVrtVtxs == 0) ? NULL : &tVrtMateVec[0];
      for (Size sVrt = 0; sVrt < sNumVrtVtxs; ++sVrt) {
        Size s = sVrtToFullArr[sVrt];
        Size t = sInMateArr[s];
        if (t == cNullItm) {
          sVrtMateArr[sVrt] = cNullItm;
        } else {
          Size tVrt = tFullToCoarseArr[t];
          sVrtMateArr[sVrt] = tVrt;
        }
      }
      for (Size tVrt = 0; tVrt < tNumVrtVtxs; ++tVrt) {
        Size t = tVrtToFullArr[tVrt];
        Size s = tInMateArr[t];
        if (s == cNullItm) {
          tVrtMateArr[tVrt] = cNullItm;
        } else {
          Size sVrt = sFullToCoarseArr[s];
          tVrtMateArr[tVrt] = sVrt;
        }
      }
    }
    // TODO: the returned weight is only for the S side.
    matchingEngine.ComputeMaxVtxWghtMatching
      (vrtGraph, &sVrtMateVec, &tVrtMateVec, &vrtCard, &vrtWght, rvrs);
  }
  assert(vrtCard == tNumVrtVtxs);
  // merge the perfect and semiperfect maximum weight matchings computed in the
  // coarse subgraphs.
  if (sOutMateArr != NULL) {
    fill(&sOutMateArr[0], &sOutMateArr[graph.mSNumVtxs], cNullItm);
  }
  if (tOutMateArr != NULL) {
    fill(&tOutMateArr[0], &tOutMateArr[graph.mTNumVtxs], cNullItm);
  }
  Size* sHrzMateArr = (sNumHrzVtxs == 0) ? NULL : &sHrzMateVec[0];
  Size* tHrzMateArr = (tNumHrzVtxs == 0) ? NULL : &tHrzMateVec[0];
  for (Size sHrz = 0; sHrz < sNumHrzVtxs; ++sHrz) {
    Size s = sHrzToFullArr[sHrz];
    Size tHrz = sHrzMateArr[sHrz];
    if (tHrz == cNullItm) {
      sOutMateArr[s] = cNullItm;
    } else {
      Size t = tHrzToFullArr[tHrz];
      sOutMateArr[s] = t;
    }
  }
  for (Size tHrz = 0; tHrz < tNumHrzVtxs; ++tHrz) {
    Size t = tHrzToFullArr[tHrz];
    Size sHrz = tHrzMateArr[tHrz];
    if (sHrz == cNullItm) {
      tOutMateArr[t] = cNullItm;
    } else {
      Size s = sHrzToFullArr[sHrz];
      tOutMateArr[t] = s;
    }
  }
  Size* sSqrMateArr = (sNumSqrVtxs == 0) ? NULL : &sSqrMateVec[0];
  Size* tSqrMateArr = (tNumSqrVtxs == 0) ? NULL : &tSqrMateVec[0];
  // simple copy for the square for a maximum vertex-weight computation.
  if (vtxWght == false) {
    for (Size sSqr = 0; sSqr < sNumSqrVtxs; ++sSqr) {
      Size s = sSqrToFullArr[sSqr];
      Size tSqr = sSqrMateArr[sSqr];
      if (tSqr == cNullItm) {
        sOutMateArr[s] = cNullItm;
      } else {
        Size t = tSqrToFullArr[tSqr];
        sOutMateArr[s] = t;
      }
    }
    for (Size tSqr = 0; tSqr < tNumSqrVtxs; ++tSqr) {
      Size t = tSqrToFullArr[tSqr];
      Size sSqr = tSqrMateArr[tSqr];
      if (sSqr == cNullItm) {
        tOutMateArr[t] = cNullItm;
      } else {
        Size s = sSqrToFullArr[sSqr];
        tOutMateArr[t] = s;
      }
    }
  } else {
    for (Size sSqr = 0; sSqr < sNumSqrVtxs; ++sSqr) {
      Size s = sSqrToFullArr[sSqr];
      sOutMateArr[s] = sInMateArr[s];
    }
    for (Size tSqr = 0; tSqr < tNumSqrVtxs; ++tSqr) {
      Size t = tSqrToFullArr[tSqr];
      tOutMateArr[t] = tInMateArr[t];
    }
  }
  Size* sVrtMateArr = (sNumVrtVtxs == 0) ? NULL : &sVrtMateVec[0];
  Size* tVrtMateArr = (tNumVrtVtxs == 0) ? NULL : &tVrtMateVec[0];
  for (Size sVrt = 0; sVrt < sNumVrtVtxs; ++sVrt) {
    Size s = sVrtToFullArr[sVrt];
    Size tVrt = sVrtMateArr[sVrt];
    if (tVrt == cNullItm) {
      sOutMateArr[s] = cNullItm;
    } else {
      Size t = tVrtToFullArr[tVrt];
      sOutMateArr[s] = t;
    }
  }
  for (Size tVrt = 0; tVrt < tNumVrtVtxs; ++tVrt) {
    Size t = tVrtToFullArr[tVrt];
    Size sVrt = tVrtMateArr[tVrt];
    if (sVrt == cNullItm) {
      tOutMateArr[t] = cNullItm;
    } else {
      Size s = sVrtToFullArr[sVrt];
      tOutMateArr[t] = s;
    }
  }
  *outCard = sqrCard + vrtCard + hrzCard;
  // TODO: the weight is not always correct, don't rely on it yet,
  // compute it separately.
  *wght = sqrWght + vrtWght + hrzWght;
}
