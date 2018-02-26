#include <cutils/byte_array.h>

Bytearray* new_bytearray_ext(size_t capacity, size_t element_size, char* array_storage, Bytearray* struct_storage, short flags)
{
	Bytearray* bytearray;

	if(struct_storage)
	{
		bytearray = struct_storage;
	} else {
		bytearray = malloc(sizeof(*bytearray));
		if(!bytearray)
			return NULL;
	}

	if(array_storage)
	{
		bytearray->items = array_storage;
	} else {
		bytearray->items = malloc(sizeof(*bytearray->items)*capacity*element_size);
		if(!bytearray->items)
		{
			free(bytearray);
			return NULL;
		}
	}
	bytearray->length = 0;
	bytearray->capacity = capacity;
	bytearray->element_size = element_size;
	bytearray->flags = flags;

	return bytearray;
}

void delete_bytearray(Bytearray* bytearray)
{
	delete_bytearray_ext(bytearray,
	                    (bytearray->flags & BT_FREE_EL) ? free : NULL,
	                    (bytearray->flags & BT_FREE_ARRAY) ? free : NULL,
	                    (bytearray->flags & BT_FREE_STRUCT) ? free : NULL);
}


void delete_bytearray_ext(Bytearray* bytearray, void(*rmv_el) (void*), void(*rmv_items) (void*), void(*rmv_struct) (void*))
{
	if(rmv_el)
	{
		size_t i;
		for(i = 0; i < bytearray->length; i++)
		{
			rmv_el(&bytearray->items[i*bytearray->element_size]);
		}
	}
	if(rmv_items)
		rmv_items(bytearray->items);
	if(rmv_struct)
		rmv_struct(bytearray);
}

void* bytearray_at(const Bytearray* bytearray, size_t index)
{
	if(index >= bytearray->length)
		return NULL;
	else
		return bytearray->items+(index*bytearray->element_size);
}

void* bytearray_pop_at(Bytearray* bytearray, size_t index)
{
	void *tmp, *ret;

	tmp = bytearray_at(bytearray, index);
	if(!tmp)
	{
		errno = 0;
		return NULL;
	}

	ret = malloc(bytearray->element_size);
	if(!ret)
	{
		errno = ENOMEM;
		return NULL;
	}

	memcpy(ret, tmp, bytearray->element_size);
	bytearray_remove(bytearray, index, NULL);
	return ret;
}

bool_t bytearray_insert(Bytearray* bytearray, size_t index, const void* item)
{
	size_t length = bytearray->length;
	size_t size = bytearray->element_size;

	if(index > length || !bytearray_adjust_size(bytearray, length+1))
		return b_false;

	memmove(bytearray->items+index*size+1*size, bytearray->items+index*size, (length*size-index*size)*sizeof(*bytearray->items));
	memcpy(bytearray->items+index*size, item, bytearray->element_size);
	++bytearray->length;
	return b_true;
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
		--bytearray->length;
	}
}

bool_t bytearray_adjust_size(Bytearray* bytearray, size_t size)
{
	if(bytearray->flags & BT_FIXED)
	{
		if(bytearray->capacity < size)
			return b_false;
		else
			return b_true;
	}

	while(bytearray->capacity < size)
	{
		size_t capacity = bytearray->capacity;
		size_t elsize = bytearray->element_size;
		char* tmp = bytearray->items;
		bytearray->items = realloc(bytearray->items, capacity*elsize*2*sizeof(*bytearray->items));
		if(!bytearray->items)
		{
			bytearray->items = tmp;
			return b_false;
		}
		bytearray->capacity *= 2;
	}
	return b_true;
}

bool_t bytearray_shrink(Bytearray* bytearray)
{
	if(bytearray->flags & BT_FIXED)
		return b_false;

	while(bytearray->capacity > bytearray->length*2)
	{
		size_t capacity = bytearray->capacity;
		size_t size = bytearray->element_size;
		char* tmp = bytearray->items;
		bytearray->items = realloc(bytearray->items, (capacity*size)/(2*sizeof(*bytearray->items)));
		if(!bytearray->items)
		{
			bytearray->items = tmp;
			return b_false;
		}
		bytearray->capacity /= 2;
	}
	return b_true;
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
