#include <stdint.h>

#include "vga.h"
#include "gdt.h"

void kmain(void)
{
    vga_init();

    uintptr_t gdt_addr = gdt_init();
    kprintf("Loaded GDT at 0x%x\n", gdt_addr);
}