#include <cutils/dyn_string.h>

String* new_string(void)
{
	return string_with_capacity(STRING_DEFAULT_SIZE);
}

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

bool string_append(String* string, char character)
{
	return string_insert(string, string->length, character);
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
	if(index > string->length || !string_adjust_size(string, string->length))
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

bool string_concat(String* string, const String* other)
{
	if(!string_adjust_size(string,string->length+other->length-1))
		return false;
	memcpy(string->chars+string->length,other->chars,other->length);
	string->length += other->length;
	return true;
}

size_t* string_find_char(const String* haystack, const char needle)
{
	size_t* ret;
	for(size_t i = 0; i < haystack->length; i++)
	{
		if(haystack->chars[i] == needle)
		{
			ret = malloc(sizeof(*ret));
			*ret = i;
			return ret;
		}
	}
	return NULL;
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

char* to_cstring(const String* string)
{
	char* cstring = malloc(string->length+1);
	memcpy(cstring, string->chars, string->length);
	cstring[string->length] = '\0';

	return cstring;
}
