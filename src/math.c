#include <cutils/math.h>

uintmax_t isqrt(uintmax_t n)
{
	uintmax_t start = 1, end = n/2, ans;
	if(n == 0 || n == 1)
		return n;

	while(start <= end)
	{
		uintmax_t mid = (start + end) / 2;

		if(mid*mid == n)
			return mid;

		if(mid*mid < n)
		{
			start = mid + 1;
			ans = mid;
		} else {
			end = mid - 1;
		}
	}
	return ans;
}

intmax_t ipow(intmax_t base, uintmax_t exp)
{
	intmax_t result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}

	return result;
}

bool is_prime(uintmax_t n)
{
	uintmax_t i;

	if (n < 2) return false;
	if (n % 2 == 0 && n != 2) return false;

	for(i = 3; i < isqrt(n); i+=2)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

static void primesieve_set(byte* numbers, size_t index)
{
	numbers[index/8] |= (byte)(1 << (index%8));
}

static bool primesieve_get(byte* numbers, size_t index)
{
	return getbit(byte, (numbers[index/8] >> index%8), 0);
}
#include <assert.h>
Bytearray* primesieve(uintmax_t limit)
{
	size_t i, j, length = limit/8+1;
	byte* numbers;
	Bytearray* bt;

	numbers = calloc(length, 1);
	if(!numbers)
		return NULL;

	bt = new_bytearray(sizeof(uintmax_t));
	if(!numbers)
	{
		free(numbers);
		return NULL;
	}


	for(i = 2; i < isqrt(limit); i++)
	{
		if(primesieve_get(numbers, i) == 0)
		{
			for(j = i*i; j < limit; j+=i)
			{
				primesieve_set(numbers, j);
			}
		}
	}

	for(i = 0; i < limit; i++)
	{
		if(primesieve_get(numbers, i) == 0)
			bytearray_push(bt, &i);
	}

	free(numbers);
	return bt;
}
