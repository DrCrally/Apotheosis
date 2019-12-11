#include <stdint.h>

#include "klog.h"

void memset(void* dst, uint8_t val, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        ((uint8_t*)dst)[i] = val;
}

void panic(void)
{
    klog("Panic: halting...\n");
    while (1)
    __asm__ ("cli\n"
             "hlt\n");
}