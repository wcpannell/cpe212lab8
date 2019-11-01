#include "test.h"
#include "NodeType.h"

using namespace std;

void test_empty_Node(void) {
    TPRINT(__func__);
    NodeType<int> * deleteme = new NodeType<int>;
    delete deleteme;
}

void test_initialized_Node(void) {
    TPRINT(__func__);
    NodeType<int>* deleteme = new NodeType<int> (1);
    assert(deleteme->getdata() == 1);
}

int main(void) {
    cout << endl << "Testing NodeType.h" << endl;
    test_initialized_Node();
    test_empty_Node();
    return 0;
}
