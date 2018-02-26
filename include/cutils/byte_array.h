#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BYTEARRAY_DEFAULT_SIZE 4

#define BT_FIXED 1
#define BT_FREE_EL 2
#define BT_FREE_ARRAY 4
#define BT_FREE_STRUCT 8

typedef enum {b_false, b_true} bool_t;

typedef struct Bytearray
{
	char* items;
	size_t capacity;
	size_t length;
	size_t element_size;
	short flags;
} Bytearray;

#define new_bytearray(element_size) bytearray_with_capacity(BYTEARRAY_DEFAULT_SIZE, element_size)
#define bytearray_with_capacity(capacity, element_size) new_bytearray_ext(capacity, element_size, NULL, NULL, BT_FREE_ARRAY | BT_FREE_STRUCT)
Bytearray* new_bytearray_ext(size_t capacity, size_t element_size, char* array_storage, Bytearray* struct_storage, short flags);
void delete_bytearray(Bytearray* bytearray);
void delete_bytearray_ext(Bytearray* bytearray, void(*rmv_el) (void*), void(*rmv_items) (void*), void(*rmv_struct) (void*));

void* bytearray_at(const Bytearray* bytearray, size_t index);
#define bytearray_pop(bytearray) bytearray_pop_at(bytearray, bytearray->length-1)
void* bytearray_pop_at(Bytearray* bytearray, size_t index);

#define bytearray_push(bytearray, item) bytearray_insert(bytearray, bytearray->length, item)
bool_t bytearray_insert(Bytearray* bytearray, size_t index, const void* item);

void bytearray_remove(Bytearray* bytearray, size_t index, void (*rmv)(void*));

bool_t bytearray_adjust_size(Bytearray* bytearray, size_t size);
bool_t bytearray_shrink(Bytearray* bytearray);
size_t* bytearray_find(const Bytearray* haystack, const void* needle, int (*cmp)(const void*, const void*));


#endif /* BYTE_ARRAY_H */

