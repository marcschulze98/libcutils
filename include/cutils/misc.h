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
#include <stdarg.h>

typedef unsigned char byte;

#ifndef CUTILS_NO_SHORTHANDLES
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
#ifdef ULLONG_MAX
typedef unsigned long long ullong;
#endif /* ULLONG_MAX */
#endif /* CUTILS_NO_SHORTHANDLES */

#define CUTIL_MAX(x,y) ((x) > (y) ? (x) : (y))
#define CUTIL_MIN(x,y) ((x) < (y) ? (x) : (y))
#define CUTIL_LOOP while(1)
#define CUTIL_RANGE(i, start, end)                                     \
for(((i) = (start)); ((start) < (end)) ? ((i) < (end)) : ((i) > (end)); ((start) < (end)) ? (i++) : (i--))
#define CUTIL_NEW(type) (malloc(sizeof(type)))
#define CUTIL_NEW_N(type, n) (malloc(n * sizeof(type)))

#ifndef CUTILS_NO_MACROS
#define MAX(x,y) CUTIL_MAX(x,y)
#define MIN(x,y) CUTIL_MIN(x,y)
#define LOOP CUTIL_LOOP
#define RANGE(i, start, end) CUTIL_RANGE(i, start, end)
#define NEW(type) CUTIL_NEW(type)
#define NEW_N(type, n) CUTIL_NEW_N(type, n)
#endif /* CUTILS_NO_MACROS */

#ifdef DEBUG
	#define DEBUG_ASSERT(x) assert(x)
#else
	#define DEBUG_ASSERT(x)
#endif /* DEBUG */


#if __STDC_VERSION__ >= 199901L
	#ifdef UINT64_MAX

	enum endianess {CUTIL_ENDIAN_ERROR = 0, CUTIL_BIG_ENDIAN = 1, CUTIL_LITTLE_ENDIAN = 2, CUTIL_MID_BIG_ENDIAN = 3, CUTIL_MID_LITTLE_ENDIAN = 4};
	static const char** endianess_strings = (const char *[]){"ENDIAN_ERROR","BIG_ENDIAN","LITTLE_ENDIAN","MID_BIG_ENDIAN","MID_LITTLE_ENDIAN"};
	HEDLEY_INLINE
	static enum endianess check_endianess(void)
	{
		union
		{
			uint32_t t1;
			uint8_t t2[4];
		} test;
		test.t1 = 255;

		if(test.t2[0] == 255)
		{
			return CUTIL_LITTLE_ENDIAN;
		} else if(test.t2[1] == 255) {
			return CUTIL_MID_LITTLE_ENDIAN;
		} else if(test.t2[2] == 255) {
			return CUTIL_MID_BIG_ENDIAN;
		} else if(test.t2[3] == 255) {
			return CUTIL_BIG_ENDIAN;
		} else {
			return CUTIL_ENDIAN_ERROR;
		}
	}

	HEDLEY_INLINE
	static uint64_t nethost64(uint64_t const from)
	{
		uint8_t data[4];
		memcpy(&data, &from, sizeof(data));

		return ((uint64_t) data[7] << 0)
		     | ((uint64_t) data[6] << 8)
		     | ((uint64_t) data[5] << 16)
		     | ((uint64_t) data[4] << 24)
		     | ((uint64_t) data[3] << 32)
		     | ((uint64_t) data[2] << 40)
		     | ((uint64_t) data[1] << 48)
		     | ((uint64_t) data[0] << 54);
	}
	#endif
	#ifdef UINT32_MAX
	HEDLEY_INLINE
	static uint32_t nethost32(uint32_t const from)
	{
		uint8_t data[4];
		memcpy(&data, &from, sizeof(data));

		return ((uint32_t) data[3] << 0)
		     | ((uint32_t) data[2] << 8)
		     | ((uint32_t) data[1] << 16)
		     | ((uint32_t) data[0] << 24);
	}
	#endif
	#ifdef UINT16_MAX
	HEDLEY_INLINE
	static uint16_t nethost16(uint16_t const from)
	{
		uint8_t data[2];
		memcpy(&data, &from, sizeof(data));

		return (uint16_t)(
		       ((uint16_t) data[1] << 0)
		     | ((uint16_t) data[0] << 8));
	}
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
	HEDLEY_INLINE
	static uintmax_t timespec_ms(const struct timespec* ts)
	{
		return (uintmax_t)ts->tv_sec * 1000 + (uintmax_t)ts->tv_nsec/1000000;
	}
#endif

#endif /* CUTILS_MISC_H */
