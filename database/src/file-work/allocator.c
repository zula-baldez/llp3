#include "../../include/file-work/private/allocator.h"


static int32_t minAlignment = 65536;
static uint64_t lastBlockOffset = 0;

static struct HashMap *mappedCache = NULL;

static void initCache(void) {
    mappedCache = initFreeMapAndReturnPointer(50, KEY_UINT64_T);
}

#ifdef __WIN32__

HANDLE hFile = NULL;
HANDLE hMap = NULL;

const char *pathToFile;

int32_t closeAllocator() {
    CloseHandle(hMap);
    CloseHandle(hFile);
    hFile = NULL;
    hMap = NULL;
    if (mappedCache != NULL) {
        freeMap(mappedCache, free);
    }
    mappedCache = NULL;
    return SUCCESS;
}

size_t fileSize() {
    if (!hFile) return 0;
    LARGE_INTEGER fileSize;
    GetFileSizeEx(hFile, &fileSize);
    return fileSize.QuadPart;
}

int32_t initAllocator(const char *filename) {
    pathToFile = filename;
    hFile = CreateFile(pathToFile, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                       OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        closeAllocator();
        return INVALID_FILE_HEADER_WIN;
    }
    uint64_t s = fileSize();
    if (s == 0) {
        closeAllocator();
        return SUCCESS;
    }
    hMap = CreateFileMapping(
            hFile,
            NULL,
            PAGE_READWRITE,
            0,
            (DWORD) 0,
            NULL);
    if (hMap == 0) {
        closeAllocator();
        return FILE_MAPPING_ERROR;
    }
    initCache();
    return SUCCESS;

}

static int32_t unmap(void *data, uint64_t size) {
    UnmapViewOfFile(data);
    return SUCCESS;
}

static int32_t getDataByOffsetAndSize(void **data, uint64_t offset, uint64_t block_size) {
    if (offset % minAlignment != 0) return ALLIGNMENT_ERROR;
    LPVOID lpBasePtr;
    ULARGE_INTEGER ulargeInteger;
    ulargeInteger.QuadPart = offset;

    lpBasePtr = MapViewOfFile(
            hMap,
            FILE_MAP_ALL_ACCESS,
            ulargeInteger.HighPart,
            ulargeInteger.LowPart,
            block_size
    );
    *data = lpBasePtr;
    return SUCCESS;
}

static int32_t expandFile(uint64_t size) {
    if (mappedCache != NULL) {
        struct ColumnNode **nodes = getData(mappedCache);
        for (uint32_t i = 0; i < mappedCache->capacity; i++) {
            struct ColumnNode *node = nodes[i];
            while (node != NULL) {
                unmap(((struct MappedBlock *) node->data)->block, ((struct MappedBlock *) node->data)->block->size);
                node = node->nextNode;
            }
        }
    }
    CloseHandle(hMap);
    CloseHandle(hFile);
    //The process cannot access the file because it is being used by another process.
    hFile = CreateFile(
            pathToFile,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
    );

    size = ((size + minAlignment - 1) / minAlignment) * minAlignment;
    if (size > 0x7FFFFFFFFFFFFFFF) {
        return TOO_BIG_FILE;
    }
    LARGE_INTEGER s;
    s.QuadPart = (int64_t) size;

    if (SetFilePointerEx(hFile, s, NULL, FILE_BEGIN) == 0) {
        return SET_FILE_POINTER_ERROR;
    }
    if (!SetEndOfFile(hFile)) {
        perror("Error setting end of file");
        return SET_END_OF_FILE_ERROR;
    }
    hMap = CreateFileMapping(
            hFile,
            NULL,
            PAGE_READWRITE,
            0,
            0,
            NULL
    );
    if (mappedCache == NULL) {
        initCache();
    } else {
        struct ColumnNode **nodes = getData(mappedCache);
        for (uint32_t i = 0; i < mappedCache->capacity; i++) {
            struct ColumnNode *node = nodes[i];
            while (node != NULL) {
                struct BlockHeader *header;
                checkForErr(getDataByOffsetAndSize((void **) &header, *(uint64_t *) node->key, BLOCK_HEADER_SIZE))
                uint64_t blockSize = header->size;
                unmap(header, BLOCK_HEADER_SIZE);
                MapViewOfFileEx(
                        hMap,
                        FILE_MAP_ALL_ACCESS,
                        (DWORD) 0,
                        (DWORD) *(uint64_t *) node->key,
                        blockSize,
                        ((struct MappedBlock *) node->data)->block

                );
                node = node->nextNode;
            }
        }
    }
    return SUCCESS;
}

