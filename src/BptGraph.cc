#include "BptGraph.h"

using namespace std;
using namespace Matchbox;

void BptGraph::GetEdgs(vector<Size>* sVtxVec, vector<Size>* tVtxVec,
    vector<Val>* edgWghtVec) const {
  // reset output.
  ResizeVector<Size>(sVtxVec, 0);
  ResizeVector<Size>(tVtxVec, 0);
  ResizeVector<Val>(edgWghtVec, 0);
  const vector<Size>* sVtxVecArr = (mSNumVtxs == 0) ? NULL : &mSVtxVecVec[0];
  const vector<Val>*
    sEdgWghtVecArr = (mSNumVtxs == 0) ? NULL : &mSEdgWghtVecVec[0];
  vector<Size> tmpSVtxVec;
  ResizeVector<Size>(&tmpSVtxVec, mNumEdgs);
  Size* tmpSVtxArr = (mNumEdgs == 0) ? NULL : &tmpSVtxVec[0];
  vector<Size> tmpTVtxVec;
  ResizeVector<Size>(&tmpTVtxVec, mNumEdgs);
  Size* tmpTVtxArr = (mNumEdgs == 0) ? NULL : &tmpTVtxVec[0];
  vector<Val> tmpEdgWghtVec;
  ResizeVector<Val>(&tmpEdgWghtVec, mNumEdgs);
  Val* tmpEdgWghtArr = (mNumEdgs == 0) ? NULL : &tmpEdgWghtVec[0];
  for (Size s = 0, k = 0; s < mSNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      Val stEdgWght = sEdgWghtArr[i];
      tmpSVtxArr[k] = s;
      tmpTVtxArr[k] = t;
      tmpEdgWghtArr[k] = stEdgWght;
      ++k;
    }
  }
  // set output.
  sVtxVec->swap(tmpSVtxVec);
  tVtxVec->swap(tmpTVtxVec);
  edgWghtVec->swap(tmpEdgWghtVec);
}

Err BptGraph::GetAdj(Size sVtx, Size* sNumEdgs, vector<Size>* sVtxVec,
    vector<Val>* sEdgWghtVec, bool rvrs) const {
  // reset output.
  *sNumEdgs = 0;
  ResizeVector<Size>(sVtxVec, 0);
  ResizeVector<Val>(sEdgWghtVec, 0);
  Size sNumVtxs = (rvrs == false) ? mSNumVtxs : mTNumVtxs;
  // check if the S-vertex is within the allowed range.
  if (sVtx >= sNumVtxs) {
    return eErrInvVtx;
  }
  const vector<vector<Size> >* sVtxVecVec = (rvrs == false) ?
    &mSVtxVecVec : &mTVtxVecVec;
  const vector<vector<Val> >* sEdgWghtVecVec = (rvrs == false) ?
    &mSEdgWghtVecVec : &mTEdgWghtVecVec;
  Size tmpSNumEdgs = (*sVtxVecVec)[sVtx].size();
  vector<Size> tmpSVtxVec;
  ResizeVector<Size>(&tmpSVtxVec, tmpSNumEdgs);
  vector<Val> tmpSEdgWghtVec;
  ResizeVector<Val>(&tmpSEdgWghtVec, tmpSNumEdgs);
  copy((*sVtxVecVec)[sVtx].begin(), (*sVtxVecVec)[sVtx].end(),
       tmpSVtxVec.begin());
  copy((*sEdgWghtVecVec)[sVtx].begin(), (*sEdgWghtVecVec)[sVtx].end(),
       tmpSEdgWghtVec.begin());
  // set output.
  *sNumEdgs = tmpSNumEdgs;
  sVtxVec->swap(tmpSVtxVec);
  sEdgWghtVec->swap(tmpSEdgWghtVec);
  return eErrNone;
}

void BptGraph::GetVtxWghts(vector<Val>* sVtxWghtVec, vector<Val>* tVtxWghtVec)
    const {
  // reset output.
  ResizeVector<Val>(sVtxWghtVec, 0);
  ResizeVector<Val>(tVtxWghtVec, 0);
  vector<Val> tmpSVtxWghtVec;
  ResizeVector<Val>(&tmpSVtxWghtVec, mSNumVtxs);
  vector<Val> tmpTVtxWghtVec;
  ResizeVector<Val>(&tmpTVtxWghtVec, mTNumVtxs);
  copy(mSVtxWghtVec.begin(), mSVtxWghtVec.end(), tmpSVtxWghtVec.begin());
  copy(mTVtxWghtVec.begin(), mTVtxWghtVec.end(), tmpTVtxWghtVec.begin());
  // set output.
  sVtxWghtVec->swap(tmpSVtxWghtVec);
  tVtxWghtVec->swap(tmpTVtxWghtVec);
}

void BptGraph::GetVtxDgrs(vector<Size>* sVtxDgrVec, vector<Size>* tVtxDgrVec)
    const {
  // reset output.
  ResizeVector<Size>(sVtxDgrVec, 0);
  ResizeVector<Size>(tVtxDgrVec, 0);
  vector<Size> tmpSVtxDgrVec;
  ResizeVector<Size>(&tmpSVtxDgrVec, mSNumVtxs);
  Size* tmpSVtxDgrArr = (mSNumVtxs == 0) ? NULL : &tmpSVtxDgrVec[0];
  vector<Size> tmpTVtxDgrVec;
  ResizeVector<Size>(&tmpTVtxDgrVec, mTNumVtxs);
  Size* tmpTVtxDgrArr = (mTNumVtxs == 0) ? NULL : &tmpTVtxDgrVec[0];
  const vector<Size>* sVtxVecArr = (mSNumVtxs == 0) ? NULL : &mSVtxVecVec[0];
  const vector<Size>* tVtxVecArr = (mTNumVtxs == 0) ? NULL : &mTVtxVecVec[0];
  for (Size s = 0; s < mSNumVtxs; ++s) {
    tmpSVtxDgrArr[s] = sVtxVecArr[s].size();
  }
  for (Size t = 0; t < mTNumVtxs; ++t) {
    tmpTVtxDgrArr[t] = tVtxVecArr[t].size();
  }
  // set output.
  sVtxDgrVec->swap(tmpSVtxDgrVec);
  tVtxDgrVec->swap(tmpTVtxDgrVec);
}

