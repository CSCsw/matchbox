#include "Graph.h"

using namespace std;
using namespace Matchbox;

void Graph::GetEdgs(vector<Size>* sVtxVec, vector<Size>* tVtxVec,
    vector<Val>* edgWghtVec) const {
  // reset output.
  ResizeVector<Size>(sVtxVec, 0);
  ResizeVector<Size>(tVtxVec, 0);
  ResizeVector<Val>(edgWghtVec, 0);
  const vector<Size>* vtxVecArr = (mNumVtxs == 0) ? NULL : &mVtxVecVec[0];
  const vector<Val>*
    edgWghtVecArr = (mNumVtxs == 0) ? NULL : &mEdgWghtVecVec[0];
  vector<Size> tmpSVtxVec;
  ResizeVector<Size>(&tmpSVtxVec, mNumEdgs);
  Size* tmpSVtxArr = (mNumEdgs == 0) ? NULL : &tmpSVtxVec[0];
  vector<Size> tmpTVtxVec;
  ResizeVector<Size>(&tmpTVtxVec, mNumEdgs);
  Size* tmpTVtxArr = (mNumEdgs == 0) ? NULL : &tmpTVtxVec[0];
  vector<Val> tmpEdgWghtVec;
  ResizeVector<Val>(&tmpEdgWghtVec, mNumEdgs);
  Val* tmpEdgWghtArr = (mNumEdgs == 0) ? NULL : &tmpEdgWghtVec[0];
  for (Size s = 0, k = 0; s < mNumVtxs; ++s) {
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &edgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      if (t < s) {
        // avoid double counting.
        continue;
      }
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

Err Graph::GetAdj(Size vtx, Size* numEdgs, vector<Size>* vtxVec,
    vector<Val>* edgWghtVec) const {
  // reset output.
  *numEdgs = 0;
  ResizeVector<Size>(vtxVec, 0);
  ResizeVector<Val>(edgWghtVec, 0);
  // check if the vertex is within the allowed range.
  if (vtx >= mNumVtxs) {
    return eErrInvVtx;
  }
  Size tmpNumEdgs = mVtxVecVec[vtx].size();
  vector<Size> tmpVtxVec;
  ResizeVector<Size>(&tmpVtxVec, tmpNumEdgs);
  vector<Val> tmpEdgWghtVec;
  ResizeVector<Val>(&tmpEdgWghtVec, tmpNumEdgs);
  copy(mVtxVecVec[vtx].begin(), mVtxVecVec[vtx].end(), tmpVtxVec.begin());
  copy(mEdgWghtVecVec[vtx].begin(), mEdgWghtVecVec[vtx].end(),
       tmpEdgWghtVec.begin());
  // set output.
  *numEdgs = tmpNumEdgs;
  vtxVec->swap(tmpVtxVec);
  edgWghtVec->swap(tmpEdgWghtVec);
  return eErrNone;
}

void Graph::GetVtxWghts(vector<Val>* vtxWghtVec) const {
  // reset output.
  ResizeVector<Val>(vtxWghtVec, 0);
  vector<Val> tmpVtxWghtVec;
  ResizeVector<Val>(&tmpVtxWghtVec, mNumVtxs);
  copy(mVtxWghtVec.begin(), mVtxWghtVec.end(), tmpVtxWghtVec.begin());
  // set output.
  vtxWghtVec->swap(tmpVtxWghtVec);
}

void Graph::GetVtxDgrs(vector<Size>* vtxDgrVec) const {
  // reset output.
  ResizeVector<Size>(vtxDgrVec, 0);
  vector<Size> tmpVtxDgrVec;
  ResizeVector<Size>(&tmpVtxDgrVec, mNumVtxs);
  Size* tmpVtxDgrArr = (mNumVtxs == 0) ? NULL : &tmpVtxDgrVec[0];
  const vector<Size>* vtxVecArr = (mNumVtxs == 0) ? NULL : &mVtxVecVec[0];
  for (Size v = 0; v < mNumVtxs; ++v) {
    tmpVtxDgrArr[v] = vtxVecArr[v].size();
  }
  // set output.
  vtxDgrVec->swap(tmpVtxDgrVec);
}

void Graph::Print(void) const {
  cout << "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" << endl;
  cout << "Graph (begin)" << endl;
  cout << "number of vertices: " << mNumVtxs << endl;
  cout << "number of edges: " << mNumEdgs << endl;
  // TODO: maintain isolated vertex counters in the data structure.
  Size numIsolatedVtxs = 0;
  for (vector<vector<Size> >::const_iterator it = mVtxVecVec.begin();
       it != mVtxVecVec.end(); ++it) {
    if (it->size() == 0) {
      ++numIsolatedVtxs;
    }
  }
  cout << "number of isolated vertices: " << numIsolatedVtxs << endl;
  if (mFullPrint == true) {
    cout.setf(ios::left | ios::scientific | ios::showpoint);
    cout.precision(mPrecision);
    cout << "vertex weights:";
    for (vector<Val>::const_iterator it = mVtxWghtVec.begin();
         it != mVtxWghtVec.end(); ++it) {
      cout << " " << *it;
    }
    cout << endl;
    cout.unsetf(ios::left | ios::scientific | ios::showpoint);
    Size v = 0;
    for (vector<vector<Size> >::const_iterator it1 = mVtxVecVec.begin();
         it1 != mVtxVecVec.end(); ++it1) {
      cout << "adjacency(" << v  << "):";
      for (vector<Size>::const_iterator it2 = it1->begin(); it2 != it1->end();
           ++it2) {
        cout << " " << *it2 ;
      }
      cout << endl;
      ++v;
    }
  }
  cout << "Graph (end)" << endl;
  cout << "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" << endl;
}

Err Graph::Set(Size numVtxs, Size numEdgs, const vector<Size>& sVtxVec,
    const vector<Size>& tVtxVec, const vector<Val>& edgWghtVec) {
  // reset object.
  Clear();
  // check if the number of vertices is within the allowed range.
  if (numVtxs >= cInfSize) {
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
  // check if the vertices are within the allowed range.
  if (find_if(sVtxVec.begin(), sVtxVec.end(),
              bind2nd(greater_equal<Size>(), numVtxs))
      != sVtxVec.end()) {
    return eErrInvVtx;
  }
  if (find_if(tVtxVec.begin(), tVtxVec.end(),
              bind2nd(greater_equal<Size>(), numVtxs))
      != tVtxVec.end()) {
    return eErrInvVtx;
  }
  // check if the edge weights are nonnegative.
  if (find_if(edgWghtVec.begin(), edgWghtVec.end(),
              bind2nd(less<Val>(), cZeroVal))
      != edgWghtVec.end()) {
    return eErrInvWght;
  }
  //Size tmpNumEdgs = numEdgs;
  vector<vector<Size> > vtxVecVec;
  vector<vector<Val> > edgWghtVecVec;
  vector<vector<Val> > vtxWghtVecVec;
  rFormAdjs(&numVtxs, &numEdgs, sVtxVec, tVtxVec, edgWghtVec, &vtxVecVec,
            &edgWghtVecVec);
   //the vertex weights are set to zero.
  vector<Val> vtxWghtVec;
  ResizeVector<Val>(&vtxWghtVec, numVtxs);
  fill(vtxWghtVec.begin(), vtxWghtVec.end(), cZeroVal);
  // set object.
  mNumVtxs = numVtxs;
  mNumEdgs = numEdgs;
  mVtxVecVec.swap(vtxVecVec);
  mEdgWghtVecVec.swap(edgWghtVecVec);
  return eErrNone;
}

Err Graph::SetVtxWghts(const vector<Val>& vtxWghtVec) {
  // check the size of the input.
  if (vtxWghtVec.size() != mNumVtxs) {
    return eErrInvNumVtxs;
  }
  // check if the vertex weights are nonnegative.
  if (find_if(vtxWghtVec.begin(), vtxWghtVec.end(),
              bind2nd(less<Val>(), cZeroVal))
      != vtxWghtVec.end()) {
    return eErrInvWght;
  }
  copy(vtxWghtVec.begin(), vtxWghtVec.end(), mVtxWghtVec.begin());
  return eErrNone;
}


void Graph::SortAdjByVtxWghts(void) {
	
	vector<vector<Size> > vtxVecVec;
  vector<vector<Val> > edgWghtVecVec;
  
	const vector<Size>* vtxVecArr = (mNumVtxs == 0) ? NULL : &mVtxVecVec[0];
  vector<Val>* edgWghtVecArr = (mNumVtxs == 0) ? NULL : &mEdgWghtVecVec[0];
 const Val* vtxWghtArr = (mNumVtxs == 0) ? NULL : &mVtxWghtVec[0];
 
   vector<vector<Size> > tmpVtxVecVec;
  ResizeVector<vector<Size> >(&tmpVtxVecVec, mNumVtxs);
  vector<Size>* tmpVtxVecArr = (mNumVtxs == 0) ? NULL : &tmpVtxVecVec[0];
  vector<vector<Val> > tmpEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpEdgWghtVecVec, mNumVtxs);
  vector<Val>* tmpEdgWghtVecArr = (mNumVtxs== 0) ? NULL : &tmpEdgWghtVecVec[0];
	for (Size s = 0; s < mNumVtxs; ++s) {
	ResizeVector<Size>(&tmpVtxVecVec[s], mVtxVecVec[s].size());	
	ResizeVector<Val>(&tmpEdgWghtVecVec[s], mVtxVecVec[s].size());
	}
	std::vector<std::pair<Size, Val> > sExpsdLst2;
	
 
  for (Size s = 0; s < mNumVtxs; ++s) {
  	
  	ResizeVector<std::pair<Size, Val> >(&sExpsdLst2, vtxVecArr[s].size());
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &edgWghtVecArr[s][0];
    //Val* sEdgWghtArr2 = (sNumEdgs == 0) ? NULL : &tmpEdgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      //Size t = sVtxArr[i];
      sExpsdLst2.push_back(std::pair<Size, Val>(i, vtxWghtArr[sVtxArr[i]]));
      //sEdgWghtArr2[i] = vtxWghtArr[s] + vtxWghtArr[t];
    }
    
    std::sort(sExpsdLst2.begin(),sExpsdLst2.end(),ValGreater<std::pair<Size, Val> >());
    
     for (Size current = 0; current <  mVtxVecVec[s].size(); ++current) {
    	tmpVtxVecArr[s][current] =  sVtxArr[sExpsdLst2[current].first];
    	tmpEdgWghtVecArr[s][current] = sEdgWghtArr[sExpsdLst2[current].first];
    }
    sExpsdLst2.clear();
  }
  //rSortAdjs(mNumVtxs, &tmpVtxVecVec, &tmpEdgWghtVecVec, true);
  vtxVecVec.swap(tmpVtxVecVec);
  edgWghtVecVec.swap(tmpEdgWghtVecVec);
  mVtxVecVec.swap(vtxVecVec);
  mEdgWghtVecVec.swap(edgWghtVecVec);
}
void Graph::SetEdgWghtsFromVtxWghts(void) {


  const vector<Size>* vtxVecArr = (mNumVtxs == 0) ? NULL : &mVtxVecVec[0];
  vector<Val>* edgWghtVecArr = (mNumVtxs == 0) ? NULL : &mEdgWghtVecVec[0];
 const Val* vtxWghtArr = (mNumVtxs == 0) ? NULL : &mVtxWghtVec[0];
	
 
  for (Size s = 0; s < mNumVtxs; ++s) {
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &edgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      sEdgWghtArr[i] = vtxWghtArr[s] + vtxWghtArr[t];
    }
  }
}