#endif
#ifdef __linux__

int32_t fd;
const char *file = NULL;

int32_t closeAllocator() {

    close(fd);
    if (mappedCache != NULL) {
        freeMap(mappedCache, free);
    }
    return SUCCESS;
}

int32_t initAllocator(const char *filename) {
    initCache();
    file = filename;
    fd = open(filename, O_CREAT | O_RDWR,
              S_IRWXU | S_IRWXG | S_IRWXO);

    if (fd == -1) {
        closeAllocator();
        return INVALID_FILE_DESCRIPTOR;
    }
    return SUCCESS;
}

static int32_t expandFile(uint64_t size) {
    uint64_t newSize = size;
    uint64_t alignedSize = ((newSize + minAlignment - 1) / minAlignment) * minAlignment;
    if(size > 0x7FFFFFFFFFFFFFFF) {
        return TOO_BIG_FILE;
    }
    if (ftruncate(fd, (int64_t)alignedSize) == -1) {

        return ERROR_EXPAND_FILE;
    }
}

static int32_t getDataByOffsetAndSize(void** data, uint64_t offset, uint64_t block_size) {
    if (offset % minAlignment != 0) ALLIGNMENT_ERROR;
    void *block_map = mmap(
            NULL,
            block_size,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            fd,
            (long int) offset
    );
    if (block_map == MAP_FAILED) {
        return MAP_ERROR_LIN;
    }
    *data = block_map;
    return SUCCESS;

}


static int32_t unmap(void *data, uint64_t size) {
    munmap(data, size);
    return SUCCESS;
}


size_t fileSize() {
    struct stat st;
    stat(file, &st);
    return st.st_size;
}

#endif

static struct BlockHeader *findBlockInCacheAndAddUsage(uint64_t offset) {
    struct MappedBlock *cachedValue = getDataByKeyAndReturnPointer(mappedCache, &offset);
    if (cachedValue != NULL) {
        cachedValue->refCount++;
        return cachedValue->block;
    }
    return NULL;
}

static void addInCache(struct BlockHeader *blockHeader) {
    struct MappedBlock *mappedBlock = malloc(sizeof(struct MappedBlock));
    mappedBlock->block = blockHeader;
    mappedBlock->refCount = 1;
    mappedBlock->offset = blockHeader->offset;
    addDataInMap(mappedCache, &mappedBlock->offset, mappedBlock);
}


static struct BlockHeader *initAllocatedBlock(uint64_t offset, uint64_t size) {
    struct BlockHeader *header;
    getDataByOffsetAndSize((void **) &header, offset, size + BLOCK_HEADER_SIZE);
    header->offset = offset;
    header->size = size;
    addInCache(header);
    return header;
}


int32_t getBlockByOffsetAndSize(struct BlockHeader **bc, uint64_t offset, uint64_t size) {
    if (offset >= fileSize()) return TOO_BIG_OFFSET;
    struct BlockHeader *res = findBlockInCacheAndAddUsage(offset);
    if (res) {
        *bc = res;
        return SUCCESS;
    }
    struct BlockHeader *header;
    checkForErr(getDataByOffsetAndSize((void **) &header, offset, size + BLOCK_HEADER_SIZE))
    addInCache(header);
    *bc = header;
    return SUCCESS;
}

