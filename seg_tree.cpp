#include "seg_tree.h"
#include <iostream>

using namespace std;
using namespace segment_tree;

int main() {
    vector<int> v = {1, 3, 2, 7, 9, 11};
    segTree<int> tree{v, [](int a, int  b) {return a < b ? a : b;}};

    cout << tree.query(0, 5) << endl;
    cout << tree.query(1, 3) << endl;
    return 0;
}