void BptGraph::Print(void) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "BptGraph (begin)" << endl;
  cout << "number of S-vertices: " << mSNumVtxs << endl;
  cout << "number of T-vertices: " << mTNumVtxs << endl;
  cout << "number of edges: " << mNumEdgs << endl;
  // TODO: maintain isolated vertex counters in the data structure.
  Size sNumIsolatedVtxs = 0;
  Size tNumIsolatedVtxs = 0;
  for (vector<vector<Size> >::const_iterator it = mSVtxVecVec.begin();
       it != mSVtxVecVec.end(); ++it) {
    if (it->size() == 0) {
      ++sNumIsolatedVtxs;
    }
  }
  for (vector<vector<Size> >::const_iterator it = mTVtxVecVec.begin();
       it != mTVtxVecVec.end(); ++it) {
    if (it->size() == 0) {
      ++tNumIsolatedVtxs;
    }
  }
  cout << "number of isolated S-vertices: " << sNumIsolatedVtxs << endl;
  cout << "number of isolated T-vertices: " << tNumIsolatedVtxs << endl;
  if (mFullPrint == true) {
    cout.setf(ios::left | ios::scientific | ios::showpoint);
    cout.precision(mPrecision);
    cout << "S-vertex weights:";
    for (vector<Val>::const_iterator it = mSVtxWghtVec.begin();
         it != mSVtxWghtVec.end(); ++it) {
      cout << " " << *it;
    }
    cout << endl;
    cout << "T-vertex weights:";
    for (vector<Val>::const_iterator it = mTVtxWghtVec.begin();
         it != mTVtxWghtVec.end(); ++it) {
      cout << " " << *it;
    }
    cout << endl;
    cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    Size s = 0;
    for (vector<vector<Size> >::const_iterator it1 = mSVtxVecVec.begin();
         it1 != mSVtxVecVec.end(); ++it1) {
      cout << "S-adjacency(" << s + 1 << "):";
      for (vector<Size>::const_iterator it2 = it1->begin(); it2 != it1->end();
           ++it2) {
        cout << " " << *it2 + 1;
      }
      cout << endl;
      ++s;
    }
    Size t = 0;
    for (vector<vector<Size> >::const_iterator it1 = mTVtxVecVec.begin();
         it1 != mTVtxVecVec.end(); ++it1) {
      cout << "T-adjacency(" << t + 1 << "):";
      for (vector<Size>::const_iterator it2 = it1->begin(); it2 != it1->end();
           ++it2) {
        cout << " " << *it2 + 1;
      }
      cout << endl;
      ++t;
    }
  }
  cout << "BptGraph (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

Err BptGraph::Set(Size sNumVtxs, Size tNumVtxs, Size numEdgs,
    const vector<Size>& sVtxVec, const vector<Size>& tVtxVec,
    const vector<Val>& edgWghtVec) {
  // reset object.
  Clear();
  // check if the number of S-vertices is within the allowed range.
  if (sNumVtxs >= cInfSize) {
    return eErrInvNumVtxs;
  }
  // check if the number of T-vertices is within the allowed range.
  if (tNumVtxs >= cInfSize) {
    return eErrInvNumVtxs;
  }
  // check if the number of edges is within the allowed range.
  if (numEdgs >= cInfSize) {
    return eErrInvNumEdgs;
  }
  // check if the input is consistent.
  if (sVtxVec.size() != numEdgs) {
    return eErrInvInput;
  }
  if (tVtxVec.size() != numEdgs) {
    return eErrInvInput;
  }
  if (edgWghtVec.size() != numEdgs) {
    return eErrInvInput;
  }
  // check if the S-vertices are within the allowed range.
  if (find_if(sVtxVec.begin(), sVtxVec.end(),
              bind2nd(greater_equal<Size>(), sNumVtxs))
      != sVtxVec.end()) {
    return eErrInvVtx;
  }
  // check if the T-vertices are within the allowed range.
  if (find_if(tVtxVec.begin(), tVtxVec.end(),
              bind2nd(greater_equal<Size>(), tNumVtxs))
      != tVtxVec.end()) {
    return eErrInvVtx;
  }
  // check if the edge weights are nonnegative.
  if (find_if(edgWghtVec.begin(), edgWghtVec.end(),
              bind2nd(less<Val>(), cZeroVal))
      != edgWghtVec.end()) {
    return eErrInvWght;
  }
  Size tmpNumEdgs = numEdgs;
  vector<vector<Size> > sVtxVecVec;
  vector<vector<Size> > tVtxVecVec;
  vector<vector<Val> > sEdgWghtVecVec;
  vector<vector<Val> > tEdgWghtVecVec;
  rFormAdjs(sNumVtxs, tNumVtxs, &tmpNumEdgs, sVtxVec, tVtxVec, edgWghtVec,
            &sVtxVecVec, &tVtxVecVec, &sEdgWghtVecVec, &tEdgWghtVecVec);
  // the vertex weights are set to zero.
  vector<Val> sVtxWghtVec;
  ResizeVector<Val>(&sVtxWghtVec, sNumVtxs);
  fill(sVtxWghtVec.begin(), sVtxWghtVec.end(), cZeroVal);
  vector<Val> tVtxWghtVec;
  ResizeVector<Val>(&tVtxWghtVec, tNumVtxs);
  fill(tVtxWghtVec.begin(), tVtxWghtVec.end(), cZeroVal);
  // set object.
  mSNumVtxs = sNumVtxs;
  mTNumVtxs = tNumVtxs;
  mNumEdgs = tmpNumEdgs;
  mSVtxVecVec.swap(sVtxVecVec);
  mTVtxVecVec.swap(tVtxVecVec);
  mSEdgWghtVecVec.swap(sEdgWghtVecVec);
  mTEdgWghtVecVec.swap(tEdgWghtVecVec);
  mSVtxWghtVec.swap(sVtxWghtVec);
  mTVtxWghtVec.swap(tVtxWghtVec);
  return eErrNone;
}

Err BptGraph::SetVtxWghts(const vector<Val>& sVtxWghtVec,
    const vector<Val>& tVtxWghtVec) {
  // check the size of the input.
  if (sVtxWghtVec.size() != mSNumVtxs) {
    return eErrInvNumVtxs;
  }
  if (tVtxWghtVec.size() != mTNumVtxs) {
    return eErrInvNumVtxs;
  }
  // check if the vertex weights are nonnegative.
  if (find_if(sVtxWghtVec.begin(), sVtxWghtVec.end(),
              bind2nd(less<Val>(), cZeroVal))
      != sVtxWghtVec.end()) {
    return eErrInvWght;
  }
  if (find_if(tVtxWghtVec.begin(), tVtxWghtVec.end(),
              bind2nd(less<Val>(), cZeroVal))
      != tVtxWghtVec.end()) {
    return eErrInvWght;
  }
  copy(sVtxWghtVec.begin(), sVtxWghtVec.end(), mSVtxWghtVec.begin());
  copy(tVtxWghtVec.begin(), tVtxWghtVec.end(), mTVtxWghtVec.begin());
  return eErrNone;
}

