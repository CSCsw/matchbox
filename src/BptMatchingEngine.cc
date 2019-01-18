#include "BptMatchingEngine.h"

using namespace std;
using namespace Matchbox;

void BptMatchingEngine::ComputeMxmlMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, bool rvrs)
    const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  Size tmpCard(0);
  rInlzGrdyForCard
    (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
}

void BptMatchingEngine::ComputeMxmlMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMxmlMatching(graph, sMateVec, tMateVec, card, false);
  } else {
    ComputeMxmlMatching(graph, sMateVec, tMateVec, card, true);
  }
}

void BptMatchingEngine::ComputeMaxCardMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, bool rvrs)
    const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  Size tmpCard = 0;
  switch (mCardGraphSrchType) {
  case eSglSrcBfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      rComputeMaxCardMatchingSglSrcBfs<VecItmQue>
        (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
      break;
    case eLstQueAndStk:
      rComputeMaxCardMatchingSglSrcBfs<LstItmQue>
        (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
      break;
    default:
      assert(false);
    }
    break;
  case eSglSrcDfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      rComputeMaxCardMatchingSglSrcDfs<VecItmQue, VecItmStk>
        (graph, tmpSMateArr, tmpTMateArr, &tmpCard, false, rvrs);
      break;
    case eLstQueAndStk:
      rComputeMaxCardMatchingSglSrcDfs<LstItmQue, LstItmStk>
        (graph, tmpSMateArr, tmpTMateArr, &tmpCard, false, rvrs);
      break;
    default:
      assert(false);
    }
    break;
  case eSglSrcDfsLkhd:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      rComputeMaxCardMatchingSglSrcDfs<VecItmQue, VecItmStk>
        (graph, tmpSMateArr, tmpTMateArr, &tmpCard, true, rvrs);
      break;
    case eLstQueAndStk:
      rComputeMaxCardMatchingSglSrcDfs<LstItmQue, LstItmStk>
        (graph, tmpSMateArr, tmpTMateArr, &tmpCard, true, rvrs);
      break;
    default:
      assert(false);
    }
    break;
  case eMplSrcSglPath:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplSrcSglPath<VecItmQue, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplSrcSglPath<LstItmQue, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eMplPathDfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplPathDfs<VecItmQue, VecItmStk, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, false, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplPathDfs<LstItmQue, LstItmStk, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, false, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eMplPathDfsLkhd:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplPathDfs<VecItmQue, VecItmStk, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, true, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplPathDfs<LstItmQue, LstItmStk, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, true, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eMplPathBfsDfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplPathBfsDfs
          <VecItmQue, VecItmStk, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        rComputeMaxCardMatchingMplPathBfsDfs
          <LstItmQue, LstItmStk, LstItmIdxdQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  default:
    assert(false);
  }
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
}

void BptMatchingEngine::ComputeMaxCardMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMaxCardMatching(graph, sMateVec, tMateVec, card, false);
  } else {
    ComputeMaxCardMatching(graph, sMateVec, tMateVec, card, true);
  }
}

void BptMatchingEngine::ComputeMaxEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght,
    bool maxCard, bool rvrs) const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *edgWght = 0.0;
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  Size tmpCard = 0;
  Val tmpEdgWght = 0.0;
  switch (mEdgWghtGraphSrchType) {
  case eSglSrcBfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        switch (mIdxdPriQueType) {
        case eLstIdxdPriQue:
          rComputeMaxEdgWghtMatchingSglSrc<VecItmQue, VecItmStk, LstItmIdxdQue,
            LstItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, maxCard,
             rvrs);
          break;
        case eBhpIdxdPriQue:
          rComputeMaxEdgWghtMatchingSglSrc<VecItmQue, VecItmStk, LstItmIdxdQue,
            BhpItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, maxCard,
             rvrs);
          break;
        case eFhpIdxdPriQue:
        default:
          assert(false);
        }
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        switch (mIdxdPriQueType) {
        case eLstIdxdPriQue:
          rComputeMaxEdgWghtMatchingSglSrc<LstItmQue, LstItmStk, LstItmIdxdQue,
            LstItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, maxCard,
             rvrs);
          break;
        case eBhpIdxdPriQue:
          rComputeMaxEdgWghtMatchingSglSrc<LstItmQue, LstItmStk, LstItmIdxdQue,
            BhpItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, maxCard,
             rvrs);
          break;
        case eFhpIdxdPriQue:
        default:
          assert(false);
        }
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eMplSrcSglPath:
  default:
    assert(false);
  }
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *edgWght = tmpEdgWght;
}

void BptMatchingEngine::ComputeMaxEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght,
    bool maxCard) const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeMaxEdgWghtMatching
      (graph, sMateVec, tMateVec, card, edgWght, maxCard, false);
  } else {
    ComputeMaxEdgWghtMatching
      (graph, sMateVec, tMateVec, card, edgWght, maxCard, true);
  }
}

Err BptMatchingEngine::ComputePrfMaxEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght,
    bool rvrs) const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *edgWght = 0.0;
  if (graph.mSNumVtxs != graph.mTNumVtxs) {
    return eErrNoPrfMatching;
  }
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  Size tmpCard = 0;
  Val tmpEdgWght = 0.0;
  Err err = eErrNone;
  // it is the dual initialization that distinguishes between a nonperfect
  // or semiperfect maximum edge-weight computation on one side (loose dual
  // initialization) and a perfect maximum edge-weight computation on the other
  // side (tight dual initialization).
  rInlzDualsTight inlzDualsFunctor(graph);
  switch (mEdgWghtGraphSrchType) {
  case eSglSrcBfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        switch (mIdxdPriQueType) {
        case eLstIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsTight,
            VecItmQue, VecItmStk, LstItmIdxdQue, LstItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eBhpIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsTight,
            VecItmQue, VecItmStk, LstItmIdxdQue, BhpItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eFhpIdxdPriQue:
        default:
          assert(false);
        }
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        switch (mIdxdPriQueType) {
        case eLstIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsTight,
            LstItmQue, LstItmStk, LstItmIdxdQue, LstItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eBhpIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsTight,
            LstItmQue, LstItmStk, LstItmIdxdQue, BhpItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eFhpIdxdPriQue:
        default:
          assert(false);
        }
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eMplSrcSglPath:
  default:
    assert(false);
  }
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *edgWght = tmpEdgWght;
  return err;
}

