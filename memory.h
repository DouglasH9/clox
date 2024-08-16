//
// Created by dougl on 8/8/2024.
//

#ifndef LOX_MEMORY_H
#define LOX_MEMORY_H

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define FREE_ARRAY(type, pointer, old_count) \
    reallocate(pointer, sizeof(type) * (old_count), 0)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
    (type*)reallocate(pointer, sizeof(type) * (old_count), \
        sizeof(type) * (new_count))

#include "common.h"

void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif //LOX_MEMORY_H