void BptGraph::SetEdgWghtsFromVtxWghts(void) {
  const vector<Size>* sVtxVecArr = (mSNumVtxs == 0) ? NULL : &mSVtxVecVec[0];
  const vector<Size>* tVtxVecArr = (mTNumVtxs == 0) ? NULL : &mTVtxVecVec[0];
  vector<Val>* sEdgWghtVecArr = (mSNumVtxs == 0) ? NULL : &mSEdgWghtVecVec[0];
  vector<Val>* tEdgWghtVecArr = (mTNumVtxs == 0) ? NULL : &mTEdgWghtVecVec[0];
  const Val* sVtxWghtArr = (mSNumVtxs == 0) ? NULL : &mSVtxWghtVec[0];
  const Val* tVtxWghtArr = (mTNumVtxs == 0) ? NULL : &mTVtxWghtVec[0];
  for (Size s = 0; s < mSNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      sEdgWghtArr[i] = sVtxWghtArr[s] + tVtxWghtArr[t];
    }
  }
  for (Size t = 0; t < mTNumVtxs; ++t) {
    Size tNumEdgs = tVtxVecArr[t].size();
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
    Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tVtxArr[j];
      tEdgWghtArr[j] = sVtxWghtArr[s] + tVtxWghtArr[t];
    }
  }
}

Err BptGraph::Read(const string& fileName, bool zeroBased) {
  // reset object.
  Clear();
  // TODO: report line number in case of error.
  ifstream fin(fileName.c_str());
  if (!fin) {
    return eErrFileOpen;
  }
  // skip comment lines.
  while (fin.peek() == '%') {
    const size_t numChars = 1024;
    char line[numChars];
    fin.getline(line, numChars);
    if (fin.eof()) {
      return eErrInvFile;
    }
  }
  Size sNumVtxs;
  fin >> sNumVtxs;
  if (fin.eof()) {
    return eErrInvFile;
  }
  // check if the number of S-vertices is within the allowed range.
  if (sNumVtxs >= cInfSize) {
    return eErrInvNumVtxs;
  }
  Size tNumVtxs;
  fin >> tNumVtxs;
  if (fin.eof()) {
    return eErrInvFile;
  }
  // check if the number of T-vertices is within the allowed range.
  if (tNumVtxs >= cInfSize) {
    return eErrInvNumVtxs;
  }
  Size numEdgs;
  fin >> numEdgs;
  if (fin.eof()) {
    return eErrInvFile;
  }
  // check if the number of edges is within the allowed range.
  if (numEdgs >= cInfSize) {
    return eErrInvNumEdgs;
  }
  Size sFirstVtx = 0;
  Size sLastVtx = sNumVtxs;
  Size tFirstVtx = 0;
  Size tLastVtx = tNumVtxs;
  if (zeroBased == false) {
    ++sFirstVtx;
    ++sLastVtx;
    ++tFirstVtx;
    ++tLastVtx;
  }
  vector<Size> sVtxVec;
  ResizeVector<Size>(&sVtxVec, numEdgs);
  Size* sVtxArr = (numEdgs == 0) ? NULL : &sVtxVec[0];
  vector<Size> tVtxVec;
  ResizeVector<Size>(&tVtxVec, numEdgs);
  Size* tVtxArr = (numEdgs == 0) ? NULL : &tVtxVec[0];
  vector<Val> edgWghtVec;
  ResizeVector<Val>(&edgWghtVec, numEdgs);
  Val* edgWghtArr = (numEdgs == 0) ? NULL : &edgWghtVec[0];
  
  fin.ignore();
  streampos oldpos = fin.tellg();
  const size_t numChars = 1024;
  char line[numChars];
  fin.getline(line, numChars);
  int tn1=0,tn2=0,tnz2=0;
  double tnz=0.0;
  bool binary;
  if(sscanf(line, "%d %d %lf", &tn1, &tn2, &tnz) == 3 || sscanf(line, "%d %d %d", &tn1, &tn2, &tnz2) == 3)
	binary=false;
   else
    binary=true;
   fin.seekg (oldpos);
   
  for (Size k = 0; k < numEdgs; ++k) {
    fin >> sVtxArr[k];
    if (fin.eof()) {
      return eErrInvFile;
    }
    // check if the S-vertices is within the allowed range.
    if ((sVtxArr[k] < sFirstVtx) || (sVtxArr[k] >= sLastVtx)) {
      return eErrInvVtx;
    }
    if (zeroBased == false) {
      --(sVtxArr[k]);
    }
    fin >> tVtxArr[k];
    if (fin.eof()) {
      return eErrInvFile;
    }
    // check if the T-vertices is within the allowed range.
    if ((tVtxArr[k] < tFirstVtx) || (tVtxArr[k] >= tLastVtx)) {
      return eErrInvVtx;
    }
    if (zeroBased == false) {
      --(tVtxArr[k]);
    }
    if(!binary)
    {
	    fin >> edgWghtArr[k];
	    if (fin.eof()) {
	      return eErrInvFile;
	    }
	    // force nonnegative edge weights.
	    if (edgWghtArr[k] < cZeroVal) {
	      edgWghtArr[k] = -edgWghtArr[k];
	    }
   }
   else
   {
   		edgWghtArr[k]=1;
   }
  }
  vector<vector<Size> > sVtxVecVec;
  vector<vector<Size> > tVtxVecVec;
  vector<vector<Val> > sEdgWghtVecVec;
  vector<vector<Val> > tEdgWghtVecVec;
  rFormAdjs(sNumVtxs, tNumVtxs, &numEdgs, sVtxVec, tVtxVec, edgWghtVec,
            &sVtxVecVec, &tVtxVecVec, &sEdgWghtVecVec, &tEdgWghtVecVec);
  // the vertex weights are set to zero.
  vector<Val> sVtxWghtVec;
  ResizeVector<Val>(&sVtxWghtVec, sNumVtxs);
  fill(sVtxWghtVec.begin(), sVtxWghtVec.end(), cZeroVal);
  vector<Val> tVtxWghtVec;
  ResizeVector<Val>(&tVtxWghtVec, tNumVtxs);
  fill(tVtxWghtVec.begin(), tVtxWghtVec.end(), cZeroVal);
  // set object.
  mSNumVtxs = sNumVtxs;
  mTNumVtxs = tNumVtxs;
  mNumEdgs = numEdgs;
  mSVtxVecVec.swap(sVtxVecVec);
  mTVtxVecVec.swap(tVtxVecVec);
  mSEdgWghtVecVec.swap(sEdgWghtVecVec);
  mTEdgWghtVecVec.swap(tEdgWghtVecVec);
  mSVtxWghtVec.swap(sVtxWghtVec);
  mTVtxWghtVec.swap(tVtxWghtVec);
  return eErrNone;
}

