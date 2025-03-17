#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <cstddef>
#include <vector>

class MemoryPool {
public:
    MemoryPool(size_t block_size, size_t total_blocks);
    ~MemoryPool();

    void* allocate();
    void deallocate(void* ptr);

private:
    struct Block {
        Block* next;
    };

    Block* free_list;
    std::vector<void*> allocations;

    size_t block_size;
    size_t total_blocks;

    void allocate_block();
};

#endif // MEMORY_POOL_HPP
