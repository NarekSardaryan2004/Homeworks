#ifndef MY_ALLOCATOR_HPP
#define MY_ALLOCATOR_HPP

#include <iostream>
#include <limits>
#include <cstdlib>
#include <new> 
#include <utility>

template <typename T>
struct MyAllocator {
    using value_type = T;

    constexpr MyAllocator() noexcept = default;
    constexpr MyAllocator(const MyAllocator&) noexcept = default;
    ~MyAllocator() = default;

    T* allocate(std::size_t n);
    void deallocate(T* p) noexcept;

    size_t max_size() const noexcept;
    
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args);
    
    template <typename U>
    void destroy(U* p);
};

#endif // MY_ALLOCATOR_HPP
