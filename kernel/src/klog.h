#ifndef KLOG_H
#define KLOG_H

#include <stddef.h>
#include <stdarg.h>

void klog_init(void);
void kprintf_vga(const char* str, ...);

#define klog(fmt, ...) kprintf_vga(fmt, ##__VA_ARGS__)


#endif