#ifndef MISC_H
#define MISC_H

#ifdef __unix__
	#define _BSD_SOURCE
	#define _DEFAULT_SOURCE
	#include <unistd.h>
#endif
#ifdef _WIN32
	#include <windows.h>
#endif

#include <stdint.h>
#include <string.h>

void sleep_ms(unsigned int milliseconds);
uint32_t ntoh32(uint32_t const net);

#endif /* MISC_H */
