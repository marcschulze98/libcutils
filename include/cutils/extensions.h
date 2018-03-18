#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <cutils/hedley.h>
#include <errno.h>
#include <stdlib.h>
#include <cutils/backport.h>
#include <string.h>
#include <ctype.h>

int strcmp_nocase(const char* s1, const char* s2);
int strncmp_nocase(const char* s1, const char* s2, size_t n);

HEDLEY_INLINE
static void* reallocsafe(void *ptr, size_t nmemb, size_t size)
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
static void* reallocsafe_inc(void *ptr, size_t nmemb, size_t size, size_t add)
{
	if(SIZE_MAX - add < size)
	{
		errno = ENOMEM;
		return NULL;
	} else {
		return reallocsafe(ptr, nmemb, size+add);
	}
}



#endif /* EXTENSIONS_H */
