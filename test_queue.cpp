#include "queue.h"
#include "test.h"
#include "Vertex.h"

Queue<int>* queue;

void test_Instantiate(void){
	TPRINT(__func__);
	queue = new Queue<int>();
}

void test_IsEmpty(void){
	TPRINT(__func__);
	assert(queue->IsEmpty());
}

void test_Enqueue_Dequeue_Front(void){
	TPRINT(__func__);
	for (int i = 0; i < 10; i++) {
		queue->Enqueue(i);
	}
	int front = queue->Front();
	int deq;
	queue->Dequeue(deq);
	assert(front == deq);
}

void test_jumpthequeue(void){
	TPRINT(__func__);
	queue->jump_the_queue(667);
	int item;
	assert(queue->Front() == 667);
	queue->Dequeue(item);
	assert(item = 667);
}

void test_destroy(void){
	TPRINT(__func__);
	delete queue;
}

void test_isfull(){
	TPRINT(__func__);
	queue = new Queue<int>(2);
	queue->Enqueue(1);
	queue->Enqueue(2);
	queue->IsFull();
	test_destroy();
}

void test_vertexqueue(){
	TPRINT(__func__);
	Queue<Vertex_T<int>* > *vqueue = new Queue<Vertex_T<int>* >;
	vqueue->Enqueue(new Vertex_T<int>(1));
	vqueue->Enqueue(new Vertex_T<int>(2));
	Vertex_T<int> *vptr;
	for (int i = 1; i <= 2; i++) {
		vqueue->Dequeue(vptr);
		assert(vptr->value == i);
	}
}



int main(void) {
	cout << "Testing queue.h" << endl;
	test_Instantiate();
	test_IsEmpty();
	test_Enqueue_Dequeue_Front();
	test_jumpthequeue();
	test_destroy();
	test_isfull();
	test_vertexqueue();
	return 0;
}
