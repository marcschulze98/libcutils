#ifndef BACKPORT_H
#define BACKPORT_H

#include <limits.h>
#if __STDC_VERSION__ >= 199901L
	#include <stdint.h>
	#include <stdbool.h>
#else

	#ifndef SIZE_MAX
		#define SIZE_MAX ((size_t)-1)
	#endif /* SIZE_MAX */

	#ifndef CUTILS_NO_BOOL
		typedef enum {false = 0, true = !false} bool;
	#endif /* CUTILS_NO_BOOL */

	#ifndef CUTILS_NO_MAX
		#ifdef ULLONG_MAX
			#define UINTMAX_MAX ULLONG_MAX
			typedef unsigned long long uintmax_t;
		#else
			#define UINTMAX_MAX ULONG_MAX
			typedef unsigned long uintmax_t;
		#endif
		#ifdef LLONG_MAX
			#define INTMAX_MAX LLONG_MAX
			#define INTMAX_MIN LLONG_MIN
			typedef long long intmax_t;
		#else
			#define INTMAX_MAX LONG_MAX
			#define INTMAX_MIN LONG_MIN
			typedef long intmax_t;
		#endif
	#endif /* CUTILS_NO_MAX */

	#ifndef CUTILS_NO_LEAST
		#define UINTLEAST8_MAX UCHAR_MAX
		typedef unsigned char uint_least8_t;
		#define UINT8_C(x) ((uint_least8_t)x)

		#define UINTLEAST16_MAX USHRT_MAX
		typedef unsigned short uint_least16_t;
		#define UINT16_C(x) ((uint_least16_t)x)

		#define UINTLEAST32_MAX ULONG_MAX
		typedef unsigned long uint_least32_t;
		#define UINT32_C(x) ((uint_least32_t)x)

		#ifdef ULLONG_MAX
		#define UINTLEAST64_MAX ULLONG_MAX
		typedef unsigned long long uint_least64_t;
		#define UINT64_C(x) ((uint_least64_t)x)
		#endif /* ULLONG_MAX */


		#define INTLEAST8_MAX SCHAR_MAX
		#define INTLEAST8_MIN SCHAR_MIN
		typedef signed char int_least8_t;
		#define INT8_C(x) ((int_least8_t)x)

		#define INTLEAST16_MAX SHRT_MAX
		#define INTLEAST16_MIN SHRT_MIN
		typedef short int_least16_t;
		#define INT16_C(x) ((int_least16_t)x)

		#define INTLEAST32_MAX LONG_MAX
		#define INTLEAST32_MIN LONG_MIN
		typedef long int_least32_t;
		#define INT32_C(x) ((int_least32_t)x)

		#ifdef LLONG_MAX
		#define INTLEAST64_MAX LLONG_MAX
		#define INTLEAST64_MIN LLONG_MIN
		typedef long long int_least64_t;
		#define INT64_C(x) ((int_least64_t)x)
		#endif /* LLONG_MAX */
	#endif /* CUTILS_NO_LEAST */

	/* for now just copy least types */
	#ifndef CUTILS_NO_FAST
		#define UINTFAST8_MAX UCHAR_MAX
		typedef unsigned char uint_fast8_t;

		#define UINTFAST16_MAX USHRT_MAX
		typedef unsigned short uint_fast16_t;

		#define UINTFAST32_MAX ULONG_MAX
		typedef unsigned long uint_fast32_t;

		#ifdef ULLONG_MAX
		#define UINTFAST64_MAX ULLONG_MAX
		typedef unsigned long long uint_fast64_t;
		#endif /* ULLONG_MAX */


		#define INTFAST8_MAX SCHAR_MAX
		#define INTFAST8_MIN SCHAR_MIN
		typedef signed char int_fast8_t;

		#define INTFAST16_MAX SHRT_MAX
		#define INTFAST16_MIN SHRT_MIN
		typedef short int_fast16_t;

		#define INTFAST32_MAX LONG_MAX
		#define INTFAST32_MIN LONG_MIN
		typedef long int_fast32_t;

		#ifdef LLONG_MAX
		#define INTFAST64_MAX LLONG_MAX
		#define INTFAST64_MIN LLONG_MIN
		typedef long long int_fast64_t;
		#endif /* LLONG_MAX */
	#endif /* CUTILS_NO_FAST */

#endif


#endif /* BACKPORT_H */
