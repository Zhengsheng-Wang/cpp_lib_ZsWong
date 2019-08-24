#include <iostream>
#include "container/map.h"

int main(){
    zsWong::Map<int, int> m1;
    std::cout << "double: " << sizeof(double) << std::endl;
    std::cout << "float: " << sizeof(float) << std::endl;
    std::cout << "long double: " << sizeof(long double) << std::endl;
    std::cout << "long float: " << sizeof(long float) << std::endl;
    return 0;
}