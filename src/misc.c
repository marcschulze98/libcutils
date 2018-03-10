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
struct timespec timespec_diff(const struct timespec* old_ts, const struct timespec* new_ts)
{
	struct timespec diff;

    if ((new_ts->tv_nsec - old_ts->tv_nsec) < 0)
    {
        diff.tv_sec = new_ts->tv_sec - old_ts->tv_sec - 1;
        diff.tv_nsec = new_ts->tv_nsec - old_ts->tv_nsec + 1000000000;
    } else {
        diff.tv_sec = new_ts->tv_sec - old_ts->tv_sec;
        diff.tv_nsec = new_ts->tv_nsec - old_ts->tv_nsec;
    }

    return diff;
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


max_uint_t timespec_ms(const struct timespec* ts)
{
	return (max_uint_t)ts->tv_sec * 1000 + (max_uint_t)ts->tv_nsec/1000000;
}
#endif
