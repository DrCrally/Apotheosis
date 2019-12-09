#include <stdint.h>
#include <stddef.h>

#include "text_cursor.h"

enum vga_color 
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t vga_row;
static size_t vga_col;
static uint8_t vga_color;
static uint16_t* vga_buffer;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return (fg | (bg << 4u));
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return ((uint16_t)uc | ((uint16_t)color << 8u));
}

static inline size_t index(size_t x, size_t y)
{
    return y * VGA_WIDTH + x;
}

void vga_update_cursor()
{
    update_cursor(vga_col, vga_row);
}

static void scroll()
{
    for (size_t y = 0; y < VGA_HEIGHT - 1; ++y)
        for (size_t x = 0; x < VGA_WIDTH; ++x)
            vga_buffer[index(x, y)] = vga_buffer[index(x, y+ 1)];

    for (size_t i = 0; i < VGA_WIDTH; ++i)
        vga_buffer[index(i, VGA_HEIGHT - 1)] = vga_entry(' ', vga_color);
}

void vga_putchar(char c)
{
    switch (c)
    {
        case '\n':
        {
            vga_col = 0;

            if (vga_row < VGA_HEIGHT - 1)
                ++vga_row;
            else
                scroll();
        } break;

        default:
        {
            const size_t index = vga_row * VGA_WIDTH + vga_col;
            vga_buffer[index] = vga_entry(c, vga_color);

            if (++vga_col == VGA_WIDTH)
            {
                vga_col = 0;
                if (++vga_row == VGA_HEIGHT)
                    vga_row = 0;
            }
        } break;
    }
}

void vga_init(void)
{
    vga_row = 0;
    vga_col = 0;
    vga_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_buffer = (uint16_t*)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = vga_entry(' ', vga_color);
        }
    }

    enable_cursor();
    update_cursor(0, 0);
}