//
// Created by moyak on 09.09.2023.
//

#ifndef LAB1_DATABASE_PRIVATE_H
#define LAB1_DATABASE_PRIVATE_H

#include <stdint.h>
#include "../public/database.h"
#include "../../file-work/public/block.h"
#include "../../util/private/types.h"
#include "../../hashmap/private/table_hashmap.h"
#include "../../file-work/private/allocator.h"
#include "../../file-work/private/table.h"
#include "../../file-work/private/block.h"
#include "../../util/private/predicate.h"
#include "../../util/private/converter.h"


struct __attribute__((__packed__)) DatabaseHeader {
    uint64_t size;
    struct BlockCoordinate tableMapPage;
    struct BlockCoordinate freeList;
};

struct BlockCoordinate getFreeList(void);
void setFreeListHeader(struct BlockCoordinate bc);

struct DatabaseHeader *getDatabaseHeader(void);


#endif //LAB1_DATABASE_PRIVATE_H

