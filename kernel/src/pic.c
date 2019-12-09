#include <stdint.h>

#include "portio.h"

//TODO: remove
#include "klog.h"

#define PIC1_COMMAND_PORT 0x20
#define PIC2_COMMAND_PORT 0xA0
#define PIC1_DATA_PORT 0x21
#define PIC2_DATA_PORT 0xA1

#define PIC_COMMAND_INIT 0x11

#define PIC_8086_MODE 0x01

#define PIC_EOI 0x20

void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8)
        outb(PIC2_COMMAND_PORT, PIC_EOI);

    outb(PIC1_COMMAND_PORT, PIC_EOI);
}

void pic_init(uint8_t offset1, uint8_t offset2)
{
    outb(PIC1_COMMAND_PORT, PIC_COMMAND_INIT);
    outb(PIC2_COMMAND_PORT, PIC_COMMAND_INIT);

    outb(PIC1_DATA_PORT, offset1);
    outb(PIC2_DATA_PORT, offset2);

    outb(PIC1_DATA_PORT, 0x04);
    outb(PIC2_DATA_PORT, 0x02);

    outb(PIC1_DATA_PORT, PIC_8086_MODE);
    outb(PIC2_DATA_PORT, PIC_8086_MODE);

    outb(PIC1_DATA_PORT, 0xFF);
    outb(PIC2_DATA_PORT, 0xFF);
}

void pic_set_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if(irq < 8)
    {
        port = PIC1_DATA_PORT;
    }
    else
    {
        port = PIC2_DATA_PORT;
        irq -= 8;
    }

    value = inb(port) | (1u << irq);
    outb(port, value);
}

void pic_clear_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if(irq < 8)
    {
        port = PIC1_DATA_PORT;
    }
    else
    {
        port = PIC2_DATA_PORT;
        irq -= 8;
    }

    value = inb(port) & ~(1u << irq);
    outb(port, value);
}