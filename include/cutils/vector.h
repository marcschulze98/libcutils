#ifndef CUTILS_VECTOR_H
#define CUTILS_VECTOR_H

#define VECTOR_DEFAULT_SIZE 4

#include <stdlib.h>
#include <string.h>
#include <cutils/common.h>

typedef struct Vector
{
	void** items;
	size_t capacity;
	size_t length;
} Vector;

Vector* vector_with_capacity(size_t capacity);
void delete_vector(Vector* vector, void(*rmv) (void*));

HEDLEY_INLINE
static void* vector_at(const Vector* vector, size_t index)
{
	return vector->items[index];
}
void* vector_pop_at(Vector* vector, size_t index);

bool vector_insert(Vector* vector, size_t index, void* item);

HEDLEY_INLINE
static void vector_remove(Vector* vector, size_t index, void (*rmv)(void*))
{
	if(index < vector->length)
	{
		if(rmv)
			rmv(vector->items[index]);
		memmove(vector->items+index, vector->items+index+1, (vector->length-index-1)*sizeof(*vector->items));
		vector->length--;
	}
}
void vector_remove_range(Vector* vector, size_t index, size_t length, void (*rmv)(void*));

bool vector_grow(Vector* vector, size_t add);
bool vector_adjust_size(Vector* vector, size_t size);
bool vector_shrink(Vector* vector);
HEDLEY_NON_NULL(3)
size_t* vector_find(const Vector* haystack, const void* needle, int (*cmp)(const void*, const void*));

#define new_vector() vector_with_capacity(VECTOR_DEFAULT_SIZE)
#define vector_pop(vector) vector_pop_at(vector, ((Vector*)vector)->length-1)
#define vector_push(vector, item) vector_insert(vector, ((Vector*)vector)->length, item)

#endif /* CUTILS_VECTOR_H */
