#include <stdint.h>
#include <stddef.h>

#include "exception.h"

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

struct IDTEntry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t gate_type : 4;
    uint8_t storage : 1;
    uint8_t priv : 2;
    uint8_t present : 1;
    uint16_t offset_high;
} __attribute__((packed));

void load_idt(struct IDTDescription desc);

static struct IDTDescription description;
static struct IDTEntry IDT[256] = {{0}};

void idt_add_entry(size_t index, void* offset, uint8_t gate_type, uint8_t priv_level)
{
    IDT[index].offset_low = (uintptr_t)offset & 0x0000FFFFu;
    IDT[index].offset_high = ((uintptr_t)offset >> 16u) & 0x0000FFFFu;
    IDT[index].selector = 0x08;
    IDT[index].gate_type = gate_type;
    IDT[index].storage = gate_type == TASK_GATE ? 1 : 0;
    IDT[index].priv = priv_level;
    IDT[index].present = 1;
}

uintptr_t idt_init()
{
    // Register CPU exceptions in IDT
    idt_add_entry(0, except_div_by_zero, TRAP_GATE, KERNEL);
    idt_add_entry(1, except_debug, TRAP_GATE, KERNEL);
    idt_add_entry(2, except_nmi, TRAP_GATE, KERNEL);
    idt_add_entry(3, except_breakpoint, TRAP_GATE, KERNEL);
    idt_add_entry(4, except_overflow, TRAP_GATE, KERNEL);
    idt_add_entry(5, except_bound_range_exceeded, TRAP_GATE, KERNEL);
    idt_add_entry(6, except_invalid_opcode, TRAP_GATE, KERNEL);
    idt_add_entry(7, except_device_not_available, TRAP_GATE, KERNEL);
    idt_add_entry(8, except_double_fault, TRAP_GATE, KERNEL);
    idt_add_entry(9, except_coprocessor_segment_overrun, TRAP_GATE, KERNEL);
    idt_add_entry(10, except_invalid_tss, TRAP_GATE, KERNEL);
    idt_add_entry(11, except_segment_not_present, TRAP_GATE, KERNEL);
    idt_add_entry(12, except_stack_segment_fault, TRAP_GATE, KERNEL);
    idt_add_entry(13, except_general_protection_fault, TRAP_GATE, KERNEL);
    idt_add_entry(14, except_page_fault, TRAP_GATE, KERNEL);
    // 15 Reserved
    idt_add_entry(16, except_x87_floating_point, TRAP_GATE, KERNEL);
    idt_add_entry(17, except_alignment_check, TRAP_GATE, KERNEL);
    idt_add_entry(18, except_machine_check, TRAP_GATE, KERNEL);
    idt_add_entry(19, except_simd_floating_point, TRAP_GATE, KERNEL);
    idt_add_entry(20, except_virtualization, TRAP_GATE, KERNEL);
    // 21 Reserved
    // 22 Reserved
    // 23 Reserved
    // 24 Reserved
    // 25 Reserved
    // 26 Reserved
    // 27 Reserved
    // 28 Reserved
    // 29 Reserved
    idt_add_entry(30, except_security, TRAP_GATE, KERNEL);
    //31 Reserved

    description.size = sizeof(IDT);
    description.offset = IDT;

    load_idt(description);

    return (uintptr_t)IDT;
}