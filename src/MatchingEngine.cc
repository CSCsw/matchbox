#include "MatchingEngine.h"

using namespace std;
using namespace Matchbox;

void MatchingEngine::ComputeMxmlMatching(const Graph& graph,
    vector<Size>* mateVec, Size* card) const {
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  rInlzGrdyForCard(graph, tmpMateArr, &tmpCard);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
}

void MatchingEngine::ComputeMaxCardMatching(const Graph& graph,
    vector<Size>* mateVec, Size* card) const {
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  switch (mCardGraphSrchType) {
  case eSglSrcBfs:
    switch (mQueAndStkType) {
    case eVecQueAndStk:
      rComputeMaxCardMatchingSglSrc2<VecItmQue>(graph, tmpMateArr, &tmpCard);
      break;
    case eLstQueAndStk:
      rComputeMaxCardMatchingSglSrc2<LstItmQue>(graph, tmpMateArr, &tmpCard);
      break;
    default:
      assert(false);
    }
    break;
  default:
    assert(false);
  }
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
}

void MatchingEngine::ComputeMaxVtxWghtMatching(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght, Size augPathLenBnd) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;

  switch (mCardGraphSrchType) 
	{
  case eSglSrcBfs:

    switch (mQueAndStkType) 
		{
    case eVecQueAndStk:

      rComputeMaxVtxWght<VecItmQue, VecItmStk>(graph, tmpMateArr, &tmpCard, &tmpVtxWght, augPathLenBnd);

      break;
    case eLstQueAndStk:
      rComputeMaxVtxWght<LstItmQue, LstItmStk>(graph, tmpMateArr, &tmpCard, &tmpVtxWght, augPathLenBnd);
      break;
    default:
      assert(false);
    		}
    break;
  default:
    assert(false);
  	}
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}

void MatchingEngine::ComputeHalfVtxWghtMatching(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rComputeHalfVtxWghtMatching<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}

void MatchingEngine::ComputeTwoThirdVtxWghtMatching(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rComputeTwoThirdVtxWghtMatching<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}

////
void MatchingEngine::SuitorVtxWghtMatching(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rSuitorVtxWght<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}
/////
void MatchingEngine::ParSuitorVtxWghtMatching(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rParSuitorVtxWght<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}
////
void MatchingEngine::ScaleOneMinusEpsVtxWght(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght, Val ep) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rScaleOneMinusEpsVtxWght<VecItmQue, VecItmStk, LstItmIdxdQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght, ep);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}
////
void MatchingEngine::ComputeHalfEdgWghtMatching(const Graph& graph, std::vector<Size>* mateVec, Size* card, Val* edgWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *edgWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpEdgWght = 0.0;
  rComputeHalfEdgWghtMatching<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpEdgWght);
   // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *edgWght=tmpEdgWght;
}
/////////
void MatchingEngine::PGVtxWghtMatching(const Graph& graph,
     std::vector<Size>* mateVec, Size* card, Val* vtxWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rPGPVtxWght<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}
////

void MatchingEngine::PGDPVtxWght(const Graph& graph, 
std::vector<Size>* mateVec, Size* card, Val* vtxWght) const 
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rPGDPVtxWght<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  // set output. 
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}
////
void MatchingEngine::LocallyDominantVtxWght(const Graph& graph, 
std::vector<Size>* mateVec, Size* card, Val* vtxWght)  const
{
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *vtxWght=0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpVtxWght = 0.0;
  rLocallyDominantVtxWght<VecItmQue>(graph, tmpMateArr, &tmpCard, &tmpVtxWght);
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *vtxWght=tmpVtxWght;
}

void MatchingEngine::ComputeAprxMaxEdgWghtMatching4(const Graph& graph,
    vector<Size>* mateVec, Size* card, Val* edgWght) const {
  // reset output.
  ResizeVector<Size>(mateVec, 0);
  *card = 0;
  *edgWght = 0.0;
  vector<Size> tmpMateVec;
  ResizeVector<Size>(&tmpMateVec, graph.mNumVtxs);
  Size* tmpMateArr = (graph.mNumVtxs == 0) ? NULL : &tmpMateVec[0];
  Size tmpCard = 0;
  Val tmpEdgWght = 0.0;
  switch (mQueAndStkType) {
  case eVecQueAndStk:
    rComputeAprxMaxEdgWghtMatching4<VecItmQue>
      (graph, tmpMateArr, &tmpCard, &tmpEdgWght);
    break;
  case eLstQueAndStk:
    rComputeAprxMaxEdgWghtMatching4<LstItmQue>
      (graph, tmpMateArr, &tmpCard, &tmpEdgWght);
    break;
  default:
    assert(false);
  }
  // set output.
  mateVec->swap(tmpMateVec);
  *card = tmpCard;
  *edgWght = tmpEdgWght;
}

