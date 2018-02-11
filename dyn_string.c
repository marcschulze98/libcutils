#include "dyn_string.h"

String* new_string(void)
{
	String* string = malloc(sizeof(*string));
	if(!string)
		return NULL;
	string->chars = calloc(sizeof(*string->chars)*STRING_DEFAULT_SIZE,1);
	if(!string->chars)
	{
		free(string);
		return NULL;
	}
	string->length = 0;
	string->capacity = STRING_DEFAULT_SIZE;

	return string;
}

bool string_append(String* string, char character)
{
	if(!string_adjust_size(string, ++string->length))
		return false;
	string->chars[string->length-1] = character;
	return true;
}

void string_remove(String* string, size_t index)
{
	if(index < string->length)
	{
		memmove(string->chars+index, string->chars+index+1, (string->length-index-1)*sizeof(*string->chars));
		string->length--;
	}
}

bool string_insert(String* string, size_t index, char character)
{
	if(!string_adjust_size(string, string->length))
		return false;

	memmove(string->chars+index+1, string->chars+index, (string->length-index)*sizeof(*string->chars));
	string->chars[index] = character;
	string->length++;
	return true;
}

char string_at(const String* string, size_t index)
{
	if(index >= string->length)
		return '\0';
	else
		return string->chars[index];
}

bool string_concat(String* string, String* other)
{
	if(!string_adjust_size(string,string->length+other->length-1))
		return false;
	memcpy(string->chars+string->length,other->chars,other->length);
	return true;
}

FindReturn string_find_char(const String* haystack, const char needle)
{
	FindReturn ret;
	for(size_t i = 0; i < haystack->length; i++)
	{
		if(haystack->chars[i] == needle)
		{
			ret.found = true;
			ret.index = i;
			return ret;
		}
	}
	ret.found = false;
	return ret;
}

bool string_adjust_size(String* string, size_t size)
{
	while(string->capacity < size)
	{
		char* tmp = string->chars;
		string->chars = realloc(string->chars, string->capacity*2*(sizeof(*string->chars)));
		if(!string->chars)
		{
			string->chars = tmp;
			return false;
		}
		string->capacity *= 2;
	}
	while(string->capacity > (size*2))
	{
		char* tmp = string->chars;
		string->chars = realloc(string->chars, string->capacity/2*(sizeof(*string->chars)));
		if(!string->chars)
		{
			string->chars = tmp;
			return false;
		}
		string->capacity /= 2;
	}
	return true;
}
