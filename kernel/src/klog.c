#include <stdarg.h>
#include <stddef.h>

#include "vga.h"

#define CREATE(name, type) \
static void name ## _vga(type number, int base, const char* digits) \
{ \
    char buf[32]; \
    size_t i = 0; \
    for (i = 0; number; number /= base) \
    buf[i++] = digits[number % base]; \
 \
    while (i--) \
        vga_putchar(buf[i]); \
}

CREATE(write_int, int)
CREATE(write_uint, unsigned int)
CREATE(write_long, long)
CREATE(write_ulong, unsigned long)
CREATE(write_longlong, unsigned long)
CREATE(write_ulonglong, unsigned long)

void klog_init()
{
    vga_init();
}

static void write_string_vga(const char* str)
{
    for (size_t i = 0; str[i]; ++i)
        vga_putchar(str[i]);
}

static void handle_specifier_vga(const char* str, size_t* i, va_list* ap)
{
    // for %x and %X, to switch between uppercase and lowercase hex digits
    static char upper[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    static char lower[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    switch (str[*i])
    {
        case 'i':
        case 'd': { write_int_vga(va_arg(*ap, int), 10, upper); } break;
        case 'b': { write_uint_vga(va_arg(*ap, int), 2, upper); } break;
        case 'o': { write_uint_vga(va_arg(*ap, int), 8, upper); } break;
        case 'u': { write_uint_vga(va_arg(*ap, int), 10, upper); } break;
        case 'X': { write_uint_vga(va_arg(*ap, int), 16, upper); } break;
        case 'x': { write_uint_vga(va_arg(*ap, int), 16, lower); } break;
        case 'l':
        {
            switch (str[++*i])
            {
                case 'i':
                case 'd': { write_long_vga(va_arg(*ap, unsigned long), 10, upper); } break;
                case 'b': { write_ulong_vga(va_arg(*ap, unsigned long), 2, upper); } break;
                case 'o': { write_ulong_vga(va_arg(*ap, unsigned long), 8, upper); } break;
                case 'u': { write_ulong_vga(va_arg(*ap, unsigned long), 10, upper); } break;
                case 'X': { write_ulong_vga(va_arg(*ap, unsigned long), 16, upper); } break;
                case 'x': { write_ulong_vga(va_arg(*ap, unsigned long), 16, lower); } break;
                case 'l':
                {
                    switch (str[++*i])
                    {
                        case 'i':
                        case 'd': { write_longlong_vga(va_arg(*ap, unsigned long), 10, upper); } break;
                        case 'b': { write_ulonglong_vga(va_arg(*ap, unsigned long), 2, upper); } break;
                        case 'o': { write_ulonglong_vga(va_arg(*ap, unsigned long), 8, upper); } break;
                        case 'u': { write_ulonglong_vga(va_arg(*ap, unsigned long), 10, upper); } break;
                        case 'X': { write_ulonglong_vga(va_arg(*ap, unsigned long), 16, upper); } break;
                        case 'x': { write_ulonglong_vga(va_arg(*ap, unsigned long), 16, lower); } break;
                    }
                } break;
            }
        } break;

        case 's': { write_string_vga(va_arg(*ap, const char*)); } break;

        default: { /* Do nothing */ } break;
    }
}

void kprintf_vga(const char* str, ...)
{
    va_list ap;
    va_start(ap, str);

    for (size_t i = 0; str[i]; ++i)
    {
        switch (str[i])
        {
            case '%':
            {
                ++i;
                handle_specifier_vga(str, &i, &ap);
            } break;

            case '\\':
            {
                vga_putchar(str[++i]);
            } break;

            default:
            {
                vga_putchar(str[i]);
            } break;
        }
    }

    va_end(ap);

    vga_update_cursor();
}