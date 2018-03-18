#ifndef MISC_H
#define MISC_H

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

#if __STDC_VERSION__ >= 199901L
	#ifdef UINT32_MAX
		uint32_t ntoh32(uint32_t const net);
	#endif
	HEDLEY_INLINE
	static void memqswap_stack(void* item1, void* item2, size_t length)
	{
		unsigned char tmp[length];
		memcpy(tmp, item1, length);
		memcpy(item1, item2, length);
		memcpy(item2, tmp, length);
		free(tmp);
	}
#endif

HEDLEY_INLINE
static void memswap(void* item1, void* item2, size_t length)
{
	unsigned char *item1_tmp, *item2_tmp;
	unsigned char tmp;

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

#if __STDC_VERSION__ >= 201112L
	#include <time.h>
#endif

void sleep_ms(unsigned int milliseconds);

#if __STDC_VERSION__ >= 201112L
	struct timespec timespec_diff(const struct timespec* old_ts, const struct timespec* new_ts);
	struct timespec timespec_add(const struct timespec* ts_1, const struct timespec* ts_2);
	uintmax_t timespec_ms(const struct timespec* ts);
#endif

#endif /* MISC_H */
