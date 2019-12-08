.intel_syntax noprefix

.global outb
.global inb

.type outb, @function
outb:
    push eax
    push edx
    mov     dx, WORD PTR [esp + 12]
    mov al, BYTE PTR [esp + 16]
    out dx, al
    pop edx
    pop eax
    ret

.type inb, @function
inb:
    push edx
    mov dx, WORD PTR [esp + 8]
    in al, dx
    pop edx
    ret
