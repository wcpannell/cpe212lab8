#ifndef NODETYPE_H
#define NODETYPE_H
#include <cstddef>
//#include "LList.h"


template <class ItemType> class NodeType {

public:
  ItemType component;
  NodeType *nextNode;

  NodeType() { nextNode = NULL; }
  NodeType(ItemType inputData) {
    component = inputData;
    nextNode = NULL;
  }
  ~NodeType() {}
};
#endif
