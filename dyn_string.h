#ifndef DYN_STRING_H
#define DYN_STRING_H
#define STRING_DEFAULT_SIZE 8
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct String
{
	char* chars;
	size_t capacity;
	size_t length;
} String;

String* new_string(void);
char string_at(const String* string, size_t index);
bool string_append(String* string, char item);
void string_remove(String* string, size_t index);
bool string_adjust_size(String* string, size_t size);
size_t* string_find_char(const String* haystack, const char needle);
bool string_insert(String* string, size_t index, char character);
bool string_concat(String* string, String* other);


#endif //DYN_STRING_H
