#ifndef CUTILS_BITFUNCS_H
#define CUTILS_BITFUNCS_H

#include <stdlib.h>
#include <cutils/common.h>

#define numbits(type) (sizeof(type)*CHAR_BIT)
#define numbytes(type) (sizeof(type))

#define getbit(value, bit) (((value) >> (bit)) & 1)

#define setbit(value, bit) ((value) |= ((uintmax_t)1 << (bit)))
#define clearbit(value, bit) ((value) &= ~((uintmax_t)1 << (bit)))

#define setbitc(value, bit, type) ((value) |= ((type)1 << (bit)))
#define clearbitc(value, bit, type) ((value) &= ~((type)1 << (bit)))

#endif /* CUTILS_BITFUNCS_H */
