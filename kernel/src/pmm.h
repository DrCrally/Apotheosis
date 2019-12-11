#ifndef PMM_H
#define PMM_H

#include <stdbool.h>

#include "multiboot.h"

void pmm_init(multiboot_info_t* info);
void* pmm_kalloc(bool kernel);
void pmm_kfree(void* page);

#endif