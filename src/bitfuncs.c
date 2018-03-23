#include <cutils/bitfuncs.h>

char* _bitstring(size_t size, uintmax_t value)
{
	char* ret = NULL;
	size_t i, pos;

	bool leading_zero = true;
	for(i = 1, pos = 0; i <= size; i++)
	{
		byte tmp =  (byte)((value & ((uintmax_t)1 << (size-i))) >> (size-i));
		if(tmp && leading_zero)
		{
			leading_zero = false;
			ret = malloc(size-i);
			if(!ret)
				return NULL;
			ret[size-i-1] = '\0';
		}
		if(!leading_zero)
			ret[pos++] = tmp ? '1' : '0';
	}
	return ret;
}