Err BptMatchingEngine::ComputePrfMaxEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght)
    const {
  return ComputePrfMaxEdgWghtMatching
    (graph, sMateVec, tMateVec, card, edgWght, false);
}

Err BptMatchingEngine::ComputeSemiPrfMaxEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght,
    bool rvrs) const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *edgWght = 0.0;
  if (((graph.mSNumVtxs > graph.mTNumVtxs) && (rvrs == false)) ||
      ((graph.mSNumVtxs < graph.mTNumVtxs) && (rvrs == true))) {
    return eErrNoPrfMatching;
  }
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  Size tmpCard = 0;
  Val tmpEdgWght = 0.0;
  Err err = eErrNone;
  // it is the dual initialization that distinguishes between a nonperfect
  // or semiperfect maximum edge-weight computation on one side (loose dual
  // initialization) and a perfect maximum edge-weight computation on the other
  // side (tight dual initialization).
  rInlzDualsLoose inlzDualsFunctor(graph);
  switch (mEdgWghtGraphSrchType) {
  case eSglSrcBfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        switch (mIdxdPriQueType) {
        case eLstIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsLoose,
            VecItmQue, VecItmStk, LstItmIdxdQue, LstItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eBhpIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsLoose,
            VecItmQue, VecItmStk, LstItmIdxdQue, BhpItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eFhpIdxdPriQue:
        default:
          assert(false);
        }
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdQueType) {
      case eLstIdxdQue:
        switch (mIdxdPriQueType) {
        case eLstIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsLoose,
            LstItmQue, LstItmStk, LstItmIdxdQue, LstItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eBhpIdxdPriQue:
          err = rComputePrfMaxEdgWghtMatchingSglSrc<rInlzDualsLoose,
            LstItmQue, LstItmStk, LstItmIdxdQue, BhpItmAndValIdxdMinPriQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs,
             inlzDualsFunctor);
          break;
        case eFhpIdxdPriQue:
        default:
          assert(false);
        }
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eMplSrcSglPath:
  default:
    assert(false);
  }
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *edgWght = tmpEdgWght;
  return err;
}

Err BptMatchingEngine::ComputeSemiPrfMaxEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght)
    const {
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    return ComputeSemiPrfMaxEdgWghtMatching
      (graph, sMateVec, tMateVec, card, edgWght, false);
  } else {
    return ComputeSemiPrfMaxEdgWghtMatching
      (graph, sMateVec, tMateVec, card, edgWght, true);
  }
}


void BptMatchingEngine::ComputeMaxVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght,
    bool rvrs) const {
  // reset output.
  vector<Size> tmpSMateVec;
  vector<Size> tmpTMateVec;
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  if (mVtxWghtAlgType == eSpcl) {
    if (mPrcmptdMaxCard == false) {
      ComputeMaxCardMatching(graph, &tmpSMateVec, &tmpTMateVec, &tmpCard);
    } else {
      sMateVec->swap(tmpSMateVec);
      tMateVec->swap(tmpTMateVec);
      tmpCard = *card;
    }
  } else {
    ResizeVector<Size>(sMateVec, 0);
    ResizeVector<Size>(tMateVec, 0);
    ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
    ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  }
  *card = 0;
  *vtxWght = 0.0;
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  switch (mVtxWghtAlgType) {
  case eDrct:
    switch (mDrctVtxWghtAlgType) {
    case eGbl:
      switch (mQueAndStkType) {
      case eVecQueAndStk:
        rComputeMaxVtxWghtMatchingDrctGbl<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght, cInfSize,
           rvrs);
        break;
      case eLstQueAndStk:
        rComputeMaxVtxWghtMatchingDrctGbl<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght, cInfSize,
           rvrs);
        break;
      default:
        assert(false);
      }
      break;
    case eLcl:
      switch (mQueAndStkType) {
      case eVecQueAndStk:
        rComputeMaxVtxWghtMatchingDrctLcl<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght, cInfSize,
           rvrs);
        break;
      case eLstQueAndStk:
        rComputeMaxVtxWghtMatchingDrctLcl<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght, cInfSize,
           rvrs);
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  case eSpcl:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      switch (mIdxdPriQueType) {
      case eLstIdxdPriQue:
        rComputeMaxVtxWghtMatchingSpcl<VecItmQue, LstItmAndValIdxdMaxPriQue>
          (graph, tmpSMateArr, tmpTMateArr, tmpCard, &tmpVtxWght, rvrs);
        break;
      case eBhpIdxdPriQue:
        rComputeMaxVtxWghtMatchingSpcl<VecItmQue, BhpItmAndValIdxdMaxPriQue>
          (graph, tmpSMateArr, tmpTMateArr, tmpCard, &tmpVtxWght, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    case eLstQueAndStk:
      switch (mIdxdPriQueType) {
      case eLstIdxdPriQue:
        rComputeMaxVtxWghtMatchingSpcl<LstItmQue, LstItmAndValIdxdMaxPriQue>
          (graph, tmpSMateArr, tmpTMateArr, tmpCard, &tmpVtxWght, rvrs);
        break;
      case eBhpIdxdPriQue:
        rComputeMaxVtxWghtMatchingSpcl<LstItmQue, BhpItmAndValIdxdMaxPriQue>
          (graph, tmpSMateArr, tmpTMateArr, tmpCard, &tmpVtxWght, rvrs);
        break;
      default:
        assert(false);
      }
      break;
    default:
      assert(false);
    }
    break;
  default:
    assert(false);
  }
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

