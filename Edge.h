#ifndef EDGE_T_H
#define EDGE_T_H

#include "Vertex.h"
#include <cstddef>
template <class ValueType> class Vertex_T;
template <class ValueType> class Edge_T {
public:
  ValueType weight;
  ValueType fromVertex;
  ValueType toVertex;

  Edge_T() {
    weight = 0;
    fromVertex = 0;
    toVertex = 0;
  }

  Edge_T(ValueType infromVertex, ValueType intoVertex, ValueType inWeight){
	  weight = inWeight;
	  fromVertex = infromVertex;
	  toVertex = intoVertex;
  }

  ~Edge_T(){};

  bool operator<(Edge_T const &obj) { return (weight < obj.weight); }

  bool operator<=(Edge_T const &obj) { return (weight <= obj.weight); }

  bool operator>(Edge_T const &obj) { return (weight > obj.weight); }

  bool operator>=(Edge_T const &obj) { return (weight >= obj.weight); }

  bool operator==(Edge_T const &obj) { return (weight == obj.weight); }

  bool operator!=(Edge_T const &obj) { return (weight != obj.weight); }

  bool operator==(Vertex_T<ValueType> const &obj) { return (*fromVertex == obj); }
};
#endif
