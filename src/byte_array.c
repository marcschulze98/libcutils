#include <cutils/byte_array.h>

Bytearray* bytearray_with_capacity(size_t capacity, size_t element_size)
{
	Bytearray* bytearray;

	bytearray = malloc(sizeof(*bytearray));
	if(!bytearray)
		return NULL;

	bytearray->items = malloc(sizeof(*bytearray->items)*capacity*element_size);
	if(!bytearray->items)
	{
		free(bytearray);
		return NULL;
	}

	bytearray->length = 0;
	bytearray->capacity = capacity;
	bytearray->element_size = element_size;

	return bytearray;
}


void delete_bytearray(Bytearray* bytearray, void(*rmv_el) (void*))
{
	if(rmv_el)
	{
		size_t i;
		for(i = 0; i < bytearray->length; i++)
		{
			rmv_el(&bytearray->items[i*bytearray->element_size]);
		}
	}

	free(bytearray->items);
	free(bytearray);
}

void bytearray_remove_range(Bytearray* bytearray, size_t index, size_t length, void (*rmv)(void*))
{
	size_t i;
	if(rmv)
	{
		for(i = index; i < length; i++)
		{
			rmv(bytearray_at(bytearray, i));
		}
	}
	memmove(bytearray->items+index, bytearray->items+index+length, (bytearray->length-(index+length))*sizeof(*bytearray->items));
	bytearray->length -= length;
}


void* bytearray_pop_at(Bytearray* bytearray, size_t index, void* retptr)
{
	void *tmp;

	tmp = bytearray_at(bytearray, index);
	if(!tmp)
		return NULL;

	retptr = retptr ? retptr : malloc(bytearray->element_size);
	if(!retptr)
		return NULL;

	memcpy(retptr, tmp, bytearray->element_size);
	bytearray_remove(bytearray, index, NULL);
	return retptr;
}

bool bytearray_insert(Bytearray* bytearray, size_t index, const void* item)
{
	size_t length = bytearray->length;
	size_t size = bytearray->element_size;

	if(!bytearray_grow(bytearray, 1))
		return false;

	memmove(bytearray->items+index*size+1*size, bytearray->items+index*size, (length*size-index*size)*sizeof(*bytearray->items));
	memcpy(bytearray->items+index*size, item, bytearray->element_size);
	bytearray->length++;
	return true;
}

bool bytearray_grow(Bytearray* bytearray, size_t add)
{
	if(bytearray->length+add < bytearray->length)
		return false;
	return bytearray_adjust_size(bytearray, bytearray->length+add);
}

bool bytearray_adjust_size(Bytearray* bytearray, size_t size)
{
	while(bytearray->capacity < size)
	{
		byte* tmp = bytearray->items;
		bytearray->items = cutil_reallocarray_inc(bytearray->items, bytearray->capacity, bytearray->element_size, bytearray->capacity);
		if(!bytearray->items)
		{
			bytearray->items = tmp;
			return false;
		}
		bytearray->capacity *= 2;
	}
	return true;
}

bool bytearray_shrink(Bytearray* bytearray)
{
	while(bytearray->capacity > bytearray->length*2)
	{
		byte* tmp = bytearray->items;
		bytearray->items = cutil_reallocarray(bytearray->items, bytearray->capacity/2, bytearray->element_size);
		if(!bytearray->items)
		{
			bytearray->items = tmp;
			return false;
		}
		bytearray->capacity /= 2;
	}
	return true;
}

size_t* bytearray_find(const Bytearray* haystack, const void* needle, int (*cmp)(const void*, const void*))
{
	size_t* ret;
	size_t i;

	for(i = 0; i < haystack->length; i++)
	{
		if(cmp(haystack->items+(i*haystack->element_size),needle) == 0)
		{
			ret = malloc(sizeof(*ret));
			*ret = i;
			return ret;
		}
	}
	return NULL;
}
