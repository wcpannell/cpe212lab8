//*******  stack.h Standard Header Information Here **********
#include "LList.h"

template <class ItemType> class Stack			// Array-based Stack class
{
 private:
	 int MAX_SIZE;
  LList<ItemType> *data;		// Head of linked list
  int item_count;

 public:
  // Default constructor
  // Postcondition: Empty stack created
  Stack(){
	  MAX_SIZE = -1;
	  data = new LList<ItemType>;
  }
  Stack(int max_size){
	  MAX_SIZE = max_size;
	  data = new LList<ItemType>;
  }

  // Checks to see if stack is empty
  // Postcondition: Returns TRUE if empty, FALSE otherwise
  bool IsEmpty() const {
	  return data->IsEmpty();
  }

  // Checks to see if stack is full
  // Postcondition: Returns TRUE if full, FALSE otherwise
  bool IsFull() const {
	  if (MAX_SIZE > 0){
		  return item_count == MAX_SIZE;
	  } else {
		  return false;
	  }
  }

  // Adds item to top of stack
  void Push(ItemType item) {
	  data->InsertasFirst(item);
	  item_count++;
  }

  // Removes top item from stack
  void Pop(ItemType &item) {
	  data->RemoveFirst(item);
	  item_count--;
  }

  // Returns a copy of top item on stack
  // Postcondition: item still on stack, copy returned
  ItemType Top() const {
	  NodeType<ItemType> *nodePtr;
	  nodePtr = data->GetHead();
	  return nodePtr->component;
  }

  // Removes all items from stack
  void MakeEmpty() {
	  data->MakeEmpty();
  }

  ~Stack(void) {
	  MakeEmpty();
	  delete data;
  }
};
