#ifndef KLOG_H
#define KLOG_H

#include <stddef.h>
#include <stdarg.h>

void klog_init();

// Choose our method of logging
#define LOG_VGA

#ifdef LOG_VGA
void kprintf_vga(const char* str, ...);
#define klog(fmt, ...) kprintf_vga(fmt, ##__VA_ARGS__)
#endif

#ifdef LOG_OTHER
// No other type of logging implemented yet
#endif

#endif