#include <iostream>
#include <cstdlib>
#include <fstream>
//#include "edgegraph.h"
#include "Vertex.h"

using namespace std;

int main(int argv, char** argc)
{
 // GraphType< Vertex_T <unsigned int> > uintGraph;
  ifstream file;
  unsigned int node, edge;

  file.open("smalldata.txt");
  for (int i = 0; i < 20; i++) {
      file >> node >> edge;
      cout << node << " " << edge << endl;
  }
  file.close();
}
