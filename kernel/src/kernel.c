#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "klog.h"
#include "pic.h"

void kmain(void) {
    klog_init();

    uintptr_t gdt_addr = gdt_init();
    klog("Loaded GDT at 0x%x\n", gdt_addr);

    uintptr_t idt_addr = idt_init();
    klog("Loaded IDT at 0x%x\n", idt_addr);

    pic_init(0x20, 0x28);
    pic_clear_mask(1);

    for (;;)
        __asm__ volatile ("hlt");
}