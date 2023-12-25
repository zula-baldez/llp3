#include "../../include/file-work/private/table.h"


static struct Column *getNextColumn(struct Column *column) {
    return (struct Column *) column->name + strlen(column->name);
}

static struct Column *getFirstColumn(struct TableHeader *tableHeader) {
    return (struct Column *) tableHeader + sizeof(struct TableHeader);
}

static struct Column **getAllColumns(struct TableHeader *tableHeader) {
    struct Column **cols = calloc(tableHeader->columnCount, sizeof(struct Column *));
    struct Column *col = getFirstColumn(tableHeader);
    for (int32_t i = 0; i < tableHeader->columnCount; i++) {
        cols[i] = col;
        col = getNextColumn(col);
    }
    return cols;
}

static struct RowPointer *getRowPointers(struct RowPage *rowPage) {
    return (struct RowPointer *) ((char *) rowPage + sizeof(struct RowPage));
}

static void *getRowData(struct RowPage *rowPage) {
    return ((char *) rowPage + rowPage->freeSpaceOffsetEnd);

}

static uint64_t getRowTakenPlace(struct RowPage *rowPage, struct BlockHeader *rowPageBlock) {
    return rowPage->freeSpaceOffsetStart + rowPageBlock->size - rowPage->freeSpaceOffsetEnd;
}

static int32_t allocateRowPage(struct BlockHeader **bh, struct TableHeader *tableHeader, uint64_t size) {
    checkForErr(allocatePageInFile(bh, size + sizeof(struct RowPage)))
    struct BlockHeader *block = *bh;
    struct RowPage *rowPage = getBlockData(block);
    rowPage->freeSpaceOffsetStart = sizeof(struct RowPage);
    rowPage->freeSpaceOffsetEnd = block->size;
    rowPage->rowCount = 0;
    rowPage->nextRowPage = INVALID_HEADER_BLOCK_COORDINATE;
    rowPage->prevRowPage = INVALID_HEADER_BLOCK_COORDINATE;

    struct BlockCoordinate curCoordinates = (struct BlockCoordinate) {block->offset, block->size};
    if (compareBlockCoordinates(tableHeader->firstRowPage, INVALID_HEADER_BLOCK_COORDINATE) != 0) {
        struct BlockHeader *firstRowPageBlock;
        int32_t err = getBlockByOffsetAndSize(&firstRowPageBlock, tableHeader->firstRowPage.offset,
                                              tableHeader->firstRowPage.size);
        if (err != SUCCESS) {
            unmapPage(*bh);
            return err;
        }
        struct RowPage *firstRowPage = getBlockData(firstRowPageBlock);
        firstRowPage->prevRowPage = curCoordinates;
        rowPage->nextRowPage = (struct BlockCoordinate) {firstRowPageBlock->offset, firstRowPageBlock->size};
        unmapPage(firstRowPageBlock);
    }
    tableHeader->firstRowPage = curCoordinates;
    return SUCCESS;
}

static int32_t removeRowPage(struct TableHeader *tableHeader, struct BlockHeader *rowPageBlock) {
    struct RowPage *rowPageToDelete = getBlockData(rowPageBlock);
    struct BlockHeader *prevBlock = NULL;
    struct BlockHeader *nextBlock = NULL;
    getBlockByOffsetAndSize(&prevBlock, rowPageToDelete->prevRowPage.offset,
                            rowPageToDelete->prevRowPage.size);
    getBlockByOffsetAndSize(&nextBlock, rowPageToDelete->nextRowPage.offset,
                            rowPageToDelete->nextRowPage.size);

    if (prevBlock == NULL) {
        tableHeader->firstRowPage = rowPageToDelete->nextRowPage;
    }
    if (prevBlock != NULL) {
        struct RowPage *rp = getBlockData(prevBlock);
        rp->nextRowPage = rowPageToDelete->nextRowPage;
    }
    if (nextBlock != NULL) {
        struct RowPage *np = getBlockData(nextBlock);
        np->prevRowPage = rowPageToDelete->prevRowPage;
    }
    unmapPage(prevBlock);
    unmapPage(nextBlock);
    freePage(rowPageBlock);
    return SUCCESS;

}

