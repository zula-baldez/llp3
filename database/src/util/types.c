#include "../../include/util/private/types.h"
size_t dataTypeLen(enum DataType dataType, void *data) {
    size_t size;
    switch (dataType) {
        case STRING_TYPE:
            size = strlen(data) + 1; //include \0 symbol
            break;
        case DOUBLE_TYPE:
            size = 8;
            break;
        default:
            size = 4;
            break;
    }
    return size;
}

