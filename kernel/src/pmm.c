#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "multiboot.h"
#include "kcommon.h"
#include "kmalloc.h"
#include "klog.h"
#include "bitmap.h"

#define PAGE_SIZE 4096

typedef struct region
{
    void* start;
    void* end;
    size_t last_allocd;
    size_t total_pages;
    size_t free_pages;
    uint8_t* bitmap;
    struct region* next;
} region_t;

static region_t* khead;
static region_t* uhead;

static inline void init_region(region_t** region, void* page)
{
    *region = kmalloc(sizeof(region_t));
    (*region)->start = page;
    (*region)->end = page + PAGE_SIZE;
    (*region)->last_allocd = 0;
    (*region)->total_pages = 1;
    (*region)->next = NULL;
}

static void process_page(region_t** head, region_t** region_ptr, void* page)
{
#define region (*region_ptr)
    if (!region)
    {
        init_region(region_ptr, page);
        *head = region;
    }
    else if (region->end != page)
    {
        init_region(&region->next, page);
        region = region->next;
    }
    else
    {
        region->end = page + PAGE_SIZE;
        ++region->total_pages;
    }
#undef region
}

static inline void generate_bitmap(region_t* head)
{
    for (region_t* node = head; node; node = node->next)
    {
        uint8_t size = (node->total_pages / 8) + (node->total_pages % 8);
        node->bitmap = kcalloc(size);
        node->free_pages = node->total_pages;
        memset(node->bitmap, 0, size);
    }
}

static inline void enumerate(region_t* head)
{
    for (region_t* node = head; node; node = node->next)
        klog("Region at 0x%llx {.total_pages=%llu, .free_pages=%llu}\n", (uintptr_t)node->start, node->total_pages, node->free_pages);
}

void pmm_init(multiboot_info_t* info)
{
    region_t* kcur = NULL;
    region_t* ucur = NULL;

    for (multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)info->mmap_addr;
        (uintptr_t)mmap < info->mmap_addr + info->mmap_length;
         mmap = (multiboot_memory_map_t*)((unsigned long)mmap + mmap->size + sizeof(mmap->size)))
    {
        // Unavailable
        if (mmap->type != MULTIBOOT_MEMORY_AVAILABLE)
            continue;

        // Reserved
        if (mmap->addr < MB(1))
            continue;

        // Exceeds maximum addresable memory on x86 without PAE
        if (mmap->addr + mmap->len > 0xFFFFFFFF)
            continue;

        // Page align starting address
        size_t diff = mmap->addr % PAGE_SIZE;
        if (diff)
        {
            klog("Unaligned page start, shifting up %llu bytes (%X) -> (%X)\n", PAGE_SIZE - diff, mmap->addr, mmap->addr + (PAGE_SIZE - diff));
            diff = PAGE_SIZE - diff;
            mmap->addr += diff;
            mmap->len -= diff;
        }

        // Page align end address
        diff = mmap->len % PAGE_SIZE;
        if (diff)
        {
            klog("Unaligned page end, shifting down %llu bytes (%X) -> (%X)\n", diff, mmap->len, mmap->len - diff);
            mmap->len -= diff;
        }

        // Not enough memory for any pages
        if (mmap->len < PAGE_SIZE)
        {
            klog("Not enough memory for page at %X, need %llu but got %llu", mmap->addr, PAGE_SIZE, mmap->len);
            continue;
        }

        for (uintptr_t page = mmap->addr; page != mmap->addr + mmap->len; page += PAGE_SIZE)
        {
            if (page < MB(6))
                continue;
            else if (page >= MB(6) && page < MB(7))
                process_page(&khead, &kcur, (void*)page);
            else if (page >= MB(7))
                process_page(&uhead, &ucur, (void*)page);
        }
    }

    generate_bitmap(khead);
    generate_bitmap(uhead);
}

void* get_page(region_t* node, size_t page)
{
    if (bit_status(node->bitmap, page))
    {
        node->last_allocd = page + 1;
        --node->free_pages;

        set_bit(node->bitmap, page);

        return node->start + (page * PAGE_SIZE);
    }

    return NULL;
}

void* pmm_kalloc(void)
{
    for (region_t* node = khead; node; node = node->next)
    {
        if (node->free_pages)
        {
            for (size_t i = node->last_allocd; i < node->total_pages - node->last_allocd; ++i)
            {
                void* page = get_page(node, i);
                if (page)
                    return page;
            }

            for (size_t i = 0; i < node->last_allocd; ++i)
            {
                void* page = get_page(node, i);
                if (page)
                    return page;
            }
        }
    }

    klog("Physical kernel page requested but none available:\n");
    enumerate(khead);
    panic();

    return NULL;
}

void pmm_kfree(void* page)
{
    // TODO: Assert page is a page aligned address

    for (region_t* node = khead; node; node = node->next)
    {
        if (page >= node->start && page < node->end)
        {
            const size_t bit = (((uintptr_t)page - (uintptr_t)node->start) / PAGE_SIZE);

            ++node->free_pages;
            node->last_allocd = bit;
            clear_bit(node->bitmap, bit);

            return;
        }
    }
}