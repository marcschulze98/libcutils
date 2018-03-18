#include <cutils/extensions.h>

int strcmp_nocase(const char* s1, const char* s2)
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

int strncmp_nocase(const char* s1, const char* s2, size_t n)
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