void BptMatchingEngine::ComputeMaxVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght)
    const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *vtxWght = 0.0;
  // compute two restricted maximum vertex-weight matchings, M_S and M_T.
  vector<Size> sMateSVec;
  ResizeVector<Size>(&sMateSVec, graph.mSNumVtxs);
  vector<Size> tMateSVec;
  ResizeVector<Size>(&tMateSVec, graph.mTNumVtxs);
  Size cardS = 0;
  Val sVtxWghtS = 0.0;
  vector<Size> sMateTVec;
  ResizeVector<Size>(&sMateTVec, graph.mSNumVtxs);
  vector<Size> tMateTVec;
  ResizeVector<Size>(&tMateTVec, graph.mTNumVtxs);
  Size cardT = 0;
  Val tVtxWghtT = 0.0;
  bool rvrs = false;
  if ((mVtxWghtAlgType == eDrct) && (mDrctVtxWghtAlgType == eLcl)) {
    rvrs = !rvrs;
  }
  // save the original precomputed maximum cardinality matching condition,
  // if the condition is false.
  bool prcmptdMaxCard = mPrcmptdMaxCard;
  if ((mVtxWghtAlgType == eSpcl) && (prcmptdMaxCard == false)) {
    ComputeMaxCardMatching(graph, &sMateSVec, &tMateSVec, &cardS);
    copy(sMateSVec.begin(), sMateSVec.end(), sMateTVec.begin());
    copy(tMateSVec.begin(), tMateSVec.end(), tMateTVec.begin());
    cardT = cardS;
    mPrcmptdMaxCard = true;
  }
  ComputeMaxVtxWghtMatching
    (graph, &sMateSVec, &tMateSVec, &cardS, &sVtxWghtS, rvrs);
  ComputeMaxVtxWghtMatching
    (graph, &sMateTVec, &tMateTVec, &cardT, &tVtxWghtT, !rvrs);
  // restore the original precomputed maximum cardinality matching condition,
  // if the condition is false.
  if ((mVtxWghtAlgType == eSpcl) && (prcmptdMaxCard == false)) {
    mPrcmptdMaxCard = false;
  }
  // merge the two restricted maximum vertex-weight matchings M_S and M_T.
  const Size* sMateSArr = (graph.mSNumVtxs == 0) ? NULL : &sMateSVec[0];
  const Size* tMateSArr = (graph.mTNumVtxs == 0) ? NULL : &tMateSVec[0];
  const Size* sMateTArr = (graph.mSNumVtxs == 0) ? NULL : &sMateTVec[0];
  const Size* tMateTArr = (graph.mTNumVtxs == 0) ? NULL : &tMateTVec[0];
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  Size* tmpSMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0];
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpTMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rMergeMatchings
    (graph, sMateSArr, tMateSArr, sMateTArr, tMateTArr, tmpSMateArr,
     tmpTMateArr, &tmpCard);
  tmpVtxWght = sVtxWghtS + tVtxWghtT;
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void BptMatchingEngine::ComputeApproxMaxVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght,
    bool rvrs, Size bnd) const {
  // reset output.
  vector<Size> tmpSMateVec;
  vector<Size> tmpTMateVec;
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
 
    ResizeVector<Size>(sMateVec, 0);
    ResizeVector<Size>(tMateVec, 0);
    ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
    ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);

  *card = 0;
  *vtxWght = 0.0;
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  
      switch (mQueAndStkType) {
      case eVecQueAndStk:
        rComputeMaxVtxWghtMatchingDrctGbl<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght, bnd,
           rvrs);
        break;
      case eLstQueAndStk:
        rComputeMaxVtxWghtMatchingDrctGbl<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght, bnd,
           rvrs);
        break;
      default:
        assert(false);
      }
      
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}


void BptMatchingEngine::ComputeApproxMaxVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght, Size bnd)
    const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *vtxWght = 0.0;
  // compute two restricted maximum vertex-weight matchings, M_S and M_T.
  vector<Size> sMateSVec;
  ResizeVector<Size>(&sMateSVec, graph.mSNumVtxs);
  vector<Size> tMateSVec;
  ResizeVector<Size>(&tMateSVec, graph.mTNumVtxs);
  Size cardS = 0;
  Val sVtxWghtS = 0.0;
  vector<Size> sMateTVec;
  ResizeVector<Size>(&sMateTVec, graph.mSNumVtxs);
  vector<Size> tMateTVec;
  ResizeVector<Size>(&tMateTVec, graph.mTNumVtxs);
  Size cardT = 0;
  Val tVtxWghtT = 0.0;
  bool rvrs = false;
  // save the original precomputed maximum cardinality matching condition,
  // if the condition is false.
  ComputeApproxMaxVtxWghtMatching
    (graph, &sMateSVec, &tMateSVec, &cardS, &sVtxWghtS, rvrs, bnd);
  ComputeApproxMaxVtxWghtMatching
    (graph, &sMateTVec, &tMateTVec, &cardT, &tVtxWghtT, !rvrs, bnd);
  // restore the original precomputed maximum cardinality matching condition,
  // if the condition is false.

  // merge the two restricted maximum vertex-weight matchings M_S and M_T.
  const Size* sMateSArr = (graph.mSNumVtxs == 0) ? NULL : &sMateSVec[0];
  const Size* tMateSArr = (graph.mTNumVtxs == 0) ? NULL : &tMateSVec[0];
  const Size* sMateTArr = (graph.mSNumVtxs == 0) ? NULL : &sMateTVec[0];
  const Size* tMateTArr = (graph.mTNumVtxs == 0) ? NULL : &tMateTVec[0];
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  Size* tmpSMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0];
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpTMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rMergeMatchings
    (graph, sMateSArr, tMateSArr, sMateTArr, tMateTArr, tmpSMateArr,
     tmpTMateArr, &tmpCard);
  tmpVtxWght = sVtxWghtS + tVtxWghtT;
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

