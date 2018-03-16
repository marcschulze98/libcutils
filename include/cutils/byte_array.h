#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cutils/common.h>

#define BYTEARRAY_DEFAULT_SIZE 4

typedef struct Bytearray
{
	char* items;
	size_t capacity;
	size_t length;
	size_t element_size;
} Bytearray;

#define new_bytearray(element_size) bytearray_with_capacity(BYTEARRAY_DEFAULT_SIZE, element_size)
Bytearray* bytearray_with_capacity(size_t capacity, size_t element_size);
void delete_bytearray(Bytearray* bytearray, void(*rmv_el) (void*));

void* bytearray_at(const Bytearray* bytearray, size_t index);
#define bytearray_pop(bytearray, retptr) bytearray_pop_at(bytearray, bytearray->length-1, retptr)
void* bytearray_pop_at(Bytearray* bytearray, size_t index, void* retptr);

#define bytearray_push(bytearray, item) bytearray_insert(bytearray, bytearray->length, item)
bool bytearray_insert(Bytearray* bytearray, size_t index, const void* item);

void bytearray_remove(Bytearray* bytearray, size_t index, void (*rmv)(void*));

bool bytearray_adjust_size(Bytearray* bytearray, size_t size);
bool bytearray_shrink(Bytearray* bytearray);
HEDLEY_NON_NULL(3)
size_t* bytearray_find(const Bytearray* haystack, const void* needle, int (*cmp)(const void*, const void*));


#endif /* BYTE_ARRAY_H */

