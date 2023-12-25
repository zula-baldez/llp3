
#include "../../include/hashmap/private/table_hashmap.h"


static int32_t rehashTable(struct BlockHeader **bh, struct BlockHeader *mapBlock) {
    struct HashMap *map = getBlockData(mapBlock);

    struct BlockHeader *newMapBlock;
    checkForErr(createBiggerMap(&newMapBlock, map))
    struct BlockCoordinate *mapData = getData(map);
    for (uint32_t i = 0; i < map->capacity; i++) {
        struct BlockCoordinate blockCoordinate = mapData[i];
        while (isValidPosition(blockCoordinate.offset)) {
            struct BlockHeader *block;

            checkForErr(getBlockByOffsetAndSize(&block, blockCoordinate.offset, blockCoordinate.size))
            struct FileNode *tableNode = getBlockData(block);
            blockCoordinate = tableNode->nextTableHeader;
            addTableInMap(newMapBlock, block);
            unmapPage(block);
        }
    }
    getDatabaseHeader()->tableMapPage = (struct BlockCoordinate) {newMapBlock->offset, newMapBlock->size};
    *bh = newMapBlock;
    return SUCCESS;
}

int32_t removeTableFromMap(struct BlockHeader *mapBlock, struct BlockHeader *tableBlock) {
    struct HashMap *map = getBlockData(mapBlock);
    struct FileNode *fileNode = getBlockData(tableBlock);
    uint32_t index = elementIndex(map, fileNode->name);
    struct BlockCoordinate *blockCoordinates = getData(map);

    struct BlockHeader *next = NULL;
    getAllBlockByOffset(&next, fileNode->nextTableHeader.offset);
    struct BlockHeader *prev = NULL;
    getAllBlockByOffset(&prev, fileNode->prevTableHeader.offset);

    struct BlockCoordinate nextCoords =
            next == NULL ? INVALID_HEADER_BLOCK_COORDINATE : (struct BlockCoordinate) {next->offset, next->size};
    struct BlockCoordinate prevCoords =
            prev == NULL ? INVALID_HEADER_BLOCK_COORDINATE : (struct BlockCoordinate) {prev->offset, prev->size};

    if (next != NULL) {
        struct FileNode *node = getBlockData(next);
        node->prevTableHeader = prevCoords;
    }
    if (prev != NULL) {
        struct FileNode *node = getBlockData(prev);
        node->nextTableHeader = nextCoords;
    }
    if (prev == NULL) {
        blockCoordinates[index] = prevCoords;
    }
    unmapPage(next);
    unmapPage(prev);
    return SUCCESS;
}

int32_t addTableInMap(struct BlockHeader *mapBlock, struct BlockHeader *tableBlock) {
    struct HashMap *map = getBlockData(mapBlock);
    struct FileNode *fileNode = getBlockData(tableBlock);
    float loadFactor = (map->countElementStored + 1) / map->capacity;
    if (loadFactor >= defaultLoadFactor) {
        checkForErr(rehashTable(&mapBlock, mapBlock))
        map = getBlockData(mapBlock);
    }
    map->countElementStored++;
    uint32_t index = elementIndex(map, fileNode->name);
    struct BlockCoordinate *blockCoordinates = getData(map);
    struct BlockCoordinate firstTableCoordinates = blockCoordinates[index];
    struct BlockCoordinate curBlockCoords = (struct BlockCoordinate) {tableBlock->offset, tableBlock->size};
    fileNode->prevTableHeader = INVALID_HEADER_BLOCK_COORDINATE;
    fileNode->nextTableHeader = INVALID_HEADER_BLOCK_COORDINATE;

    if (isValidPosition(firstTableCoordinates.offset)) {
        struct BlockHeader *prevBlock;

        checkForErr(getAllBlockByOffset(&prevBlock, firstTableCoordinates.offset));
        struct FileNode *prevFileNode = getBlockData(prevBlock);
        fileNode->nextTableHeader = firstTableCoordinates;
        prevFileNode->prevTableHeader = curBlockCoords;
        unmapPage(prevBlock);
    }
    blockCoordinates[index] = curBlockCoords;
    return SUCCESS;
}

static void configHashMap(struct BlockHeader *mapBlock, enum KeyType keyType) {
    uint64_t capacity = (mapBlock->size - sizeof(struct HashMap)) / sizeof(struct BlockCoordinate);
    struct HashMap *map = getBlockData(mapBlock);
    map->capacity = capacity;
    map->countElementStored = 0;
    map->keyType = keyType;
    struct BlockCoordinate *blockCoordinates = getData(map);
    for (uint32_t i = 0; i < capacity; i++) {
        blockCoordinates[i] = INVALID_HEADER_BLOCK_COORDINATE;
    }

}


int32_t initFreeFileMapAndReturnBlock(struct BlockHeader **bh, enum KeyType keyType) {
    struct BlockHeader *mapBlock;
    checkForErr(allocatePageInFile(&mapBlock, sizeof(struct BlockHeader)))
    configHashMap(mapBlock, keyType);
    *bh = mapBlock;
    return SUCCESS;
}

int32_t createBiggerMap(struct BlockHeader **bh, struct HashMap *map) {
    struct BlockHeader *mapBlock;

    checkForErr(allocatePageInFile(&mapBlock, sizeof(struct BlockCoordinate) * map->capacity * 2))
    configHashMap(mapBlock, map->keyType);
    *bh = mapBlock;
    return SUCCESS;

}
int32_t getTableByNameAndReturnBlock(struct BlockHeader **bh, struct HashMap *map, const void *key) {
    uint32_t index = elementIndex(map, key);
    struct BlockCoordinate *blockCoordinates = getData(map);
    struct BlockCoordinate blockCoordinate = blockCoordinates[index];

    if (compareBlockCoordinates(blockCoordinate, INVALID_HEADER_BLOCK_COORDINATE) == 0) {
        return NO_SUCH_TABLE;
    }

    struct BlockHeader *header;
    checkForErr(getBlockByOffsetAndSize(&header, blockCoordinate.offset, blockCoordinate.size))
    struct FileNode *fileNode = getBlockData(header);
    struct BlockHeader *res = NULL;
    while (fileNode != NULL && compareBlockCoordinates(blockCoordinate, INVALID_HEADER_BLOCK_COORDINATE) != 0 &&
           strcmp(key, fileNode->name) != 0) {

        blockCoordinate = fileNode->nextTableHeader;
        unmapPage(header);
        checkForErr(getBlockByOffsetAndSize(&header, blockCoordinate.offset, blockCoordinate.size))
        fileNode = getBlockData(header);
    }
    if (fileNode != NULL && compareBlockCoordinates(blockCoordinate, INVALID_HEADER_BLOCK_COORDINATE) != 0) {
        res = header;
    }
    *bh = res;
    return SUCCESS;
}
