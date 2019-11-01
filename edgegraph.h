#ifndef EGRAPH_H
#define EGRAPH_H

// Forward declaration of ItemType
//typedef char ItemType;

//#include "queue.h"
//#include "stack.h"
#include "LList.h"
#include <iostream>
#include <string>

const int NULL_EDGE = 0;

template <class VertexType>
// Assumption: VertexType is a type for which the "=", "==", and "<<" are
// defined
class GraphType {
private:
  int numVertices;
  int maxVertices;
  LList< LList <VertexType> > edges;
  LList<VertexType>* vertices;
  LList<bool>* marks; // marks[i] is mark for vertices[i].
public:
// Post: Arrays of size 50 are dynamically allocated for
//       marks and vertices. numVertices is set to 0;
//       maxVertices is set to 50.
  GraphType()
{
  numVertices = 0;
  maxVertices = 50;
  vertices = new LList<VertexType>;
  marks = new LList<bool>;
}

// Post: Arrays of size maxV are dynamically allocated for
//       marks and vertices.
//       numVertices is set to 0; maxVertices is set to maxV.
  GraphType(int maxV)
{
  numVertices = 0;
  maxVertices = maxV;
  vertices = new LList<VertexType>;
  marks = new LList<bool>;
}

// Post: Arrays for vertices and marks have been deallocated.
  ~GraphType()
{
  delete vertices;
  delete marks;
}

  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
// Post: Vertex has been stored in vertices.
//       Corresponding row and column of edges has been set
//       to NULL_EDGE.
//       numVertices has been incremented.
  void AddVertex(VertexType vertex)
{
  vertices[numVertices] = vertex;

  for (int index = 0; index < numVertices; index++)
  {
    edges[numVertices][index] = NULL_EDGE;
    edges[index][numVertices] = NULL_EDGE;
  }
  numVertices++;
}

// Post: Edge (fromVertex, toVertex) is stored in edges.
  void AddEdge(VertexType fromVertex, VertexType toVertex, int weight)
{
  int row;
  int col;

  row = IndexIs(vertices, fromVertex);
  col = IndexIs(vertices, toVertex);
  edges[row][col] = weight;
}

// Post: Returns the weight associated with the edge
//       (fromVertex, toVertex).
  int WeightIs(VertexType fromVertex, VertexType toVertex)
{
  int row;
  int col;

  row = IndexIs(vertices, fromVertex);
  col = IndexIs(vertices, toVertex);
  return edges[row][col];
}

// Post: Returns the index of vertex in vertices.
  int IndexIs(VertexType *vertices, VertexType vertex)
{
  int index = 0;

  while (!(vertex == vertices[index]))
    index++;
  return index;
}

  void GetToVertices(VertexType vertex, Queue & adjVertices)
{
  int fromIndex;
  int toIndex;

  fromIndex = IndexIs(vertices, vertex);
  for (toIndex = 0; toIndex < numVertices; toIndex++)
    if (edges[fromIndex][toIndex] != NULL_EDGE)
      adjVertices.Enqueue(vertices[toIndex]);
}

  void ClearMarks()
{
  for (int i = 0; i < numVertices; i++)
  {
    marks[i] = false;
  }
}

  void MarkVertex(VertexType vertex)
{
  for (int i = 0; i < numVertices; i++)
  {
    if (vertex == vertices[i])
    {
      marks[i] = true;
    }
  }
}

  bool IsMarked(VertexType vertex)
{
  for (int i = 0; i < numVertices; i++)
  {
    if (vertex == vertices[i])
    {
      return (marks[i]);
    }
  }

  return false; // Should never happen
}

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

// Assumption: VertexType is a type for which the "==" and "<<" operators are defined.
  void BreadthFirstSearch(GraphType<VertexType> graph, VertexType startVertex,
                          VertexType endVertex)
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

  void ShortestPath(VertexType startVertex, VertexType endVertex, Queue &path)
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

};
#endif
