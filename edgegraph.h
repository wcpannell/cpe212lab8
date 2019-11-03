#ifndef EGRAPH_H
#define EGRAPH_H

// Forward declaration of ItemType
// typedef char ItemType;

#include "Edge.h"
#include "LList.h"
#include "Vertex.h"
#include "queue.h"
#include "stack.h"
#include <iostream>
#include <string>

const int NULL_EDGE = 0;
class GraphFull {};

template <class VertexType>
// Assumption: VertexType is a type for which the "=", "==", and "<<" are
// defined
class GraphType {
private:
  int numVertices;
  int maxVertices; ///< -1 means no limit
  LList<Vertex_T<VertexType>* > *vertices;
  LList<Edge_T<VertexType>* > *edges;

public:
  GraphType() {
    numVertices = 0;
    maxVertices = -1;
    vertices = new LList<Vertex_T<VertexType>* >;
	edges = new LList<Edge_T<VertexType>* >;
  }

  GraphType(int maxV) {
    numVertices = 0;
    maxVertices = maxV;
    vertices = new LList<Vertex_T<VertexType>* >;
    edges = new LList<Edge_T<VertexType>* >;
  }

  // Post: Arrays for vertices and marks have been deallocated.
  ~GraphType() {
    MakeEmpty();
    delete vertices;
    delete edges;
  }

  void MakeEmpty() {
	  vertices->MakeEmpty();
	  edges->MakeEmpty();
  }
  bool IsEmpty() const { return vertices->IsEmpty(); }

  bool IsFull() const { return numVertices == maxVertices; }

  // Post: Vertex has been stored in vertices.
  //       numVertices has been incremented.
  void AddVertex(Vertex_T<VertexType> *vertex) {
    if ((numVertices < maxVertices) || (maxVertices < 0)) {
      vertices->Insert(vertex);
      numVertices++;
    } else {
      throw(GraphFull());
    }
  }

  /*// Post: Edge (fromVertex, toVertex) is stored in edges.
  void AddEdge(Vertex_T<VertexType> fromVertex, Vertex_T<VertexType> toVertex,
               VertexType weight) {
    Edge_T<VertexType> *newEdge =
        new Edge_T<VertexType>(weight, fromVertex, toVertex);
    Vertex_T<VertexType> fromVertexPtr = vertices->GetPtr(fromVertex);
    //edges->Insert(newEdge);
    fromVertexPtr->edges->Insert(newEdge);
  }*/

  /** Add edge (by pointers)
   */
  void AddEdge(
		  Vertex_T<VertexType> *fromVertex,
		  Vertex_T<VertexType> *toVertex,
          VertexType inWeight) {
	  Edge_T<VertexType>* newEdge =
		  new Edge_T<VertexType>(inWeight, fromVertex, toVertex);
	  edges->Insert(newEdge);
      fromVertex->edges->Insert(newEdge);
	  fromVertex->numEdges++;
      toVertex->edges->Insert(newEdge);
	  toVertex->numEdges++;
  }

  /** Add edge by searching for vertices by value
   */
  void AddEdge(VertexType fromVertexValue, VertexType toVertexValue, VertexType weight) {
    Edge_T<VertexType> *newEdge = new Edge_T<VertexType>(weight);

    try {
      Vertex_T<VertexType> *fromVertex = GetVertexByValue(fromVertexValue);
      Vertex_T<VertexType> *toVertex = GetVertexByValue(toVertexValue);

	  newEdge->fromVertex = fromVertex;
	  newEdge->toVertex = toVertex;

	  edges->Insert(newEdge);
      fromVertex->edges->Insert(newEdge);
	  fromVertex->numEdges++;
      toVertex->edges->Insert(newEdge);
	  toVertex->numEdges++;

    } catch (NotFound) {
      cout << "a VertexValue was not found in vertices" << endl;
      return;
    }
  }

  // This method reaches into the item type classes to work. It's dirty.
  // Post: Returns the weight associated with the edge
  //       (fromVertex, toVertex).
  VertexType WeightIs(VertexType fromVertex, VertexType toVertex) {
	  Edge_T<VertexType> *edge = GetEdgeByVerticesValue(fromVertex, toVertex);
	  return edge->weight;
  }

  /* deprecated
  // Post: Returns the index of vertex in vertices.
    int IndexIs(VertexType *vertices, VertexType vertex)
  {
    int index = 0;

    while (!(vertex == vertices[index]))
      index++;
    return index;
  }
  */

