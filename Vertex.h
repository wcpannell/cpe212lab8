#ifndef VERTEX_T_H
#define VERTEX_T_H

#include "LList.h"
#include <cstddef>

template <class ValueType> class Vertex_T {
    public:
        //value and edges could be private with getter/setter methods
        //but that got annoying with NodeType, so this follows the Python
        //"We're all consenting adults" method of (not) hiding attributes.
        ValueType value;
        LList<ValueType>* edges;

        Vertex_T() { edges = NULL; }

        Vertex_T(ValueType inputData) {
            value = inputData;
            edges = NULL;
        }

        Vertex_T(ValueType inputData, LList<ValueType>* inputEdges) {
            value = inputData;
            edges = inputEdges;
        }

        ~Vertex_T() {
            delete edges;
        }

        bool operator < (Vertex_T const &obj) {
            return (value < obj.value);
        }

        bool operator <= (Vertex_T const &obj) {
            return (value <= obj.value);
        }

        bool operator > (Vertex_T const &obj) {
            return (value > obj.value);
        }

        bool operator >= (Vertex_T const &obj) {
            return (value >= obj.value);
        }

        bool operator == (Vertex_T const &obj) {
            return (value == obj.value);
        }

        bool operator != (Vertex_T const &obj) {
            return (value != obj.value);
        }
};
#endif
