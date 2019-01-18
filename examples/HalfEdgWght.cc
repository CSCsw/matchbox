#include <iostream>
#include <vector>
#include <map>
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "Graph.h"
#include "ConvertEngine.h"
#include "AdjGraphEngine.h"
#include "MatchingEngine.h"
#include "Timer.h"

using namespace std;
using namespace Matchbox;

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "usage: "
         << argv[0]
         << " graphFile"
         << endl;
    return 1;
  }


  // get the graph.
  Graph graph;
  cout << "reading graph file ..." << endl;
  if (graph.Read(argv[1]) != eErrNone) {
      cout << "graph file reading error" << endl;
      return 1;
  }
  cout << "done reading graph file" << endl;
  
  // work variables.
  vector<Size> mateVec;
  Size card;
  Val edgWght;

  Timer timer;
  MatchingEngine matchingEngine;
  cout << "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[" << endl;
  cout << "computing matching ..." << endl;
  timer.Start();
  matchingEngine.ComputeHalfEdgWghtMatching(graph, &mateVec, &card, &edgWght);
  timer.Stop();
  cout << "done computing matching" << endl;
  timer.Print();
  cout << "weight: " <<fixed << edgWght <<endl;
  cout << "card: " << card <<endl;
  cout << "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
  cout << "==================================================" << endl;

  //graph.SetFullPrint(false);
  //graph.Print();

  //matchingEngine.SetFullPrint(true);
  //matchingEngine.PrintMatching(mateVec, card);
  cout << "checking matching ..." << endl;
  bool valid = matchingEngine.CheckMatching(graph, mateVec, card);
  assert(valid == true);
  cout << "done checking matching" << endl;
  return 0;
}
