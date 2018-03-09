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

#if __STDC_VERSION__ >= 199901L
	#include <stdint.h>
	typedef uintmax_t max_uint_t;
	uint32_t ntoh32(uint32_t const net);
#else
	typedef unsigned long max_uint_t;
#endif


#if __STDC_VERSION__ >= 201112L
	#include <time.h>
#endif

void sleep_ms(unsigned int milliseconds);

#if __STDC_VERSION__ >= 201112L
	struct timespec timespec_diff(const struct timespec* old_ts, const struct timespec* new_ts);
	struct timespec timespec_add(const struct timespec* ts_1, const struct timespec* ts_2);
	max_uint_t timespec_ms(const struct timespec* ts);
#endif

#endif /* MISC_H */
