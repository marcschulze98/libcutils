#include <cutils/dyn_string.h>

String* string_with_capacity(size_t capacity, bool null_terminated)
{
	String* string = malloc(sizeof(*string));
	if(!string)
		return NULL;
	string->chars = malloc(capacity+(null_terminated?1:0));
	if(!string->chars)
	{
		free(string);
		return NULL;
	}
	if(null_terminated)
		string->chars[0] = '\0';
	string->length = 0;
	string->capacity = capacity;
	string->null_terminated = null_terminated;

	return string;
}

void string_remove_range(String* string, size_t index, size_t length)
{
	memmove(string->chars+index, string->chars+index+length, (string->length-(index+length)+(string->null_terminated?1:0)));
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

	memmove(string->chars+last-offset, string->chars+last+1, string->length-last-1+(string->null_terminated?1:0));

	string->length -= offset+(first ? 0 : 1);
	return offset;
}

bool string_insert(String* string, size_t index, char character)
{
	if(index > string->length || !string_grow(string, 1))
		return false;

	memmove(string->chars+index+1, string->chars+index, (string->length-index+(string->null_terminated?1:0))*sizeof(*string->chars));
	string->chars[index] = character;
	string->length++;
	return true;
}

char string_pop_at(String* string, size_t index)
{
	char tmp = string_at(string, index);
	string_remove(string, index);
	return tmp;
}

bool string_concat(String* string, const String* other)
{
	if(other->length == 0)
		return true;
	if(!string_grow(string, other->length-1))
		return false;
	memcpy(string->chars+string->length,other->chars,other->length);
	string->length += other->length;
	string->chars[string->length] = '\0';
	return true;
}

bool string_find_char(const String* haystack, char needle, size_t* pos)
{
	char* ret = memchr(haystack->chars, needle, haystack->length);
	if(!ret)
	{
		return false;
	} else {
		*pos = (size_t)(ret-haystack->chars);
		return true;
	}
}

int string_cmp(const String* s1, const String* s2)
{
	int ret = memcmp(s1->chars, s2->chars, s1->length < s2->length ? s1->length : s2->length);
	if(ret == 0 && s1->length != s2->length)
		return s1->length < s2->length ? -1 : 1;
	else
		return ret;
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

bool string_grow(String* string, size_t add)
{
	if(string->length+add < string->length)
		return false;
	return string_adjust_size(string, string->length+add);
}

bool string_adjust_size(String* string, size_t size)
{
	if(size == SIZE_MAX && string->null_terminated)
		return false;

	while(string->capacity < size+(string->null_terminated?1:0))
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

String* from_cstring(const char* cstring, bool null_terminated)
{
	String* string = string_with_capacity(strlen(cstring), null_terminated);
	if(!string)
	{
		return NULL;
	} else {
		memcpy(string->chars, cstring, strlen(cstring));
		string->length = strlen(cstring);
		if(null_terminated)
			string->chars[string->length] = '\0';
		return string;
	}
}

String* from_cstring_reuse(char* cstring, size_t capacity, bool null_terminated)
{
	String* string;

	if(!cstring)
		return NULL;

	string = malloc(sizeof(*string));
	if(!string)
		return NULL;

	string->chars = cstring;
	string->length = strlen(cstring);
	string->capacity = capacity;

	return string;
}

String* from_cstring_del(char* cstring, bool null_terminated)
{
	String* ret = from_cstring(cstring, null_terminated);
	if(!ret)
		return NULL;
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
