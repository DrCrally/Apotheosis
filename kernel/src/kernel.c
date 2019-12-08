#include "vga.h"

void kmain(void)
{
    vga_init();
    vga_writestring("Hello world, this is my apotheosis.\n");
    vga_writestring("This is a second line.\n");
}