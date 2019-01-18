#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H
#include <math.h>
namespace Matchbox {

template<class Itm>
class Increment {
public:
  Itm operator()(Itm itm) const { return ++itm; }
};

template<class ItmValPair>
class ItmLess {
public:
  bool operator()(const ItmValPair& x, const ItmValPair& y) const {
    return (x.first < y.first);
  }
};

template<class ItmValPair>
class ItmGreater {
public:
  bool operator()(const ItmValPair& x, const ItmValPair& y) const {
    return (x.first > y.first);
  }
};

template<class ItmValPair>
class ValLess {
public:
  bool operator()(const ItmValPair& x, const ItmValPair& y) const {
    return (x.second < y.second);
  }
};

template<class ItmValPair>
class ValGreater {
public:
  bool operator()(const ItmValPair& x, const ItmValPair& y) const {
    return (x.second > y.second || (fabs(x.second - y.second) <= 0.00009 && x.first < y.first) );
  }
};

template<class ItmValPair>
class ValGreater2 {
public:
  bool operator()(const ItmValPair& x, const ItmValPair& y) const {
    return (x.second > y.second );
  }
};

template<class ItmValPairofPair>
class ValGreaterPairs {
public:
  bool operator()(ItmValPairofPair& x, ItmValPairofPair& y) const {
  	
    return (x.second > y.second || (fabs(x.second - y.second) <= 0.00009 && x.first.first < y.first.first));
  }
};

template<class ItmValEdge>
class ValEdge {
public:
  bool operator()(ItmValEdge& x, ItmValEdge& y) const {
  	
    return (x.w > y.w || (fabs(x.w - y.w) <= 0.00009 && x.s < y.s));
  }
};

} // namespace Matchbox

#endif // FUNCTIONAL_H
