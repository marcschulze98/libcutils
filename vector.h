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

typedef struct FindReturn
{
	bool found;
	size_t index; //if found is false, this contains rubbish
} FindReturn;

Vector* new_vector(void);
void* vector_at(const Vector* vector, size_t index);
void* vector_pop(Vector* vector, size_t index);
bool vector_push(Vector* vector, void* item);
void vector_remove(Vector* vector, size_t index);
bool vector_adjust_size(Vector* vector, size_t size);
FindReturn vector_find(const Vector* haystack, const void* needle, bool (*cmp)(const void*, const void*));
bool vector_insert(Vector* vector, size_t index, void* item);


#endif //VECTOR_H
