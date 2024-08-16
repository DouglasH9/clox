//
// Created by dougl on 7/17/2024.
//

#ifndef LOX_CHUNK_H
#define LOX_CHUNK_H

#include "common.h"

typedef enum {
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;

void init_chunk(Chunk* chunk);

void write_chunk(Chunk* chunk, uint8_t byte);

#endif //LOX_CHUNK_H
