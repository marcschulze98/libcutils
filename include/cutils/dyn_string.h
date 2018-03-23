#ifndef CUTILS_DYN_STRING_H
#define CUTILS_DYN_STRING_H

#define STRING_DEFAULT_SIZE 8

#include <stdlib.h>
#include <string.h>
#include <cutils/common.h>

typedef struct String
{
	char* chars;
	size_t capacity;
	size_t length;
	bool null_terminated;
} String;

#define new_string(null_terminated) string_with_capacity(STRING_DEFAULT_SIZE, null_terminated)
String* string_with_capacity(size_t capacity, bool null_terminated);
void delete_string(String* string);

HEDLEY_INLINE
static char string_at(const String* string, size_t index)
{
	return string->chars[index];
}

#define string_pop(string) string_pop_at(string, string->length-1)
char string_pop_at(String* string, size_t index);

bool string_insert(String* string, size_t index, char character);
#define string_push(string, character) string_insert(string, string->length, character)

HEDLEY_INLINE
static void string_remove(String* string, size_t index)
{
	if(index < string->length)
	{
		memmove(string->chars+index, string->chars+index+1, (string->length-index-1+(string->null_terminated?1:0))*sizeof(*string->chars));
		string->length--;
	}
}
void string_remove_range(String* string, size_t index, size_t length);
size_t string_strip(String* string, char character);

bool string_grow(String* string, size_t add);
bool string_adjust_size(String* string, size_t size);
bool string_find_char(const String* haystack, const char needle, size_t* pos);
HEDLEY_INLINE
static bool string_find_str(const String* haystack, const String* needle, size_t* pos)
{
	return cutil_memmem(haystack->chars, haystack->length, needle->chars, needle->length, pos);
}
HEDLEY_INLINE
static int string_cmp(const String* s1, const String* s2)
{
	return memcmp(s1->chars, s2->chars, s1->length);
}

size_t string_count(const String* string, char character);

bool string_concat(String* string, const String* other);

String* from_cstring(const char* cstring, bool null_terminated);
String* from_cstring_reuse(char* cstring, size_t capacity, bool null_terminated);
String* from_cstring_del(char* cstring, bool null_terminated);
char* to_cstring(const String* string);
char* to_cstring_del(String* string);
void string_move(String* dest, String* src);

#endif /* CUTILS_DYN_STRING_H */
