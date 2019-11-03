//a driver for testing of the LList class

#include "LList.h"
#include "Vertex.h"
#include <iostream>
#include <fstream>
#include "test.h"

using namespace std;

LList<int> alist;

void test_Get_and_GetPtr(void) {
	TPRINT(__func__);
	LList < Vertex_T <int>* > list;
	Vertex_T<int> *value = new Vertex_T<int>(0);
	list.Insert(value);
	Vertex_T<int> *vertex;
	vertex = list.Get(value);
	vertex->marked = true;
	Vertex_T<int> *newvertex;
	newvertex = list.Get(vertex);
	assert(newvertex->marked);
	list.MakeEmpty();
}

void test_Insert_Remove_asFirst(void) {
	TPRINT(__func__);
	alist.InsertasFirst(3);
	int returnval;
	alist.RemoveFirst(returnval);

	assert(returnval == 3);
}

void test_InsertAsLast(void) {
	TPRINT(__func__);
	alist.Print();
	alist.InsertasLast(667);
	alist.InsertasLast(667);
	alist.Print();
	LList<int> *list = new LList<int>;
	list->InsertasLast(776);
	int item;
	list->RemoveFirst(item);
	assert(item == 776);
}

int main()
{

	cout<<"testing insert function:\n";
	for(int i=0; i<=6; i++)
	{
		alist.Insert(i);
	}
	alist.Print();

	cout<<"testing removal of first item:\n";
	alist.Delete(0);
	alist.Print();

	cout<<"testing removal of item in list:\n";
	alist.Delete(3);
	alist.Print();

	cout<<"testing removal of last item in list:\n";
	alist.Delete(6);
	alist.Print();

	cout<<"testing attempted removal of item not in list:\n";
	alist.Delete(6);
	alist.Print();

	cout<<"testing removal of entire list:\n";
	alist.MakeEmpty();
	alist.Print();


	alist.InsertasFirst(5);
	alist.Print();
	alist.InsertasFirst(3);
	alist.Print();
	alist.Insert(4);
	alist.Print();

	test_Get_and_GetPtr();
	test_Insert_Remove_asFirst();
	test_InsertAsLast();
}
