#include "memory_pool.hpp"

#include <iostream>

int main() {
    MemoryPool pool(sizeof(int), 10);

    int* p1 = static_cast<int*>(pool.allocate());
    *p1 = 42;

    int* p2 = static_cast<int*>(pool.allocate());
    *p2 = 17;

    std::cout << *p1 << ' ' << *p2 << '\n';

    pool.deallocate(p1);
    pool.deallocate(p2);

    return 0;
}
