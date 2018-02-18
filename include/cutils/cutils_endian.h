#ifndef CUTILS_ENDIAN_H
#define CUTILS_ENDIAN_H
#include <stdint.h>
#include <string.h>

inline uint32_t ntoh32(uint32_t const net)
{
	uint8_t data[4];
	memcpy(&data, &net, sizeof(data));

	return ((uint32_t) data[3] << 0)
	     | ((uint32_t) data[2] << 8)
	     | ((uint32_t) data[1] << 16)
	     | ((uint32_t) data[0] << 24);
}

#endif //CUTILS_ENDIAN_H
