#include <stdlib.h>
#include "vm.h"


int main() {
    uint8_t hello[] = {
            PUSH, 0x00, 0x01,
            PUSH, 0x00, 0x02,
            IADD,
            HALT
    };
    VM *vm = vm_create(hello, sizeof(hello));
    vm_run(vm);
    vm_free(vm);
    return 0;
}
