#include <stdlib.h>
#include "vm.h"
#include "debug.h"
#define  DISPATCH if (vm->DP < vm->code_len)  { goto *labels[vm->code[vm->DP++]]; } else { goto end; }

static inline uint8_t vm_fetch(VM *vm) {
    vm->DP += 1;
    return vm->code[vm->DP];
}


static inline void vm_push(VM *vm, uint16_t value) {
    vm->stack[++vm->SP] = value;
}

uint16_t vm_pop(VM *vm) {
    return vm->stack[vm->SP--];
}

void vm_run(VM *vm) {
    static  void* labels[5] = { &&push, &&pop, &&iadd, &&isub, &&imul };

    uint8_t d1, d2;
    uint16_t v;
    TRACE("Beginning program execution");
    DISPATCH
    push:
        d1 = vm_fetch(vm);
        d2 = vm_fetch(vm);
        v = (d2 << 8) | d1;
        vm_push(vm, v);

        DISPATCH
    pop:
        v = vm->stack[vm->SP--];
        TRACE("Popped %d",v );
        DISPATCH
    iadd:
        vm_push(vm, vm_pop(vm) + vm_pop(vm));

        DISPATCH
    isub:
        vm_push(vm, vm_pop(vm) - vm_pop(vm));
        DISPATCH
    imul:
        vm_push(vm, vm_pop(vm) * vm_pop(vm));
        DISPATCH

    end:

        TRACE("Program exited successfully");
}


void vm_free(VM *vm) {
    free(vm);
}

VM *vm_create(uint8_t *code, int code_len) {
    VM *vm = calloc(1, sizeof(VM));


    vm->SP = 0;
    vm->DP = 0;
    vm->FP = 0;
    vm->code = code;
    vm->code_len = code_len;

    return vm;
}