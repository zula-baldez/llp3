//
// Created by moyak on 14.09.2023.
//

#ifndef LAB1_MEMORY_HASHMAP_H
#define LAB1_MEMORY_HASHMAP_H

#include "abstract_hashmap.h"
#include <memory.h>
#include <stdlib.h>
#include "../../util/public/types.h"
#include "../../structures/public/table_structures.h"

typedef void (*DataEraser)(void*data);

void *getDataByKeyAndReturnPointer(struct HashMap *map, void *key);

void addDataInMap(struct HashMap *map,  void *key, void *data);

void removeData(struct HashMap *map,const void *key, DataEraser dataEraser);

struct HashMap *initFreeMapAndReturnPointer(int32_t columnCount, enum KeyType keyType);

void freeMapWithFreeErasing(void *hmap);

void clearMap(struct HashMap *map, DataEraser dataEraser);

void freeMap(struct HashMap *map, DataEraser dataEraser);



#endif //LAB1_MEMORY_HASHMAP_H
