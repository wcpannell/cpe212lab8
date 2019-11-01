#ifndef NODETYPE_H
#define NODETYPE_H
#include <cstddef>
//#include "LList.h"


template <class ItemType> class LList; // Linked List class
template <class ItemType> class NodeType {
  friend class LList<ItemType>;

private:
  ItemType component;
  NodeType *nextNode;

public:
  NodeType() { nextNode = NULL; }
  NodeType(ItemType inputData) {
    component = inputData;
    nextNode = NULL;
  }
  ItemType getdata(void) { return component; }
  ~NodeType() {}
};
#endif
