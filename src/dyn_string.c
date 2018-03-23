#include <cutils/dyn_string.h>

String* string_with_capacity(size_t capacity)
{
	String* string = malloc(sizeof(*string));
	if(!string)
		return NULL;
	string->chars = calloc(capacity,sizeof(*string->chars));
	if(!string->chars)
	{
		free(string);
		return NULL;
	}
	string->length = 0;
	string->capacity = capacity;

	return string;
}

void string_remove_range(String* string, size_t index, size_t length)
{
	memmove(string->chars+index, string->chars+index+length, (string->length-(index+length)));
	string->length -= length;
}

size_t string_strip(String* string, char character)
{
	size_t i, last = 0, offset = 0;
	bool first = true;

	for(i = 0; i < string->length; i++)
	{
		if(string_at(string,i) == character)
		{
			if(first)
			{
				first = false;
			} else {
				memmove(string->chars+last-offset, string->chars+last+1, i-last-1);
				offset++;
			}

			last = i;
		}
	}

	memmove(string->chars+last-offset, string->chars+last+1, string->length-last-1);

	string->length -= offset+(first ? 0 : 1);
	return offset;
}

bool string_insert(String* string, size_t index, char character)
{
	if(index > string->length || string->length == SIZE_MAX || !string_adjust_size(string, string->length))
		return false;

	memmove(string->chars+index+1, string->chars+index, (string->length-index)*sizeof(*string->chars));
	string->chars[index] = character;
	string->length++;
	return true;
}

char string_pop_at(String* string, size_t index)
{
	char tmp = string_at(string, index);
	if(!tmp)
	{
		return '\0';
	} else {
		string_remove(string, index);
		return tmp;
	}
}

bool string_concat(String* string, const String* other)
{
	if(!string_adjust_size(string,string->length+other->length-1))
		return false;
	memcpy(string->chars+string->length,other->chars,other->length);
	string->length += other->length;
	return true;
}

bool string_find_char(const String* haystack, const char needle, size_t* pos)
{
	size_t i;

	for(i = 0; i < haystack->length; i++)
	{
		if(haystack->chars[i] == needle)
		{
			*pos = i;
			return true;
		}
	}
	return false;
}

size_t string_count(const String* string, char character)
{
	size_t i, ret = 0;
	for(i = 0; i < string->length; i++)
	{
		if(string_at(string, i) == character)
			ret++;
	}
	return ret;
}

bool string_adjust_size(String* string, size_t size)
{
	while(string->capacity < size)
	{
		char* tmp = string->chars;
		string->chars = cutil_reallocarray_inc(string->chars, sizeof(*string->chars), string->capacity, string->capacity);
		if(!string->chars)
		{
			string->chars = tmp;
			return false;
		}
		string->capacity *= 2;
	}
	return true;
}


void delete_string(String* string)
{
	free(string->chars);
	free(string);
}

String* from_cstring(const char* cstring)
{
	String* string = string_with_capacity(strlen(cstring));
	if(!string)
	{
		return NULL;
	} else {
		memcpy(string->chars, cstring, strlen(cstring));
		string->length = strlen(cstring);
		return string;
	}
}

String* from_cstring_reuse(char* cstring, size_t capacity)
{
	String* string;

	if(cstring)
		return NULL;

	string = malloc(sizeof(*string));
	if(!string)
		return NULL;

	string->length = strlen(cstring);
	string->capacity = capacity;

	return string;
}

String* from_cstring_del(char* cstring)
{
	String* ret = from_cstring(cstring);
	free(cstring);
	return ret;
}

char* to_cstring(const String* string)
{
	char* cstring = malloc(string->length+1);
	memcpy(cstring, string->chars, string->length);
	cstring[string->length] = '\0';

	return cstring;
}

char* to_cstring_del(String* string)
{
	char* ret = to_cstring(string);
	delete_string(string);
	return ret;
}

void string_move(String* dest, String* src)
{
	free(dest->chars);
	dest->chars = src->chars;
	free(src);
}
