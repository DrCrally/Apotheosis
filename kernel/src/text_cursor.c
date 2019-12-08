#include "klib.h"

void enable_cursor()
{
    const uint8_t cur_beg = 0;
    const uint8_t cur_end = 15;

    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5u) & 0xC0u) | cur_beg);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5u) & 0xE0u) | cur_end);
}

void disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void update_cursor(int x, int y)
{
    uint16_t pos = y * 80 + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFFu));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8u) & 0xFFu));
}