//////////////////////////////////////////////////////////////////////Ahmed begining///////////////////
Err BptGraph::ReadWeights(const string& fileName, bool zeroBased) {
  // reset object.
  //Clear();
  // TODO: report line number in case of error.
  ifstream fin(fileName.c_str());
  if (!fin) {
    return eErrFileOpen;
  }
  // skip comment lines.
  while (fin.peek() == '%') {
    const size_t numChars = 1024;
    char line[numChars];
    fin.getline(line, numChars);
    if (fin.eof()) {
      return eErrInvFile;
    }
  }
  
  Size numVtxs;
  fin >> numVtxs;
  if (fin.eof()) {
    return eErrInvFile;
  }
  // check if the number of vertices is within the allowed range.
  if (numVtxs >= cInfSize) {
    return eErrInvNumVtxs;
  }
    Size sNumVtxs;
  Size tNumVtxs;
  vector<Val> sVtxWghtVec;
  vector<Val> tVtxWghtVec;
  GetNumVtxs(&sNumVtxs, &tNumVtxs);
  
  ResizeVector<Val>(&sVtxWghtVec, sNumVtxs);
  ResizeVector<Val>(&tVtxWghtVec, tNumVtxs);
  
  for (Size s = 0; s < sNumVtxs; ++s) {
    fin >> sVtxWghtVec[s];
    //cout << "s read vertex weight " <<sVtxWghtVec[s]<< " for vertex "<< s<< endl;
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
   fin >> tVtxWghtVec[t];
   
   //cout << "t read vertex weight " <<tVtxWghtVec[t]<< " for vertex "<< t<< endl;
  }
  
   SetVtxWghts(sVtxWghtVec, tVtxWghtVec);
    //vector<Val> vtxWghtVec;
   //ResizeVector<Val>(&vtxWghtVec, numVtxs);
   //Val* vtxWghtArr = (numVtxs == 0) ? NULL : &vtxWghtVec[0];
 
  /*for (Size k = 0; k < numVtxs; ++k) {
    fin >> vtxWghtArr[k];
    if (fin.eof()) {
      return eErrInvFile;
    }
  }*/
  //copy(vtxWghtVec.begin(), vtxWghtVec.end(), this->mVtxWghtVec.begin());
 //mVtxWghtVec.swap(vtxWghtVec);
  return eErrNone;
}
////////////////////////////////////////////////////////////////////////////////////////////////

Err BptGraph::Symmetrize(void) {
  if (mSNumVtxs != mTNumVtxs) {
    return eErrInvNumVtxs;
  }
  vector<Size>* sVtxVecArr = (mSNumVtxs == 0) ? NULL : &mSVtxVecVec[0];
  vector<Size>* tVtxVecArr = (mTNumVtxs == 0) ? NULL : &mTVtxVecVec[0];
  vector<Val>* sEdgWghtVecArr = (mSNumVtxs == 0) ? NULL : &mSEdgWghtVecVec[0];
  vector<Val>* tEdgWghtVecArr = (mTNumVtxs == 0) ? NULL : &mTEdgWghtVecVec[0];
  // use temporary adjacencies for merging.
  // compute the temporary adjacency sizes.
  vector<Size> numEdgsVec;
  ResizeVector<Size>(&numEdgsVec, mSNumVtxs);
  Size* numEdgsArr = (mSNumVtxs == 0) ? NULL : &numEdgsVec[0];
  if (numEdgsArr != NULL) {
    fill(&numEdgsArr[0], &numEdgsArr[mSNumVtxs], 0);
  }
  Size numEdgs = 0;
  for (Size s = 0; s < mSNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    Size tNumEdgs = tVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    const Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[s][0];
    Size i = 0;
    Size j = 0;
    Size sNumMissingEdgs = 0;
    Size tNumMissingEdgs = 0;
    Size numCommonEdgs = 0;
    while ((i < sNumEdgs) && (j < tNumEdgs)) {
      if (sVtxArr[i] < tVtxArr[j]) {
        ++tNumMissingEdgs;
        ++i;
      } else if (sVtxArr[i] > tVtxArr[j]) {
        ++sNumMissingEdgs;
        ++j;
      } else {
        if (sEdgWghtArr[i] != tEdgWghtArr[j]) {
          return eErrNotSymmetrizable;
        }
        ++numCommonEdgs;
        ++i;
        ++j;
      }
    }
    // leftovers.
    sNumMissingEdgs += tNumEdgs - j;
    tNumMissingEdgs += sNumEdgs - i;
    numEdgsArr[s] = numCommonEdgs;
    if (CanAdd(numEdgsArr[s], sNumMissingEdgs) == false) {
      return eErrInvNumEdgs;
    }
    numEdgsArr[s] += sNumMissingEdgs;
    if (CanAdd(numEdgsArr[s], tNumMissingEdgs) == false) {
      return eErrInvNumEdgs;
    }
    numEdgsArr[s] += tNumMissingEdgs;
    if (CanAdd(numEdgs, numEdgsArr[s]) == false) {
      return eErrInvNumEdgs;
    }
    numEdgs += numEdgsArr[s];
  }
  // set up the temporary adjacencies.
  vector<vector<Size> > tmpSVtxVecVec;
  ResizeVector<vector<Size> >(&tmpSVtxVecVec, mSNumVtxs);
  vector<Size>* tmpSVtxVecArr = (mSNumVtxs == 0) ? NULL : &tmpSVtxVecVec[0];
  vector<vector<Size> > tmpTVtxVecVec;
  ResizeVector<vector<Size> >(&tmpTVtxVecVec, mTNumVtxs);
  vector<Size>* tmpTVtxVecArr = (mTNumVtxs == 0) ? NULL : &tmpTVtxVecVec[0];
  vector<vector<Val> > tmpSEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpSEdgWghtVecVec, mSNumVtxs);
  vector<Val>* tmpSEdgWghtVecArr =
    (mSNumVtxs == 0) ? NULL : &tmpSEdgWghtVecVec[0];
  vector<vector<Val> > tmpTEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpTEdgWghtVecVec, mTNumVtxs);
  vector<Val>* tmpTEdgWghtVecArr =
    (mTNumVtxs == 0) ? NULL : &tmpTEdgWghtVecVec[0];
  for (Size s = 0; s < mSNumVtxs; ++s) {
    ResizeVector<Size>(&tmpSVtxVecArr[s], numEdgsArr[s]);
    ResizeVector<Val>(&tmpSEdgWghtVecArr[s], numEdgsArr[s]);
  }
  for (Size t = 0; t < mTNumVtxs; ++t) {
    ResizeVector<Size>(&tmpTVtxVecArr[t], numEdgsArr[t]);
    ResizeVector<Val>(&tmpTEdgWghtVecArr[t], numEdgsArr[t]);
  }
  // release unused memory.
  ResizeVector<Size>(&numEdgsVec, 0);
  // merge the adjacencies.
  for (Size s = 0; s < mSNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    Size tNumEdgs = tVtxVecArr[s].size();
    Size tmpNumEdgs = tmpSVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    const Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[s][0];
    Size* tmpSVtxArr = (tmpNumEdgs == 0) ? NULL : &tmpSVtxVecArr[s][0];
    Size* tmpTVtxArr = (tmpNumEdgs == 0) ? NULL : &tmpTVtxVecArr[s][0];
    Val* tmpSEdgWghtArr = (tmpNumEdgs == 0) ? NULL : &tmpSEdgWghtVecArr[s][0];
    Val* tmpTEdgWghtArr = (tmpNumEdgs == 0) ? NULL : &tmpTEdgWghtVecArr[s][0];
    Size i = 0;
    Size j = 0;
    Size k = 0;
    while ((i < sNumEdgs) && (j < tNumEdgs)) {
      if (sVtxArr[i] < tVtxArr[j]) {
        tmpSVtxArr[k] = sVtxArr[i];
        tmpTVtxArr[k] = sVtxArr[i];
        tmpSEdgWghtArr[k] = sEdgWghtArr[i];
        tmpTEdgWghtArr[k] = sEdgWghtArr[i];
        ++i;
      } else if (sVtxArr[i] > tVtxArr[j]) {
        tmpSVtxArr[k] = tVtxArr[j];
        tmpTVtxArr[k] = tVtxArr[j];
        tmpSEdgWghtArr[k] = tEdgWghtArr[j];
        tmpTEdgWghtArr[k] = tEdgWghtArr[j];
        ++j;
      } else {
        tmpSVtxArr[k] = sVtxArr[i];
        tmpTVtxArr[k] = sVtxArr[i];
        tmpSEdgWghtArr[k] = sEdgWghtArr[i];
        tmpTEdgWghtArr[k] = sEdgWghtArr[i];
        ++i;
        ++j;
      }
      ++k;
    }
    // leftovers.
    while (i < sNumEdgs) {
      tmpSVtxArr[k] = sVtxArr[i];
      tmpTVtxArr[k] = sVtxArr[i];
      tmpSEdgWghtArr[k] = sEdgWghtArr[i];
      tmpTEdgWghtArr[k] = sEdgWghtArr[i];
      ++i;
      ++k;
    }
    while (j < tNumEdgs) {
      tmpSVtxArr[k] = tVtxArr[j];
      tmpTVtxArr[k] = tVtxArr[j];
      tmpSEdgWghtArr[k] = tEdgWghtArr[j];
      tmpTEdgWghtArr[k] = tEdgWghtArr[j];
      ++j;
      ++k;
    }
  }
  // set merged adjacencies.
  mNumEdgs = numEdgs;
  mSVtxVecVec.swap(tmpSVtxVecVec);
  mTVtxVecVec.swap(tmpTVtxVecVec);
  mSEdgWghtVecVec.swap(tmpSEdgWghtVecVec);
  mTEdgWghtVecVec.swap(tmpTEdgWghtVecVec);
  return eErrNone;
}

