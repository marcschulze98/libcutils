#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cutils/common.h>
#include <stdlib.h>

typedef struct SLnode
{
	void* item;
	struct SLnode* next;
} SLnode;

typedef struct DLnode
{
	void* item;
	struct DLnode* next;
	struct DLnode* prev;
} DLnode;

typedef struct LinkedList
{
	void* head; /*SLnode if doubly_linked is false, otherwise DLnode*/
	void* tail;
	size_t length;
	bool_t doubly_linked;
	bool_t circularly_linked;
} LinkedList;

LinkedList* new_ll(bool_t doubly_linked, bool_t circularly_linked);

void delete_sll(LinkedList* ll, void(*rmv) (void*));
void delete_dll(LinkedList* ll, void(*rmv) (void*));
HEDLEY_INLINE
static void delete_ll(LinkedList* ll, void(*rmv) (void*))
{
	if(ll->doubly_linked)
		delete_dll(ll, rmv);
	else
		delete_sll(ll, rmv);
}

void* sll_at(const LinkedList* ll, size_t index);
void* dll_at(const LinkedList* ll, size_t index);
HEDLEY_INLINE
static void* ll_at(const LinkedList* ll, size_t index)
{
	if(ll->doubly_linked)
		return sll_at(ll, index);
	else
		return dll_at(ll, index);
}
#define ll_pop(ll) ll_pop_at(ll, ll->length-1)
void* sll_pop_at(LinkedList* ll, size_t index);
void* dll_pop_at(LinkedList* ll, size_t index);
HEDLEY_INLINE
static void* ll_pop_at(LinkedList* ll, size_t index)
{
	if(ll->doubly_linked)
		return sll_pop_at(ll, index);
	else
		return dll_pop_at(ll, index);
}

#define ll_push(ll, item) ll_insert(ll, ll->length, item)
bool_t sll_insert(LinkedList* ll, size_t index, void* item);
bool_t dll_insert(LinkedList* ll, size_t index, void* item);
HEDLEY_INLINE
static bool_t ll_insert(LinkedList* ll, size_t index, void* item)
{
	if(ll->doubly_linked)
		return sll_insert(ll, index, item);
	else
		return dll_insert(ll, index, item);
}


void sll_remove(LinkedList* ll, size_t index, void (*rmv)(void*));
void dll_remove(LinkedList* ll, size_t index, void (*rmv)(void*));
HEDLEY_INLINE
static void ll_remove(LinkedList* ll, size_t index, void (*rmv)(void*))
{
	if(ll->doubly_linked)
		sll_remove(ll, index, rmv);
	else
		dll_remove(ll, index, rmv);
}
void sll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*));
void dll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*));
HEDLEY_INLINE
static void ll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*))
{
	if(ll->doubly_linked)
		sll_remove_range(ll, index, length, rmv);
	else
		dll_remove_range(ll, index, length, rmv);
}

size_t* sll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*));
size_t* dll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*));
HEDLEY_INLINE
static size_t* ll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*))
{
	if(haystack->doubly_linked)
		return sll_find(haystack, needle, cmp);
	else
		return dll_find(haystack, needle, cmp);
}
void sll_swap(LinkedList* ll, size_t item1, size_t item2);
void dll_swap(LinkedList* ll, size_t item1, size_t item2);
HEDLEY_INLINE
static void ll_swap(LinkedList* ll, size_t item1, size_t item2)
{
	if(ll->doubly_linked)
		sll_swap(ll, item1, item2);
	else
		dll_swap(ll, item1, item2);
}


#endif /* LINKED_LIST_H */