static size_t copyDataToBlockEnd(enum DataType type, void *freeSpaceEnd, void *data) {
    size_t dataCopiedLen = dataTypeLen(type, data);
    memcpy((char *) freeSpaceEnd - dataCopiedLen, data, dataCopiedLen);
    return dataCopiedLen;
}

static int32_t getFirstRowPageBlock(struct BlockHeader **bh, struct TableHeader *tableHeader) {
    struct BlockCoordinate firstRowCoords = tableHeader->firstRowPage;
    if (compareBlockCoordinates(tableHeader->firstRowPage, INVALID_HEADER_BLOCK_COORDINATE) != 0) {
        return getBlockByOffsetAndSize(bh, firstRowCoords.offset, firstRowCoords.size);
    }
    return SUCCESS;
}

static int32_t getNextPage(struct BlockHeader **nPage, struct BlockHeader *rowPageBlock) {
    struct RowPage *rowPage = getBlockData(rowPageBlock);
    int32_t err = SUCCESS;
    if (compareBlockCoordinates(rowPage->nextRowPage, INVALID_HEADER_BLOCK_COORDINATE) != 0) {
        err = getBlockByOffsetAndSize(nPage, rowPage->nextRowPage.offset, rowPage->nextRowPage.size);
    } else {
        *nPage = NULL;
    }
    unmapPage(rowPageBlock);
    return err;
}


static size_t getRowLen(int32_t columnNum, struct Column **columns, struct RecordData *recordData) {
    size_t len = 0;
    for (int32_t i = 0; i < columnNum; i++) {
        len += dataTypeLen(columns[i]->dataType, recordData->data[i]);
    }
    return len;
}

static void copyRowPage(struct BlockHeader *fromBlock, struct BlockHeader *toBlock) {
    struct RowPage *from = getBlockData(fromBlock);
    struct RowPage *to = getBlockData(toBlock);

    to->rowCount = from->rowCount;
    memcpy(getRowPointers(to), getRowPointers(from), sizeof(struct RowPointer) * from->rowCount);
    size_t dataLen = fromBlock->size - from->freeSpaceOffsetEnd;
    void *destAddress = (char *) to + toBlock->size - dataLen;
    void* srcAddr = (char *) from  + from->freeSpaceOffsetEnd;
    memcpy(destAddress, srcAddr, dataLen);

}

static int32_t
getPageWithEnoughSpace(struct BlockHeader **bh, struct TableHeader *tableHeader, struct RecordData *recordData,
                       struct Column **columns) {

    struct BlockHeader *rowPageBlock = NULL;
    getFirstRowPageBlock(&rowPageBlock, tableHeader);
    size_t spaceNeeded = getRowLen(tableHeader->columnCount, columns, recordData) + sizeof(struct RowPointer);
    struct RowPage *rowPage = getBlockData(rowPageBlock); //invalid if rowPageBlock is null
    int32_t err;
    if (rowPageBlock == NULL) {
        err = allocateRowPage(bh, tableHeader, spaceNeeded);
        unmapPage(rowPageBlock);
        return err;
    }

    if (rowPage->freeSpaceOffsetEnd - rowPage->freeSpaceOffsetStart >= spaceNeeded) {
        *bh = rowPageBlock;
        return SUCCESS;
    }

    uint64_t takenPlace = getRowTakenPlace(rowPage, rowPageBlock);
    if (takenPlace * 2 > rowPageBlock->size) { //if taken more than 50%
        err = allocateRowPage(bh, tableHeader, spaceNeeded);
        unmapPage(rowPageBlock);
    } else {
        err = allocateRowPage(bh, tableHeader, spaceNeeded + takenPlace);
        if (err == SUCCESS) {
            copyRowPage(rowPageBlock, *bh);
            removeRowPage(tableHeader, rowPageBlock);
        }
    }
    return err;
}


static void removeRowPageIfItIsTooEmpty(struct TableHeader *tableHeader, struct BlockHeader *rowPageBlock) {
    if (rowPageBlock == NULL) {
        return;
    }
    struct RowPage *rowPage = getBlockData(rowPageBlock);
    uint64_t takenPlace = getRowTakenPlace(rowPage, rowPageBlock);
    if (takenPlace * 2 < rowPageBlock->size) {
        struct RecordData *recordData = prepareRecordDataStructure(tableHeader);
        recordData->rowPageBlock = rowPageBlock;
        int32_t read = readRecord(recordData, tableHeader);

        while (recordData->rowPageBlock == rowPageBlock && read == 0) {
            addRow(tableHeader, recordData, NULL);
            read = readRecord(recordData, tableHeader);
        }
        removeRowPage(tableHeader, rowPageBlock);
        freeRecordData(recordData);
    }

}

