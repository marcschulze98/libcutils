#ifndef CUTILS_LINKED_LIST_H
#define CUTILS_LINKED_LIST_H

#include <cutils/common.h>
#include <stdlib.h>

typedef struct SLnode
{
	void* item;
	void* next; /*has to be void* so the next field is compatible between the structs*/
} SLnode;

typedef struct DLnode
{
	#if __STDC_VERSION__ >= 201112L
	union
	{
	#endif
		struct SLnode sl;
	#if __STDC_VERSION__ >= 201112L
		struct
		{
			void* item;
			void* next;
		};
	};
	#endif
	struct DLnode* prev;
} DLnode;

typedef struct LinkedList
{
	void* head; /*SLnode if doubly_linked is false, otherwise DLnode*/
	void* tail;
	size_t length;
	bool doubly_linked;
	bool circularly_linked;
} LinkedList;

LinkedList* new_ll(bool doubly_linked, bool circularly_linked);
void delete_ll(LinkedList* ll, void(*rmv) (void*));

void* llnode_at(const LinkedList* ll, size_t index);
HEDLEY_INLINE
static void* ll_at(const LinkedList* ll, size_t index)
{
	return ((SLnode*)llnode_at(ll, index))->item;
}
#define ll_pop(ll) ll_pop_at(ll, ll->length-1)
void* ll_pop_at(LinkedList* ll, size_t index);

#define ll_push(ll, item) ll_insert(ll, ll->length, item)
bool sll_insert(LinkedList* ll, size_t index, void* item);
bool dll_insert(LinkedList* ll, size_t index, void* item);
HEDLEY_INLINE
static bool ll_insert(LinkedList* ll, size_t index, void* item)
{
	if(ll->doubly_linked)
		return dll_insert(ll, index, item);
	else
		return sll_insert(ll, index, item);
}

void sll_remove(LinkedList* ll, size_t index, void (*rmv)(void*));
void dll_remove(LinkedList* ll, size_t index, void (*rmv)(void*));
HEDLEY_INLINE
static void ll_remove(LinkedList* ll, size_t index, void (*rmv)(void*))
{
	if(ll->doubly_linked)
		dll_remove(ll, index, rmv);
	else
		sll_remove(ll, index, rmv);
}
void sll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*));
void dll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*));
HEDLEY_INLINE
static void ll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*))
{
	if(ll->doubly_linked)
		dll_remove_range(ll, index, length, rmv);
	else
		sll_remove_range(ll, index, length, rmv);
}

size_t* ll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*));

void sll_swap(LinkedList* ll, size_t item1, size_t item2);
void dll_swap(LinkedList* ll, size_t item1, size_t item2);
HEDLEY_INLINE
static void ll_swap(LinkedList* ll, size_t item1, size_t item2)
{
	if(ll->doubly_linked)
		dll_swap(ll, item1, item2);
	else
		sll_swap(ll, item1, item2);
}


#endif /* CUTILS_LINKED_LIST_H */
