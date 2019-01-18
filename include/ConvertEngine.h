#ifndef CONVERT_ENGINE_H
#define CONVERT_ENGINE_H

#include <vector>
#include <cassert>

#include "Types.h"
#include "BptGraph.h"
#include "Graph.h"
#include "Utility.h" // for CanAdd.

namespace Matchbox {

class ConvertEngine {
public:
  /// Constructor.
  ConvertEngine() {}

  /// Destructor.
  ~ConvertEngine() {}

  ///
  Err Convert(const BptGraph& bptGraph, Graph* graph);
private:
  // forbid the copy constructor and the assignment operator.
  ConvertEngine(const ConvertEngine&);
  ConvertEngine& operator=(const ConvertEngine&);
}; // class ConvertEngine

} // namespace Matchbox

#endif // CONVERT_ENGINE_H
