#include "allocator.hpp"

#include <vector>

template <typename T>
T* MyAllocator<T>::allocate(std::size_t n) {
    std::cout << "Allocating " << n << " objects" << std::endl;
    if (n > max_size()) throw std::bad_alloc();
    
    void* ptr = std::malloc(n * sizeof(T));
    if (!ptr) throw std::bad_alloc();
    
    return static_cast<T*>(ptr);
}

template <typename T>
void MyAllocator<T>::deallocate(T* p) noexcept {
    std::cout << "Deallocating memory" << std::endl;
    std::free(p);
}

template <typename T>
size_t MyAllocator<T>::max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template <typename T>
template <typename U, typename... Args>
void MyAllocator<T>::construct(U* p, Args&&... args) {
    std::cout << "Constructing object" << std::endl;
    new (p) U(std::forward<Args>(args)...);
}

template <typename T>
template <typename U>
void MyAllocator<T>::destroy(U* p) {
    std::cout << "Destroying object" << std::endl;
    p->~U();
}


int main() {
    MyAllocator<int> allocator;

    int* arr = allocator.allocate(5);
    std::cout << "Memory allocated for 5 integers.\n";

    for (int i = 0; i < 5; ++i) {
        allocator.construct(&arr[i], i * 10);
    }

    std::cout << "Allocated and constructed values: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
        allocator.destroy(&arr[i]);
    }

    allocator.deallocate(arr);
    std::cout << "Memory deallocated.\n";

    return 0;
}
