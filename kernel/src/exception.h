#ifndef EXCEPTION_H
#define EXCEPTION_H

struct interrupt_frame;

void except_div_by_zero(struct interrupt_frame* unused);

#endif