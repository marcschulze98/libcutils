#include "vector.h"

Vector* new_vector(void)
{
	return vector_with_capacity(VECTOR_DEFAULT_SIZE);
}

Vector* vector_with_capacity(size_t capacity)
{
	Vector* vector = malloc(sizeof(*vector));
	if(!vector)
		return NULL;
	vector->items = malloc(sizeof(*vector->items)*capacity);
	if(!vector->items)
	{
		free(vector);
		return NULL;
	}
	vector->length = 0;
	vector->capacity = capacity;

	return vector;
}

void* vector_at(const Vector* vector, size_t index)
{
	if(index >= vector->length)
		return NULL;
	else
		return vector->items[index];
}

void* vector_pop(Vector* vector)
{
	return vector_pop_at(vector, vector->length-1);
}

void* vector_pop_at(Vector* vector, size_t index)
{
	void* tmp = vector_at(vector, index);
	if(!tmp)
	{
		return NULL;
	} else {
		vector_remove(vector, index, NULL);
		return tmp;
	}
}


void vector_remove(Vector* vector, size_t index, void (*rmv)(void*))
{
	if(index < vector->length)
	{
		if(rmv)
			rmv(vector->items[index]);
		memmove(vector->items+index, vector->items+index+1, (vector->length-index-1)*sizeof(*vector->items));
		vector->length--;
	}
}

bool vector_push(Vector* vector, void* item)
{
	return vector_insert(vector, vector->length, item);
}

size_t* vector_find(const Vector* haystack, const void* needle, int (*cmp)(const void*, const void*))
{
	size_t* ret;
	for(size_t i = 0; i < haystack->length; i++)
	{
		if(cmp ? cmp(haystack->items[i],needle) == 0 : haystack->items[i] == needle)
		{
			ret = malloc(sizeof(*ret));
			*ret = i;
			return ret;
		}
	}
	return NULL;
}

bool vector_insert(Vector* vector, size_t index, void* item)
{
	if(index > vector->length || !vector_adjust_size(vector, vector->length+1))
		return false;

	memmove(vector->items+index+1, vector->items+index, (vector->length-index)*sizeof(*vector->items));
	vector->items[index] = item;
	++vector->length;
	return true;
}

bool vector_adjust_size(Vector* vector, size_t size)
{
	while(vector->capacity < size)
	{
		void** tmp = vector->items;
		vector->items = realloc(vector->items, vector->capacity*2*sizeof(*vector->items));
		if(!vector->items)
		{
			vector->items = tmp;
			return false;
		}
		vector->capacity *= 2;
	}
	return true;
}

bool vector_shrink(Vector* vector)
{
	while(vector->capacity > (vector->length*2))
	{
		void** tmp = vector->items;
		vector->items = realloc(vector->items, vector->capacity/2*sizeof(*vector->items));
		if(!vector->items)
		{
			vector->items = tmp;
			return false;
		}
		vector->capacity /= 2;
	}
	return true;
}

void delete_vector(Vector* vector, void (*rmv)(void*))
{
	for(size_t i = 0; i < vector->length; i++)
	{
		if(rmv)
			rmv(vector->items[i]);
	}
	free(vector->items);
	free(vector);
}
