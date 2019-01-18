#ifndef ADJ_GRAPH_ENGINE_H
#define ADJ_GRAPH_ENGINE_H

#include <vector>
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "Graph.h"

namespace Matchbox {

class AdjGraphEngine {
public:
  /// Constructor.
  AdjGraphEngine() {}

  /// Destructor.
  ~AdjGraphEngine() {}

  ///
  Err GetAdjGraph(const BptGraph& bptGraph, Graph* graph);
private:
  // forbid the copy constructor and the assignment operator.
  AdjGraphEngine(const AdjGraphEngine&);
  AdjGraphEngine& operator=(const AdjGraphEngine&);
}; // class AdjGraphEngine

} // namespace Matchbox

#endif // ADJ_GRAPH_ENGINE_H