void BptGraph::rSortAdjs(Size sNumVtxs, Size tNumVtxs,
    vector<vector<Size> >* sVtxVecVec, vector<vector<Size> >* tVtxVecVec,
    vector<vector<Val> >* sEdgWghtVecVec, vector<vector<Val> >* tEdgWghtVecVec,
    bool doubleStorage) const {
  assert(sNumVtxs < cInfSize);
  assert(tNumVtxs < cInfSize);
  assert(sNumVtxs == sVtxVecVec->size());
  assert(tNumVtxs == tVtxVecVec->size());
  assert(sNumVtxs == sEdgWghtVecVec->size());
  assert(tNumVtxs == tEdgWghtVecVec->size());
  vector<Size>* sVtxVecArr = (sNumVtxs == 0) ? NULL : &(*sVtxVecVec)[0];
  vector<Size>* tVtxVecArr = (tNumVtxs == 0) ? NULL : &(*tVtxVecVec)[0];
  vector<Val>* sEdgWghtVecArr = (sNumVtxs == 0) ? NULL : &(*sEdgWghtVecVec)[0];
  vector<Val>* tEdgWghtVecArr = (tNumVtxs == 0) ? NULL : &(*tEdgWghtVecVec)[0];
  // use temporary adjacencies for sorting.
  // compute the temporary adjacency sizes.
  vector<Size> sNumEdgsVec;
  ResizeVector<Size>(&sNumEdgsVec, sNumVtxs);
  Size* sNumEdgsArr = (sNumVtxs == 0) ? NULL : &sNumEdgsVec[0];
  if (sNumEdgsArr != NULL) {
    fill(&sNumEdgsArr[0], &sNumEdgsArr[sNumVtxs], 0);
  }
  vector<Size> tNumEdgsVec;
  ResizeVector<Size>(&tNumEdgsVec, tNumVtxs);
  Size* tNumEdgsArr = (tNumVtxs == 0) ? NULL : &tNumEdgsVec[0];
  if (tNumEdgsArr != NULL) {
    fill(&tNumEdgsArr[0], &tNumEdgsArr[tNumVtxs], 0);
  }
  for (Size s = 0; s < sNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      ++(tNumEdgsArr[t]);
    }
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    Size tNumEdgs = tVtxVecArr[t].size();
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tVtxArr[j];
      ++(sNumEdgsArr[s]);
    }
  }
  // set up the temporary adjacencies.
  vector<vector<Size> > tmpSVtxVecVec;
  ResizeVector<vector<Size> >(&tmpSVtxVecVec, sNumVtxs);
  vector<Size>* tmpSVtxVecArr = (sNumVtxs == 0) ? NULL : &tmpSVtxVecVec[0];
  vector<vector<Size> > tmpTVtxVecVec;
  ResizeVector<vector<Size> >(&tmpTVtxVecVec, tNumVtxs);
  vector<Size>* tmpTVtxVecArr = (tNumVtxs == 0) ? NULL : &tmpTVtxVecVec[0];
  vector<vector<Val> > tmpSEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpSEdgWghtVecVec, sNumVtxs);
  vector<Val>* tmpSEdgWghtVecArr =
    (sNumVtxs == 0) ? NULL : &tmpSEdgWghtVecVec[0];
  vector<vector<Val> > tmpTEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpTEdgWghtVecVec, tNumVtxs);
  vector<Val>* tmpTEdgWghtVecArr =
    (tNumVtxs == 0) ? NULL : &tmpTEdgWghtVecVec[0];
  for (Size s = 0; s < sNumVtxs; ++s) {
    ResizeVector<Size>(&tmpSVtxVecArr[s], sNumEdgsArr[s]);
    ResizeVector<Val>(&tmpSEdgWghtVecArr[s], sNumEdgsArr[s]);
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    ResizeVector<Size>(&tmpTVtxVecArr[t], tNumEdgsArr[t]);
    ResizeVector<Val>(&tmpTEdgWghtVecArr[t], tNumEdgsArr[t]);
  }
  // release unused memory.
  ResizeVector<Size>(&sNumEdgsVec, 0);
  ResizeVector<Size>(&tNumEdgsVec, 0);
  // sort the adjacencies.
  vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  vector<Size> tIdxVec;
  ResizeVector<Size>(&tIdxVec, tNumVtxs);
  Size* tIdxArr = (tNumVtxs == 0) ? NULL : &tIdxVec[0];
  if (tIdxArr != NULL) {
    fill(&tIdxArr[0], &tIdxArr[tNumVtxs], 0);
  }
  // first bucket sort step on the S-adjacencies. if correct double storage
  // is guaranteed then this directly provides the sorted T-adjacencies.
  for (Size s = 0; s < sNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &sVtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      Val stEdgWght = sEdgWghtArr[i];
      tmpTVtxVecArr[t][tIdxArr[t]] = s;
      tmpTEdgWghtVecArr[t][tIdxArr[t]] = stEdgWght;
      ++(tIdxArr[t]);
    }
  }
  // first bucket sort step on the T-adjacencies. if correct double storage
  // is guaranteed then this directly provides the sorted S-adjacencies.
  for (Size t = 0; t < tNumVtxs; ++t) {
    Size tNumEdgs = tVtxVecArr[t].size();
    const Size* tVtxArr = (tNumEdgs == 0) ? NULL : &tVtxVecArr[t][0];
    const Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tVtxArr[j];
      Val tsEdgWght = tEdgWghtArr[j];
      tmpSVtxVecArr[s][sIdxArr[s]] = t;
      tmpSEdgWghtVecArr[s][sIdxArr[s]] = tsEdgWght;
      ++(sIdxArr[s]);
    }
  }
  if (doubleStorage == true) {
    sVtxVecVec->swap(tmpSVtxVecVec);
    tVtxVecVec->swap(tmpTVtxVecVec);
    sEdgWghtVecVec->swap(tmpSEdgWghtVecVec);
    tEdgWghtVecVec->swap(tmpTEdgWghtVecVec);
    return;
  }
  if (sIdxArr != NULL) {
    fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  if (tIdxArr != NULL) {
    fill(&tIdxArr[0], &tIdxArr[tNumVtxs], 0);
  }
  // second bucket sort step on the S-adjacencies. required if correct double
  // storage is not guaranteed.
  for (Size t = 0; t < tNumVtxs; ++t) {
    Size tNumEdgs = tmpTVtxVecArr[t].size();
    const Size* tmpTVtxArr = (tNumEdgs == 0) ? NULL : &tmpTVtxVecArr[t][0];
    const Val* tmpTEdgWghtArr =
      (tNumEdgs == 0) ? NULL : &tmpTEdgWghtVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tmpTVtxArr[j];
      Val tsEdgWght = tmpTEdgWghtArr[j];
      sVtxVecArr[s][sIdxArr[s]] = t;
      sEdgWghtVecArr[s][sIdxArr[s]] = tsEdgWght;
      ++(sIdxArr[s]);
    }
  }
  // second bucket sort step on the T-adjacencies. required if correct double
  // storage is not guaranteed.
  for (Size s = 0; s < sNumVtxs; ++s) {
    Size sNumEdgs = tmpSVtxVecArr[s].size();
    const Size* tmpSVtxArr = (sNumEdgs == 0) ? NULL : &tmpSVtxVecArr[s][0];
    const Val* tmpSEdgWghtArr =
      (sNumEdgs == 0) ? NULL : &tmpSEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = tmpSVtxArr[i];
      Val stEdgWght = tmpSEdgWghtArr[i];
      tVtxVecArr[t][tIdxArr[t]] = s;
      tEdgWghtVecArr[t][tIdxArr[t]] = stEdgWght;
      ++(tIdxArr[t]);
    }
  }
}

