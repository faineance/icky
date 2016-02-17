#include <stdlib.h>
#include "vm.h"


int main() {
    uint8_t hello[] = {
            PUSH, 0x01, 0x00,
            PUSH, 0x03, 0x00,
            IADD,
            HALT
    };
    VM *vm = vm_create(hello, sizeof(hello));
    vm_run(vm);
    vm_free(vm);
    return 0;
}