Err Graph::Read(const string& fileName, bool zeroBased) {
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
  Size numVtxs;
  fin >> numVtxs;
  if (fin.eof()) {
    return eErrInvFile;
  }
  // check if the number of vertices is within the allowed range.
  if (numVtxs >= cInfSize) {
    return eErrInvNumVtxs;
  }
  Size numEdgs;
  fin >> numEdgs;
  if (fin.eof()) {
    return eErrInvFile;
  }
  if(numEdgs == numVtxs)
  {
  	fin >> numEdgs;
  	if (fin.eof()) {
    return eErrInvFile;
  	}
  }
  // check if the number of edges is within the allowed range.
  if (numEdgs >= cInfSize) {
    return eErrInvNumEdgs;
  }
  Size firstVtx = 0;
  Size lastVtx = numVtxs;
  if (zeroBased == false) {
    ++firstVtx;
    ++lastVtx;
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
  int tn1=0,tn2=0;
  double tnz=0;
  bool binary;
  if(sscanf(line, "%d %d %lf", &tn1, &tn2, &tnz) == 3)
	binary=false;
   else
    binary=true;
   fin.seekg (oldpos);
  for (Size k = 0; k < numEdgs; ++k) {
    fin >> sVtxArr[k];
    if (fin.eof()) {
      return eErrInvFile;
    }
    // check if the vertices is within the allowed range.
    if ((sVtxArr[k] < firstVtx) || (sVtxArr[k] >= lastVtx)) {
      return eErrInvVtx;
    }
    
    if (zeroBased == false) {
      --(sVtxArr[k]);
    }
    
    
    fin >> tVtxArr[k];
    if (fin.eof()) {
      return eErrInvFile;
    }
    // check if the vertices is within the allowed range.
    if ((tVtxArr[k] < firstVtx) || (tVtxArr[k] >= lastVtx)) {
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
  vector<vector<Size> > vtxVecVec;
  vector<vector<Val> > edgWghtVecVec;

  rFormAdjs(&numVtxs, &numEdgs, sVtxVec, tVtxVec, edgWghtVec, &vtxVecVec,
            &edgWghtVecVec);
  // the vertex weights are set to zero.
  vector<Val> vtxWghtVec;
  ResizeVector<Val>(&vtxWghtVec, numVtxs);
  fill(vtxWghtVec.begin(), vtxWghtVec.end(), cZeroVal);
  // set object.
  mNumVtxs = numVtxs;
  mNumEdgs = numEdgs;
  mVtxVecVec.swap(vtxVecVec);
  mEdgWghtVecVec.swap(edgWghtVecVec);
  mVtxWghtVec.swap(vtxWghtVec);

  return eErrNone;
}


Err Graph::ReadWeights(const string& fileName, bool zeroBased) {
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
  
    vector<Val> vtxWghtVec;
   ResizeVector<Val>(&vtxWghtVec, numVtxs);
   Val* vtxWghtArr = (numVtxs == 0) ? NULL : &vtxWghtVec[0];
 
  for (Size k = 0; k < numVtxs; ++k) {
    fin >> vtxWghtArr[k];
    //if(vtxWghtArr[k]==0)
    //return eErrInvFile;
    if (fin.eof()) {
      return eErrInvFile;
    }
  }
  
 if(SetVtxWghts(vtxWghtVec) != eErrNone)
 return eErrInvWght;
 
  return eErrNone;
}


void Graph::rSortAdjs(Size numVtxs, vector<vector<Size> >* vtxVecVec,
    vector<vector<Val> >* edgWghtVecVec, bool doubleStorage) const {
  assert(numVtxs < cInfSize);
  assert(numVtxs == vtxVecVec->size());
  assert(numVtxs == edgWghtVecVec->size());
  vector<Size>* vtxVecArr = (numVtxs == 0) ? NULL : &(*vtxVecVec)[0];
  vector<Val>* edgWghtVecArr = (numVtxs == 0) ? NULL : &(*edgWghtVecVec)[0];
  // use temporary adjacencies for sorting.
  // compute the temporary adjacency sizes.
  vector<Size> numEdgsVec;
  ResizeVector<Size>(&numEdgsVec, numVtxs);
  Size* numEdgsArr = (numVtxs == 0) ? NULL : &numEdgsVec[0];
  if (numEdgsArr != NULL) {
    fill(&numEdgsArr[0], &numEdgsArr[numVtxs], 0);
  }
  for (Size s = 0; s < numVtxs; ++s) {
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      ++(numEdgsArr[t]);
    }
  }
  // set up the temporary adjacencies.
  vector<vector<Size> > tmpVtxVecVec;
  ResizeVector<vector<Size> >(&tmpVtxVecVec, numVtxs);
  vector<Size>* tmpVtxVecArr = (numVtxs == 0) ? NULL : &tmpVtxVecVec[0];
  vector<vector<Val> > tmpEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpEdgWghtVecVec, numVtxs);
  vector<Val>* tmpEdgWghtVecArr = (numVtxs == 0) ? NULL : &tmpEdgWghtVecVec[0];
  for (Size v = 0; v < numVtxs; ++v) {
    ResizeVector<Size>(&tmpVtxVecArr[v], numEdgsArr[v]);
    ResizeVector<Val>(&tmpEdgWghtVecArr[v], numEdgsArr[v]);
  }
  // release unused memory.
  ResizeVector<Size>(&numEdgsVec, 0);
  // sort the adjacencies.
  vector<Size> idxVec;
  ResizeVector<Size>(&idxVec, numVtxs);
  Size* idxArr = (numVtxs == 0) ? NULL : &idxVec[0];
  if (idxArr != NULL) {
    fill(&idxArr[0], &idxArr[numVtxs], 0);
  }
  // first bucket sort step on the adjacencies. if correct double storage
  // is guaranteed then this directly provides the sorted adjacencies.
  for (Size s = 0; s < numVtxs; ++s) {
    Size sNumEdgs = vtxVecArr[s].size();
    const Size* sVtxArr = (sNumEdgs == 0) ? NULL : &vtxVecArr[s][0];
    const Val* sEdgWghtArr = (sNumEdgs == 0) ? NULL : &edgWghtVecArr[s][0];
    for (Size i = 0; i < sNumEdgs; ++i) {
      Size t = sVtxArr[i];
      Val stEdgWght = sEdgWghtArr[i];
      tmpVtxVecArr[t][idxArr[t]] = s;
      tmpEdgWghtVecArr[t][idxArr[t]] = stEdgWght;
      ++(idxArr[t]);
    }
  }
  if (doubleStorage == true) {
    vtxVecVec->swap(tmpVtxVecVec);
    edgWghtVecVec->swap(tmpEdgWghtVecVec);
    return;
  }
  if (idxArr != NULL) {
    fill(&idxArr[0], &idxArr[numVtxs], 0);
  }
  // second bucket sort step on the adjacencies. required if correct double
  // storage is not guaranteed.
  for (Size t = 0; t < numVtxs; ++t) {
    Size tNumEdgs = tmpVtxVecArr[t].size();
    const Size* tmpTVtxArr = (tNumEdgs == 0) ? NULL : &tmpVtxVecArr[t][0];
    const Val* tmpTEdgWghtArr =
      (tNumEdgs == 0) ? NULL : &tmpEdgWghtVecArr[t][0];
    for (Size j = 0; j < tNumEdgs; ++j) {
      Size s = tmpTVtxArr[j];
      Val tsEdgWght = tmpTEdgWghtArr[j];
      vtxVecArr[s][idxArr[s]] = t;
      edgWghtVecArr[s][idxArr[s]] = tsEdgWght;
      ++(idxArr[s]);
    }
  }
}

void Graph::rRemoveDupEdgs(Size numVtxs, Size* numEdgs,
    vector<vector<Size> >* vtxVecVec, vector<vector<Val> >* edgWghtVecVec)
    const {
  assert(numVtxs < cInfSize);
  assert(numVtxs == vtxVecVec->size());
  assert(numVtxs == edgWghtVecVec->size());
  vector<Size>* vtxVecArr = (numVtxs == 0) ? NULL : &(*vtxVecVec)[0];
  vector<Val>* edgWghtVecArr = (numVtxs == 0) ? NULL : &(*edgWghtVecVec)[0];
  Size numDupEdgs = 0;
  // remove duplicate edges from the adjacencies.
  for (Size s = 0; s < numVtxs; ++s) {
    Size sNumEdgs = vtxVecArr[s].size();
    if (sNumEdgs > 0) {
      Size sNumDupEdgs = 0;
      const Size* sVtxArr = &vtxVecArr[s][0];
      const Val* sEdgWghtArr = &edgWghtVecArr[s][0];
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
        vtxVecArr[s].swap(tmpSVtxVec);
        edgWghtVecArr[s].swap(tmpSEdgWghtVec);
      }
    }
  }
  numDupEdgs /= 2;
  *numEdgs -= numDupEdgs;
}

