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
  //LList<Edge_T<VertexType>> *edges;
  LList<Vertex_T<VertexType>> *vertices;

public:
  GraphType() {
    numVertices = 0;
    maxVertices = -1;
    //edges = new LList<Edge_T<VertexType>>;
    vertices = new LList<VertexType>;
  }

  GraphType(int maxV) {
    numVertices = 0;
    maxVertices = maxV;
    vertices = new LList<VertexType>;
    //edges = new LList<Edge_T<VertexType>>;
  }

  // Post: Arrays for vertices and marks have been deallocated.
  ~GraphType() {
    delete vertices;
    //delete edges;
  }

  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;

  // Post: Vertex has been stored in vertices.
  //       numVertices has been incremented.
  void AddVertex(Vertex_T<VertexType> vertex) {
    if ((numVertices < maxVertices) || (maxVertices < 0)) {
      vertices->Insert(vertex);
      numVertices++;
    } else {
      throw(GraphFull());
    }
  }

  // Post: Edge (fromVertex, toVertex) is stored in edges.
  void AddEdge(Vertex_T<VertexType> fromVertex, Vertex_T<VertexType> toVertex,
               VertexType weight) {
    Edge_T<VertexType> *newEdge =
        new Edge_T<VertexType>(weight, fromVertex, toVertex);
    NodeType<VertexType> vertexNode = vertices->GetNodePtr(NodeType<VertexType>(fromVertex));
    //edges->Insert(newEdge);
    vertexNode->component->edges->Insert(newEdge);
  }

  void AddEdge(VertexType fromVertex, VertexType toVertex, VertexType weight) {
    Edge_T<VertexType> *newEdge = new Edge_T<VertexType>(weight);

    Vertex_T<VertexType> vertex(fromVertex);
    try {
      newEdge->fromVertex = vertices->Get(vertex);
    } catch (NotFound) {
      cout << "fromVertex not found in vertices" << endl;
      return;
    }

    vertex.value = toVertex;
    try {
      newEdge->toVertex = vertices->Get(vertex);
    } catch (NotFound) {
      cout << "toVertex not found in vertices" << endl;
      return;
    }

    NodeType<VertexType> vertexNode = vertices->GetNodePtr(NodeType<VertexType>(newEdge->fromVertex));
    vertexNode->component->edges->Get(newEdge);
  }

  // This method reaches into the item type classes to work. It's dirty.
  // Post: Returns the weight associated with the edge
  //       (fromVertex, toVertex).
  int WeightIs(VertexType fromVertex, VertexType toVertex) {
    NodeType<Edge_T<VertexType>> *currentNodePtr = edges->GetHead();
    bool isEnd = false;
    while (!isEnd) {
      if ((currentNodePtr->component->fromVertex == fromVertex) &&
          (currentNodePtr->component->toVertex == toVertex)) {
        return currentNodePtr->component->weight;
      } else if (currentNodePtr->nextNode == NULL) {
        isEnd = true;
      } else {
        currentNodePtr = currentNodePtr->nextNode;
      }
    }
    throw NotFound();
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

  void GetToVertices(VertexType vertex, Queue &adjVertices) {
    int fromIndex;
    int toIndex;
    NodeType<Vertex_T<VertexType>> *currentNodePtr = vertices->GetHead();
    bool isEnd = false;
    while (!isEnd) {
      currentNodePtr->component->marked = false;
      if (currentNodePtr->nextNode == NULL) {
        isEnd = true;
      } else {
        currentNodePtr = currentNodePtr->nextNode;
      }
    }

    fromIndex = IndexIs(vertices, vertex);
    for (toIndex = 0; toIndex < numVertices; toIndex++)
      if ((edges[fromIndex][toIndex] != NULL_EDGE) && !adjVertices.IsFull()) {
        adjVertices.Enqueue(vertices[toIndex]);
      }

    void ClearMarks() {
      NodeType<Vertex_T<VertexType>> *currentNodePtr = vertices->GetHead();
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
      NodeType<Vertex_T<VertexType>> matchVertex(vertex);
      NodeType<Vertex_T<VertexType>> *foundVertex;
      foundVertex = vertices->GetNodePtr(matchVertex);
      foundVertex->component->marked = true;
    }

    bool IsMarked(VertexType vertex) {
      NodeType<Vertex_T<VertexType>> matchVertex(vertex);
      NodeType<Vertex_T<VertexType>> *foundVertex;
      foundVertex = vertices->GetNodePtr(matchVertex);
      return foundVertex->component->marked;
    }
    /* out of scope for assignment, update later
    // Assumes VertexType is a type for which the "==" and "<<"
    // operators are defined
      void DepthFirstSearch(GraphType<VertexType> graph, VertexType startVertex,
                            VertexType endVertex)
    {
      using namespace std;
      Stack stack;
      Queue vertexQ;

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
    are defined. void BreadthFirstSearch(GraphType<VertexType> graph, VertexType
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
