#ifndef VERTEX_SET_H
#define VERTEX_SET_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


template<class Size, class Mark>
void PrintVertexSet(std::vector<Mark> markVec,
                    Size cardinality) {
  std::cout << "mark: ";
  std::copy(markVec.begin(), markVec.end(),
            std::ostream_iterator<Mark>(std::cout, " "));
  std::cout << std::endl;
  std::cout << "cardinality: " << cardinality << std::endl;
}

template<class Size, class Mark>
void PrintVertexSet(std::vector<Mark> sMarkVec,
                    std::vector<Mark> tMarkVec,
                    Size cardinality) {
  std::cout << "S mark: ";
  std::copy(sMarkVec.begin(), sMarkVec.end(),
            std::ostream_iterator<Mark>(std::cout, " "));
  std::cout << std::endl;
  std::cout << "T mark: ";
  std::copy(tMarkVec.begin(), tMarkVec.end(),
            std::ostream_iterator<Mark>(std::cout, " "));
  std::cout << std::endl;
  std::cout << "cardinality: " << cardinality << std::endl;
}

#endif // VERTEX_SET_H
