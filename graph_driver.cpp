#include <iostream>
#include <cstdlib>
#include <fstream>
#include "edgegraph.h"

using namespace std;

int main(int argv, char** argc)
{
 GraphType<unsigned int> graph;
  ifstream file;
  unsigned int fnode, tnode;
  Vertex_T<unsigned int> *fnodePtr, *tnodePtr;

  file.open("words2xx");
  //file.open("smalldata.txt");
 
  //We already know the first vertex will be new and value 0
  fnodePtr = new Vertex_T<unsigned int>(0);
  while (file >> fnode >> tnode) {
      //cout << fnode << " " << tnode << endl;
	  // isduplicate too slow
	// we know the input data is sorted so the value shouldn't
	// change often.
	  if (fnodePtr->value != fnode) {
		  fnodePtr = new Vertex_T<unsigned int>(fnode);
			  graph.AddVertex(fnodePtr);
	  }
		  
	  fnodePtr->edges->InsertasFirst(new Edge_T<unsigned int>(fnode, tnode, -1));
	  fnodePtr->numEdges++;
  }
  file.close();

  Vertex_T<unsigned int> *greatest = graph.GetVertexByMostEdges();
  Vertex_T<unsigned int> *least = graph.GetVertexByLeastEdges();

  cout << "Vertex " << greatest->value << " has Greatest Number of Directed Edges with " << greatest->numEdges << endl;
  cout << "Vertex " << least->value << " has Least Number of Directed Edges with " << least->numEdges << endl;
}