//////////////////The Suitor approx algorithm for vertex weighted matching////////////////////
void BptMatchingEngine::ComputeMaxVtxWghtMatchingSuitor(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght) const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *vtxWght = 0.0;
  // compute two restricted maximum vertex-weight matchings, M_S and M_T.
  vector<Size> sMateSVec;
  ResizeVector<Size>(&sMateSVec, graph.mSNumVtxs);
  vector<Size> tMateSVec;
  ResizeVector<Size>(&tMateSVec, graph.mTNumVtxs);
  Size cardS = 0;
  Val sVtxWghtS = 0.0;
  vector<Size> sMateTVec;
  ResizeVector<Size>(&sMateTVec, graph.mSNumVtxs);
  vector<Size> tMateTVec;
  ResizeVector<Size>(&tMateTVec, graph.mTNumVtxs);
  Size cardT = 0;
  Val tVtxWghtT = 0.0;
  bool rvrs = false;
  
  
  ComputeMaxVtxWghtMatchingSuitor
    (graph, &sMateSVec, &tMateSVec, &cardS, &sVtxWghtS, rvrs);
  ComputeMaxVtxWghtMatchingSuitor
    (graph, &sMateTVec, &tMateTVec, &cardT, &tVtxWghtT, !rvrs);
 
  // merge the two restricted maximum vertex-weight matchings M_S and M_T.
  const Size* sMateSArr = (graph.mSNumVtxs == 0) ? NULL : &sMateSVec[0];
  const Size* tMateSArr = (graph.mTNumVtxs == 0) ? NULL : &tMateSVec[0];
  const Size* sMateTArr = (graph.mSNumVtxs == 0) ? NULL : &sMateTVec[0];
  const Size* tMateTArr = (graph.mTNumVtxs == 0) ? NULL : &tMateTVec[0];
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  Size* tmpSMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0];
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpTMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rMergeMatchings
    (graph, sMateSArr, tMateSArr, sMateTArr, tMateTArr, tmpSMateArr,
     tmpTMateArr, &tmpCard);
  tmpVtxWght = sVtxWghtS + tVtxWghtT;
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

void BptMatchingEngine::ComputeMaxVtxWghtMatchingSuitor(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght,
    bool rvrs) const {
  // reset output.
  vector<Size> tmpSMateVec;
  vector<Size> tmpTMateVec;
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;

    ResizeVector<Size>(sMateVec, 0);
    ResizeVector<Size>(tMateVec, 0);
    ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
    ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);

  *card = 0;
  *vtxWght = 0.0;
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  	
  	
      switch (mQueAndStkType) {
      case eVecQueAndStk:
        rComputeMaxVtxWghtMatchingSuitor<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght,
           rvrs);
        break;
      case eLstQueAndStk:
        rComputeMaxVtxWghtMatchingSuitor<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght,
           rvrs);
        break;
      default:
        assert(false);
      }
      
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

//////////////////locally dominant approx. algorithm for vertex weighted matching////////////////////
void BptMatchingEngine::ComputeMaxVtxWghtMatchingLocal(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght) const {
  // reset output.
  vector<Size> tmpSMateVec;
  vector<Size> tmpTMateVec;
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
 
    ResizeVector<Size>(sMateVec, 0);
    ResizeVector<Size>(tMateVec, 0);
    ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
    ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  
  *card = 0;
  *vtxWght = 0.0;
  Size* tmpSMateArr = ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) ;
  Size* tmpTMateArr = ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  
      switch (mQueAndStkType) {
      case eVecQueAndStk:
       rComputeMaxVtxWghtMatchingLocal<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght);
        break;
      case eLstQueAndStk:
         rComputeMaxVtxWghtMatchingLocal<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght);
        break;
      default:
        assert(false);
      }
     
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

////////////Greedy half approx. algorithm for vertex weighted matching///////////////////
void BptMatchingEngine::ComputeHalfVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght,
    bool rvrs) const {
  // reset output.
  vector<Size> tmpSMateVec;
  vector<Size> tmpTMateVec;
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
 
    ResizeVector<Size>(sMateVec, 0);
    ResizeVector<Size>(tMateVec, 0);
    ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
    ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);

  *card = 0;
  *vtxWght = 0.0;
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  
      switch (mQueAndStkType) {
      case eVecQueAndStk:
        rComputeHalfVtxWghtMatchingDrctGbl<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght,
           rvrs);
        break;
      case eLstQueAndStk:
        rComputeHalfVtxWghtMatchingDrctGbl<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght,
           rvrs);
        break;
      default:
        assert(false);
      }
      
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}


void BptMatchingEngine::ComputeHalfVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght)
    const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *vtxWght = 0.0;
  // compute two restricted maximum vertex-weight matchings, M_S and M_T.
  vector<Size> sMateSVec;
  ResizeVector<Size>(&sMateSVec, graph.mSNumVtxs);
  vector<Size> tMateSVec;
  ResizeVector<Size>(&tMateSVec, graph.mTNumVtxs);
  Size cardS = 0;
  Val sVtxWghtS = 0.0;
  vector<Size> sMateTVec;
  ResizeVector<Size>(&sMateTVec, graph.mSNumVtxs);
  vector<Size> tMateTVec;
  ResizeVector<Size>(&tMateTVec, graph.mTNumVtxs);
  Size cardT = 0;
  Val tVtxWghtT = 0.0;
  bool rvrs = false;
  // save the original precomputed maximum cardinality matching condition,
  // if the condition is false.
  ComputeHalfVtxWghtMatching
    (graph, &sMateSVec, &tMateSVec, &cardS, &sVtxWghtS, rvrs);
  ComputeHalfVtxWghtMatching
    (graph, &sMateTVec, &tMateTVec, &cardT, &tVtxWghtT, !rvrs);
  // restore the original precomputed maximum cardinality matching condition,
  // if the condition is false.

  // merge the two restricted maximum vertex-weight matchings M_S and M_T.
  const Size* sMateSArr = (graph.mSNumVtxs == 0) ? NULL : &sMateSVec[0];
  const Size* tMateSArr = (graph.mTNumVtxs == 0) ? NULL : &tMateSVec[0];
  const Size* sMateTArr = (graph.mSNumVtxs == 0) ? NULL : &sMateTVec[0];
  const Size* tMateTArr = (graph.mTNumVtxs == 0) ? NULL : &tMateTVec[0];
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  Size* tmpSMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0];
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpTMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rMergeMatchings
    (graph, sMateSArr, tMateSArr, sMateTArr, tMateTArr, tmpSMateArr,
     tmpTMateArr, &tmpCard);
  tmpVtxWght = sVtxWghtS + tVtxWghtT;
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}

