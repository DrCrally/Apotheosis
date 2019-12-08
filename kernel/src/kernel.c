#include "vga.h"

void kmain(void)
{
    int x = 7;
    int y = 5;

    vga_init();
    kprintf("x = %d, &x = 0x%x\n", x, &x);
    kprintf("y = %d, &y = 0x%x", y, &y);
}