#include "memory_pool.hpp"

#include <algorithm>
#include <new>

MemoryPool::MemoryPool(size_t block_size, size_t total_blocks)
    : block_size(block_size), total_blocks(total_blocks), free_list(nullptr) {
    allocate_block();
}

MemoryPool::~MemoryPool() {
    for (void* ptr : allocations) {
        ::operator delete(ptr);
    }
}

void* MemoryPool::allocate() {
    if (free_list == nullptr) {
        allocate_block();
    }

    Block* block = free_list;
    free_list = block->next;
    return block;
}

void MemoryPool::deallocate(void* ptr) {
    Block* block = static_cast<Block*>(ptr);
    block->next = free_list;
    free_list = block;
}

void MemoryPool::allocate_block() {
    size_t blockSizeWithHeader = std::max(sizeof(Block), block_size);
    void* newBlock = ::operator new(blockSizeWithHeader * total_blocks);
    allocations.push_back(newBlock);

    char* blockPtr = static_cast<char*>(newBlock);
    for (size_t i = 0; i < total_blocks; ++i) {
        Block* block = reinterpret_cast<Block*>(blockPtr + i * blockSizeWithHeader);
        block->next = free_list;
        free_list = block;
    }
}
