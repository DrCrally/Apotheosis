.intel_syntax noprefix

.global load_idt

.type load_idt, @function
load_idt:
    lidt [esp + 4]
    sti
    ret
