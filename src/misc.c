#include <cutils/misc.h>

void sleep_ms(unsigned int milliseconds)
{
    #ifdef __unix__
		usleep(milliseconds * 1000);
	#endif
	#ifdef _WIN32
		Sleep(milliseconds);
	#endif
}

#if __STDC_VERSION__ >= 199901L
#ifdef UINT32_MAX
uint32_t ntoh32(uint32_t const net)
{
	uint8_t data[4];
	memcpy(&data, &net, sizeof(data));

	return ((uint32_t) data[3] << 0)
	     | ((uint32_t) data[2] << 8)
	     | ((uint32_t) data[1] << 16)
	     | ((uint32_t) data[0] << 24);
}
#endif
#endif

#if __STDC_VERSION__ >= 201112L

bool timespec_bigger(const struct timespec* ts1, const struct timespec* ts2)
{
	if(ts1->tv_sec > ts2->tv_sec)
	{
		return true;
	} else if(ts1->tv_sec < ts2->tv_sec) {
		return false;
	} else {
		if(ts1->tv_nsec > ts2->tv_nsec)
		{
			return true;
		} else if(ts1->tv_nsec < ts2->tv_nsec) {
			return false;
		} else {
			return false;
		}
	}
}

bool timespec_equal(const struct timespec* ts1, const struct timespec* ts2)
{
	if(ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec == ts2->tv_nsec)
	{
		return true;
	} else {
		return false;
	}
}

bool timespec_smaller(const struct timespec* ts1, const struct timespec* ts2)
{
	if(timespec_equal(ts1, ts2))
	{
		return false;
	} else if(timespec_bigger(ts1, ts2)) {
		return false;
	} else {
		return true;
	}
}

struct timespec timespec_diff(const struct timespec* ts1, const struct timespec* ts2)
{
	struct timespec result;

	if((ts1->tv_sec < ts2->tv_sec) ||
	  ((ts1->tv_sec == ts2->tv_sec) &&
	  (ts1->tv_nsec <= ts2->tv_nsec)))
	{
		result.tv_sec = result.tv_nsec = 0 ;
	} else {
		result.tv_sec = ts1->tv_sec - ts2->tv_sec ;
		if (ts1->tv_nsec < ts2->tv_nsec) {
			result.tv_nsec = ts1->tv_nsec + 1000000000L - ts2->tv_nsec ;
			result.tv_sec-- ;
		} else {
			result.tv_nsec = ts1->tv_nsec - ts2->tv_nsec ;
		}
	}

	return result;

}

struct timespec timespec_add(const struct timespec* ts_1, const struct timespec* ts_2)
{
	struct timespec res;

    if (999999999 - ts_1->tv_nsec < ts_2->tv_nsec)
    {
        res.tv_sec = ts_1->tv_sec + ts_2->tv_sec + 1;
        res.tv_nsec = ts_1->tv_nsec + (ts_2->tv_nsec - 1000000000) ;
    } else {
        res.tv_sec = ts_1->tv_sec + ts_2->tv_sec;
        res.tv_nsec = ts_1->tv_nsec + ts_2->tv_nsec;
    }

    return res;
}


uintmax_t timespec_ms(const struct timespec* ts)
{
	return (uintmax_t)ts->tv_sec * 1000 + (uintmax_t)ts->tv_nsec/1000000;
}
#endif
