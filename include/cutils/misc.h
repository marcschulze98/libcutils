#ifndef MISC_H
#define MISC_H
#include <stdint.h>
#include <string.h>

#ifdef __unix__
	#include <unistd.h>
#endif
#ifdef _WIN32
	#include <windows.h>
#endif

void sleep_ms(unsigned int milliseconds);
uint32_t ntoh32(uint32_t const net);
#endif //MISC_H
