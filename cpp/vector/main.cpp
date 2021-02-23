#include "vector.h"
#include <iostream>

int main(){
    myvector::vector<u_int64_t> a;
    a.push_back(1);
    a.push_back(129);
    u_int64_t z = a.pop_back();
    std::cout << z;
    std::cout << a[0];
}