#ifndef VERTEX_T_H
#define VERTEX_T_H

#include "LList.h"
#include "Edge.h"

template <class ValueType> class Edge_T;
template <class ValueType> class Vertex_T {
public:
  // value and edges could be private with getter/setter methods
  // but that got annoying with NodeType, so this follows the Python
  //"We're all consenting adults" method of (not) hiding attributes.
  ValueType value;
  bool marked;
  LList< Edge_T<ValueType>* > *edges;

  Vertex_T() { marked = false; }

  Vertex_T(ValueType inputData) {
    value = inputData;
    marked = false;
    edges = new LList< Edge_T<ValueType>* >();
  }

  Vertex_T(ValueType inputData, bool inputMark) {
    value = inputData;
    marked = inputMark;
    edges = new LList< Edge_T<ValueType>* >();
  }

  Vertex_T(ValueType inputData, bool inputMark, LList< Edge_T<ValueType>* >* inputedges) {
    value = inputData;
    marked = inputMark;
    edges = inputedges;
  }

  ~Vertex_T() {
  //delete edges;
  }

  bool operator<(Vertex_T const &obj) { return (value < obj.value); }

  bool operator<=(Vertex_T const &obj) { return (value <= obj.value); }

  bool operator>(Vertex_T const &obj) { return (value > obj.value); }

  bool operator>=(Vertex_T const &obj) { return (value >= obj.value); }

  bool operator==(Vertex_T const &obj) { return (value == obj.value); }

  bool operator!=(Vertex_T const &obj) { return (value != obj.value); }
};
#endif