void BptMatchingEngine::ComputeHalfEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght) 
	const {
	if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    ComputeHalfEdgWghtMatching
      (graph, sMateVec, tMateVec, card, edgWght,  false);
  } else {
    ComputeHalfEdgWghtMatching
      (graph, sMateVec, tMateVec, card, edgWght,  true);
  }
}

void BptMatchingEngine::ComputeHalfEdgWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* edgWght, bool rvrs) 
	const {

  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *edgWght = 0.0;
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  Size tmpCard = 0;
  Val tmpEdgWght = 0.0;

  rComputeHalfEdgWghtMatching<VecItmQue>
            (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpEdgWght, rvrs);

  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *edgWght = tmpEdgWght;
}
/////////
////////////Greedy two third approx. algorithm for vertex weighted matching///////////////////
void BptMatchingEngine::ComputeTwoThirdVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght,
    bool rvrs) const {
  // reset output.
  vector<Size> tmpSMateVec;
  vector<Size> tmpTMateVec;
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
 
    ResizeVector<Size>(sMateVec, 0);
    ResizeVector<Size>(tMateVec, 0);
    ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
    ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);

  *card = 0;
  *vtxWght = 0.0;
  Size* tmpSMateArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]);
  Size* tmpTMateArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0]);
  
      switch (mQueAndStkType) {
      case eVecQueAndStk:
        rComputeTwoThirdVtxWghtMatchingDrctGbl<VecItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght,
           rvrs);
        break;
      case eLstQueAndStk:
       rComputeTwoThirdVtxWghtMatchingDrctGbl<LstItmQue>
          (graph, tmpSMateArr, tmpTMateArr, &tmpCard, &tmpVtxWght,
           rvrs);
        break;
      default:
        assert(false);
      }
      
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}


void BptMatchingEngine::ComputeTwoThirdVtxWghtMatching(const BptGraph& graph,
    vector<Size>* sMateVec, vector<Size>* tMateVec, Size* card, Val* vtxWght)
    const {
  // reset output.
  ResizeVector<Size>(sMateVec, 0);
  ResizeVector<Size>(tMateVec, 0);
  *card = 0;
  *vtxWght = 0.0;
  // compute two restricted maximum vertex-weight matchings, M_S and M_T.
  vector<Size> sMateSVec;
  ResizeVector<Size>(&sMateSVec, graph.mSNumVtxs);
  vector<Size> tMateSVec;
  ResizeVector<Size>(&tMateSVec, graph.mTNumVtxs);
  Size cardS = 0;
  Val sVtxWghtS = 0.0;
  vector<Size> sMateTVec;
  ResizeVector<Size>(&sMateTVec, graph.mSNumVtxs);
  vector<Size> tMateTVec;
  ResizeVector<Size>(&tMateTVec, graph.mTNumVtxs);
  Size cardT = 0;
  Val tVtxWghtT = 0.0;
  bool rvrs = false;
  // save the original precomputed maximum cardinality matching condition,
  // if the condition is false.
  ComputeTwoThirdVtxWghtMatching
    (graph, &sMateSVec, &tMateSVec, &cardS, &sVtxWghtS, rvrs);
  ComputeTwoThirdVtxWghtMatching
    (graph, &sMateTVec, &tMateTVec, &cardT, &tVtxWghtT, !rvrs);
  // restore the original precomputed maximum cardinality matching condition,
  // if the condition is false.

  // merge the two restricted maximum vertex-weight matchings M_S and M_T.
  const Size* sMateSArr = (graph.mSNumVtxs == 0) ? NULL : &sMateSVec[0];
  const Size* tMateSArr = (graph.mTNumVtxs == 0) ? NULL : &tMateSVec[0];
  const Size* sMateTArr = (graph.mSNumVtxs == 0) ? NULL : &sMateTVec[0];
  const Size* tMateTArr = (graph.mTNumVtxs == 0) ? NULL : &tMateTVec[0];
  vector<Size> tmpSMateVec;
  ResizeVector<Size>(&tmpSMateVec, graph.mSNumVtxs);
  Size* tmpSMateArr = (graph.mSNumVtxs == 0) ? NULL : &tmpSMateVec[0];
  vector<Size> tmpTMateVec;
  ResizeVector<Size>(&tmpTMateVec, graph.mTNumVtxs);
  Size* tmpTMateArr = (graph.mTNumVtxs == 0) ? NULL : &tmpTMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rMergeMatchings
    (graph, sMateSArr, tMateSArr, sMateTArr, tMateTArr, tmpSMateArr,
     tmpTMateArr, &tmpCard);
  tmpVtxWght = sVtxWghtS + tVtxWghtT;
  // set output.
  sMateVec->swap(tmpSMateVec);
  tMateVec->swap(tmpTMateVec);
  *card = tmpCard;
  *vtxWght = tmpVtxWght;
}


////////////////////////////

