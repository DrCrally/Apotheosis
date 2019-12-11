#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>

void kfree(void* ptr);
void* kmalloc(size_t size);
void* kcalloc(size_t size);

#endif