//����� rowPageBlock ���������� �
int32_t addRow(struct TableHeader *tableHeader, struct RecordData *recordData, void **pVoid) {
    if (tableHeader == NULL || recordData == NULL) {
        return NPE;
    }

    struct Column **columns = getAllColumns(tableHeader);
    struct BlockHeader *rowPageBlock;
    int32_t err = getPageWithEnoughSpace(&rowPageBlock, tableHeader, recordData, columns);
    if (err != SUCCESS) {
        free(columns);
        return err;
    }

    struct RowPage *rowPage = getBlockData(rowPageBlock);
    recordData->rowPageBlock = rowPageBlock;
    for (int32_t i = tableHeader->columnCount - 1; i >= 0; i--) {
        size_t dataCopiedLen = copyDataToBlockEnd(columns[i]->dataType,
                                                  ((char *) rowPage) + rowPage->freeSpaceOffsetEnd,
                                                  recordData->data[i]);
        rowPage->freeSpaceOffsetEnd -= dataCopiedLen;
    }
    rowPage->rowCount++;
    tableHeader->rowCount++;
    struct RowPointer *rowPointer = (struct RowPointer *) ((char *) rowPage + rowPage->freeSpaceOffsetStart);
    rowPointer->offset = rowPage->freeSpaceOffsetEnd;
    rowPointer->isToDelete = false;
    rowPage->freeSpaceOffsetStart += sizeof(struct RowPointer);
    free(columns);
    return SUCCESS;
}

//1 -> name not found
static int32_t getOperandDataByName(struct ColumnData *columnData, struct HashMap *map, char *name) {
    struct ColumnData *res = (struct ColumnData *) getDataByKeyAndReturnPointer(map, name);
    if (res == NULL) {
        return NO_SUCH_OPERAND_NAME;
    } else {
        *columnData = *res;
        return SUCCESS;
    }
}

static int32_t getOperandDataByValue(struct ColumnData *columnData, enum DataType dataType, void *value) {
    columnData->dataType = dataType;
    columnData->data = value;
    columnData->columnNum = -1;
    return SUCCESS;
}

static int32_t getOperandData(struct ColumnData *columnData, struct HashMap *map, struct Operand *operand) {
    if (operand->isOperandAName) {
        return getOperandDataByName(columnData, map, operand->operandValue.columnName);
    } else {
        return getOperandDataByValue(columnData, operand->operandValue.freeVariable->dataType,
                                     operand->operandValue.freeVariable->operand);
    }
}


static bool compareColumnDatas(struct ColumnData leftOperand, struct ColumnData rightOperand, enum Operator operator) {
    struct CompareResult compareRes = compareColumns(leftOperand, rightOperand);
    bool compareResult = false;
    if (compareRes.errorCode == 0) {
        compareResult = validateCompareResult(operator, compareRes.compareResult);
    } else {
        return false;
    }
    return compareResult;

}

static int32_t
checkIfRecordSatisfiesConditions(bool *res, struct HashMap *map, int32_t conditionCount, struct Condition *conditions) {
    bool valid = true;
    for (int32_t i = 0; i < conditionCount; i++) {
        struct ColumnData leftOperand;
        struct ColumnData rightOperand;
        int32_t err1 = getOperandData(&leftOperand, map, &conditions[i].left);
        if (err1 != 0) {
            return err1;
        }
        int32_t err2 = getOperandData(&rightOperand, map, &conditions[i].right);
        if (err2 != 0) {
            return err1;
        }
        valid = valid & compareColumnDatas(leftOperand, rightOperand, conditions[i].op);
    }
    *res = valid;
    return SUCCESS;
}


