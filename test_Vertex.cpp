#include "LList.h"
#include "Vertex.h"
#include "test.h"

using namespace std;

void test_Empty_Init(void) {
    TPRINT(__func__);
    Vertex_T<int> asdf;
    asdf.value = 1;
    asdf.edges = new LList<int>;
    assert(asdf.value == 1);
    assert(asdf.edges->IsEmpty());
}

void test_Half_Init(void) {
    TPRINT(__func__);
    Vertex_T<int> asdf(1);
    asdf.edges = new LList<int>;
    assert(asdf.value == 1);
    assert(asdf.edges->IsEmpty());
}

void test_Full_Init(void) {
    TPRINT(__func__);
    LList<int>* edgesPtr = new LList<int>;
    Vertex_T<int> asdf(1, edgesPtr);
    assert(asdf.value == 1);
    assert(asdf.edges->IsEmpty());
}

void test_LList_of_Vertices(void) {
    TPRINT(__func__);
    LList< Vertex_T <int> > listoverts;
    Vertex_T <int>* vertex_a = new Vertex_T<int>(1);
    listoverts.Insert(*vertex_a);
    Vertex_T <int> comeback;
    listoverts.RemoveFirst(comeback);
    assert(comeback.value == 1);
    assert(comeback.edges == NULL);
}

void test_Comparisons(void) {
    TPRINT(__func__);
    Vertex_T<int> a, b, temp;
    a.value = 1;
    b.value = 2;
    temp.value = 1;
    assert(a<b);
    assert(a<=b);
    assert(b>a);
    assert(b>=a);
    assert(a!=b);
    assert(a<=temp);
    assert(a==temp);
    temp.value = 2;
    assert(b<=temp);
    assert(b==temp);
}

int main(void) {
   cout << "Testing ValueType.h" << endl;
   test_Empty_Init();
   test_Half_Init();
   test_Full_Init();
   test_LList_of_Vertices();
   test_Comparisons();

    return 0;
}
