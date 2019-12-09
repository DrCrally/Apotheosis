#include <stdint.h>

#include "kcommon.h"
#include "klog.h"
#include "exception.h"

__attribute__((interrupt))
void except_div_by_zero(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Division by Zero\n");
    panic();
}

__attribute__((interrupt))
void except_debug(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Debug\n");
    panic();
}

__attribute__((interrupt))
void except_nmi(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Non-Maskable Interrupt\n");
    panic();
}

__attribute__((interrupt))
void except_breakpoint(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Breakpoint\n");
    panic();
}

__attribute__((interrupt))
void except_overflow(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Overflow\n");
    panic();
}

__attribute__((interrupt))
void except_bound_range_exceeded(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Bound Range Exceeded\n");
    panic();
}

__attribute__((interrupt))
void except_invalid_opcode(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Invalid Opcode\n");
    panic();
}

__attribute__((interrupt))
void except_device_not_available(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Device Not Availalble\n");
    panic();
}

__attribute__((interrupt))
void except_double_fault(struct interrupt_frame* unused, uint32_t err)
{
    UNUSED(unused);
    klog("Exception: Double Fault, error code = %u\n", err);
    panic();
}

__attribute__((interrupt))
void except_coprocessor_segment_overrun(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Coprocessor Segment Overrun\n");
    panic();
}

__attribute__((interrupt))
void except_invalid_tss(struct interrupt_frame* unused, uint32_t index)
{
    UNUSED(unused);
    klog("Exception: Invalid TSS, index = %u\n", index);
    panic();
}

__attribute__((interrupt))
void except_segment_not_present(struct interrupt_frame* unused, uint32_t index)
{
    UNUSED(unused);
    klog("Exception: Segment Not Present, segment selector index = %u\n", index);
    panic();
}

__attribute__((interrupt))
void except_stack_segment_fault(struct interrupt_frame* unused, uint32_t index)
{
    UNUSED(unused);
    klog("Exception: Stack-Segment Fault, stack segment selector index =%u\n", index);
    panic();
}

__attribute__((interrupt))
void except_general_protection_fault(struct interrupt_frame* unused, uint32_t index)
{
    UNUSED(unused);
    klog("Exception: General Protection Fault, segment selector index = %u\n", index);
    panic();
}

__attribute__((interrupt))
void except_page_fault(struct interrupt_frame* unused, uint32_t err)
{
    UNUSED(unused);
    klog("Exception: Page Fault, error code = %u\n", err);
    panic();
}

__attribute__((interrupt))
void except_x87_floating_point(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: x87 Floating-Point Exception\n");
    panic();
}

__attribute__((interrupt))
void except_alignment_check(struct interrupt_frame* unused, uint32_t err)
{
    UNUSED(unused);
    klog("Exception: Alignment check, error code = %u\n", err);
    panic();
}

__attribute__((interrupt))
void except_machine_check(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Machine Check\n");
    panic();
}

__attribute__((interrupt))
void except_simd_floating_point(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: SIMD Floating-Point Exception\n");
    panic();
}

__attribute__((interrupt))
void except_virtualization(struct interrupt_frame* unused)
{
    UNUSED(unused);
    klog("Exception: Virtualization\n");
    panic();
}

__attribute__((interrupt))
void except_security(struct interrupt_frame* unused, uint32_t err)
{
    UNUSED(unused);
    klog("Exception: Security, error code = %d\n", err);
    panic();
}