Err BptMatchingEngine::GetMatchedEdgWght(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size card,
    Val *edgWght) const {
  if (CheckMatching(graph, sMateVec, tMateVec, card) == false) {
    return eErrInvMatching;
  }
  const Size* sMateArr = (graph.mSNumVtxs == 0) ? NULL : &sMateVec[0];
  const Size* tMateArr = (graph.mTNumVtxs == 0) ? NULL : &tMateVec[0];
  vector<Val> edgWghtVec;
  ResizeVector<Val>(&edgWghtVec, card);
  Val* edgWghtArr = (card == 0) ? NULL : &edgWghtVec[0];
  if (graph.mSNumVtxs <= graph.mTNumVtxs) {
    const vector<Size>*
      sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
    const vector<Val>* sEdgWghtVecArr =
      (graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0];
    for (Size s = 0, k = 0; s < graph.mSNumVtxs; ++s) {
      Size t = sMateArr[s];
      if (t == cNullItm) {
        continue;
      }
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        if (sVtxArr[i] == t) {
          edgWghtArr[k] = sEdgWghtArr[i];
          ++k;
          break;
        }
      }
    }
  } else {
    const vector<Size>*
      tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];
    const vector<Val>* tEdgWghtVecArr =
      (graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0];
    for (Size t = 0, k = 0; t < graph.mTNumVtxs; ++t) {
      Size s = tMateArr[t];
      if (s == cNullItm) {
        continue;
      }
      Size tNumEdgs = tVtxVecArr[t].size();
      const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
      const Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[t][0];
      for (Size j = 0; j < tNumEdgs; ++j) {
        if (tVtxArr[j] == s) {
          edgWghtArr[k] = tEdgWghtArr[j];
          ++k;
          break;
        }
      }
    }
  }
  sort(edgWghtVec.begin(), edgWghtVec.end());
  *edgWght = accumulate(edgWghtVec.begin(), edgWghtVec.end(), 0.0);
  return eErrNone;
}

Err BptMatchingEngine::GetMatchedVtxWght(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size card,
    Val *sVtxWght, Val *tVtxWght, Val *edgWght) const {
  if (CheckMatching(graph, sMateVec, tMateVec, card) == false) {
    return eErrInvMatching;
  }
  const Val*
    sVtxWghtArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0];
  const Val*
    tVtxWghtArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0];
  const Size* sMateArr = (graph.mSNumVtxs == 0) ? NULL : &sMateVec[0];
  const Size* tMateArr = (graph.mTNumVtxs == 0) ? NULL : &tMateVec[0];
  vector<Val> tmpSVtxWghtVec;
  ResizeVector<Val>(&tmpSVtxWghtVec, card);
  Val* tmpSVtxWghtArr = (card == 0) ? NULL : &tmpSVtxWghtVec[0];
  vector<Val> tmpTVtxWghtVec;
  ResizeVector<Val>(&tmpTVtxWghtVec, card);
  Val* tmpTVtxWghtArr = (card == 0) ? NULL : &tmpTVtxWghtVec[0];
  for (Size s = 0, i = 0; s < graph.mSNumVtxs; ++s) {
    if (sMateArr[s] != cNullItm) {
      tmpSVtxWghtArr[i] = sVtxWghtArr[s];
      ++i;
    }
  }
  for (Size t = 0, j = 0; t < graph.mTNumVtxs; ++t) {
    if (tMateArr[t] != cNullItm) {
      tmpTVtxWghtArr[j] = tVtxWghtArr[t];
      ++j;
    }
  }
  sort(tmpSVtxWghtVec.begin(), tmpSVtxWghtVec.end());
  sort(tmpTVtxWghtVec.begin(), tmpTVtxWghtVec.end());
  *sVtxWght = accumulate(tmpSVtxWghtVec.begin(), tmpSVtxWghtVec.end(), 0.0);
  *tVtxWght = accumulate(tmpTVtxWghtVec.begin(), tmpTVtxWghtVec.end(), 0.0);
  *edgWght = *sVtxWght + *tVtxWght;
  return eErrNone;
}

bool BptMatchingEngine::CheckMatching(const BptGraph& graph,
    const vector<Size>& sMateVec, const vector<Size>& tMateVec, Size card)
    const {
  // check if the number of vertices is consistent.
  if (graph.mSNumVtxs != sMateVec.size()) {
    return false;
  }
  if (graph.mTNumVtxs != tMateVec.size()) {
    return false;
  }
  assert(card <= sMateVec.size());
  assert(card <= tMateVec.size());
  const vector<Size>*
    sVtxVecArr = (graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0];
  const vector<Size>*
    tVtxVecArr = (graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0];
  const Size* sMateArr = (graph.mSNumVtxs == 0) ? NULL : &sMateVec[0];
  const Size* tMateArr = (graph.mTNumVtxs == 0) ? NULL : &tMateVec[0];
  // check the matching from the S-side.
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    Size t = sMateArr[s];
    if (t != cNullItm) {
      assert(t < graph.mTNumVtxs);
      assert(tMateArr[t] == s);
      // check if there is an edge between s and t.
      if (find(sVtxVecArr[s].begin(), sVtxVecArr[s].end(), t) ==
          sVtxVecArr[s].end()) {
        return false;
      }
    }
  }
  // check the matching from the T-side.
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    Size s = tMateArr[t];
    if (s != cNullItm) {
      assert(s < graph.mSNumVtxs);
      assert(sMateArr[s] == t);
      // check if there is an edge between t and s.
      if (find(tVtxVecArr[t].begin(), tVtxVecArr[t].end(), s) ==
          tVtxVecArr[t].end()) {
        return false;
      }
    }
  }
  return true;
}

