//
// Created by dougl on 7/17/2024.
//

#ifndef LOX_CHUNK_H
#define LOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
} OpCode;

typedef struct {
    int offset;
    int line;
} LineStart;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    ValueArray constants;
    int line_count;
    int line_capacity;
    LineStart* lines;
} Chunk;

void init_chunk(Chunk* chunk);
void free_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte, int line);
void write_constant(Chunk* chunk, Value value, int line);
int add_constant(Chunk* chunk, Value value);
int get_line(Chunk* chunk, int instruction);

#endif //LOX_CHUNK_H
