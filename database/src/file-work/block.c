//
// Created by moyak on 11.09.2023.
//
#include "../../include/file-work/private/block.h"

int32_t compareBlockCoordinates(struct BlockCoordinate p1, struct BlockCoordinate p2) {
    return (p1.size == p2.size && p1.offset == p2.offset) ? 0 : 1;
}


