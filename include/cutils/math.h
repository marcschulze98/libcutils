#ifndef CUTILS_MATH_H
#define CUTILS_MATH_H

#include <cutils/common.h>
#include <cutils/byte_array.h>
#include <cutils/bitfuncs.h>

uintmax_t isqrt(uintmax_t n);
intmax_t ipow(intmax_t base, uintmax_t exp);
bool is_prime(uintmax_t n);
Bytearray* primesieve(uintmax_t limit);



#endif /* CUTILS_MATH_H */

