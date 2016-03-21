#include <stdlib.h>
#include "vm.h"
#include "debug.h"
#define DISPATCH  { goto *labels[vm->code[vm->DP++]]; }
#define INLINE __always_inline

static INLINE uint8_t vm_fetch(VM *vm) {
    return vm->code[vm->DP++];
}

static INLINE void vm_push(VM *vm, uint16_t value) {
    vm->stack[++vm->SP] = value;
}

static INLINE uint16_t vm_pop(VM *vm) {
    return vm->stack[vm->SP--];
}

void vm_run(VM *vm) {
    static  void* labels[8] = { &&push, &&pop, &&iadd, &&isub, &&imul, &&inc, &&dec, &&halt};

    uint8_t d1, d2;
    uint16_t v;
    TRACE("Beginning program execution");
    DISPATCH
    push:
        d1 = vm_fetch(vm);
        d2 = vm_fetch(vm);

        v = (d2 << 8) | d1;
        vm_push(vm, v);
        TRACE("Pushed %d", v);
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
    inc:
        vm_push(vm, (uint16_t)(vm_pop(vm) + 1));
        DISPATCH
    dec:
        vm_push(vm, (uint16_t)(vm_pop(vm) - 1));
        DISPATCH
    halt:
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
