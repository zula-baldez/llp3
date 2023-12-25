#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../../file-work/private/block.h"
#include "../../hashmap/private/memory_hashmap.h"
#include "../../aggregator/private/database.h"
#include <unistd.h>

#ifdef __linux__
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <memory.h>


#elif _WIN32

#include <windows.h>

#endif

//block can become bigger after merging
//so allocator needs to check if the mapped size and block size equals
struct __attribute__((__packed__)) MappedBlock {
    struct BlockHeader *block;
    uint64_t offset; //to not invalidate key after unnmapping block
    int32_t refCount;
};


int32_t closeAllocator(void);


size_t fileSize(void);

int32_t initAllocator(const char *filename);

bool isValidPosition(uint64_t offset);

int32_t getBlockByOffsetAndSize(struct BlockHeader **bc, uint64_t offset, uint64_t size);

int32_t getAllBlockByOffset(struct BlockHeader **bc, uint64_t offset);

int32_t allocatePageInFile(struct BlockHeader **res, uint64_t size);

int32_t freePage(struct BlockHeader *block);

int32_t unmapPage(struct BlockHeader *block);

#endif //ALLOCATOR_H