bool Graph::rCheckNoDupEdgs(Size numVtxs,
    const vector<vector<Size> >& vtxVecVec) const {
  assert(numVtxs < cInfSize);
  assert(numVtxs == vtxVecVec.size());
  const vector<Size>* vtxVecArr = (numVtxs == 0) ? NULL : &vtxVecVec[0];
  // check the adjacencies for duplicate edges.
  for (Size v = 0; v < numVtxs; ++v) {
    if (adjacent_find(vtxVecArr[v].begin(), vtxVecArr[v].end())
        != vtxVecArr[v].end()) {
      return false;
    }
  }
  return true;
}

void Graph::rFormAdjs(Size* numVtxss, Size* numEdgs, const vector<Size>& sVtxVec,
    const vector<Size>& tVtxVec, const vector<Val>& edgWghtVec,
    vector<vector<Size> >* vtxVecVec, vector<vector<Val> >* edgWghtVecVec)
    const {
    	Size numVtxs =*numVtxss;
  assert(numVtxs < cInfSize);
  assert(*numEdgs < cInfSize);
  assert(*numEdgs == sVtxVec.size());
  assert(*numEdgs == tVtxVec.size());
  assert(*numEdgs == edgWghtVec.size());
  const Size* sVtxArr = (*numEdgs == 0) ? NULL : &sVtxVec[0];
  const Size* tVtxArr = (*numEdgs == 0) ? NULL : &tVtxVec[0];
  const Val* edgWghtArr = (*numEdgs == 0) ? NULL : &edgWghtVec[0];
 
  // compute the adjacency sizes.
  vector<Size> numEdgsVec;
  ResizeVector<Size>(&numEdgsVec, numVtxs);
  Size* numEdgsArr = (numVtxs == 0) ? NULL : &numEdgsVec[0];
  if (numEdgsArr != NULL) {
    fill(&numEdgsArr[0], &numEdgsArr[numVtxs], 0);
  }
  ////////////
  /*vector<Size> nonIsol;
  ResizeVector<Size>(&nonIsol, numVtxs);
  Size* nonIsolArr = (numVtxs == 0) ? NULL : &nonIsol[0];
  if (nonIsolArr != NULL) {
    fill(&nonIsolArr[0], &nonIsolArr[numVtxs], 0);
  }*/
  /////////////
  Size numLoopEdgs = 0;
  for (Size k = 0; k < *numEdgs; ++k) {
    Size s = sVtxArr[k];
    Size t = tVtxArr[k];
    if (s == t) {
      // remove loop edges.
      ++numLoopEdgs;
      continue;
    }
    ++(numEdgsArr[s]);
    ++(numEdgsArr[t]);
    ////////
   // nonIsolArr[s]=1;
   // nonIsolArr[t]=1;
    /////////
  }
  /////////////
  /*vector<Size> newidx;
  ResizeVector<Size>(&newidx, numVtxs);
  Size* newidxArr = (numVtxs == 0) ? NULL : &newidx[0];
  if (newidxArr != NULL) {
    fill(&newidxArr[0], &newidxArr[numVtxs], cNullItm);
  }
  Size id = 0;
  for (Size v = 0; v < numVtxs; ++v) {
  	if(nonIsolArr[v]==1)
  	{
  		newidxArr[v]=id;
		  id++;	
	  }
  }
  Size oldnumVtx = numVtxs;
  numVtxs = id;
  *numVtxss =id;*/
  /////////////
  // set up the adjacencies.
  Size tmpNumEdgs = *numEdgs;
  vector<vector<Size> > tmpVtxVecVec;
  ResizeVector<vector<Size> >(&tmpVtxVecVec, numVtxs);
  vector<Size>* tmpVtxVecArr = (numVtxs == 0) ? NULL : &tmpVtxVecVec[0];
  vector<vector<Val> > tmpEdgWghtVecVec;
  ResizeVector<vector<Val> >(&tmpEdgWghtVecVec, numVtxs);
  vector<Val>* tmpEdgWghtVecArr = (numVtxs == 0) ? NULL : &tmpEdgWghtVecVec[0];

  for (Size v = 0; v < numVtxs; ++v) {
  //for (Size v = 0; v < oldnumVtx; ++v) {
  //	if(newidxArr[v] != cNullItm)
  //	{
	 
    ResizeVector<Size>(&tmpVtxVecArr[v], numEdgsArr[v]);
    ResizeVector<Val>(&tmpEdgWghtVecArr[v], numEdgsArr[v]);
    //ResizeVector<Size>(&tmpVtxVecArr[newidxArr[v]], numEdgsArr[v]);
    //ResizeVector<Val>(&tmpEdgWghtVecArr[newidxArr[v]], numEdgsArr[v]);
   // }
  }
  // release unused memory.
  ResizeVector<Size>(&numEdgsVec, 0);
  // transfer data from the input to the adjacencies.
  vector<Size> idxVec;
  ResizeVector<Size>(&idxVec, numVtxs);
  Size* idxArr = (numVtxs == 0) ? NULL : &idxVec[0];
  if (idxArr != NULL) {
    fill(&idxArr[0], &idxArr[numVtxs], 0);
  }
  for (Size k = 0; k < *numEdgs; ++k) {
    Size s = sVtxArr[k];
    Size t = tVtxArr[k];
	////////
	//s = newidxArr[s];
	//t = newidxArr[t];
	///////
    if (s == t) {
      // remove loop edges.
      continue;
    }
    Val stEdgWght = edgWghtArr[k];
    tmpVtxVecArr[s][idxArr[s]] = t;
    tmpEdgWghtVecArr[s][idxArr[s]] = stEdgWght;

    ++(idxArr[s]);
    tmpVtxVecArr[t][idxArr[t]] = s;
    tmpEdgWghtVecArr[t][idxArr[t]] = stEdgWght;

    ++(idxArr[t]);
  }
  tmpNumEdgs -= numLoopEdgs;
  // sort the adjacencies and remove duplicate edges.
  //rSortAdjs(numVtxs, &tmpVtxVecVec, &tmpEdgWghtVecVec, true);
  rRemoveDupEdgs(numVtxs, &tmpNumEdgs, &tmpVtxVecVec, &tmpEdgWghtVecVec);
  bool noDupEdgs = rCheckNoDupEdgs(numVtxs, tmpVtxVecVec);
  assert(noDupEdgs == true);
  // set output.
  *numEdgs = tmpNumEdgs;
  vtxVecVec->swap(tmpVtxVecVec);
  edgWghtVecVec->swap(tmpEdgWghtVecVec);
}
