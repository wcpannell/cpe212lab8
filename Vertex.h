#ifndef VERTEX_T_H
#define VERTEX_T_H

#include "Edge.h"
#include "LList.h"

template <class ValueType> class Vertex_T {
public:
  // value and edges could be private with getter/setter methods
  // but that got annoying with NodeType, so this follows the Python
  //"We're all consenting adults" method of (not) hiding attributes.
  ValueType value;
  LList< Edge_T<ValueType> >* edges= LList< Edge_T<ValueType> >();
  bool marked;

  Vertex_T() { marked = false; }

  Vertex_T(ValueType inputData) {
    value = inputData;
    marked = false;
  }

  Vertex_T(ValueType inputData, bool inputMark) {
    value = inputData;
    marked = inputMark;
  }

  ~Vertex_T() {
  delete edges;
  }

  bool operator<(Vertex_T const &obj) { return (value < obj.value); }

  bool operator<=(Vertex_T const &obj) { return (value <= obj.value); }

  bool operator>(Vertex_T const &obj) { return (value > obj.value); }

  bool operator>=(Vertex_T const &obj) { return (value >= obj.value); }

  bool operator==(Vertex_T const &obj) { return (value == obj.value); }

  bool operator!=(Vertex_T const &obj) { return (value != obj.value); }
};
#endif
