#pragma once

#include <stdint.h>
#include <stddef.h>

#define MAX_INT 16
#define MAX_REGS 16
#define MAX_STACK 256
#define DP regs[13] // data pointer
#define FP regs[14] // frame pointer
#define SP regs[15] // stack pointer



typedef struct {
    uint8_t *code;
    int code_len;

    uint16_t interrupts[MAX_INT];
    int16_t regs[MAX_REGS];
    uint16_t stack[MAX_STACK];
} VM;

VM *vm_create(uint8_t *code, int code_len);

void vm_free(VM *vm);

void vm_run(VM *vm);
typedef enum {
    PUSH = 0x00,
    POP  = 0x01,
    IADD = 0x02,
    ISUB = 0x03,
    IMUL = 0x04,
    HALT = 0x05,
} Instruction;
static uint8_t vm_fetch(VM *vm);

static void vm_push(VM *vm, uint16_t value);

uint16_t vm_pop(VM *vm);
typedef struct {
    int return_ip;
    uint16_t arg1;
    uint16_t arg2;
    uint16_t arg3;
} Frame;