void BptGraph::rRemoveDupEdgs(Size sNumVtxs, Size tNumVtxs, Size* numEdgs,
    vector<vector<Size> >* sVtxVecVec, vector<vector<Size> >* tVtxVecVec,
    vector<vector<Val> >* sEdgWghtVecVec, vector<vector<Val> >* tEdgWghtVecVec)
    const {
  assert(sNumVtxs < cInfSize);
  assert(tNumVtxs < cInfSize);
  assert(sNumVtxs == sVtxVecVec->size());
  assert(tNumVtxs == tVtxVecVec->size());
  assert(sNumVtxs == sEdgWghtVecVec->size());
  assert(tNumVtxs == tEdgWghtVecVec->size());
  vector<Size>* sVtxVecArr = (sNumVtxs == 0) ? NULL : &(*sVtxVecVec)[0];
  vector<Size>* tVtxVecArr = (tNumVtxs == 0) ? NULL : &(*tVtxVecVec)[0];
  vector<Val>* sEdgWghtVecArr = (sNumVtxs == 0) ? NULL : &(*sEdgWghtVecVec)[0];
  vector<Val>* tEdgWghtVecArr = (tNumVtxs == 0) ? NULL : &(*tEdgWghtVecVec)[0];
  Size numDupEdgs = 0;
  // remove duplicate edges from the S-adjacencies.
  for (Size s = 0; s < sNumVtxs; ++s) {
    Size sNumEdgs = sVtxVecArr[s].size();
    if (sNumEdgs > 0) {
      Size sNumDupEdgs = 0;
      const Size* sVtxArr = &sVtxVecArr[s][0];
      const Val* sEdgWghtArr = &sEdgWghtVecArr[s][0];
      Size i = 0;
      Size t = sVtxArr[i];
      while (++i < sNumEdgs) {
        if (t != sVtxArr[i]) {
          t = sVtxArr[i];
        } else {
          ++sNumDupEdgs;
        }
      }
      assert(sNumEdgs > sNumDupEdgs);
      if (sNumDupEdgs > 0) {
        vector<Size> tmpSVtxVec;
        ResizeVector<Size>(&tmpSVtxVec, sNumEdgs - sNumDupEdgs);
        Size* tmpSVtxArr = &tmpSVtxVec[0];
        vector<Val> tmpSEdgWghtVec;
        ResizeVector<Val>(&tmpSEdgWghtVec, sNumEdgs - sNumDupEdgs);
        Val* tmpSEdgWghtArr = &tmpSEdgWghtVec[0];
        Size i1 = 0;
        Size i2 = 0;
        tmpSVtxArr[i2] = sVtxArr[i1];
        tmpSEdgWghtArr[i2] = sEdgWghtArr[i1];
        while (++i1 < sNumEdgs) {
          if (tmpSVtxArr[i2] != sVtxArr[i1]) {
            ++i2;
            tmpSVtxArr[i2] = sVtxArr[i1];
            tmpSEdgWghtArr[i2] = sEdgWghtArr[i1];
          } else {
            ++numDupEdgs;
          }
        }
        sVtxVecArr[s].swap(tmpSVtxVec);
        sEdgWghtVecArr[s].swap(tmpSEdgWghtVec);
      }
    }
  }
  // remove duplicate edges from the T-adjacencies.
  for (Size t = 0; t < tNumVtxs; ++t) {
    Size tNumEdgs = tVtxVecArr[t].size();
    if (tNumEdgs > 0) {
      Size tNumDupEdgs = 0;
      const Size* tVtxArr = &tVtxVecArr[t][0];
      const Val* tEdgWghtArr = &tEdgWghtVecArr[t][0];
      Size j = 0;
      Size s = tVtxArr[j];
      while (++j < tNumEdgs) {
        if (s != tVtxArr[j]) {
          s = tVtxArr[j];
        } else {
          ++tNumDupEdgs;
        }
      }
      assert(tNumEdgs > tNumDupEdgs);
      if (tNumDupEdgs > 0) {
        vector<Size> tmpTVtxVec;
        ResizeVector<Size>(&tmpTVtxVec, tNumEdgs - tNumDupEdgs);
        Size* tmpTVtxArr = &tmpTVtxVec[0];
        vector<Val> tmpTEdgWghtVec;
        ResizeVector<Val>(&tmpTEdgWghtVec, tNumEdgs - tNumDupEdgs);
        Val* tmpTEdgWghtArr = &tmpTEdgWghtVec[0];
        Size j1 = 0;
        Size j2 = 0;
        tmpTVtxArr[j2] = tVtxArr[j1];
        tmpTEdgWghtArr[j2] = tEdgWghtArr[j1];
        while (++j1 < tNumEdgs) {
          if (tmpTVtxArr[j2] != tVtxArr[j1]) {
            ++j2;
            tmpTVtxArr[j2] = tVtxArr[j1];
            tmpTEdgWghtArr[j2] = tEdgWghtArr[j1];
          } else {
            ++numDupEdgs;
          }
        }
        tVtxVecArr[t].swap(tmpTVtxVec);
        tEdgWghtVecArr[t].swap(tmpTEdgWghtVec);
      }
    }
  }
  numDupEdgs /= 2;
  *numEdgs -= numDupEdgs;
}

