#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_DEFAULT_SIZE 4
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Vector
{
	void** items;
	size_t capacity;
	size_t length;
} Vector;

#define new_vector() vector_with_capacity(VECTOR_DEFAULT_SIZE)
Vector* vector_with_capacity(size_t capacity);
void delete_vector(Vector* vector, void(*rmv) (void*));

void* vector_at(const Vector* vector, size_t index);
#define vector_pop(vector) vector_pop_at(vector, vector->length-1)
void* vector_pop_at(Vector* vector, size_t index);

bool vector_insert(Vector* vector, size_t index, void* item);
#define vector_push(vector, item) vector_insert(vector, vector->length, item)

void vector_remove(Vector* vector, size_t index, void (*rmv)(void*));

bool vector_adjust_size(Vector* vector, size_t size);
bool vector_shrink(Vector* vector);
size_t* vector_find(const Vector* haystack, const void* needle, int (*cmp)(const void*, const void*));


#endif /* VECTOR_H */
