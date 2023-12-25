//
// Created by moyak on 19.09.2023.
//

#ifndef LAB1_BLOCK_PRIVATE_H
#define LAB1_BLOCK_PRIVATE_H
#include "../public/table.h"
#include "../../status/private/status_codes.h"

struct __attribute__((__packed__)) BlockCoordinate {
    uint64_t offset;
    uint64_t size;
};

struct __attribute__((__packed__)) BlockHeader {
    uint64_t offset;
    uint64_t size;
    uint64_t previousBlockOffset;
    bool isFree;
};


#define BLOCK_HEADER_SIZE (uint64_t) sizeof(struct BlockHeader)
#define INVALID_HEADER_BLOCK_COORDINATE (struct BlockCoordinate){1,1}


int32_t compareBlockCoordinates(struct BlockCoordinate p1, struct BlockCoordinate p2);

#endif //LAB1_BLOCK_PRIVATE_H
