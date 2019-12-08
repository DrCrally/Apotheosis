#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        ++len;
    
    return len;
}

void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %0, %1" : : "a"(val), "d"(port) );
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %1, %0" : "=a"(ret) : "d"(port) );
    return ret;
}