  void GetToVertices(VertexType vertex, Queue<Vertex_T<VertexType>* > &adjVertices) {
    Vertex_T<VertexType> *vertexPtr = GetVertexByValue(vertex);
	GetToVertices(vertexPtr, adjVertices);
  }

  void GetToVertices(Vertex_T<VertexType> *vertexPtr, Queue<Vertex_T<VertexType>* > &adjVertices) {
	NodeType<Edge_T<VertexType>* > *currentNodePtr =
        vertexPtr->edges->GetHead();

	// Iterate over each edge in list
    bool isEnd = false;
    while (!isEnd) {
		if (vertexPtr == currentNodePtr->component->fromVertex) {
		  if ((currentNodePtr->component->toVertex != NULL) &&
			  !adjVertices.IsFull()) {
			adjVertices.Enqueue(currentNodePtr->component->toVertex);
		  }
		} else if (vertexPtr == currentNodePtr->component->toVertex) {
		  if ((currentNodePtr->component->fromVertex != NULL) &&
			  !adjVertices.IsFull()) {
			adjVertices.Enqueue(currentNodePtr->component->fromVertex);
		  }
		}
	  if (currentNodePtr->nextNode == NULL) {
        isEnd = true;
      } else {
        currentNodePtr = currentNodePtr->nextNode;
      }
    }
  }

  Vertex_T<VertexType> *GetVertexByValue(VertexType value) {
	  NodeType<Vertex_T<VertexType>* > *currentNodePtr = vertices->GetHead();
    bool isEnd = false;
    while (!isEnd) {
      if (currentNodePtr->component->value == value) {
		  return currentNodePtr->component;
	  } else if (currentNodePtr->nextNode == NULL) {
        isEnd = true;
      } else {
        currentNodePtr = currentNodePtr->nextNode;
      }
    }
    throw NotFound();
  }

  Edge_T<VertexType> *GetEdgeByVerticesValue(VertexType vertex1value, VertexType vertex2value) {
	  Vertex_T<VertexType> *Vertex1Ptr = GetVertexByValue(vertex1value);
	  Vertex_T<VertexType> *Vertex2Ptr = GetVertexByValue(vertex2value);
	  NodeType<Edge_T<VertexType>* > *currentNodePtr =  Vertex2Ptr->edges->GetHead();
	  bool isEnd = false;
	  while (!isEnd) {
		  if (Vertex1Ptr->edges->IsDuplicate(currentNodePtr->component)) {
			  return currentNodePtr->component;
		  } else if (currentNodePtr->nextNode == NULL) {
			  isEnd = true;
		  } else {
			  currentNodePtr = currentNodePtr->nextNode;
		  }
	  }
	  throw NotFound();

	  /* Brute force method. slow.
	  LList<Edge_T<VertexType>* > currentNodePtr = edges->GetHead();
    while (!isEnd) {
      if (
			  ((currentNodePtr->component->fromVertex->value == vertex1value)
			  || (currentNodePtr->component->fromVertex->value == vertex2value))
			  && ((currentNodePtr->component->toVertex->value == vertex1value)
			  || (currentNodePtr->component->toVertex->value == vertex2value))){
		  return currentNodePtr->component;
	  } else if (currentNodePtr->nextNode == NULL) {
        isEnd = true;
      } else {
        currentNodePtr = currentNodePtr->nextNode;
      }
    }
    throw NotFound();
	*/
  }

  Vertex_T<VertexType> *GetVertexByMostEdges(void) {
	  NodeType<Vertex_T<VertexType> *> *currentNodePtr = vertices->GetHead();
	  if (currentNodePtr == NULL) { throw NotFound(); }
	  Vertex_T<VertexType> *greatest = currentNodePtr->component;
	  bool isEnd = false;

	  while (!isEnd) {
		  if (currentNodePtr->component->numEdges > greatest->numEdges) {
			  greatest = currentNodePtr->component;
		  }
		  if (currentNodePtr->nextNode == NULL) {
			  isEnd = true;
		  } else {
			  currentNodePtr = currentNodePtr->nextNode;
		  }
	  }
	  return greatest;
  }

  Vertex_T<VertexType> *GetVertexByLeastEdges(void) {
	  NodeType<Vertex_T<VertexType> *> *currentNodePtr = vertices->GetHead();
	  if (currentNodePtr == NULL) { throw NotFound(); }
	  Vertex_T<VertexType> *least = currentNodePtr->component;
	  bool isEnd = false;

	  while (!isEnd) {
		  if (currentNodePtr->component->numEdges < least->numEdges) {
			  least = currentNodePtr->component;
		  }
		  if (currentNodePtr->nextNode == NULL) {
			  isEnd = true;
		  } else {
			  currentNodePtr = currentNodePtr->nextNode;
		  }
	  }
	  return least;
  }

