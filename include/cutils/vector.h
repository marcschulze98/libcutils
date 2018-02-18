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

Vector* new_vector(void);
Vector* vector_with_capacity(size_t capacity);
void delete_vector(Vector* vector, void(*rmv) (void*));

void* vector_at(const Vector* vector, size_t index);
void* vector_pop(Vector* vector);
void* vector_pop_at(Vector* vector, size_t index);

bool vector_insert(Vector* vector, size_t index, void* item);
bool vector_push(Vector* vector, void* item);
void vector_remove(Vector* vector, size_t index, void (*rmv)(void*));

bool vector_adjust_size(Vector* vector, size_t size);
bool vector_shrink(Vector* vector);
size_t* vector_find(const Vector* haystack, const void* needle, int (*cmp)(const void*, const void*));



#endif //VECTOR_H
