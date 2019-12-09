#include "klog.h"

void panic(void)
{
    klog("Panic: halting...\n");
    while (1)
    __asm__ ("cli\n"
             "hlt\n");
}