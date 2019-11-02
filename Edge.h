#ifndef EDGE_T_H
#define EDGE_T_H

#include "Vertex.h"
#include <cstddef>

template <class ValueType> class Edge_T {
public:
  ValueType weight;
  Vertex_T<ValueType> *fromVertex;
  Vertex_T<ValueType> *toVertex;

  Edge_T() {
    weight = 0;
    fromVertex = NULL;
    toVertex = NULL;
  }

  Edge_T(ValueType inWeight) {
    weight = inWeight;
    fromVertex = NULL;
    toVertex = NULL;
  }

  Edge_T(ValueType inWeight, Vertex_T<ValueType> *fromPtr,
         Vertex_T<ValueType> *toPtr) {
    weight = inWeight;
    fromVertex = fromPtr;
    toVertex = toPtr;
  }

  bool operator<(Edge_T const &obj) { return (weight < obj.weight); }

  bool operator<=(Edge_T const &obj) { return (weight <= obj.weight); }

  bool operator>(Edge_T const &obj) { return (weight > obj.weight); }

  bool operator>=(Edge_T const &obj) { return (weight >= obj.weight); }

  bool operator==(Edge_T const &obj) { return (weight == obj.weight); }

  bool operator!=(Edge_T const &obj) { return (weight != obj.weight); }

  bool operator==(Vertex_T<ValueType> const &obj) { return (*fromVertex == obj); }
};
#endif
