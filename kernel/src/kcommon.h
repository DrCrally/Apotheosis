#ifndef KCOMMON_H
#define KCOMMON_H

// Remove warning for unused parameters
#define UNUSED(x) (void)(x)

#define KB(bytes) (bytes * 1024)
#define MB(bytes) (bytes * 1024 * 1024)
#define GB(bytes) (bytes * 1024 * 1024 * 1024)

// Kernel panic
void panic(void);

#endif