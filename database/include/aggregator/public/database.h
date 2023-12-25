//
// Created by moyak on 09.09.2023.
//

#ifndef LAB1_DATABASE_H
#define LAB1_DATABASE_H

#include <stdint.h>
#include "../../file-work/public/block.h"
#include "../../util/public/types.h"
#include "../../file-work/public/table.h"
#include "../../util/public/predicate.h"

struct DatabaseHeader;


int32_t openDatabaseFileOrCreate(const char *path);

int32_t closeDatabaseFile(void);

int32_t createTable(const char *name, int32_t columnNum, enum DataType *types, const char **names);

int32_t deleteTable(const char *name);

int32_t deleteTableByHeader(struct TableHeader *tableHeader);

int32_t getTable(struct TableHeader **table, const char *name);

int32_t freeTable(struct TableHeader *tableHeader);


#endif //LAB1_DATABASE_H

