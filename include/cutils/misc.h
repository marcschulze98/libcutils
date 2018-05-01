#ifndef CUTILS_MISC_H
#define CUTILS_MISC_H

#ifdef __unix__
	#ifndef _BSD_SOURCE
	#define _BSD_SOURCE 1
	#endif
	#ifndef _DEFAULT_SOURCE
	#define _DEFAULT_SOURCE 1
	#endif
	#include <unistd.h>
#endif
#ifdef _WIN32
	#include <windows.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <cutils/common.h>
#include <ctype.h>

typedef unsigned char byte;

#ifndef CUTILS_NO_SHORTHANDLES
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;
#endif /* CUTILS_NO_SHORTHANDLES */

#if __STDC_VERSION__ >= 199901L
	#ifdef UINT32_MAX
		uint32_t ntoh32(uint32_t const net);
	#endif
	HEDLEY_INLINE
	static void memqswap_stack(void* item1, void* item2, size_t length)
	{
		byte tmp[length];
		memcpy(tmp, item1, length);
		memcpy(item1, item2, length);
		memcpy(item2, tmp, length);
	}
#endif

HEDLEY_INLINE
static void memswap(void* item1, void* item2, size_t length)
{
	byte *item1_tmp, *item2_tmp;
	byte tmp;

	item1_tmp = item1;
	item2_tmp = item2;

	while(length--)
	{
		tmp = item1_tmp[length];
		item1_tmp[length] = item2_tmp[length];
		item2_tmp[length] = tmp;
	}
}

HEDLEY_INLINE
static void memqswap(void* item1, void* item2, void* tmp, size_t length)
{
	memcpy(tmp, item1, length);
	memcpy(item1, item2, length);
	memcpy(item2, tmp, length);
}

void sleep_ms(unsigned int milliseconds);

#if __STDC_VERSION__ >= 201112L
	#include <time.h>
	bool timespec_bigger(const struct timespec* ts1, const struct timespec* ts2);
	bool timespec_equal(const struct timespec* ts1, const struct timespec* ts2);
	bool timespec_smaller(const struct timespec* ts1, const struct timespec* ts2);
	/* subtracts ts2 from ts1, if ts2 > ts1 then zero is returned */
	struct timespec timespec_diff(const struct timespec* ts1, const struct timespec* ts2);
	struct timespec timespec_add(const struct timespec* ts_1, const struct timespec* ts_2);
	uintmax_t timespec_ms(const struct timespec* ts);
#endif

#endif /* CUTILS_MISC_H */
