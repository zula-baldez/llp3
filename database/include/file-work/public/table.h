//
// Created by moyak on 11.09.2023.
//

#ifndef LAB1_TABLE_PUBLIC_H
#define LAB1_TABLE_PUBLIC_H

#include "../../util/public/types.h"
#include "../public/block.h"
#include "../public/record.h"
#include "../../util/public/predicate.h"
#include "../../structures/public/table_structures.h"

struct __attribute__((__packed__)) JoinResult {
    struct TableHeader *tableHeader;//to be able to remove it after using
    struct RecordData *recordData; //to be able to read data
};

int32_t addRow(struct TableHeader *tableHeader, struct RecordData *recordData, void **pVoid);

int32_t readRecord(struct RecordData *recordData, struct TableHeader *tableHeader);

int32_t deleteRow(struct TableHeader *tableHeader, int32_t conditionCount, struct Condition *conditions);

int32_t
updateRow(struct TableHeader *tableHeader, int32_t updateColumnsCount, struct UpdateColumnValue *updateColumnValues,
          int32_t conditionCount, struct Condition *conditions);

int32_t selectWithConditions(struct RecordData *recordData, struct TableHeader *tableHeader, int32_t conditionCount,
                             struct Condition *conditions);

int32_t joinTables(struct JoinResult *joinResult, int32_t selectColumnsNum, struct TableAliasAndColumn *selectColumns,
                   int32_t joinTablesNum, struct JoinTablesHeaders *joinTables,
                   int32_t joinConditionNum, struct JoinCondition *joinCondition,
                   int32_t filtersNum, struct JoinWhereCondition *joinWhereCondition);


//allocates joined table in memory
#endif //LAB1_TABLE_PUBLIC_H
