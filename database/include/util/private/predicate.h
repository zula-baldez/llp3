//
// Created by moyak on 13.09.2023.
//

#ifndef LAB1_CONDITION_PRIVATE_H
#define LAB1_CONDITION_PRIVATE_H

#include "../public/predicate.h"
#include <string.h>
#include "../../hashmap/private/abstract_hashmap.h"

struct CompareResult compareColumns(struct ColumnData left, struct ColumnData right);

bool validateCompareResult(enum Operator operator, int32_t compareResult);

bool areTypesComparable(enum DataType dt1, enum DataType dt2);

#endif //LAB1_CONDITION_PRIVATE_H
