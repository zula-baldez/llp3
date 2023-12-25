//
// Created by moyak on 11.09.2023.
//

#ifndef LAB1_TABLE_HASHMAP_H
#define LAB1_TABLE_HASHMAP_H

#include "../../file-work/public/block.h"
#include "../../structures/public/table_structures.h"
#include "abstract_hashmap.h"
#include "../../file-work/private/allocator.h"
#include "../../file-work/private/block.h"
#include "../../aggregator/private/database.h"

int32_t addTableInMap(struct BlockHeader *mapBlock, struct BlockHeader *tableBlock);

int32_t initFreeFileMapAndReturnBlock(struct BlockHeader **bh, enum KeyType keyType);

int32_t createBiggerMap(struct BlockHeader **bh, struct HashMap *map);

int32_t getTableByNameAndReturnBlock(struct BlockHeader **bh, struct HashMap *map, const void *key);

int32_t removeTableFromMap(struct BlockHeader *mapBlock, struct BlockHeader *tableBlock);


#endif //LAB1_TABLE_HASHMAP_H


