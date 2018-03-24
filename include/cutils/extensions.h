#ifndef CUTILS_EXTENSIONS_H
#define CUTILS_EXTENSIONS_H

#include <cutils/hedley.h>
#include <errno.h>
#include <stdlib.h>
#include <cutils/backport.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <cutils/common.h>

int cutil_strcasecmp(const char* s1, const char* s2);
int cutil_strncasecmp(const char* s1, const char* s2, size_t n);

size_t cutil_strnlen(const char *s, size_t maxlen);

char* cutil_strdup(const char *s);
char* cutil_strndup(const char *s, size_t n);

bool cutil_memmem(const void* haystack, size_t haystacklen, const void* needle, size_t needlelen, size_t* pos);

#if __STDC_VERSION__ >= 199901L
int cutil_asprintf(char** strp, const char* format, ...);
#endif

HEDLEY_INLINE
static void* cutil_reallocarray(void *ptr, size_t nmemb, size_t size)
{
	size_t new_size = nmemb * size;

	if(nmemb != 0 && new_size / nmemb != size)
	{
		errno = ENOMEM;
		return NULL;
	} else {
		return realloc(ptr, new_size);
	}
}

HEDLEY_INLINE
static void* cutil_reallocarray_inc(void *ptr, size_t nmemb, size_t size, size_t add)
{
	if(SIZE_MAX - add < size)
	{
		errno = ENOMEM;
		return NULL;
	} else {
		return cutil_reallocarray(ptr, nmemb+add, size);
	}
}



#endif /* CUTILS_EXTENSIONS_H */