void BptMatchingEngine::PrintMatching(const vector<Size>& sMateVec,
    const vector<Size>& tMateVec, Size card) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "Matching (begin)" << endl;
  cout << "cardinality: " << card << endl;
  if (mFullPrint == true) {
    cout << "S-mates:";
    for (vector<Size>::const_iterator it = sMateVec.begin();
         it != sMateVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
    cout << "T-mates:";
    for (vector<Size>::const_iterator it = tMateVec.begin();
         it != tMateVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
  }
  cout << "Matching (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void BptMatchingEngine::PrintMatching(const vector<Size>& sMateVec,
    const vector<Size>& tMateVec, Size card, Val wght) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "Matching (begin)" << endl;
  cout << "cardinality: " << card << endl;
  cout.setf(ios::left | ios::scientific | ios::showpoint);
  cout.precision(mPrecision);
  cout << "weight: " << wght << endl;
  cout.unsetf(ios::left | ios::scientific | ios::showpoint);
  if (mFullPrint == true) {
    cout << "S-mates:";
    for (vector<Size>::const_iterator it = sMateVec.begin();
         it != sMateVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
    cout << "T-mates:";
    for (vector<Size>::const_iterator it = tMateVec.begin();
         it != tMateVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
  }
  cout << "Matching (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void BptMatchingEngine::rInlzDualsLoose::operator()(Val* sDualArr,
    Val* tDualArr, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? mGraph.mSNumVtxs : mGraph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? mGraph.mTNumVtxs : mGraph.mSNumVtxs;
  const vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((mGraph.mSNumVtxs == 0) ? NULL : &mGraph.mSEdgWghtVecVec[0]) :
    ((mGraph.mTNumVtxs == 0) ? NULL : &mGraph.mTEdgWghtVecVec[0]);
  for (Size s = 0; s < sNumVtxs; ++s) {
    sDualArr[s] = 0.0;
    Size sNumEdgs = sEdgWghtVecArr[s].size();
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Val stEdgWght = sEdgWghtArr[i];
      if (sDualArr[s] < stEdgWght) {
        sDualArr[s] = stEdgWght;
      }
    }
  }
  if (tDualArr != NULL) {
    fill(&tDualArr[0], &tDualArr[tNumVtxs], 0.0);
  }
}

void BptMatchingEngine::rInlzDualsTight::operator()(Val* sDualArr,
    Val* tDualArr, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? mGraph.mSNumVtxs : mGraph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? mGraph.mTNumVtxs : mGraph.mSNumVtxs;
  const vector<Size>* tVtxVecArr = (rvrs == false) ?
    ((mGraph.mTNumVtxs == 0) ? NULL : &mGraph.mTVtxVecVec[0]) :
    ((mGraph.mSNumVtxs == 0) ? NULL : &mGraph.mSVtxVecVec[0]);
  const vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((mGraph.mSNumVtxs == 0) ? NULL : &mGraph.mSEdgWghtVecVec[0]) :
    ((mGraph.mTNumVtxs == 0) ? NULL : &mGraph.mTEdgWghtVecVec[0]);
  const vector<Val>* tEdgWghtVecArr = (rvrs == false) ?
    ((mGraph.mTNumVtxs == 0) ? NULL : &mGraph.mTEdgWghtVecVec[0]) :
    ((mGraph.mSNumVtxs == 0) ? NULL : &mGraph.mSEdgWghtVecVec[0]);
  for (Size s = 0; s < sNumVtxs; ++s) {
    sDualArr[s] = 0.0;
    Size sNumEdgs = sEdgWghtVecArr[s].size();
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Val stEdgWght = sEdgWghtArr[i];
      if (sDualArr[s] < stEdgWght) {
        sDualArr[s] = stEdgWght;
      }
    }
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    tDualArr[t] = cNegInfVal;
    Size tNumEdgs = tVtxVecArr[t].size();
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
    const Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tVtxArr[j];
      Val tsEdgWght = tEdgWghtArr[j];
      if (tDualArr[t] < tsEdgWght - sDualArr[s]) {
        tDualArr[t] = tsEdgWght - sDualArr[s];
      }
    }
  }
}

void BptMatchingEngine::rInlzGrdyForCard(const BptGraph& graph, Size* sMateArr,
    Size* tMateArr, Size* card, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  const vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit s.
#endif
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        if (tMateArr[t] == cNullItm) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
          sMateArr[s] = t;
          tMateArr[t] = s;
          ++(*card);
          break;
        }
      }
    }
  }
}

void BptMatchingEngine::rInlzGrdyForEdgWght(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr, Size* card,
    Val* edgWght, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
  *edgWght = 0.0;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  const vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit s.
#endif
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        Val stEdgWght = sEdgWghtArr[i];
        if ((tMateArr[t] == cNullItm) &&
            (tDualArr[t] == stEdgWght - sDualArr[s])) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
          sMateArr[s] = t;
          tMateArr[t] = s;
          ++(*card);
          *edgWght += stEdgWght;
          break;
        }
      }
    }
  }
}

void BptMatchingEngine::rInlzRefinedForEdgWght(const BptGraph& graph,
    Size* sMateArr, Size* tMateArr, Val* sDualArr, Val* tDualArr, Size* card,
    Val* edgWght, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  //Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  std::vector<Size> sSeondEdgeVec;
  ResizeVector<Size>(&sSeondEdgeVec, sNumVtxs);
  Size* sSeondEdgeArr = (sNumVtxs == 0) ? NULL : &sSeondEdgeVec[0];
  if (sSeondEdgeArr != NULL) {
      std::fill(&sSeondEdgeArr[0], &sSeondEdgeArr[sNumVtxs], cNullItm);
    }
  *card = 0;
  *edgWght = 0.0;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  const vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);
  const vector<Val>* sEdgWghtVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSEdgWghtVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTEdgWghtVecVec[0]);
    
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (sMateArr[s] == cNullItm) {
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit s.
#endif
	  Size maxEdgeId=cNullItm;
	  Size secondMaxEdgeId=cNullItm;
	  Val max =0.0;
	  Val max2 =0.0;
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        Val stEdgWght = sEdgWghtArr[i];
        Val slack = stEdgWght - tDualArr[t];
        if(slack >= max2)
        {
        	if(slack >= max)
        	{
        		max2=max;
        		max = slack;
        		secondMaxEdgeId=maxEdgeId;
        		maxEdgeId = t;
			}
			else
			{
				max2 = slack;
				secondMaxEdgeId=t;
			}
        }
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
      }
      
      if(maxEdgeId != cNullItm)
      {
      		if(tMateArr[maxEdgeId]==cNullItm)
      		{
      			sSeondEdgeArr[s]=secondMaxEdgeId;
      			sDualArr[s]=max2;
      			tDualArr[maxEdgeId]=max-max2;
      			sMateArr[s] = maxEdgeId;
	          tMateArr[maxEdgeId] = s;
	         ++(*card);
	          *edgWght += max;
			}
			else
			{
				sDualArr[s]=max;
				Size s2 = tMateArr[maxEdgeId];
				Size t2 =sSeondEdgeArr[s2];
				if( t2 != cNullItm && tMateArr[t2]==cNullItm)
				{
				   sMateArr[s2] = t2;
		          tMateArr[t2] = s2;
		          sMateArr[s] = maxEdgeId;
		          tMateArr[maxEdgeId] = s;
		          ++(*card);
		          *edgWght += max;
				}
				
			}
	  }
    }
  }
}

