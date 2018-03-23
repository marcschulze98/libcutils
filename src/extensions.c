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

size_t cutil_strnlen(const char *s, size_t maxlen)
{
	size_t len;

	for(len = 0; len < maxlen; len++, s++)
	{
		if (!*s)
			break;
	}
	return (len);
}

char* cutil_strdup(const char *s)
{
	char* ret;
	size_t len = strlen(s);

	ret = malloc(len+1);
	memcpy(ret, s, len+1);

	return ret;
}

char* cutil_strndup(const char *s, size_t n)
{
	char* ret;
	size_t len = cutil_strnlen(s, n);

	len = len <= n ? len : n;

	ret = malloc(len+1);
	memcpy(ret, s, len+1);

	return ret;
}

bool cutil_memmem(const void* haystack, size_t haystacklen, const void* needle, size_t needlelen, size_t* pos)
{
	size_t i, j, tmp;
	const byte* haystackb = haystack;
	const byte* needleb = needle;


	if (haystacklen == 0 || needlelen == 0)
		return false;

	for(i = 0; i < haystacklen; i++)
	{
		for(j = 0, tmp = i; j < needlelen && i < haystacklen; j++, i++)
		{
			if(haystackb[i] != needleb[j])
			{
				break;
			} else if(j == needlelen-1){
				*pos = tmp;
				return true;
			}
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

	va_start(ap, format);
	ret = snprintf(*strp, needed, format, ap);
	va_end(ap);

	return ret;
}
#endif
