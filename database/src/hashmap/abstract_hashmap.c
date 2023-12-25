#include <string.h>
#include "../../include/hashmap/private/abstract_hashmap.h"

static uint64_t stringHash(const char *str) {
    unsigned long hash = 0;
    int32_t c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

static uint64_t uint64Hash(const void *key) {
    return *((uint64_t *) key);
}

uint32_t elementIndex(struct HashMap *map, const void *key) {
    switch (map->keyType) {
        case KEY_STRING:
            return stringHash(key) % map->capacity;
        case KEY_UINT64_T:
            return uint64Hash(key) % map->capacity;
        default:
            return 0;
    }
}

bool keysEquals(struct HashMap *map, const void *key1, const void *key2) {
    switch (map->keyType) {
        case KEY_STRING:
            return strcmp(key1, key2) == 0;
        case KEY_UINT64_T:
            return *(uint64_t *) key1 == *(uint64_t *) key2;
        default:
            return 0;
    }
}


void *getData(struct HashMap *map) {
    return (char *) map + sizeof(struct HashMap);
}



