//
// Created by dougl on 8/16/2024.
//
#include <stdio.h>
#include "debug.h"
#include "value.h"

void disassemble_chunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset);
    }
}

static int constant_instruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

static int long_constant_instruction(const char* name, Chunk* chunk, int offset) {
    uint32_t constant = chunk->code[offset + 1] |
                        (chunk->code[offset + 2] << 8) |
                        (chunk->code[offset + 3] << 16);
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 4;
}

static int simple_instruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassemble_instruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    int line = get_line(chunk, offset);

    if (offset > 0 && line == get_line(chunk, offset - 1)) {
        printf("   | ");
    } else {
        printf("%4d ", line);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return long_constant_instruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_ADD:
            return simple_instruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simple_instruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simple_instruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simple_instruction("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simple_instruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