Err MatchingEngine::GetMatchedEdgWght(const Graph& graph,
    const vector<Size>& mateVec, Size card, Val *edgWght) const {
  if (CheckMatching(graph, mateVec, card) == false) {
    return eErrInvMatching;
  }
  const vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  const vector<Val>*
    edgWghtVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mEdgWghtVecVec[0];
  const Size* mateArr = (graph.mNumVtxs == 0) ? NULL : &mateVec[0];
  vector<Val> edgWghtVec;
  ResizeVector<Val>(&edgWghtVec, card);
  Val* edgWghtArr = (card == 0) ? NULL : &edgWghtVec[0];
  for (Size s = 0, k = 0; s < graph.mNumVtxs; ++s) {
    Size t = mateArr[s];
    if (t == cNullItm) {
      continue;
    }
    if (t < s) {
      // avoid double counting.
      continue;
    }
    assert(t > s);
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &edgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      if (sVtxArr[i] == t) {
        edgWghtArr[k] = sEdgWghtArr[i];
        ++k;
        break;
      }
    }
  }
  sort(edgWghtVec.begin(), edgWghtVec.end());
  *edgWght = accumulate(edgWghtVec.begin(), edgWghtVec.end(), 0.0);
  return eErrNone;
}

Err MatchingEngine::GetMatchedVtxWght(const Graph& graph,
    const vector<Size>& mateVec, Size card, Val *vtxWght, Val *edgWght) const {
  if (CheckMatching(graph, mateVec, card) == false) {
    return eErrInvMatching;
  }
  const Val*
    vtxWghtArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxWghtVec[0];
  const Size* mateArr = (graph.mNumVtxs == 0) ? NULL : &mateVec[0];
  vector<Val> tmpVtxWghtVec;
  ResizeVector<Val>(&tmpVtxWghtVec, card);
  Val* tmpVtxWghtArr = (card == 0) ? NULL : &tmpVtxWghtVec[0];
  for (Size s = 0, i = 0; s < graph.mNumVtxs; ++s) {
    if (mateArr[s] != cNullItm) {
      tmpVtxWghtArr[i] = vtxWghtArr[s];
      ++i;
    }
  }
  sort(tmpVtxWghtVec.begin(), tmpVtxWghtVec.end());
  *vtxWght = accumulate(tmpVtxWghtVec.begin(), tmpVtxWghtVec.end(), 0.0);
  *edgWght = *vtxWght;
  return eErrNone;
}

bool MatchingEngine::CheckMatching(const Graph& graph,
    const vector<Size>& mateVec, Size card) const {
  // check if the number of vertices is consistent.
  if (graph.mNumVtxs != mateVec.size()) {
    return false;
  }
  assert(card <= mateVec.size());
  const vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  const Size* mateArr = (graph.mNumVtxs == 0) ? NULL : &mateVec[0];
  // check the matching.
  for (Size s = 0; s < graph.mNumVtxs; ++s) {
    Size t = mateArr[s];
    if (t != cNullItm) {
      assert(t < graph.mNumVtxs);
      assert(s != t);
      if(mateArr[t] != s)
      {
      	cout << "the problem is the mate of " <<s<< " is  "<<mateArr[s]<< " but the mate of "<<t<< " is "<< mateArr[t]<<endl;
	  }
      assert(mateArr[t] == s);
      // check if there is an edge between s and t.
      if (find(vtxVecArr[s].begin(), vtxVecArr[s].end(), t) ==
          vtxVecArr[s].end()) {
          	cout << "the problem is there is no edge between " <<s<< " and "<<t<< endl;
        return false;
      }
    }
  }
  return true;
}

void MatchingEngine::PrintMatching(const vector<Size>& mateVec, Size card)
    const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "Matching (begin)" << endl;
  cout << "cardinality: " << card << endl;
  if (mFullPrint == true) {
    cout << "mates:";
    for (vector<Size>::const_iterator it = mateVec.begin();
         it != mateVec.end(); ++it) {
      cout << " " << *it;
    }
    cout << endl;
  }
  cout << "Matching (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void MatchingEngine::PrintMatching(const vector<Size>& mateVec, Size card,
    Val wght) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "Matching (begin)" << endl;
  cout << "cardinality: " << card << endl;
  cout.setf(ios::left | ios::scientific | ios::showpoint);
  cout.precision(mPrecision);
  cout << "weight: " << wght << endl;
  cout.unsetf(ios::left | ios::scientific | ios::showpoint);
  if (mFullPrint == true) {
    cout << "mates:";
    for (vector<Size>::const_iterator it = mateVec.begin();
         it != mateVec.end(); ++it) {
      cout << " " << *it + 1;
    }
    cout << endl;
  }
  cout << "Matching (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

void MatchingEngine::rInlzGrdyForCard(const Graph& graph, Size* mateArr,
    Size* card) const {
  if (mateArr != NULL) {
    fill(&mateArr[0], &mateArr[graph.mNumVtxs], cNullItm);
  }
  *card = 0;
  const vector<Size>*
    vtxVecArr = (graph.mNumVtxs == 0) ? NULL : &graph.mVtxVecVec[0];
  for (Size s = 0; s < graph.mNumVtxs; ++s) {
    if (mateArr[s] == cNullItm) {
      Size sNumEdgs = vtxVecArr[s].size();
      const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
      for (Size i = 0; i < sNumEdgs; ++i) {
        Size t = sVtxArr[i];
        assert(s != t);
        if (mateArr[t] == cNullItm) {
          mateArr[s] = t;
          mateArr[t] = s;
          ++(*card);
          break;
        }
      }
    }
  }
}