static void
mapFieldNamesToDataPointers(struct HashMap *map, struct TableHeader *tableHeader, struct RecordData *recordData) {
    clearMap(map, free);
    for (int32_t i = 0; i < tableHeader->columnCount; i++) {
        struct ColumnData *columnData = malloc(sizeof(struct ColumnData));
        columnData->dataType = recordData->columns[i]->dataType;
        columnData->columnNum = i;
        columnData->data = recordData->data[i];
        addDataInMap(map, recordData->columns[i]->name, columnData);
    }
}

int32_t selectWithConditions(struct RecordData *recordData, struct TableHeader *tableHeader, int32_t conditionCount,
                             struct Condition *conditions) {
    bool found = false;
    if (recordData == NULL || tableHeader == NULL) {
        return NPE;
    }
    struct HashMap *map = initFreeMapAndReturnPointer(tableHeader->columnCount, KEY_STRING);
    while (!found && readRecord(recordData, tableHeader) == 0) {
        mapFieldNamesToDataPointers(map, tableHeader, recordData);
        checkIfRecordSatisfiesConditions(&found, map, conditionCount, conditions);
        clearMap(map, free);
    }
    freeMap(map, free);
    if (found) return SUCCESS;
    return ALL_DATA_READ;
}

static int32_t deleteMarkedRows(struct TableHeader *tableHeader) {
    int32_t allDeletedRowsNum = 0;

    struct BlockHeader *rowPageBlock;
    checkForErr(getFirstRowPageBlock(&rowPageBlock, tableHeader))
    struct RowPage *rowPage = getBlockData(rowPageBlock);
    while (rowPageBlock != NULL) {
        int32_t curRow = 0;
        uint64_t freeSpaceLen = 0;
        int32_t deletedCount = 0;

        struct RowPointer *rowPointers = getRowPointers(rowPage);
        for (int32_t i = 0; i < rowPage->rowCount; i++) {
            uint64_t rowLen = (i == 0) ? rowPageBlock->size - rowPointers[i].offset : rowPointers[i - 1].offset -
                                                                                      rowPointers[i].offset;
            if (rowPointers[i].isToDelete) {
                deletedCount++;
                freeSpaceLen += rowLen;
            } else {
                memmove((void *) ((char *) rowPage + rowPointers[i].offset + freeSpaceLen),
                        (void *) ((char *) rowPage + rowPointers[i].offset),
                        rowLen);
                rowPointers[curRow].offset = rowPointers[i].offset + freeSpaceLen;
                rowPointers[curRow].isToDelete = false;
                curRow++;

            }
        }
        rowPage->freeSpaceOffsetEnd += freeSpaceLen;

        rowPage->freeSpaceOffsetStart -= deletedCount * sizeof(struct RowPointer);
        rowPage->rowCount -= deletedCount;

        checkForErr(getNextPage(&rowPageBlock, rowPageBlock))
        rowPage = getBlockData(rowPageBlock);
        allDeletedRowsNum += deletedCount;
        removeRowPageIfItIsTooEmpty(tableHeader, rowPageBlock);
    }
    tableHeader->rowCount -= allDeletedRowsNum;

    return allDeletedRowsNum;
}

int32_t deleteRow(struct TableHeader *tableHeader, int32_t conditionCount, struct Condition *conditions) {
    if (tableHeader == NULL) {
        return NPE;
    }
    struct RecordData *recordData = prepareRecordDataStructure(tableHeader);

    int32_t readResult = readRecord(recordData, tableHeader);
    if (readResult != 0) {
        return SUCCESS;
    }
    struct BlockHeader *rowPageBlock = recordData->rowPageBlock;
    struct RowPage *rowPage = getBlockData(rowPageBlock);
    struct RowPointer *rowPointers = (struct RowPointer *) ((char *) rowPage + sizeof(struct RowPage));
    int32_t columnNum = rowPage->rowCount - 1;
    //mark row pointers to delete
    do {
        if (columnNum < 0) {
            rowPageBlock = recordData->rowPageBlock;
            rowPage = getBlockData(rowPageBlock);
            rowPointers = (struct RowPointer *) ((char *) rowPage + sizeof(struct RowPage));
            columnNum = rowPage->rowCount - 1; //new page moment)))
        }
        struct HashMap *map = initFreeMapAndReturnPointer(tableHeader->columnCount, KEY_STRING);
        mapFieldNamesToDataPointers(map, tableHeader, recordData);
        bool satisfies;
        int32_t err = checkIfRecordSatisfiesConditions(&satisfies, map, conditionCount, conditions);
        if (err != 0) {
            freeRecordData(recordData);
            return err;
        }
        if (satisfies) {
            rowPointers[columnNum].isToDelete = true;
        }
        columnNum--;
        freeMap(map, free);
    } while (readRecord(recordData, tableHeader) == 0);
    int32_t deletedCount = deleteMarkedRows(tableHeader);
    freeRecordData(recordData);
    return deletedCount;

}


