#ifndef CUTILS_BYTE_ARRAY_H
#define CUTILS_BYTE_ARRAY_H
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cutils/common.h>

#define BYTEARRAY_DEFAULT_SIZE 4

typedef struct Bytearray
{
	byte* items;
	size_t capacity;
	size_t length;
	size_t element_size;
} Bytearray;

Bytearray* bytearray_with_capacity(size_t capacity, size_t element_size);
void delete_bytearray(Bytearray* bytearray, void(*rmv_el) (void*));

HEDLEY_INLINE
static void* bytearray_at(const Bytearray* bytearray, size_t index)
{
	return bytearray->items+(index*bytearray->element_size);
}
void* bytearray_pop_at(Bytearray* bytearray, size_t index, void* retptr);

bool bytearray_insert(Bytearray* bytearray, size_t index, const void* item);

HEDLEY_INLINE
static void bytearray_remove(Bytearray* bytearray, size_t index, void (*rmv)(void*))
{
	if(index < bytearray->length)
	{
		size_t length = bytearray->length;
		size_t elsize = bytearray->element_size;
		if(rmv)
			rmv(&bytearray->items[index*elsize]);

		memmove(bytearray->items+index*elsize, bytearray->items+index*elsize+1*elsize, length*elsize-index*elsize-1*elsize);
		bytearray->length--;
	}
}
void bytearray_remove_range(Bytearray* bytearray, size_t index, size_t length, void (*rmv)(void*));

bool bytearray_grow(Bytearray* bytearray, size_t add);
bool bytearray_adjust_size(Bytearray* bytearray, size_t size);
bool bytearray_shrink(Bytearray* bytearray);
HEDLEY_NON_NULL(3)
size_t* bytearray_find(const Bytearray* haystack, const void* needle, int (*cmp)(const void*, const void*));

#define new_bytearray(element_size) bytearray_with_capacity(BYTEARRAY_DEFAULT_SIZE, element_size)
#define bytearray_pop(bytearray, retptr) bytearray_pop_at(bytearray, bytearray->length-1, retptr)
#define bytearray_push(bytearray, item) bytearray_insert(bytearray, bytearray->length, item)

#endif /* CUTILS_BYTE_ARRAY_H */

