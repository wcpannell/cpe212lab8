//*******  LList.h Standard Header Information Here **********
#ifndef LLIST_H
#define LLIST_H

#include <cstddef>
#include <iostream>
#include "NodeType.h"

using namespace std;

class NotFound{};

template <class ItemType>
class LList // Linked List class
{
private:
  NodeType<ItemType> *head; // Head of linked list

public:
  // Default constructor
  // Postcondition: Empty list created
  LList() { head = NULL; }

  // Checks to see if list is empty
  // Postcondition: Returns TRUE if empty, FALSE otherwise
  bool IsEmpty() const { return (head == NULL); }

  // Prints list contents
  // Postcondition: list contents, if any, has been printed
  void Print() const {
    NodeType<ItemType> *currentNodePtr = head;

    while (currentNodePtr != NULL) {
      cout << currentNodePtr->component << endl;
      currentNodePtr = currentNodePtr->nextNode;
    }
    if (IsEmpty())
      cout << "list is empty\n";
    cout << "end of print\n";
  }

  // Adds item to beginning of list
  // Precondition: item < first list item
  // Postcondition: item is first in List &
  //	list items are in order
  void InsertasFirst(ItemType item) {
    NodeType<ItemType> *tempPtr = new NodeType<ItemType>(item);

    // tempPtr->component = item;
    tempPtr->nextNode = head;
    head = tempPtr;
  }

  // checks if item exists in list
  bool IsDuplicate(ItemType item) {
      try {
         Get(item);
      }
      catch (NotFound) {
          return false;
      }
      return true;
  }

  // Adds item to correct place in list
  // Precondition: items in list are in ascending order
  // Postcondition: new node containing item added to
  // list 	& all list items in ascending order
  void Insert(ItemType item) {
    NodeType<ItemType> *temp = new NodeType<ItemType>;
    temp->component = item;
    bool isEnd = false;
    NodeType<ItemType> *made = head;

    if (head == NULL || temp->component <= head->component) {
      InsertasFirst(temp->component);
    } else {
      while (!isEnd && (made->component <= temp->component)) {
        if (made->nextNode == NULL) {
          isEnd = true;
        } else {
          made = made->nextNode;
        }
      }
      temp->nextNode = made->nextNode;
      made->nextNode = temp;
    }
  }

  // Removes first item occurrence from list if not empty
  // Postcondition: item set to first item on list &
  //	item is no longer in list &
  // 	list items in ascending order
  void RemoveFirst(ItemType &item) {
    NodeType<ItemType> *tempPtr = head;

    item = head->component;
    head = head->nextNode;
    delete tempPtr;
  }

  /** Returns first occurence of node component from list if it exists.
   * @param ItemType component. Node component to search for.
   * @returns ItemType component if found.
   */
  ItemType Get(ItemType item) {
    bool isEnd = false;
    NodeType<ItemType> *listnode = head;
    while (!isEnd) {
      if (listnode->component == item) {
        return listnode->component;
      } else if (listnode->nextNode == NULL) {
        isEnd = true;
      } else {
        listnode = listnode->nextNode;
      }
    }
    throw NotFound();
  }

  /*ItemType* GetPtr(ItemType item) {
    bool isEnd = false;
    NodeType<ItemType> *listnode = head;
    while (!isEnd) {
      if (listnode->component == item) {
        return &listnode->component;
      } else if (listnode->nextNode == NULL) {
        isEnd = true;
      } else {
        listnode = listnode->nextNode;
      }
    }
    throw NotFound();
  }*/

  NodeType<ItemType>* GetHead(void) {
      return head;
  }

  NodeType<ItemType>* GetNodePtr(NodeType<ItemType> Node) {
    bool isEnd = false;
    NodeType<ItemType> *listnode = head;
    while (!isEnd) {
      if (listnode->component == Node->component) {
        return listnode;
      } else if (listnode->nextNode == NULL) {
        isEnd = true;
      } else {
        listnode = listnode->nextNode;
      }
    }
    throw NotFound();
  }

  // Removes item from the list
  // Precondition: item is in list
  // Postcondition: first occurrence of item is no longer
  //	in list & list items are in ascending order
  void Delete(ItemType item) {
    NodeType<ItemType> *made = head;
    NodeType<ItemType> *before = head;

    bool isEnd = false;
    bool found = false;

    while (!isEnd && (made->component != item)) {
      made = made->nextNode;
      if (made->nextNode == NULL)
        isEnd = true;
    }

    if (made->component == item)
      found = true;

    while (made != head && before->nextNode != made) {
      before = before->nextNode;
    }
    if (found) {
      if (made == head) {
        RemoveFirst(made->component);
      } else {
        before->nextNode = made->nextNode;
        made->nextNode = NULL;
        delete made;
      }
    } else {
      cout << "Item not found. Could not delete.\n";
    }
  }

  void MakeEmpty() {
    while (!IsEmpty()) {
      NodeType<ItemType> *temp = head;
      head = head->nextNode;
      delete temp;
    }
  }

  // Destructor
  // Postcondition: List destroyed
  ~LList() {
  MakeEmpty();
  }
};
#endif
