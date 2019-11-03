#include "test.h"
#include "stack.h"

Stack<int> *stack;

void test_Instantiate_IsEmpty(void) {
	FUNCPRINT;
	stack = new Stack<int>(10);
	assert(stack->IsEmpty());
	assert(!stack->IsFull());
}

void test_Destroy_MakeEmpty(void) {
	FUNCPRINT;
	//MakeEmpty called on delete
	delete stack;
}

void test_Push(void) {
	FUNCPRINT;
	for (int i = 0; i < 10; i++) {
		stack->Push(i);
	}
	assert(stack->Top() == 9);
	assert(stack->IsFull());
}

void test_Pop_Top(void) {
	FUNCPRINT;
	int item;
	for (int i = 9; i >= 0; i--) {
		assert(i == stack->Top());
		stack->Pop(item);
		assert(i == item);
	}
}


int main(void) {
	cout << "Testing stack.h" << endl;
	test_Instantiate_IsEmpty();
	test_Push();
	test_Pop_Top();
	test_Destroy_MakeEmpty();
	return 0;
}
