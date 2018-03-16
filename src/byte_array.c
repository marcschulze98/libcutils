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

void* bytearray_at(const Bytearray* bytearray, size_t index)
{
	if(index >= bytearray->length)
		return NULL;
	else
		return bytearray->items+(index*bytearray->element_size);
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

	if(index > length || !bytearray_adjust_size(bytearray, length+1))
		return false;

	memmove(bytearray->items+index*size+1*size, bytearray->items+index*size, (length*size-index*size)*sizeof(*bytearray->items));
	memcpy(bytearray->items+index*size, item, bytearray->element_size);
	bytearray->length++;
	return true;
}

void bytearray_remove(Bytearray* bytearray, size_t index, void (*rmv)(void*))
{
	if(index < bytearray->length)
	{
		size_t length = bytearray->length;
		size_t elsize = bytearray->element_size;
		if(rmv)
			rmv(&bytearray->items[index*elsize]);

		memmove(bytearray->items+index*elsize, bytearray->items+index*elsize+1*elsize, (length*elsize-index*elsize-1*elsize)*sizeof(*bytearray->items));
		bytearray->length--;
	}
}

bool bytearray_adjust_size(Bytearray* bytearray, size_t size)
{
	while(bytearray->capacity < size)
	{
		size_t capacity = bytearray->capacity;
		size_t elsize = bytearray->element_size;
		char* tmp = bytearray->items;
		bytearray->items = realloc(bytearray->items, capacity*elsize*2*sizeof(*bytearray->items));
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
		size_t capacity = bytearray->capacity;
		size_t size = bytearray->element_size;
		char* tmp = bytearray->items;
		bytearray->items = realloc(bytearray->items, (capacity*size)/(2*sizeof(*bytearray->items)));
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
