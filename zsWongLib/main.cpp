#include "container/list.h"
#include "container/map.h"
#include "algorithm/sort.h"
#include "container/graph.h"
#include <iostream>

int main(){
    zsWong::DGraph<char, int> _DGraph_test('C');
    _DGraph_test.add_vertex('C', 6, 'A').add_vertex('B', 1, 'D').add_vertex('C', 2, 'D');
    std::cout << _DGraph_test;
    return 0;
}