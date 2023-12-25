//
// Created by moyak on 14.09.2023.
//
#include <stdio.h>
#include "../../include/hashmap/private/memory_hashmap.h"


static struct ColumnNode *findNodeInMap(struct HashMap *map,const void *key) {
    struct ColumnNode **mapData = getData(map);
    uint32_t index = elementIndex(map, key);
    struct ColumnNode *res = NULL;
    struct ColumnNode *firstNode = mapData[index];
    struct ColumnNode *curNode = firstNode;
    while (curNode != NULL) {
        if (keysEquals(map, key, curNode->key)) {
            res = curNode;
        }
        curNode = curNode->nextNode;
    }
    return res;
}

void removeData(struct HashMap *map,const void *key, DataEraser dataEraser) {
    struct ColumnNode *columnNode = findNodeInMap(map, key);
    if (columnNode != NULL) {
        if(columnNode->prevNode != NULL) {
            columnNode->prevNode->nextNode = columnNode->nextNode;
        }
        if(columnNode->nextNode != NULL) {
            columnNode->nextNode->prevNode = columnNode->prevNode;
        }
        if(columnNode->prevNode == NULL) {
            uint32_t index = elementIndex(map, key);
            struct ColumnNode **mapData = getData(map);
            mapData[index] = columnNode->nextNode;
        }
    }
    if(dataEraser != NULL) {
        dataEraser(columnNode->data);
    }
    free(columnNode);
    map->countElementStored--;
}

static struct HashMap *rehashMemoryTable(struct HashMap *map) {
    return map;

}
static struct ColumnNode *allocColumnNode(void) {
    return calloc(1, sizeof(struct ColumnNode));
}

//init space that 2 times bigger that column count
static struct HashMap *mallocMap(int32_t columnCount, enum KeyType keyType) {
    struct HashMap *map = malloc(sizeof(struct HashMap) + sizeof(struct ColumnNode *) * columnCount * 2);
    struct ColumnNode** nodes = getData(map);
    map->capacity = columnCount * 2;
    for(uint32_t i = 0 ; i < map->capacity; i++) {
        nodes[i] = NULL;
    }
    map->countElementStored = 0;
    map->keyType = keyType;
    return map;
}

void addDataInMap(struct HashMap *map, void *key, void *data) {
    float loadFactor = (map->countElementStored + 1) / map->capacity;
    if (loadFactor >= defaultLoadFactor) {
        map = rehashMemoryTable(map);
    }
    map->countElementStored++;
    struct ColumnNode **mapData = getData(map);
    uint32_t index = elementIndex(map, key);
    struct ColumnNode *firstNode = mapData[index];
    struct ColumnNode *columnNode = findNodeInMap(map, key);
    if (columnNode != NULL) {
        columnNode->data = data;
        return;
    }

    columnNode = allocColumnNode();

    *columnNode = (struct ColumnNode) {NULL, NULL,key, data};

    if (firstNode != NULL) {
        columnNode->nextNode = firstNode;
        firstNode->prevNode = columnNode;
    }
    mapData[index] = columnNode;

}

struct HashMap *initFreeMapAndReturnPointer(int32_t columnCount, enum KeyType keyType) {
    return mallocMap(columnCount, keyType);
}

void *getDataByKeyAndReturnPointer(struct HashMap *map, void *key) {
    uint32_t index = elementIndex(map, key);
    struct ColumnNode **mapData = getData(map);
    struct ColumnNode *node = mapData[index];
    void *data = NULL;

    while (node != NULL && !keysEquals(map, key, node->key)) {
        node = node->nextNode;
    }
    if (node != 0) {
        data = (void *) node->data;
    }
    return data;
}

void freeMapWithFreeErasing(void *hmap) {
    struct HashMap* map = (struct HashMap*) hmap;
    struct ColumnNode **mapData = getData(map);
    for (uint32_t i = 0; i < map->capacity; i++) {
        struct ColumnNode *node = mapData[i];
        while (node != NULL) {
            struct ColumnNode *nextNode = node->nextNode;
            free(node->data);
            free(node);
            node = nextNode;
        }
        mapData[i] = NULL;
    }
    free(map);
}



void clearMap(struct HashMap *map, DataEraser dataEraser) {
    struct ColumnNode **mapData = getData(map);
    for (uint32_t i = 0; i < map->capacity; i++) {
        struct ColumnNode *node = mapData[i];
        while (node != NULL) {
            struct ColumnNode *nextNode = node->nextNode;
            if(dataEraser != NULL) {
                dataEraser(node->data);
            }
            free(node);
            node = nextNode;
        }
        mapData[i] = NULL;
    }
    map->countElementStored = 0;

}


void freeMap(struct HashMap *map, DataEraser dataEraser) {
    clearMap(map, dataEraser);
    free(map);
}

