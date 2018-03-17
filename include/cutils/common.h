#ifndef CUTILS_COMMON_H
#define CUTILS_COMMON_H

#include <stddef.h>
#include <cutils/hedley.h>
#ifndef SIZE_MAX
	#define SIZE_MAX ((size_t)(-1))
#endif

#if __STDC_VERSION__ >= 199901L
	#include <stdbool.h>
#else
	#ifndef CUTILS_NO_BOOL
	typedef enum {false = 0, true = 1} bool;
	#endif
#endif


#endif /* CUTILS_COMMON_H */
