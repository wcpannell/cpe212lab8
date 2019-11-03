#include "test.h"
#include "edgegraph.h"

using namespace std;

GraphType<int>* graph;

void test_AddVertex(void) {
	TPRINT(__func__);
	Vertex_T<int>* vertex = new Vertex_T<int>(1);
	graph->AddVertex(vertex);
}

void test_GetVertexByValue(void) {
	TPRINT(__func__);
	Vertex_T<int>* vertexptr = graph->GetVertexByValue(1);
	assert(vertexptr->value == 1);
}

void test_AddEdge(void) {
	TPRINT(__func__);
	Vertex_T<int>* toVertex = new Vertex_T<int>(2);
	Vertex_T<int>* toVertex3 = new Vertex_T<int>(3);
	graph->AddVertex(toVertex);
	graph->AddVertex(toVertex3);
	//Vertex_T<int> *fromVertex = graph->vertices->GetPtr(Vertex_T<int>(1))
	graph->AddEdge(toVertex3, toVertex, 300);
	graph->AddEdge(1,2,-1);
	graph->AddEdge(1,3,200);
}

void test_WeightIs(void) {
	TPRINT(__func__);
	assert(graph->WeightIs(1,2) == -1);
	assert(graph->WeightIs(1,3) == 200);
}

void test_IsFull_IsEmpty(){
	TPRINT(__func__);
	GraphType<int> *tempGraph = new GraphType<int>(1);
	assert(tempGraph->IsEmpty());
	tempGraph->AddVertex(new Vertex_T<int>(1));
	assert(tempGraph->IsFull());
}

void test_GetToVertices() {
	Queue< Vertex_T<int> >*  adjQueue = new Queue< Vertex_T<int> >;
}




int main(void) {
    cout << "Testing edgegraph->h" << endl;
	graph = new GraphType<int>();
	test_AddVertex();
	test_GetVertexByValue();
	test_AddEdge();
	test_WeightIs();
	test_IsFull_IsEmpty();
    return 0;
}
