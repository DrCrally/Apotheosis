#include "kcommon.h"
#include "vga.h"
#include "exception.h"

__attribute__((interrupt)) void except_div_by_zero(struct interrupt_frame* unused)
        {
    UNUSED(unused);
    kprintf("DIVIDE BY ZERO\n");
    panic();
}