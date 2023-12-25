//
// Created by moyak on 14.09.2023.
//

#ifndef LAB1_RECORD_PUBLIC_H
#define LAB1_RECORD_PUBLIC_H

#include <stdlib.h>
#include "block.h"
#include "../../structures/public/table_structures.h"

struct __attribute__((__packed__)) RecordData {
    int32_t columnNum;
    struct BlockHeader *rowPageBlock;
    char *unreadData;
    struct Column **columns;
    void **data;
};


struct RecordData *prepareRecordDataStructure(struct TableHeader *tableHeader);

void freeRecordData(struct RecordData *recordData);

void clearRecordDataToReadFromBegin(struct RecordData *recordData);

#endif //LAB1_RECORD_PUBLIC_H