void MatchingEngine::rAugment(Size* mateArr, Size* ptr1Arr, Size* ptr2Arr,
    Size sLast, Size tLast) const {
  mateArr[tLast] = sLast;
  list<Size> augStk;
  augStk.push_back(tLast);
  augStk.push_back(sLast);
  while (augStk.size() > 0) {
    Size s = augStk.back();
    augStk.pop_back();
    Size t = augStk.back();
    augStk.pop_back();
    Size tt = mateArr[s];
    mateArr[s] = t;
    if (tt == cNullItm) {
      continue;
    }
    if (mateArr[tt] != s) {
      continue;
    }
    Size s1 = ptr1Arr[s];
    Size s2 = ptr2Arr[s];
    if (s2 == cNullItm) {
      mateArr[tt] = s1;
      augStk.push_back(tt);
      augStk.push_back(s1);
    } else {
      augStk.push_back(s2);
      augStk.push_back(s1);
      augStk.push_back(s1);
      augStk.push_back(s2);
    }
  }
}

void MatchingEngine::rAugment(Size* mateArr, Size* ptr1Arr, Size* ptr2Arr,
    Size sLast, Size tLast, Val* alen) const {
  mateArr[tLast] = sLast;
  list<Size> augStk;
  augStk.push_back(tLast);
  augStk.push_back(sLast);
  while (augStk.size() > 0) {
    Size s = augStk.back();
    augStk.pop_back();
    Size t = augStk.back();
    augStk.pop_back();
    Size tt = mateArr[s];
    mateArr[s] = t;
    (*alen)++;
    if (tt == cNullItm) {
      continue;
    }
    if (mateArr[tt] != s) {
      continue;
    }
    Size s1 = ptr1Arr[s];
    Size s2 = ptr2Arr[s];
    if (s2 == cNullItm) {
      mateArr[tt] = s1;
      //(*alen)++;
      augStk.push_back(tt);
      augStk.push_back(s1);
    } else {
      augStk.push_back(s2);
      augStk.push_back(s1);
      augStk.push_back(s1);
      augStk.push_back(s2);
    }
  }
}

void MatchingEngine::fix(Size* mateArr, Size* ptr1Arr, Size* ptr2Arr,
    Size sLast, Size tLast) const {
    Size l = mateArr[tLast];
    mateArr[l]=cNullItm;
	Size temps1 = ptr1Arr[l];
	Size temps2 = ptr2Arr[l];
	if(temps2 == cNullItm)
	{
		mateArr[tLast] = sLast;
	}
	
  list<Size> augStk;
  
  	
  if(temps1 != cNullItm && temps2 != cNullItm)
	{
	  augStk.push_back(ptr2Arr[l]);
      augStk.push_back(ptr1Arr[l]);
      augStk.push_back(ptr1Arr[l]);
      augStk.push_back(ptr2Arr[l]);
		
	}
	else 
	{
        augStk.push_back(tLast);
  		augStk.push_back(sLast);
	}
  
  while (augStk.size() > 0) {

    Size s = augStk.back();
    augStk.pop_back();
    Size t = augStk.back();
    augStk.pop_back();

    Size tt = mateArr[s];
    mateArr[s] = t;
    if (tt == cNullItm) {

      continue;
    }
    if (mateArr[tt] != s) {
      continue;
    }

    Size s1 = ptr1Arr[s];
    Size s2 = ptr2Arr[s];
    if (s2 == cNullItm) {
      mateArr[tt] = s1;
      augStk.push_back(tt);
      augStk.push_back(s1);
    } else {
      augStk.push_back(s2);
      augStk.push_back(s1);
      augStk.push_back(s1);
      augStk.push_back(s2);
    }
  }
}

Size MatchingEngine::rFind(Size* linkArr, Size u) const {
  Size uu = u;
  while (uu != linkArr[uu]) {
    uu = linkArr[uu];
  }
  Size v = uu;
  uu = u;
  while (uu != v) {
    Size uuu = linkArr[uu];
    linkArr[uu] = v;
    uu = uuu;
  }
  return v;
}

void MatchingEngine::rUnion(Size* linkArr, Size* rankArr, Size u, Size v)
    const {
  rLink(linkArr, rankArr, rFind(linkArr, u), rFind(linkArr, v));
}

void MatchingEngine::rLink(Size* linkArr, Size* rankArr, Size u, Size v)
    const {
  if (rankArr[u] > rankArr[v]) {
    linkArr[v] = u;
  } else {
    linkArr[u] = v;
    if (rankArr[u] == rankArr[v]) {
      ++(rankArr[v]);
    }
  }
}

Size MatchingEngine::logbase2(Val x) const {
    return 32 - __builtin_clz((Size)x) - 1;
}



