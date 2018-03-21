#ifndef CUTILS_BITFUNCS_H
#define CUTILS_BITFUNCS_H

#include <stdlib.h>
#include <cutils/common.h>

#define numbits(type) (sizeof(type)*CHAR_BIT)

#define bitstring(type, value) _bitstring(numbits(type), (type)(value))
/* FIXME: fix out of range calls (bitstring(unsigned char, 256)) */
char* _bitstring(size_t size, uintmax_t value);

#define getbit(type, value, bit) (((value) & (((type)1 << (bit)))) >> (bit))
#define setbit(type, value, bit) ((value) |= ((type)1 << (bit)))
#define clearbit(type, value, bit) ((value) &= (type)~((type)1 << (bit)))

#endif /* CUTILS_BITFUNCS_H */
