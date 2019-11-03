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
  long counter = 1;

  file.open("words2xx");
  //file.open("smalldata.txt");
  while (file >> fnode >> tnode) {
      //cout << fnode << " " << tnode << endl;
	  graph.AddVertex(fnode);
	  graph.AddVertex(tnode);
	  graph.AddEdge(fnode, tnode, -1);
	  if ((counter % 5000) == 0) {
		  cout << "Processed " << counter << "Edges, " <<
			  graph.numVertices << "Vertices." << endl;
	  }
	  counter++;
  }
  file.close();

  Vertex_T<unsigned int> *greatest = graph.GetVertexByMostEdges();
  Vertex_T<unsigned int> *least = graph.GetVertexByLeastEdges();

  cout << "Vertex " << greatest->value << " has Greatest Number of Directed Edges with " << greatest->numEdges << endl;
  cout << "Vertex " << least->value << " has Least Number of Directed Edges with " << least->numEdges << endl;
}
