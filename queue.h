
//*******  queue.h header **********

template <class ItemType> class Queue
{
  private:
    ItemType* items;			// Queue items
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
  items = new ItemType[maxQue];	// Allocate array for queue
} // End Queue::Queue()
    Queue(int max)			// Parameterized constructor
{
  maxQue = max + 1;			// Want a queue which stores max elements
  front = maxQue - 1;		// front == rear implies Empty
  rear = maxQue -1;
  items = new ItemType[maxQue];	// Allocate array for queue
} // End Queue::Queue(…)

    ~Queue()			// Destructor
{
  delete [] items;			// Deallocate the queue array
} // End Queue::~Queue()

    void MakeEmpty()		// Initialize queue to empty
{
  front = maxQue - 1;
  rear = maxQue -1;
} // Queue::MakeEmpty()

    bool IsEmpty() const		// Determine if queue is empty
{
  return (front == rear);
} // End Queue::IsEmpty()

    bool IsFull() const		// Determine if queue is full
{
  return ((rear + 1) % maxQue == front);
} // End Queue::IsFull()

    void Enqueue(ItemType newItem)	// Add item to rear of queue
{				// Precondition:  queue NOT full
  rear = (rear+1) % maxQue;
  items[rear] = newItem;
} // End Queue::Enqueue(…)

    void Dequeue(ItemType& item)	// Remove item from front of queue
{				// Precondition:  queue NOT empty
  front = (front + 1) % maxQue;
  item = items[front];
} // End Queue::Dequque(…)

    void jump_the_queue(ItemType newItem)
{
  				// Precondition: queue NOT empty
 items[front] = newItem;
 front -= 1;
  if (front < 0){
	front += maxQue;
  }
}

    char Front()
{
  return(items[front]);
}
};

