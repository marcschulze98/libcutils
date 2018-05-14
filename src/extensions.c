#include <cutils/extensions.h>

int cutil_strcasecmp(const char* s1, const char* s2)
{
	const unsigned char* p1 = (const unsigned char*)s1;
	const unsigned char* p2 = (const unsigned char*)s2;
	unsigned char c1, c2;

	do
	{
		c1 = (unsigned char)tolower(*p1++);
		c2 = (unsigned char)tolower(*p2++);
		if (c1 == '\0')
			return c1 - c2;
	}
	while (c1 == c2);

	return c1 - c2;
}

int cutil_strncasecmp(const char* s1, const char* s2, size_t n)
{
	const unsigned char* p1 = (const unsigned char*)s1;
	const unsigned char* p2 = (const unsigned char*)s2;
	unsigned char c1, c2;

	if(n == 0)
		return 0;

	do
	{
		c1 = (unsigned char)tolower(*p1++);
		c2 = (unsigned char)tolower(*p2++);
		if (c1 == '\0')
			return c1 - c2;
	}
	while (c1 == c2 && --n);

	return c1 - c2;
}

size_t cutil_strnlen(const char* s, size_t maxlen)
{
	size_t len;

	for(len = 0; len < maxlen; len++, s++)
	{
		if (!*s)
			break;
	}
	return (len);
}

char* cutil_strndup(const char* s, size_t n)
{
	char* ret;
	size_t len = cutil_strnlen(s, n);

	len = CUTIL_MIN(len, n);

	ret = malloc(len+1);
	if(!ret)
		return NULL;
	memcpy(ret, s, len+1);

	return ret;
}

bool cutil_memmem(const void* haystack, size_t haystacklen, const void* needle, size_t needlelen, size_t* pos)
{
	size_t newoffset, offset = 0, i, j;
	const byte* haystackb = haystack;
	const byte* needleb = needle;
	byte* start;
	bool newoffset_set = false;

	if(needlelen == 0)
	{
		*pos = 0;
		return true;
	}

	if(HEDLEY_UNLIKELY((haystacklen == 0 && needlelen > 0 )|| haystacklen < needlelen))
		return false;

	CUTIL_LOOP
	{
		start = memchr(haystackb+offset, needleb[0], haystacklen-offset);
		if(!start)
		{
			return false;
		} else if(needlelen == 1) {
			*pos = (size_t)(start-haystackb);
			return true;
		}

		for(i = (size_t)(start-haystackb+1), j = 1; i < haystacklen && j < needlelen; i++, j++)
		{
			if(!newoffset_set && haystackb[i] == needleb[0])
			{
				newoffset = i;
				newoffset_set = true;
			}

			if(haystackb[i] != needleb[j])
			{
				break;
			} else if(j == needlelen-1) {
				*pos = (size_t)(start-haystackb);
				return true;
			}
		}

		if(newoffset_set)
		{
			offset = newoffset;
			newoffset_set = false;
		} else {
			offset = i;
		}
	}


	return false;
}

#if __STDC_VERSION__ >= 199901L
int cutil_asprintf(char** strp, const char* format, ...)
{
	va_list ap;
	size_t needed;
	int ret;

	va_start(ap, format);
	needed = (size_t)vsnprintf(NULL, 0, format, ap);
	va_end(ap);

	*strp = malloc(needed);

	if(!*strp)
		return -1;

	va_start(ap, format);
	ret = snprintf(*strp, needed, format, ap);
	va_end(ap);

	return ret;
}
#endif
