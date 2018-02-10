#include "vector.h"

Vector* new_vector(void)
{
	Vector* vector = malloc(sizeof(*vector));
	if(!vector)
		return NULL;
	vector->items = malloc(sizeof(*vector->items)*VECTOR_DEFAULT_SIZE);
	if(!vector->items)
	{
		free(vector);
		return NULL;
	}
	vector->length = 0;
	vector->capacity = VECTOR_DEFAULT_SIZE;

	return vector;
}

void* vector_at(const Vector* vector, size_t index)
{
	if(index >= vector->length)
		return NULL;
	else
		return vector->items[index];
}

void* vector_pop(Vector* vector, size_t index)
{
	if(index >= vector->length)
		return NULL;
	else
	{
		void* tmp = vector->items[index];
		memmove(vector->items+index, vector->items+index+1, (vector->length-index-1)*sizeof(*vector->items));
		vector->length--;
		return tmp;
	}
}

void vector_remove(Vector* vector, size_t index)
{
	if(index < vector->length)
	{
		free(vector->items[index]);
		memmove(vector->items+index, vector->items+index+1, (vector->length-index-1)*sizeof(*vector->items));
		vector->length--;
	}
}

bool vector_push(Vector* vector, void* item)
{
	if(!vector_adjust_size(vector, ++vector->length))
		return false;
	vector->items[vector->length-1] = item;
	return true;
}

FindReturn vector_find(const Vector* haystack, const void* needle, bool (*cmp)(const void*, const void*))
{
	FindReturn ret;
	for(size_t i = 0; i < haystack->length; i++)
	{
		if(cmp)
		{
			if(cmp(haystack->items[i],needle))
			{
				ret.found = true;
				ret.index = i;
				return ret;
			}
		} else {
			if(haystack->items[i] == needle)
			{
				ret.found = true;
				ret.index = i;
				return ret;
			}
		}
	}
	ret.found = false;
	return ret;
}

bool vector_insert(Vector* vector, size_t index, void* item)
{
	if(!vector_adjust_size(vector, vector->length))
		return false;

	memmove(vector->items+index+1, vector->items+index, (vector->length-index)*sizeof(*vector->items));
	vector->items[index] = item;
	vector->length++;
	return true;
}

bool vector_adjust_size(Vector* vector, size_t size)
{
	while(vector->capacity < size)
	{
		void** tmp = vector->items;
		vector->items = realloc(vector->items, vector->capacity*2*(sizeof(*vector->items)));
		if(!vector->items)
		{
			vector->items = tmp;
			return false;
		}
		vector->capacity *= 2;
	}
	while(vector->capacity > (size*2))
	{
		void** tmp = vector->items;
		vector->items = realloc(vector->items, vector->capacity/2*(sizeof(*vector->items)));
		if(!vector->items)
		{
			vector->items = tmp;
			return false;
		}
		vector->capacity /= 2;
	}
	return true;
}
