#ifndef EDGE_SET_H
#define EDGE_SET_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "Functional.h"

template<class Size, class Vertex>
void PrintEdgeSet(std::vector<Vertex> mateVec,
                  Size cardinality) {
  std::cout << "mate: ";
  std::transform(mateVec.begin(), mateVec.end(),
                 std::ostream_iterator<Vertex>(std::cout, " "),
                 Matchbox::Increment<Vertex>());
  std::cout << std::endl;
  std::cout << "cardinality: " << cardinality << std::endl;
}

template<class Size, class Vertex>
void PrintEdgeSet(std::vector<Vertex> sMateVec,
                  std::vector<Vertex> tMateVec,
                  Size cardinality) {
  std::cout << "S mate: ";
  std::transform(sMateVec.begin(), sMateVec.end(),
                 std::ostream_iterator<Vertex>(std::cout, " "),
                 Matchbox::Increment<Vertex>());
  std::cout << std::endl;
  std::cout << "T mate: ";
  std::transform(tMateVec.begin(), tMateVec.end(),
                 std::ostream_iterator<Vertex>(std::cout, " "),
                 Matchbox::Increment<Vertex>());
  std::cout << std::endl;
  std::cout << "cardinality: " << cardinality << std::endl;
}

#endif // EDGE_SET_H
