//
// Created by moyak on 14.09.2023.
//

#ifndef LAB1_ABSTRACT_HASHMAP_H
#define LAB1_ABSTRACT_HASHMAP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/public/types.h"

static const float defaultLoadFactor = 0.75f;
enum KeyType {
    KEY_STRING,
    KEY_UINT64_T
};
struct __attribute__((__packed__)) HashMap {
    enum KeyType keyType;
    uint32_t capacity;
    uint32_t countElementStored;

};


//structures to store columns in linked list in file



struct __attribute__((__packed__)) ColumnData {
    enum DataType dataType;
    uint32_t columnNum;
    void *data;
};
//in memory
struct __attribute__((__packed__)) ColumnNode {
    struct ColumnNode *nextNode;
    struct ColumnNode *prevNode;
    void *key;
    void *data;
};

uint32_t elementIndex(struct HashMap *map, const void *key);

bool keysEquals(struct HashMap *map, const void *key1, const void *key2);

void *getData(struct HashMap *map);

#endif //LAB1_ABSTRACT_HASHMAP_H

