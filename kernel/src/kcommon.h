#ifndef KCOMMON_H
#define KCOMMON_H

#include <stdint.h>
#include <stddef.h>

// Remove warning for unused parameters
#define UNUSED(x) (void)(x)

#define KB(bytes) ((bytes) * 1024)
#define MB(bytes) ((bytes) * 1024 * 1024)
#define GB(bytes) ((bytes) * 1024 * 1024 * 1024)

void memset(void* dst, uint8_t val, size_t size);

// Kernel panic
void panic(void);

#endif