int32_t readRecord(struct RecordData *recordData, struct TableHeader *tableHeader) {

    recordData->columns = recordData->columns == NULL ? getAllColumns(tableHeader) : recordData->columns;
    if (recordData->rowPageBlock == NULL) {
        struct BlockHeader *rpb = recordData->rowPageBlock;
        checkForErr(getFirstRowPageBlock(&rpb, tableHeader))
        recordData->rowPageBlock = rpb;
    }
    struct RowPage *rowPage = getBlockData(recordData->rowPageBlock);
    recordData->unreadData =
            recordData->unreadData == NULL ? (char *) rowPage + rowPage->freeSpaceOffsetEnd : recordData->unreadData;

    while (recordData->rowPageBlock != NULL &&
           recordData->unreadData >= (char *) rowPage + recordData->rowPageBlock->size) {
        struct BlockHeader *rpb = recordData->rowPageBlock;
        checkForErr(getNextPage(&rpb, recordData->rowPageBlock))
        recordData->rowPageBlock = rpb;
        if (recordData->rowPageBlock != NULL) {
            rowPage = getBlockData(recordData->rowPageBlock);
            recordData->unreadData = (char *) rowPage + rowPage->freeSpaceOffsetEnd;
        }
    }
    if (recordData->rowPageBlock == NULL) {
        return ALL_DATA_READ;
    }
    for (int32_t i = 0; i < tableHeader->columnCount; i++) {
        recordData->data[i] = recordData->unreadData;
        recordData->unreadData += dataTypeLen(recordData->columns[i]->dataType, recordData->unreadData);
    }
    return SUCCESS;
}

//����� �������, ���� ��������, �������� ������ ������� �� ����� ������
int32_t
updateRow(struct TableHeader *tableHeader, int32_t updateColumnsCount, struct UpdateColumnValue *updateColumnValues,
          int32_t conditionCount, struct Condition *conditions) {
    if (tableHeader == NULL) {
        return NPE;
    }
    struct RecordData *recordDataRead = prepareRecordDataStructure(tableHeader);
    struct RecordData *recordDataWrite = prepareRecordDataStructure(tableHeader);
    int32_t readResult = readRecord(recordDataRead, tableHeader);
    if (readResult != 0) {
        return SUCCESS;
    }
    struct BlockHeader *rowPageBlock = recordDataRead->rowPageBlock;
    struct RowPage *rowPage = getBlockData(rowPageBlock);
    struct RowPointer *rowPointers = (struct RowPointer *) ((char *) rowPage + sizeof(struct RowPage));
    int32_t rowNum = rowPage->rowCount - 1;

    do {
        if (rowNum < 0) {
            //new page moment
            rowPageBlock = recordDataRead->rowPageBlock;
            rowPage = getBlockData(rowPageBlock);
            rowPointers = (struct RowPointer *) ((char *) rowPage + sizeof(struct RowPage));
            rowNum = rowPage->rowCount - 1;
        }
        struct HashMap *map = initFreeMapAndReturnPointer(tableHeader->columnCount, KEY_STRING);
        mapFieldNamesToDataPointers(map, tableHeader, recordDataRead);
        bool satisfies = false;
        int32_t err = checkIfRecordSatisfiesConditions(&satisfies, map, conditionCount, conditions);
        if (err != 0) {
            freeMap(map, free);
            freeRecordData(recordDataRead);
            freeRecordData(recordDataWrite);
            deleteMarkedRows(tableHeader);
            return err;
        }
        if (satisfies) {
            memcpy(recordDataWrite->data, recordDataRead->data, tableHeader->columnCount * sizeof(void *));
            for (int32_t col = 0; col < updateColumnsCount; col++) {
                struct ColumnData columnData;
                err = getOperandData(&columnData, map, &updateColumnValues[col].assignedValue);
                if (err != 0) {
                    freeMap(map, free);
                    freeRecordData(recordDataRead);
                    freeRecordData(recordDataWrite);
                    deleteMarkedRows(tableHeader);
                    return err;
                }
                void *newData = columnData.data;
                uint32_t colIndex = ((struct ColumnData *) getDataByKeyAndReturnPointer(map,
                                                                                        updateColumnValues[col].name))->columnNum;
                if (!areTypesComparable(columnData.dataType, recordDataRead->columns[colIndex]->dataType)) {
                    freeMap(map, free);
                    freeRecordData(recordDataRead);
                    freeRecordData(recordDataWrite);
                    deleteMarkedRows(tableHeader);
                    return TYPES_NOT_COMPARABLE;
                }
                recordDataWrite->data[colIndex] = newData;
            }
            rowPointers[rowNum].isToDelete = true;
            addRow(tableHeader, recordDataWrite, NULL);
        }
        rowNum--;
        freeMap(map, free);
    } while (readRecord(recordDataRead, tableHeader) == 0);
    freeRecordData(recordDataRead);
    freeRecordData(recordDataWrite);
    deleteMarkedRows(tableHeader);
    return SUCCESS;
}


