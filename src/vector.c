#include <cutils/vector.h>

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

void vector_remove_range(Vector* vector, size_t index, size_t length, void (*rmv)(void*))
{
	size_t i;
	if(rmv)
	{
		for(i = index; i < length; i++)
		{
			rmv(vector_at(vector, i));
		}
	}
	memmove(vector->items+index, vector->items+index+length, (vector->length-(index+length))*sizeof(*vector->items));
	vector->length -= length;
}

size_t* vector_find(const Vector* haystack, const void* needle, int (*cmp)(const void*, const void*))
{
	size_t i, *ret;

	for(i = 0; i < haystack->length; i++)
	{
		if(cmp(haystack->items[i],needle) == 0)
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
	if(index > vector->length || !vector_grow(vector, 1))
		return false;

	memmove(vector->items+index+1, vector->items+index, (vector->length-index)*sizeof(*vector->items));
	vector->items[index] = item;
	vector->length++;
	return true;
}

bool vector_grow(Vector* vector, size_t add)
{
	if(vector->length+add < vector->length)
		return false;
	return vector_adjust_size(vector, vector->length+add);
}

bool vector_adjust_size(Vector* vector, size_t size)
{
	while(vector->capacity < size)
	{
		void** tmp = vector->items;
		vector->items = cutil_reallocarray_inc(vector->items, vector->capacity,  sizeof(*vector->items), vector->capacity);
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
		vector->items = cutil_reallocarray(vector->items, vector->capacity/2, sizeof(*vector->items));
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
	if(rmv)
	{
		size_t i;
		for(i = 0; i < vector->length; i++)
		{
			rmv(vector->items[i]);
		}
	}
	free(vector->items);
	free(vector);
}
