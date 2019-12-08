#include <stdint.h>

#include "vga.h"
#include "gdt.h"
#include "idt.h"

void kmain(void)
{
    vga_init();

    uintptr_t gdt_addr = gdt_init();
    kprintf("Loaded GDT at 0x%x\n", gdt_addr);

    uintptr_t idt_addr = idt_init();
    kprintf("Loaded IDT at 0x%x\n", idt_addr);

//    volatile int x = 5 / 0;
}