#ifndef BITMAP_H
#define BITMAP_H

#include <stdbool.h>
#include <stdint.h>

static inline bool bit_status(uint8_t* bitmap, size_t bit)
{
    return !(bitmap[bit / 8] & (1u << (bit % 8)));
}

static inline void set_bit(uint8_t* bitmap, size_t bit)
{
    bitmap[bit / 8] |= (1u << (bit % 8));
}

static inline void clear_bit(uint8_t* bitmap, size_t bit)
{
    bitmap[bit / 8] &= ~(1u << (bit % 8));
}

#endif