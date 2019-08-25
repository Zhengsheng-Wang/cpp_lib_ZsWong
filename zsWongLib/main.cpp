#include <iostream>
#include "container/list.h"
#include "container/map.h"
#include "algorithm/sort.h"

int main(){
    zsWong::List<int> _li;
    _li.push(29).push(55).push(5).push(34).push(19).push(2);
    std::cout << _li << std::endl;
    _li = zsWong::sortQuick<zsWong::List<int>, int>(_li);
    std::cout << _li << std::endl;
    return 0;
}