int32_t getAllBlockByOffset(struct BlockHeader **bc, uint64_t offset) {
    *bc = NULL;
    if (offset >= fileSize()) {
        return TOO_BIG_OFFSET;
    }
    if (offset % minAlignment != 0) {
        return ALLIGNMENT_ERROR;
    }

    struct BlockHeader *res = findBlockInCacheAndAddUsage(offset);
    if (res) {
        *bc = res;
        return SUCCESS;
    }
    struct BlockHeader *header;
    checkForErr(getDataByOffsetAndSize((void **) &header, offset, BLOCK_HEADER_SIZE))
    uint64_t blockSize = header->size;
    unmap(header, BLOCK_HEADER_SIZE);
    struct BlockHeader *head;
    checkForErr(getDataByOffsetAndSize((void **) &head, offset, blockSize + BLOCK_HEADER_SIZE))
    addInCache(head);
    *bc = head;
    return SUCCESS;

}

static int32_t allocatePageInEndOfFile(struct BlockHeader **blockHeader, uint64_t size) {
    uint64_t realNeededSize = size + BLOCK_HEADER_SIZE;
    uint64_t minAvailableToAllocateSize = ((realNeededSize + minAlignment - 1) / minAlignment) * minAlignment;
    uint64_t lastSize = fileSize();
    struct BlockHeader block = {lastSize, minAvailableToAllocateSize - BLOCK_HEADER_SIZE, lastBlockOffset, false};
    checkForErr(expandFile(lastSize + minAvailableToAllocateSize))
    struct BlockHeader *blockPtr = initAllocatedBlock(lastSize, block.size);
    *blockPtr = block;
    lastBlockOffset = lastSize;
    *blockHeader = blockPtr;
    return SUCCESS;
}

static void removeFromCacheAndUnmap(struct BlockHeader *blockHeader) {
    removeData(mappedCache, &blockHeader->offset,
               free);  //need to clear cache manually if block was in cache with wrong mapped size
    unmap(blockHeader, blockHeader->size + BLOCK_HEADER_SIZE);
}

int32_t allocatePageInFile(struct BlockHeader **bh, uint64_t size) {
    struct BlockHeader *res = NULL;
    struct BlockHeader *header;
    struct BlockCoordinate blockCoordinate = getFreeList();
    while (compareBlockCoordinates(blockCoordinate, INVALID_HEADER_BLOCK_COORDINATE) != 0 && res == NULL) {
        checkForErr(getAllBlockByOffset(&header, blockCoordinate.offset));

        if (header->isFree && header->size >= size) {
            size_t realSize = size + BLOCK_HEADER_SIZE;
            uint64_t minAvailableToAllocateSize =
                    ((realSize + minAlignment - 1) / minAlignment) * minAlignment; //new block size with header
            if (header->size + BLOCK_HEADER_SIZE - minAvailableToAllocateSize > 0) {
                struct BlockHeader *nb = (struct BlockHeader *) ((char *) header + minAvailableToAllocateSize);
                nb->previousBlockOffset = header->offset;
                nb->isFree = true;
                nb->offset = header->offset + minAvailableToAllocateSize;
                nb->size = header->size - minAvailableToAllocateSize;
            }
            header->size = minAvailableToAllocateSize - BLOCK_HEADER_SIZE;

            removeFromCacheAndUnmap(header);
            checkForErr(getAllBlockByOffset(&header, blockCoordinate.offset))
            res = header;
            res->isFree = false;
            *bh = res;
        } else {
            struct FreeListNode *fln = getBlockData(header);
            blockCoordinate = fln->nextTableHeader;
            unmapPage(header);
        }
    }
    if (res == NULL) {
        checkForErr(allocatePageInEndOfFile(bh, size))
    }
    return SUCCESS;
}

static void deleteFreeListNode(struct FreeListNode *freeListNode) {
    struct BlockHeader *left = NULL;
    struct BlockHeader *right = NULL;
    getAllBlockByOffset(&left, freeListNode->prevTableHeader.offset);
    getAllBlockByOffset(&right, freeListNode->nextTableHeader.offset);
    struct BlockCoordinate leftCoord =
            left == NULL ? INVALID_HEADER_BLOCK_COORDINATE : (struct BlockCoordinate) {left->offset, left->size};
    struct BlockCoordinate rightCoord =
            right == NULL ? INVALID_HEADER_BLOCK_COORDINATE : (struct BlockCoordinate) {right->offset, right->size};

    if (left != NULL) {
        struct FreeListNode* l = getBlockData(left);
        l->nextTableHeader = rightCoord;
    }

    if (right != NULL) {
        struct FreeListNode* l = getBlockData(right);
        l->prevTableHeader = leftCoord;
    }

    if (left == NULL) {
        setFreeListHeader(rightCoord);
    }

}


