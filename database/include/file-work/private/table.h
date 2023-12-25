//
// Created by moyak on 11.09.2023.
//

#ifndef LAB1_TABLE_PRIVATE_H
#define LAB1_TABLE_PRIVATE_H

#include "../public/table.h"
#include "../../file-work/private/allocator.h"
#include "../../hashmap/private/memory_hashmap.h"
#include "../../file-work/private/block.h"
#include "../../util/private/types.h"
#include "../../util/private/predicate.h"
#include "../../structures/private/table_structures.h"
#include "../../util/private/converter.h"

int32_t allocTable(struct BlockHeader **bh, const char *name, int32_t columnNum, const enum DataType *types,
                   const char **names);


#endif //LAB1_TABLE_PRIVATE_H