int32_t allocTable(struct BlockHeader **bh, const char *name, int32_t columnNum, const enum DataType *types,
                   const char **names) {
    size_t tableHeaderSize = sizeof(struct TableHeader);
    for (int i = 0; i < columnNum; i++) {
        tableHeaderSize += sizeof(enum DataType);
        tableHeaderSize += strlen(names[i]) + 1;
    }
    struct BlockHeader *tableBlock;
    checkForErr(allocatePageInFile(&tableBlock, tableHeaderSize))
    struct FileNode *fileNode = getBlockData(tableBlock);
    strcpy(fileNode->name, name);

    struct TableHeader *tableHeader = convertFileNodeToTableHeader(fileNode);
    tableHeader->columnCount = columnNum;
    tableHeader->rowCount = 0;
    tableHeader->offsetFromBlockBegin = (char *) tableHeader - (char *) tableBlock;
    tableHeader->firstRowPage = INVALID_HEADER_BLOCK_COORDINATE;
    struct Column *curColumn = getFirstColumn(tableHeader);

    fileNode->nextTableHeader = INVALID_HEADER_BLOCK_COORDINATE;
    fileNode->prevTableHeader = INVALID_HEADER_BLOCK_COORDINATE;

    for (int32_t i = 0; i < columnNum; i++) {
        curColumn->dataType = types[i];
        strcpy(curColumn->name, names[i]);
        curColumn = getNextColumn(curColumn);
    }
    *bh = tableBlock;
    return SUCCESS;
}


static int32_t
checkIfJoinedRowSatisfiesJoinConditions(bool *res, struct HashMap *aliasToTableHashMap, int32_t joinConditionNum,
                                        struct JoinCondition *joinCondition) {
    bool validationResult = true;
    for (int32_t i = 0; i < joinConditionNum; i++) {
        struct HashMap *tableFieldsMapLeft = getDataByKeyAndReturnPointer(aliasToTableHashMap,
                                                                          joinCondition[i].leftOperand.tableAlias);
        struct ColumnData leftOperand;
        struct ColumnData rightOperand;
        checkForErr(getOperandDataByName(&leftOperand, tableFieldsMapLeft,
                                         joinCondition[i].leftOperand.columnName))
        struct HashMap *tableFieldsMap = getDataByKeyAndReturnPointer(aliasToTableHashMap,
                                                                      joinCondition[i].rightOperand.tableAlias);
        checkForErr(getOperandDataByName(&rightOperand, tableFieldsMap, joinCondition[i].rightOperand.columnName))
        validationResult &= compareColumnDatas(leftOperand, rightOperand, joinCondition[i].operator);
    }
    *res = validationResult;
    return SUCCESS;
}

