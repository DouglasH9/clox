//
// Created by dougl on 8/16/2024.
//

#ifndef LOX_VALUE_H
#define LOX_VALUE_H

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

// memory management for ValueArray
void init_value_array(ValueArray* array);
void write_value_array(ValueArray* array, Value value);
void free_value_array(ValueArray* array);

#endif //LOX_VALUE_H
