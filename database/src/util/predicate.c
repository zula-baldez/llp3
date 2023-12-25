//
// Created by moyak on 15.09.2023.
//

#include "../../include/util/private/predicate.h"

//returns 0 if condition is true
//1 if false
//2 if operands have uncomparable types

typedef int32_t (*ComparisonFunction)(const void*, const void*);

static int32_t compareString(const void* left, const void* right) {
    return strcmp((const char*)left, (const char*)right);
}

static int32_t compareInt(const void* left, const void* right) {
    int32_t leftValue = *((int*)left);
    int32_t rightValue = *((int*)right);
    return leftValue - rightValue;
}

static int32_t compareDouble(const void* left, const void* right) {
    double leftValue = *((double*)left);
    double rightValue = *((double*)right);
    if (leftValue < rightValue) return -1;
    if (leftValue > rightValue) return 1;
    return 0;
}
static int32_t compareDoubleInt(const void* left, const void* right) {
    double leftValue = *((double*)left);
    int32_t rightValue = *((int*)right);
    if (leftValue < rightValue) return -1;
    if (leftValue > rightValue) return 1;
    return 0;
}
static int32_t compareIntDouble(const void* left, const void* right) {
    return -compareDoubleInt(right, left);
}


static void changeBoolToInt(struct ColumnData* operand) {
    if(operand->dataType == BOOL_TYPE) {
        operand->dataType = INT_TYPE;
    }
}
static struct CompareResult errorResult = {2, 0};

struct CompareResult compareColumns(struct ColumnData leftOperand, struct ColumnData rightOperand) {
    changeBoolToInt(&leftOperand);
    changeBoolToInt(&rightOperand);
    ComparisonFunction compare = NULL;
    if(leftOperand.dataType == STRING_TYPE && rightOperand.dataType == STRING_TYPE) {
        compare = compareString;
    }
    if(leftOperand.dataType == INT_TYPE && rightOperand.dataType == INT_TYPE) {
        compare = compareInt;
    }
    if(leftOperand.dataType == DOUBLE_TYPE && rightOperand.dataType == DOUBLE_TYPE) {
        compare = compareDouble;
    }
    if(leftOperand.dataType == INT_TYPE && rightOperand.dataType == DOUBLE_TYPE) {
        compare = compareIntDouble;
    }
    if(leftOperand.dataType == DOUBLE_TYPE && rightOperand.dataType == INT_TYPE) {
        compare = compareDoubleInt;
    }
    if(compare == NULL) {
        return errorResult;
    }
    return (struct CompareResult){0, compare(leftOperand.data, rightOperand.data)};
}

bool areTypesComparable(enum DataType dt1, enum DataType dt2) {
    if(dt1 == BOOL_TYPE) dt1 = INT_TYPE;
    if(dt2 == BOOL_TYPE) dt2 = INT_TYPE;
    if(dt1 == STRING_TYPE || dt2 == STRING_TYPE) return dt1 == dt2;
    return true;
}

bool validateCompareResult(enum Operator operator, int32_t compareResult) {
    bool valid;
    switch (operator) {
        case EQUALS:
            valid =  compareResult == 0;
            break;
        case LESS:
            valid = compareResult < 0;
            break;
        case MORE:
            valid = compareResult > 0;
            break;
        default:
            valid = false;
    }
    return valid;

}