void BptMatchingEngine::rInlzGrdyForVtxWght(const BptGraph& graph, Size* sMateArr,
    Size* tMateArr,std::pair<Size,Val>* sortedArr, Size* card, bool rvrs) const {
  Size sNumVtxs = (rvrs == false) ? graph.mSNumVtxs : graph.mTNumVtxs;
  Size tNumVtxs = (rvrs == false) ? graph.mTNumVtxs : graph.mSNumVtxs;
  if (sMateArr != NULL) {
    fill(&sMateArr[0], &sMateArr[sNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    fill(&tMateArr[0], &tMateArr[tNumVtxs], cNullItm);
  }
  *card = 0;
#ifdef STATS
  mStats.mNumBfsVstdVtxs = 0;
  mStats.mNumBfsVstdEdgs = 0;
#endif
  const vector<Size>* sVtxVecArr = (rvrs == false) ?
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxVecVec[0]) :
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxVecVec[0]);

  const Val* tVtxWghtArr = (rvrs == false) ?
    ((graph.mTNumVtxs == 0) ? NULL : &graph.mTVtxWghtVec[0]) :
    ((graph.mSNumVtxs == 0) ? NULL : &graph.mSVtxWghtVec[0]);
    
  //for (Size s = 0; s < sNumVtxs; ++s) {
   for (Size current = 0; current < sNumVtxs; ++current) {
    	Size s =  sortedArr[current].first;
    //if (sMateArr[s] == cNullItm) {
    	Val maxVtxWght = cNegInfVal;
    	Size tempT=cNullItm;
    	Size flag=0;
#ifdef STATS
      ++(mStats.mNumBfsVstdVtxs); // visit s.
#endif
      Size sNumEdgs = sVtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
#ifdef STATS
      ++(mStats.mNumBfsVstdEdgs); // visit (s,t).
#endif
        if (tMateArr[t] == cNullItm) {
#ifdef STATS
          ++(mStats.mNumBfsVstdVtxs); // visit t.
#endif
		if (maxVtxWght < tVtxWghtArr[t]) {
          tempT = t;
          maxVtxWght = tVtxWghtArr[t];
        }
        }
        else
        {
        	flag=1;
        	break;
		}
      }
      if(!flag)
      {
      	sMateArr[s] = tempT;
        tMateArr[tempT] = s;
          ++(*card);
	  }
    //}
  }
}

Size BptMatchingEngine::rAugment(Size* sMateArr, Size* tMateArr, Size* sPtrArr,
    Size sLast, Size tLast) const {
  Size s = sLast;
  Size t = tLast;
  Size k = 0;
  while (s != cNullItm) {
    Size tt = sMateArr[s];
    sMateArr[s] = t;
    tMateArr[t] = s;
    s = sPtrArr[s];
    t = tt;
    ++k;
  }
  assert(k > 0);
  return 2 * k - 1;
}

Size BptMatchingEngine::rReverse(Size* sMateArr, Size* tMateArr, Size* sPtrArr,
    Size sLast) const {
  Size s = sPtrArr[sLast];
  Size t = sMateArr[sLast];
  sMateArr[sLast] = cNullItm;
  Size k = 0;
  while (s != cNullItm) {
    Size tt = sMateArr[s];
    sMateArr[s] = t;
    tMateArr[t] = s;
    s = sPtrArr[s];
    t = tt;
    ++k;
  }
  return 2 * k;
}

void BptMatchingEngine::rMergeMatchings(const BptGraph& graph,
    const Size* sMateSArr, const Size* tMateSArr, const Size* sMateTArr,
    const Size* tMateTArr, Size* sMateArr, Size* tMateArr, Size* card) const {
  if (sMateArr != NULL) {
    fill(&sMateArr[0], &sMateArr[graph.mSNumVtxs], cNullItm);
  }
  if (tMateArr != NULL) {
    fill(&tMateArr[0], &tMateArr[graph.mTNumVtxs], cNullItm);
  }
  *card = 0;
  // add M_S edges from symmetric difference paths.
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    if ((sMateSArr[s] != cNullItm) && (sMateTArr[s] == cNullItm)) {
      Size ss = s;
      do {
        Size tt = sMateSArr[ss];
        sMateArr[ss] = tt;
        tMateArr[tt] = ss;
        ++(*card);
        ss = tMateTArr[tt];
      } while ((ss != cNullItm) && (sMateSArr[ss] != cNullItm));
    }
  }
  // add M_T edges from symmetric difference paths.
  for (Size t = 0; t < graph.mTNumVtxs; ++t) {
    if ((tMateTArr[t] != cNullItm) && (tMateSArr[t] == cNullItm)) {
      Size tt = t;
      do {
        Size ss = tMateTArr[tt];
        sMateArr[ss] = tt;
        tMateArr[tt] = ss;
        ++(*card);
        tt = sMateSArr[ss];
      } while ((tt != cNullItm) && (tMateTArr[tt] != cNullItm));
    }
  }
  // add remaining M_S edges.
  for (Size s = 0; s < graph.mSNumVtxs; ++s) {
    if ((sMateSArr[s] != cNullItm) && (sMateArr[s] == cNullItm)) {
      Size t = sMateSArr[s];
      sMateArr[s] = t;
      tMateArr[t] = s;
      ++(*card);
    }
  }
}


