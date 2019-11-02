#include "Edge.h"
#include "LList.h"
#include "Vertex.h"
#include "test.h"

using namespace std;

void test_Empty_Init(void) {
  TPRINT(__func__);
  Edge_T<int> asdf;
  asdf.weight = 1;
  asdf.fromVertex = new Vertex_T<int>(1);
  asdf.toVertex = new Vertex_T<int>(2);
  assert(asdf.weight == 1);
  assert(asdf.fromVertex->value == 1);
  assert(asdf.toVertex->value == 2);
}

void test_Half_Init(void) {
  TPRINT(__func__);
  Edge_T<int> asdf(1);
  asdf.fromVertex = new Vertex_T<int>(1);
  asdf.toVertex = new Vertex_T<int>(2);
  assert(asdf.weight == 1);
  assert(asdf.fromVertex->value == 1);
  assert(asdf.toVertex->value == 2);
}

void test_Full_Init(void) {
  TPRINT(__func__);
  Vertex_T<int> *fromVertexPtr = new Vertex_T<int>(1);
  Vertex_T<int> *toVertexPtr = new Vertex_T<int>(2);
  Edge_T<int> asdf(1, fromVertexPtr, toVertexPtr);
  assert(asdf.weight == 1);
  assert(asdf.fromVertex->value == 1);
  assert(asdf.toVertex->value == 2);
}

void test_LList_of_Edges(void) {
  TPRINT(__func__);
  LList< Edge_T<int> > edgeList;
  Vertex_T<int> *fromVertexPtr = new Vertex_T<int>(1);
  Vertex_T<int> *toVertexPtr = new Vertex_T<int>(2);
  Edge_T<int> *vertex_a = new Edge_T<int>(1, fromVertexPtr, toVertexPtr);
  edgeList.Insert(*vertex_a);
  Edge_T<int> comeback;
  edgeList.RemoveFirst(comeback);
  assert(comeback.weight == 1);
  assert(comeback.fromVertex->value == 1);
  assert(comeback.toVertex->value == 2);
}

void test_Comparisons(void) {
  TPRINT(__func__);
  Edge_T<int> a, b, temp;
  a.weight = 1;
  b.weight = 2;
  temp.weight = 1;
  assert(a < b);
  assert(a <= b);
  assert(b > a);
  assert(b >= a);
  assert(a != b);
  assert(a <= temp);
  assert(a == temp);
  temp.weight = 2;
  assert(b <= temp);
  assert(b == temp);
}

void test_Vertex_comparison_from_LList(void) {
  TPRINT(__func__);
  LList< Edge_T<int> > edgeList;
  Vertex_T<int> *fromVertexPtr = new Vertex_T<int>(1);
  Vertex_T<int> *toVertexPtr = new Vertex_T<int>(2);
  Edge_T<int> *vertex_a = new Edge_T<int>(1, fromVertexPtr, toVertexPtr);
  edgeList.Insert(*vertex_a);

  LList< Vertex_T<int> > listoverts;
  Vertex_T<int> *vertex_b = new Vertex_T<int>(1, true);
  Vertex_T<int> *vertex_c = new Vertex_T<int>(2, true);
  listoverts.Insert(*vertex_b);
  listoverts.Insert(*vertex_c);
  Vertex_T<int> comeback;
  comeback = listoverts.Get(Vertex_T<int>(1));

  assert(edgeList.Get(*vertex_a) == comeback);
}

int main(void) {
  cout << "Testing Edge.h" << endl;
  test_Empty_Init();
  test_Half_Init();
  test_Full_Init();
  test_LList_of_Edges();
  test_Comparisons();
  test_Vertex_comparison_from_LList();

  return 0;
}
