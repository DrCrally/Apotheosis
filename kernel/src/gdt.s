.intel_syntax noprefix

.global load_gdt

.type load_gdt, @function
load_gdt:
    cli
    lgdt [esp + 4]

    jmp 0x08:reload_CS

reload_CS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