static int32_t
getColumnDataByJoinWhereCondition(struct ColumnData *columnData, struct HashMap *aliasToTableHashMap,
                                  struct JoinWhereOperand joinWhereOperand) {

    if (joinWhereOperand.isOperandAName) {
        struct HashMap *tableHashmap = getDataByKeyAndReturnPointer(aliasToTableHashMap,
                                                                    joinWhereOperand.operandValue.nameAndColumn->aliasName);
        return getOperandDataByName(columnData, tableHashmap, joinWhereOperand.operandValue.nameAndColumn->columnName);
    } else {
        return getOperandDataByValue(columnData, joinWhereOperand.operandValue.freeVariable->dataType,
                                     joinWhereOperand.operandValue.freeVariable->operand);
    }
}

static int32_t checkIfJoinedRowSatisfiesWhereConditions(bool *res,
                                                        struct HashMap *aliasToTableHashMap,
                                                        int32_t filtersNum,
                                                        struct JoinWhereCondition *joinWhereCondition) {
    bool validationResult = true;
    for (int32_t i = 0; i < filtersNum; i++) {
        struct ColumnData leftOperand;
        int32_t er = getColumnDataByJoinWhereCondition(&leftOperand, aliasToTableHashMap,
                                                       joinWhereCondition[i].leftOperand);
        if (er != 0) return er;
        struct ColumnData rightOperand;
        er = getColumnDataByJoinWhereCondition(&rightOperand, aliasToTableHashMap,
                                               joinWhereCondition[i].rightOperand);
        if (er != 0) return er;
        validationResult &= compareColumnDatas(leftOperand, rightOperand, joinWhereCondition[i].operator);
    }
    *res = validationResult;
    return SUCCESS;
}


struct JoinColumnStat {
    int64_t allRowsNum;
    int32_t allColumnsNum;
};

static int32_t getBlocksAndMapTableData(struct JoinColumnStat *joinColumnStat,
                                        int32_t joinTablesNum, struct JoinTablesHeaders *joinTables,
                                        struct HashMap *tableAliasToTableHashmap,
                                        struct RecordData *readTableRecords[]
) {
    *joinColumnStat = (struct JoinColumnStat) {1, 0};
    for (int32_t i = 0; i < joinTablesNum; i++) {

        struct HashMap *columnNameToColumnData = initFreeMapAndReturnPointer(
                joinTables[i].tableHeader->columnCount, KEY_STRING);

        addDataInMap(tableAliasToTableHashmap, joinTables[i].tableAlias, (void *) columnNameToColumnData);
        joinColumnStat->allRowsNum *= joinTables[i].tableHeader->rowCount;
        joinColumnStat->allColumnsNum += joinTables[i].tableHeader->columnCount;
        readTableRecords[i] = prepareRecordDataStructure(joinTables[i].tableHeader);
        int32_t st = readRecord(readTableRecords[i], joinTables[i].tableHeader);
        if (st != 0) {
            return st;
        }
        mapFieldNamesToDataPointers(columnNameToColumnData, joinTables[i].tableHeader, readTableRecords[i]);
    }
    return SUCCESS;
}

static int32_t
allocJoinTable(struct BlockHeader **blockHeader, int32_t selectColumnsNum, struct TableAliasAndColumn *selectColumns,
               struct HashMap *tableAliasToTableHashmap) {
    enum DataType joinedRowDataTypes[selectColumnsNum];
    const char *joinedRowNames[selectColumnsNum];
    for (int32_t i = 0; i < selectColumnsNum; i++) {
        struct HashMap *firstRowData = getDataByKeyAndReturnPointer(tableAliasToTableHashmap,
                                                                    selectColumns[i].aliasName);
        if (firstRowData == NULL) {
            return 1;
        }
        struct ColumnData *columnData = getDataByKeyAndReturnPointer(firstRowData, selectColumns[i].columnName);
        joinedRowDataTypes[i] = columnData->dataType;
        joinedRowNames[i] = selectColumns[i].columnName;
    }
    checkForErr(allocTable(blockHeader, "join-result", selectColumnsNum, joinedRowDataTypes,
                           joinedRowNames))
    return SUCCESS;
}


