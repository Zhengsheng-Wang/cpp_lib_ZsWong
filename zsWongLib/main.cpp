#include "container/list.h"
#include "container/map.h"
#include "algorithm/sort.h"
#include "container/graph.h"
#include <iostream>

int main(){
    zsWong::DGraph<char, int> _DGraph_test('C');
    _DGraph_test.add_vertex('C', 6, 'A');
    std::cout << _DGraph_test;
    zsWong::List<int> _List_list;
    _List_list.push(1);
    std::cout << _List_list << std::endl;
    return 0;
}