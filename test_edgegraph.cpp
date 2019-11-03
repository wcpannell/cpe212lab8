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
	tempGraph->MakeEmpty();
	delete tempGraph;
}

void test_GetToVertices() {
	TPRINT(__func__);
	Queue< Vertex_T<int>* >*  adjQueue = new Queue< Vertex_T<int>* >();
	Vertex_T<int>* fromVertex = graph->GetVertexByValue(1);

	//Use "fromVertex"
	graph->GetToVertices(fromVertex, *adjQueue);
	Vertex_T<int> *connectedVertex;
	adjQueue->Dequeue(connectedVertex);
	assert(connectedVertex->value == 2);
	adjQueue->Dequeue(connectedVertex);
	assert(connectedVertex->value == 3);

	//Use "toVertex"
	graph->GetToVertices(2, *adjQueue);
	adjQueue->Dequeue(connectedVertex);
	assert(connectedVertex->value == 3);
	adjQueue->Dequeue(connectedVertex);
	assert(connectedVertex->value == 1);
}

void test_marks(void) {
	TPRINT(__func__);
	Vertex_T<int> *vertex = graph->GetVertexByValue(2);
	graph->MarkVertex(1);
	graph->MarkVertex(vertex);
	assert(graph->IsMarked(1));
	assert(graph->IsMarked(vertex));
	graph->ClearMarks();
	for (int i = 1; i <= 3; i++) {
		assert(!graph->IsMarked(i));
	}
}

void test_get_vertex_by_numEdges(void){
	FUNCPRINT;
	//Insert a vertex with 1 edge so we have a clear max and min
	graph->AddVertex(new Vertex_T<int>(667));
	graph->AddEdge(1,667,-1);
	Vertex_T<int> *most = graph->GetVertexByMostEdges();
	Vertex_T<int> *least = graph->GetVertexByLeastEdges();
	assert(most->numEdges == 3);
	assert(least->numEdges == 1);
}

void test_MakeEmpty_and_Clean(void) {
	TPRINT(__func__);
	delete graph; // calls MakeEmpty in Destructor.
}




int main(void) {
    cout << "Testing edgegraph->h" << endl;
	graph = new GraphType<int>();
	test_AddVertex();
	test_GetVertexByValue();
	test_AddEdge();
	test_WeightIs();
	test_IsFull_IsEmpty();
	test_GetToVertices();
	test_marks();
	test_get_vertex_by_numEdges();
	test_MakeEmpty_and_Clean();
    return 0;
}
