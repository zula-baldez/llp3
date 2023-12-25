//
// Created by moyak on 15.09.2023.
//

#ifndef LAB1_STRUCTURES_PUBLIC_H
#define LAB1_STRUCTURES_PUBLIC_H

#include "../../file-work/public/block.h"
#include "../../util/public/types.h"

struct __attribute__((__packed__)) Column {
    enum DataType dataType;
    char name[];
};

struct TableHeader;

#endif //LAB1_STRUCTURES_PUBLIC_H


