#include "LList.h"
//*******  queue.h header **********

template <class ItemType> class Queue
{
  private:
    LList<ItemType> *items;			// Queue items
    int maxQue;			// Max number of queue items + 1
    int front;
//int front;			// Index of element before the front of queue
    int rear;			// Index of rear element of queue

  public:
    Queue()			// Constructor
{
  maxQue = -1;			// Want a queue which stores 500 elements
  front = maxQue - 1;		// front == rear implies Empty
  rear = maxQue -1;
  items = new LList<ItemType>();	// Allocate array for queue
} // End Queue::Queue()
    Queue(int max)			// Parameterized constructor
{
  maxQue = max + 1;			// Want a queue which stores max elements
  front = maxQue - 1;		// front == rear implies Empty
  rear = maxQue -1;
  items = new LList<ItemType>();	// Allocate array for queue
} // End Queue::Queue(…)

    ~Queue()			// Destructor
{
  delete items;			// Deallocate the queue array
} // End Queue::~Queue()

    void MakeEmpty()		// Initialize queue to empty
{
	items->MakeEmpty();
} // Queue::MakeEmpty()

    bool IsEmpty() const		// Determine if queue is empty
{
  return (front == rear);
} // End Queue::IsEmpty()

    bool IsFull() const		// Determine if queue is full
{
	if( maxQue > 0 ){
	  return ((rear + 1) % maxQue == front);
	} else {
		// If maxQue < 0, then there is no size limit
		return false;
	}
} // End Queue::IsFull()

    void Enqueue(ItemType newItem)	// Add item to rear of queue
{				// Precondition:  queue NOT full
	if( maxQue > 0 ){
	  rear = (rear+1) % maxQue;
	} else { rear++; }

	items->InsertasLast(newItem);
} // End Queue::Enqueue(…)

    void Dequeue(ItemType& item)	// Remove item from front of queue
{				// Precondition:  queue NOT empty
	if (maxQue > 0) {
  front = (front + 1) % maxQue;
	} else { front++; }

	items->RemoveFirst(item);
} // End Queue::Dequque(…)

    void jump_the_queue(ItemType newItem)
{
  				// Precondition: queue NOT empty
	items->InsertasFirst(newItem);
	if (maxQue > 0) {
 front -= 1;
  if (front < 0){
	front += maxQue;
  }
	} else { rear++;}
}

    ItemType Front()
{
	NodeType<ItemType> *head = items->GetHead();
	return head->component;
}
};