int32_t joinTables(struct JoinResult *joinResult, int32_t selectColumnsNum, struct TableAliasAndColumn *selectColumns,
                   int32_t joinTablesNum, struct JoinTablesHeaders *joinTables,
                   int32_t joinConditionNum, struct JoinCondition *joinCondition,
                   int32_t filtersNum, struct JoinWhereCondition *joinWhereCondition) {
    struct HashMap *tableAliasToTableHashmap = initFreeMapAndReturnPointer(joinTablesNum, KEY_STRING);
    struct RecordData *readTableRecords[joinTablesNum];
    struct JoinColumnStat joinColumnStat;
    int32_t err = getBlocksAndMapTableData(&joinColumnStat, joinTablesNum, joinTables, tableAliasToTableHashmap,
                                           readTableRecords);
    if (err != SUCCESS) {
        freeMap(tableAliasToTableHashmap, freeMapWithFreeErasing);
        return err;
    }
    int64_t allRowsNum = joinColumnStat.allRowsNum;
    struct BlockHeader *joinResultHeader;
    err = allocJoinTable(&joinResultHeader, selectColumnsNum, selectColumns, tableAliasToTableHashmap);
    if (err != SUCCESS) {
        freeMap(tableAliasToTableHashmap, freeMapWithFreeErasing);
        return err;
    }
    struct TableHeader *joinTableHeader = convertFileNodeToTableHeader(getBlockData(joinResultHeader));
    struct RecordData *joinedRowRecordData = prepareRecordDataStructure(joinTableHeader);
    for (int32_t currentRecordCombinationIndex = 0;
         currentRecordCombinationIndex < allRowsNum; currentRecordCombinationIndex++) {
        bool satisfies = true;
        bool compRes;
        err = checkIfJoinedRowSatisfiesJoinConditions(&compRes, tableAliasToTableHashmap, joinConditionNum,
                                                      joinCondition);
        if (err != 0) {
            freeMap(tableAliasToTableHashmap, freeMapWithFreeErasing);
            return err;
        }

        satisfies &= compRes;
        err = checkIfJoinedRowSatisfiesWhereConditions(&compRes, tableAliasToTableHashmap, filtersNum,
                                                       joinWhereCondition);
        satisfies &= compRes;
        if (err != SUCCESS) {
            freeMap(tableAliasToTableHashmap, freeMapWithFreeErasing);
            return err;
        }
        if (satisfies) {
            for (int32_t selectColIndex = 0; selectColIndex < selectColumnsNum; selectColIndex++) {
                struct HashMap *tableByAlias = getDataByKeyAndReturnPointer(tableAliasToTableHashmap,
                                                                            selectColumns[selectColIndex].aliasName);
                struct ColumnData *columnData = getDataByKeyAndReturnPointer(tableByAlias,
                                                                             selectColumns[selectColIndex].columnName);
                joinedRowRecordData->data[selectColIndex] = columnData->data;
            }
            addRow(joinTableHeader, joinedRowRecordData, NULL);
        }
        int32_t tableReadIndex = 0;
        while (tableReadIndex < joinTablesNum &&
               readRecord(readTableRecords[tableReadIndex],
                          joinTables[tableReadIndex].tableHeader) != 0) {
            clearRecordDataToReadFromBegin(readTableRecords[tableReadIndex]);
            readRecord(readTableRecords[tableReadIndex], joinTables[tableReadIndex].tableHeader);
            struct HashMap *tableMap = getDataByKeyAndReturnPointer(tableAliasToTableHashmap,
                                                                    joinTables[tableReadIndex].tableAlias);
            mapFieldNamesToDataPointers(tableMap,
                                        joinTables[tableReadIndex].tableHeader,
                                        readTableRecords[tableReadIndex]);
            tableReadIndex++;
        }
        if (tableReadIndex < joinTablesNum) {
            struct HashMap *tableMap = getDataByKeyAndReturnPointer(tableAliasToTableHashmap,
                                                                    joinTables[tableReadIndex].tableAlias);
            mapFieldNamesToDataPointers(tableMap, joinTables[tableReadIndex].tableHeader,
                                        readTableRecords[tableReadIndex]);
        }
    }
    for (int i = 0; i < joinTablesNum; i++) {
        freeRecordData(readTableRecords[i]);
    }
    freeMap(tableAliasToTableHashmap, freeMapWithFreeErasing);
    *joinResult = (struct JoinResult) {convertFileNodeToTableHeader((struct FileNode *) getBlockData(joinResultHeader)),
                                       joinedRowRecordData};
    return SUCCESS;
}
