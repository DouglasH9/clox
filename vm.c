//
// Created by dougl on 8/20/2024.
//
#include <stdio.h>
#include "common.h"
#include "vm.h"
#include "debug.h"
#include "memory.h"

VM vm;

static void reset_stack() {
    vm.stack_count = 0;
}

void initVM() {
    vm.stack = NULL;
    vm.stack_capacity = 0;
    reset_stack();
}

void freeVM() {

}

void push(Value value) {
    if (vm.stack_capacity < vm.stack_count + 1) {
        int old_capacity = vm.stack_capacity;
        vm.stack_capacity = GROW_CAPACITY(old_capacity);
        vm.stack = GROW_ARRAY(Value, vm.stack, old_capacity, vm.stack_capacity);
    }
    vm.stack[vm.stack_count] = value;
    vm.stack_count++;
}

Value pop() {
    vm.stack_count--;
    return vm.stack[vm.stack_count];
}

static InterpretResult run() {

#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("             ");
        for (Value* slot = vm.stack; slot < vm.stack + vm.stack_count; slot++) {
            printf("[ ");
            print_value(*slot);
            printf(" ]");
        }
        printf("\n");
        disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD: BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE: BINARY_OP(/); break;
            case OP_NEGATE: push(-pop()); break;
            case OP_RETURN: {
                print_value(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}