static void addInFreeList(struct BlockHeader *block) {
    block->isFree = true;
    struct FreeListNode *freeListNode = getBlockData(block);

    struct BlockCoordinate coords = getFreeList();

    if (compareBlockCoordinates(coords, INVALID_HEADER_BLOCK_COORDINATE) == 0) {
        freeListNode->nextTableHeader = INVALID_HEADER_BLOCK_COORDINATE;
        freeListNode->prevTableHeader = INVALID_HEADER_BLOCK_COORDINATE;
    } else {
        struct BlockHeader *prev;
        getAllBlockByOffset(&prev, coords.offset);
        struct FreeListNode *prevListNode = getBlockData(prev);
        freeListNode->prevTableHeader = INVALID_HEADER_BLOCK_COORDINATE;
        freeListNode->nextTableHeader = (struct BlockCoordinate) {prev->offset, prev->size};
        prevListNode->prevTableHeader = (struct BlockCoordinate) {block->offset, block->size};

    }
    setFreeListHeader((struct BlockCoordinate) {block->offset, block->size});


}

static int32_t mergeWhilePossible(struct BlockHeader **newBlock, struct BlockHeader *block) {
    deleteFreeListNode(getBlockData(block));
    uint64_t offset = block->offset + block->size + BLOCK_HEADER_SIZE;
    struct BlockHeader *curHeader = NULL;
    int32_t err = getAllBlockByOffset(&curHeader, offset);
    uint64_t resSize = block->size;


    while (err == SUCCESS && curHeader != NULL && curHeader->isFree) {
        offset += curHeader->offset + curHeader->size + BLOCK_HEADER_SIZE;
        resSize += curHeader->size + BLOCK_HEADER_SIZE;
        deleteFreeListNode(getBlockData(curHeader));
        removeFromCacheAndUnmap(curHeader);
        err = getAllBlockByOffset(&curHeader, offset);
    }
    unmapPage(curHeader); //if is not null that there is no need to clear cache manually
    err = getAllBlockByOffset(&curHeader, block->previousBlockOffset);

    struct BlockHeader *prevHeader = block;
    while (err == SUCCESS && curHeader != NULL && curHeader->isFree && curHeader != prevHeader) {
        resSize += prevHeader->size + BLOCK_HEADER_SIZE;
        deleteFreeListNode(getBlockData(prevHeader));
        removeFromCacheAndUnmap(prevHeader);
        prevHeader = curHeader;
        err = getAllBlockByOffset(&curHeader, prevHeader->offset);
    }
    if (err == SUCCESS && curHeader != NULL && prevHeader != curHeader) {
        unmapPage(curHeader); //not free so mapped size in cache is correct
    }
    uint64_t resOffset = prevHeader->offset;
    removeFromCacheAndUnmap(prevHeader);
    checkForErr(getBlockByOffsetAndSize(&prevHeader, resOffset, resSize))
    prevHeader->size = resSize;
    *newBlock = prevHeader;
    addInFreeList(prevHeader);
    return SUCCESS;
}


int32_t freePage(struct BlockHeader *block) {
    addInFreeList(block);
    checkForErr(mergeWhilePossible(&block, block))
    checkForErr(unmapPage(block))
    return SUCCESS;
}

int32_t unmapPage(struct BlockHeader *block) {
    if (block != NULL) {

        struct MappedBlock *cachedValue = getDataByKeyAndReturnPointer(mappedCache, &block->offset);
        if (cachedValue != NULL) {
            cachedValue->refCount--;
            if (cachedValue->refCount == 0) {
                removeData(mappedCache, &block->offset, free);
                unmap(block, block->size + BLOCK_HEADER_SIZE);
            }

        }
    }
    return SUCCESS;
}

bool isValidPosition(uint64_t offset) {
    return offset % minAlignment == 0;
}
