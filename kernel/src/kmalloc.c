#include <stdint.h>
#include <stddef.h>

#include "klog.h"
#include "kcommon.h"

#define HEAP_BASE MB(2)
#define HEAP_SIZE MB(4)

#define CHUNK_SIZE 8

#define MAP_SIZE (HEAP_SIZE / CHUNK_SIZE / 8)

typedef struct header
{
    size_t start_chunk;
    size_t chunks;
} header_t;

static size_t free = HEAP_SIZE;
static size_t allocated = 0;

// Bitmap of 8 byte chunks of memory
static uint8_t alloc_map[MAP_SIZE] = {0};

void kfree(void* ptr)
{
    if (!ptr)
        return;

    // Get pointer to header
    header_t* header = (header_t*)((uint8_t*)ptr - sizeof(header_t));

    // Mark chunks as free
    for (size_t k = header->start_chunk; k < header->start_chunk + header->chunks; ++k)
        alloc_map[k / 8] &= ~(1u << (k % 8));

    allocated -= header->chunks * CHUNK_SIZE;
    free += header->chunks * CHUNK_SIZE;
}

void* kmalloc(size_t size)
{
    size_t real_size = size + sizeof(header_t);
    size_t chunks_needed = real_size / CHUNK_SIZE;

    if (real_size % CHUNK_SIZE)
        ++chunks_needed;

    if (chunks_needed * CHUNK_SIZE > free)
    {
        klog("Kmalloc out of memory, requested %llu bytes with only %llu bytes free and %llu allocated\n", size, free, allocated);
        panic();
    }

    size_t chunks_found = 0;
    size_t chunk_start = 0;
    for (size_t i = 0; i < MAP_SIZE; ++i)
    {
        // No chunks available
        if (alloc_map[i] == 0xFF)
            continue;

        for (size_t j = 0; j < 8; ++j)
        {
            // Check if chunk is free
            if (!(alloc_map[i] & (1u << j)))
            {
                if (chunks_found == 0)
                    chunk_start = i * 8 + j;

                ++chunks_found;

                if (chunks_needed == chunks_found)
                {
                    header_t* header = (header_t*)(HEAP_BASE + (chunk_start * CHUNK_SIZE));
                    uint8_t* ptr = (uint8_t*)header;

                    ptr += sizeof(header_t);

                    header->chunks = chunks_found;
                    header->start_chunk = chunk_start;

                    // Mark chunks as allocated
                    for (size_t k = chunk_start; k < chunk_start + chunks_found; ++k)
                        alloc_map[k / 8] |= (1u << (k % 8));

                    allocated += chunks_found * CHUNK_SIZE;
                    free -= chunks_found * CHUNK_SIZE;

                    return ptr;
                }
            }
            else
            {
                // Required number of continuous chunks not found, reset the counter and start again with the next chunk
                chunks_found = 0;
            }
        }
    }

    klog("Kmalloc failed to allocate memory of size %llu bytes, %llu bytes free and %llu allocated\n", size, free, allocated);
    panic();

    // Unreachable, silence warning
    return NULL;
}

void* kcalloc(size_t size)
{
    void* ptr = kmalloc(size);
    memset(ptr, 0, size);
    return ptr;
}