bool BptGraph::rCheckNoDupEdgs(Size sNumVtxs, Size tNumVtxs,
    const vector<vector<Size> >& sVtxVecVec,
    const vector<vector<Size> >& tVtxVecVec) const {
  assert(sNumVtxs < cInfSize);
  assert(tNumVtxs < cInfSize);
  assert(sNumVtxs == sVtxVecVec.size());
  assert(tNumVtxs == tVtxVecVec.size());
  const vector<Size>* sVtxVecArr = (sNumVtxs == 0) ? NULL : &sVtxVecVec[0];
  const vector<Size>* tVtxVecArr = (tNumVtxs == 0) ? NULL : &tVtxVecVec[0];
  // check the S-adjacencies for duplicate edges.
  for (Size s = 0; s < sNumVtxs; ++s) {
    if (adjacent_find(sVtxVecArr[s].begin(), sVtxVecArr[s].end())
        != sVtxVecArr[s].end()) {
      return false;
    }
  }
  // check the T-adjacencies for duplicate edges.
  for (Size t = 0; t < tNumVtxs; ++t) {
    if (adjacent_find(tVtxVecArr[t].begin(), tVtxVecArr[t].end())
        != tVtxVecArr[t].end()) {
      return false;
    }
  }
  return true;
}

void BptGraph::rFormAdjs(Size sNumVtxs, Size tNumVtxs, Size* numEdgs,
    const vector<Size>& sVtxVec, const vector<Size>& tVtxVec,
    const vector<Val>& edgWghtVec, vector<vector<Size> >* sVtxVecVec,
    vector<vector<Size> >* tVtxVecVec, vector<vector<Val> >* sEdgWghtVecVec,
    vector<vector<Val> >* tEdgWghtVecVec) const {
  assert(sNumVtxs < cInfSize);
  assert(tNumVtxs < cInfSize);
  assert(*numEdgs < cInfSize);
  assert(*numEdgs == sVtxVec.size());
  assert(*numEdgs == tVtxVec.size());
  assert(*numEdgs == edgWghtVec.size());
  const Size* sVtxArr = (*numEdgs == 0) ? NULL : &sVtxVec[0];
  const Size* tVtxArr = (*numEdgs == 0) ? NULL : &tVtxVec[0];
  const Val* edgWghtArr = (*numEdgs == 0) ? NULL : &edgWghtVec[0];
  // compute the adjacency sizes.
  vector<Size> sNumEdgsVec;
  ResizeVector<Size>(&sNumEdgsVec, sNumVtxs);
  Size* sNumEdgsArr = (sNumVtxs == 0) ? NULL : &sNumEdgsVec[0];
  if (sNumEdgsArr != NULL) {
    fill(&sNumEdgsArr[0], &sNumEdgsArr[sNumVtxs], 0);
  }
  vector<Size> tNumEdgsVec;
  ResizeVector<Size>(&tNumEdgsVec, tNumVtxs);
  Size* tNumEdgsArr = (tNumVtxs == 0) ? NULL : &tNumEdgsVec[0];
  if (tNumEdgsArr != NULL) {
    fill(&tNumEdgsArr[0], &tNumEdgsArr[tNumVtxs], 0);
  }
  for (Size k = 0; k < *numEdgs; ++k) {
    Size s = sVtxArr[k];
    Size t = tVtxArr[k];
    ++(sNumEdgsArr[s]);
    ++(tNumEdgsArr[t]);
  }
  // set up the adjacencies.
  Size tmpNumEdgs = *numEdgs;
  vector<vector<Size> > tmpSVtxVecVec;
  ResizeVector<vector<Size> >(&tmpSVtxVecVec, sNumVtxs);
  vector<Size>* tmpSVtxVecArr = (sNumVtxs == 0) ? NULL : &tmpSVtxVecVec[0];
  vector<vector<Size> > tmpTVtxVecVec;
  ResizeVector<vector<Size> >(&tmpTVtxVecVec, tNumVtxs);
  vector<Size>* tmpTVtxVecArr = (tNumVtxs == 0) ? NULL : &tmpTVtxVecVec[0];
  vector<vector<Val> > tmpSEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpSEdgWghtVecVec, sNumVtxs);
  vector<Val>* tmpSEdgWghtVecArr =
    (sNumVtxs == 0) ? NULL : &tmpSEdgWghtVecVec[0];
  vector<vector<Val> > tmpTEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpTEdgWghtVecVec, tNumVtxs);
  vector<Val>* tmpTEdgWghtVecArr =
    (tNumVtxs == 0) ? NULL : &tmpTEdgWghtVecVec[0];
  for (Size s = 0; s < sNumVtxs; ++s) {
    ResizeVector<Size>(&tmpSVtxVecArr[s], sNumEdgsArr[s]);
    ResizeVector<Val>(&tmpSEdgWghtVecArr[s], sNumEdgsArr[s]);
  }
  for (Size t = 0; t < tNumVtxs; ++t) {
    ResizeVector<Size>(&tmpTVtxVecArr[t], tNumEdgsArr[t]);
    ResizeVector<Val>(&tmpTEdgWghtVecArr[t], tNumEdgsArr[t]);
  }
  // release unused memory.
  ResizeVector<Size>(&sNumEdgsVec, 0);
  ResizeVector<Size>(&tNumEdgsVec, 0);
  // transfer data from the input to the adjacencies.
  vector<Size> sIdxVec;
  ResizeVector<Size>(&sIdxVec, sNumVtxs);
  Size* sIdxArr = (sNumVtxs == 0) ? NULL : &sIdxVec[0];
  if (sIdxArr != NULL) {
    fill(&sIdxArr[0], &sIdxArr[sNumVtxs], 0);
  }
  vector<Size> tIdxVec;
  ResizeVector<Size>(&tIdxVec, tNumVtxs);
  Size* tIdxArr = (tNumVtxs == 0) ? NULL : &tIdxVec[0];
  if (tIdxArr != NULL) {
    fill(&tIdxArr[0], &tIdxArr[tNumVtxs], 0);
  }
  for (Size k = 0; k < *numEdgs; ++k) {
    Size s = sVtxArr[k];
    Size t = tVtxArr[k];
    Val stEdgWght = edgWghtArr[k];
    tmpSVtxVecArr[s][sIdxArr[s]] = t;
    tmpSEdgWghtVecArr[s][sIdxArr[s]] = stEdgWght;
    ++(sIdxArr[s]);
    tmpTVtxVecArr[t][tIdxArr[t]] = s;
    tmpTEdgWghtVecArr[t][tIdxArr[t]] = stEdgWght;
    ++(tIdxArr[t]);
  }
  // sort the adjacencies and remove duplicate edges.
  rSortAdjs
    (sNumVtxs, tNumVtxs, &tmpSVtxVecVec, &tmpTVtxVecVec, &tmpSEdgWghtVecVec,
     &tmpTEdgWghtVecVec, true);
  rRemoveDupEdgs
    (sNumVtxs, tNumVtxs, &tmpNumEdgs, &tmpSVtxVecVec, &tmpTVtxVecVec,
     &tmpSEdgWghtVecVec, &tmpTEdgWghtVecVec);
  bool noDupEdgs = rCheckNoDupEdgs
    (sNumVtxs, tNumVtxs, tmpSVtxVecVec, tmpTVtxVecVec);
  assert(noDupEdgs == true);
  // set output.
  *numEdgs = tmpNumEdgs;
  sVtxVecVec->swap(tmpSVtxVecVec);
  tVtxVecVec->swap(tmpTVtxVecVec);
  sEdgWghtVecVec->swap(tmpSEdgWghtVecVec);
  tEdgWghtVecVec->swap(tmpTEdgWghtVecVec);
}

