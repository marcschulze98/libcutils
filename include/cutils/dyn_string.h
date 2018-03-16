#ifndef DYN_STRING_H
#define DYN_STRING_H

#define STRING_DEFAULT_SIZE 8

#include <stdlib.h>
#include <string.h>
#include <cutils/common.h>

typedef struct String
{
	char* chars;
	size_t capacity;
	size_t length;
} String;

#define new_string() string_with_capacity(STRING_DEFAULT_SIZE)
String* string_with_capacity(size_t capacity);
void delete_string(String* string);

char string_at(const String* string, size_t index);
#define string_pop(string) string_pop_at(string, string->length-1)
char string_pop_at(String* string, size_t index);

bool string_insert(String* string, size_t index, char character);
#define string_push(string, character) string_insert(string, string->length, character)

void string_remove(String* string, size_t index);
void string_remove_range(String* string, size_t index, size_t length);

bool string_adjust_size(String* string, size_t size);
size_t* string_find_char(const String* haystack, const char needle);
size_t* string_find_str(const String* haystack, const String* needle);

bool string_concat(String* string, const String* other);

String* from_cstring(const char* cstring);
String* from_cstring_del(char* cstring);
char* to_cstring(const String* string);
char* to_cstring_del(String* string);


#endif /* DYN_STRING_H */
