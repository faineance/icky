#pragma once

#include <setjmp.h>

typedef enum {
    WORKING = 1,
    DONE
};

typedef struct {
    jmp_buf callee_ctx;
    jmp_buf caller_ctx;
} Coroutine;


void yield(Coroutine *coroutine) {
    if (!setjmp(coroutine->callee_ctx)) {
        longjmp(coroutine->caller_ctx, WORKING);
    }
}

int next(Coroutine* coroutine) {
    int ret = setjmp(coroutine->caller_ctx);
    if(!ret) {
        longjmp(coroutine->callee_ctx, 1);

    } else {
        return (ret == WORKING);
    }
}

typedef struct {
    Coroutine* c;
    void* args;
    void* sp;
    void* fp;
} Frame;

// Oh so unportable
#define get_sp(p) asm volatile("movq %%rsp, %0" : "=r"(p))

#define get_fp(p) asm volatile("movq %%rbp, %0" : "=r"(p))

#define set_sp(p) asm volatile("movq %0, %%rsp" : : " r"(p))

#define set_fp(p) asm volatile("movq %0, %%rbp" : : "r"(p))
