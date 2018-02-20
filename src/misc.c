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

uint32_t ntoh32(uint32_t const net)
{
	uint8_t data[4];
	memcpy(&data, &net, sizeof(data));

	return ((uint32_t) data[3] << 0)
	     | ((uint32_t) data[2] << 8)
	     | ((uint32_t) data[1] << 16)
	     | ((uint32_t) data[0] << 24);
}
