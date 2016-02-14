#pragma once
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define TRACE(M, ...)
#else
#define TRACE(M, ...) fprintf(stdout, "DEBUG %s:%s:%d: " M "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#endif