Val BptGraph::rGetMatchedEdgWghtBnd(void) const {
  Size numEdgWghts = min(mSNumVtxs, mTNumVtxs);
  vector<Val> edgWghtVec;
  ResizeVector<Val>(&edgWghtVec, numEdgWghts);
  Val* edgWghtArr = (numEdgWghts == 0) ? NULL : &edgWghtVec[0];
  if (mSNumVtxs <= mTNumVtxs) {
    const vector<Val>*
      sEdgWghtVecArr = (mSNumVtxs == 0) ? NULL : &mSEdgWghtVecVec[0];
    for (Size s = 0, k = 0; s < mSNumVtxs; ++s) {
      Size sNumEdgs = sEdgWghtVecArr[s].size();
      const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0];
      Val maxEdgWght = 0.0;
      for (Size i = 0; i < sNumEdgs; ++i) {
        if (maxEdgWght < sEdgWghtArr[i]) {
          maxEdgWght = sEdgWghtArr[i];
        }
      }
      edgWghtArr[k] = maxEdgWght;
      ++k;
    }
  } else {
    const vector<Val>*
      tEdgWghtVecArr = (mTNumVtxs == 0) ? NULL : &mTEdgWghtVecVec[0];
    for (Size t = 0, k = 0; t < mTNumVtxs; ++t) {
      Size tNumEdgs = tEdgWghtVecArr[t].size();
      const Val* tEdgWghtArr = (tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[t][0];
      Val maxEdgWght = 0.0;
      for (Size j = 0; j < tNumEdgs; ++j) {
        if (maxEdgWght < tEdgWghtArr[j]) {
          maxEdgWght = tEdgWghtArr[j];
        }
      }
      edgWghtArr[k] = maxEdgWght;
      ++k;
    }
  }
  sort(edgWghtVec.begin(), edgWghtVec.end());
  return accumulate(edgWghtVec.begin(), edgWghtVec.end(), 0.0);
}

void BptGraph::rShiftEdgWghts(Val edgWghtShift) const {
  const vector<Val>*
    sEdgWghtVecArr = (mSNumVtxs == 0) ? NULL : &mSEdgWghtVecVec[0];
  for (Size s = 0; s < mSNumVtxs; ++s) {
    Size sNumEdgs = sEdgWghtVecArr[s].size();
    Val* sEdgWghtArr = const_cast<Val*>
      ((sNumEdgs == 0) ? NULL : &sEdgWghtVecArr[s][0]);
    for (Size i = 0; i < sNumEdgs; ++i) {
      sEdgWghtArr[i] += edgWghtShift;
    }
  }
  const vector<Val>*
    tEdgWghtVecArr = (mTNumVtxs == 0) ? NULL : &mTEdgWghtVecVec[0];
  for (Size t = 0; t < mTNumVtxs; ++t) {
    Size tNumEdgs = tEdgWghtVecArr[t].size();
    Val* tEdgWghtArr = const_cast<Val*>
      ((tNumEdgs == 0) ? NULL : &tEdgWghtVecArr[t][0]);
    for (Size j = 0; j < tNumEdgs; ++j) {
      tEdgWghtArr[j] += edgWghtShift;
    }
  }
}
