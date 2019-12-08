#include <stdint.h>

struct GDTDescription
{
    uint16_t size;
    void* offset;
} __attribute__((packed));

void load_gdt(struct GDTDescription addr);

static struct GDTDescription description;
static uint64_t GDT[256] = {0};

uintptr_t gdt_init()
{
    GDT[0] = 0;                  // Null segment
    GDT[1] = 0x00CF9A000000FFFF; // Kernel code
    GDT[2] = 0x00CF92000000FFFF; // Kernel data
    GDT[3] = 0x00CFFA000000FFFF; // User code
    GDT[4] = 0x00CFF2000000FFFF; // User code

    description.size = sizeof(GDT);
    description.offset = GDT;

    load_gdt(description);

    return (uintptr_t)GDT;
}