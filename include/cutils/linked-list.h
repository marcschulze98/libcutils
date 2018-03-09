#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
	void* head;
	void* tail;
	size_t length;
	bool_t doubly_linked;
} LinkedList;

LinkedList* new_ll(bool_t doubly_linked);
void delete_ll(LinkedList* ll, void(*rmv) (void*));

void* ll_at(const LinkedList* ll, size_t index);
#define ll_pop(ll) ll_pop_at(ll, ll->length-1)
void* ll_pop_at(LinkedList* ll, size_t index);

bool_t ll_insert(LinkedList* ll, size_t index, void* item);
#define ll_push(ll, item) ll_insert(ll, ll->length, item)

void ll_remove(LinkedList* ll, size_t index, void (*rmv)(void*));
void ll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*));

size_t* ll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*));


#endif /* LINKED_LIST_H */
