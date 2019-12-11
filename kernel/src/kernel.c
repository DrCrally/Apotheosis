#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "klog.h"
#include "pic.h"
#include "multiboot.h"
#include "kcommon.h"
#include "pmm.h"

void kmain(multiboot_info_t* info, uint32_t magic)
{
    klog_init();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        klog("Multiboot magic number not found, should be %X, was %X\n", MULTIBOOT_BOOTLOADER_MAGIC, magic);
        panic();
    }

    uintptr_t gdt_addr = gdt_init();
    klog("Loaded GDT at 0x%x\n", gdt_addr);

    uintptr_t idt_addr = idt_init();
    klog("Loaded IDT at 0x%x\n", idt_addr);

    pic_init(0x20, 0x28);
    pic_clear_mask(1);

    pmm_init(info);

    for (;;)
        __asm__ volatile ("hlt");
}