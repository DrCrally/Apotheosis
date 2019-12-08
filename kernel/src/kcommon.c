#include "vga.h"

void panic(void)
{
    kprintf("Panic: halting...\n");
    while (1)
    __asm__ ("cli\n"
             "hlt\n");
}