  void ClearMarks() {
    NodeType<Vertex_T<VertexType>* > *currentNodePtr = vertices->GetHead();
    bool isEnd = false;
    while (!isEnd) {
      currentNodePtr->component->marked = false;
      if (currentNodePtr->nextNode == NULL) {
        isEnd = true;
      } else {
        currentNodePtr = currentNodePtr->nextNode;
      }
    }
  }

  void MarkVertex(VertexType vertex) {
    Vertex_T<VertexType> *foundVertex;
    foundVertex = GetVertexByValue(vertex);
    foundVertex->marked = true;
  }

  void MarkVertex(Vertex_T<VertexType> *vertex) {
    vertex->marked = true;
  }

  bool IsMarked(VertexType vertex) {
    Vertex_T<VertexType> *foundVertex = GetVertexByValue(vertex);
    return foundVertex->marked;
  }

  bool IsMarked(Vertex_T<VertexType> *vertex) {
	  return vertex->marked;
  }

  /* These are out of scope for the assignment.
   * Fix later
  // Assumes VertexType is a type for which the "==" and "<<"
  // operators are defined
    void DepthFirstSearch(GraphType<VertexType> graph, VertexType startVertex,
                          VertexType endVertex)
  {
    using namespace std;
    Stack stack;
    Queue<Vertex_T<int>* > vertexQ;

    bool found = false;
    VertexType vertex;
    VertexType item;

    graph.ClearMarks();
    stack.Push(startVertex);
    do
    {
      stack.Pop(vertex);
      if (vertex == endVertex)
      {
        cout << vertex;
        found = true;
      }
      else
      {
        if (!graph.IsMarked(vertex))
        {
          graph.MarkVertex(vertex);
          cout << vertex;
          graph.GetToVertices(vertex, vertexQ);

          while (!vertexQ.IsEmpty())
          {
            vertexQ.Dequeue(item);
            if (!graph.IsMarked(item))
              stack.Push(item);
          }
        }
      }
    } while (!stack.IsEmpty() && !found);
    if (!found)
      cout << "Path not found." << endl;
  }

  // Assumption: VertexType is a type for which the "==" and "<<" operators
  //are defined.
  void BreadthFirstSearch(GraphType<VertexType> graph, VertexType
  startVertex, VertexType endVertex)
  {
    using namespace std;
    Queue queue;
    Queue vertexQ;

    bool found = false;
    VertexType vertex;
    VertexType item;
    graph.ClearMarks();
    queue.Enqueue(startVertex);

    do
    {
      queue.Dequeue(vertex);

      if (vertex == endVertex)
      {
        cout << vertex;
        found = true;
      }
      else
      {
        if (!graph.IsMarked(vertex))
        {
          graph.MarkVertex(vertex);
          cout << vertex;
          graph.GetToVertices(vertex, vertexQ);

          while (!vertexQ.IsEmpty())
          {
            vertexQ.Dequeue(item);
            if (!graph.IsMarked(item))
              queue.Enqueue(item);
          }
        }
      }
    } while (!queue.IsEmpty() && found);
    if (!found)
      cout << "Path not found." << endl;
  }

    void ShortestPath(VertexType startVertex, VertexType endVertex, Queue
  &path)
  {
    using namespace std;
    Queue queue;
    Queue vertexQ;

    bool found = false;
    VertexType vertex;
    VertexType item;
    ClearMarks();
    queue.Enqueue(startVertex);

    do
    {
      queue.Dequeue(vertex);
      int vertexIndex = IndexIs(vertices, vertex);
      int endVertexIndex = IndexIs(vertices, endVertex);
      if (vertex == endVertex)
      {
        path.Enqueue(vertex);
        found = true;
      }
      else if (edges[vertexIndex][endVertexIndex] != NULL_EDGE)
      {
        path.Enqueue(vertex);
        path.Enqueue(endVertex);
        found = true;
      }
      else
      {
        if (!IsMarked(vertex))
        {
          MarkVertex(vertex);
          path.Enqueue(vertex);
          GetToVertices(vertex, vertexQ);
          while (!vertexQ.IsEmpty())
          {
            vertexQ.Dequeue(item);
            if (!IsMarked(item))
            {
              queue.Enqueue(item);
            }
          }
        }
      }
    } while (!queue.IsEmpty() && !found);
    if (!found)
    {
      cout << "Path not found." << endl;
      path.MakeEmpty();
      return;
    }
  }
  */
};
#endif
