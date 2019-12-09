#ifndef EXCEPTION_H
#define EXCEPTION_H

struct interrupt_frame;

void except_div_by_zero(struct interrupt_frame* unused);
void except_debug(struct interrupt_frame* unused);
void except_nmi(struct interrupt_frame* unused);
void except_breakpoint(struct interrupt_frame* unused);
void except_overflow(struct interrupt_frame* unused);
void except_bound_range_exceeded(struct interrupt_frame* unused);
void except_invalid_opcode(struct interrupt_frame* unused);
void except_device_not_available(struct interrupt_frame* unused);
void except_double_fault(struct interrupt_frame* unused, uint32_t err);
void except_coprocessor_segment_overrun(struct interrupt_frame* unused);
void except_invalid_tss(struct interrupt_frame* unused, uint32_t index);
void except_segment_not_present(struct interrupt_frame* unused, uint32_t index);
void except_stack_segment_fault(struct interrupt_frame* unused, uint32_t index);
void except_general_protection_fault(struct interrupt_frame* unused, uint32_t index);
void except_page_fault(struct interrupt_frame* unused, uint32_t err);
void except_x87_floating_point(struct interrupt_frame* unused);
void except_alignment_check(struct interrupt_frame* unused, uint32_t err);
void except_machine_check(struct interrupt_frame* unused);
void except_simd_floating_point(struct interrupt_frame* unused);
void except_virtualization(struct interrupt_frame* unused);
void except_security(struct interrupt_frame* unused, uint32_t err);

#endif