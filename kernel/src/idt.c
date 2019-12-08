#include <stdint.h>
#include <stddef.h>

#include "exception.h"
#include "vga.h"

#define TASK_GATE 0x05
#define INTERRUPT_GATE 0x0E
#define TRAP_GATE 0x0F

#define KERNEL 0x00
#define USER 0x03

struct IDTDescription
{
    uint16_t size;
    void* offset;
} __attribute__((packed));

void load_idt(struct IDTDescription desc);

static struct IDTDescription description;
static uint64_t IDT[256] = {0};

    void idt_add_entry(size_t index, void* offset, uint8_t gate_type, uint8_t priv_level)
    {
        uint8_t byte = 0xef;
        uint64_t entry = 0x00008e0000080000;

//    byte |= (uint8_t)(priv_level << 5u);
//    byte |= gate_type;
//    if (gate_type == TASK_GATE)
//        byte |= 0x10u;

    entry |= ((uintptr_t)offset & 0x0000FFFFu);
    entry |= (((uint64_t)offset << 32u) & 0xFFFF000000000000u);
//    entry |= ((uint64_t)byte << 48u);

    kprintf("Entry: 0x%x\n", (unsigned long long)entry);

    IDT[index] = entry;
}

uintptr_t idt_init()
{
    for (uint8_t i = 0xff; i > 0x10; --i)
        idt_add_entry(i, except_div_by_zero, TRAP_GATE, KERNEL);

    idt_add_entry(0, except_div_by_zero, INTERRUPT_GATE, KERNEL);

    description.size = sizeof(IDT);
    description.offset = IDT;

    load_idt(description);

    return (uintptr_t)IDT;
}