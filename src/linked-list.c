#include <cutils/linked-list.h>
#include <cutils/misc.h>

LinkedList* new_ll(bool_t doubly_linked, bool_t circularly_linked)
{
	LinkedList* ret = malloc(sizeof(*ret));
	ret->head = NULL;
	ret->tail = NULL;
	ret->length = 0;
	ret->doubly_linked = doubly_linked;
	ret->circularly_linked = circularly_linked;
	return ret;
}

void delete_sll(LinkedList* ll, void(*rmv) (void*))
{
	size_t i;
	SLnode *current, *tmp;

	current = ll->head;

	for(i = 0; i < ll->length; i++)
	{

		if(rmv)
			rmv(current->item);
		tmp = current;
		current = current->next;
		free(tmp);

	}
}

void delete_dll(LinkedList* ll, void(*rmv) (void*))
{
	size_t i;
	DLnode *current, *tmp;

	current = ll->head;

	for(i = 0; i < ll->length; i++)
	{

		if(rmv)
			rmv(current->item);
		tmp = current;
		current = current->next;
		free(tmp);

	}
}

void* sll_at(const LinkedList* ll, size_t index)
{
	size_t i;
	SLnode* current;

	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current->item;
}

void* dll_at(const LinkedList* ll, size_t index)
{
	size_t i;
	DLnode* current;

	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current->item;
}

void* sll_pop_at(LinkedList* ll, size_t index)
{
	size_t i;
	SLnode* current;
	void* tmp;

	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	tmp = current->item;
	ll_remove(ll, index, NULL);
	return tmp;
}

void* dll_pop_at(LinkedList* ll, size_t index)
{
	size_t i;
	DLnode* current;
	void* tmp;

	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	tmp = current->item;
	ll_remove(ll, index, NULL);
	return tmp;
}

bool_t sll_insert(LinkedList* ll, size_t index, void* item)
{
	size_t i;
	SLnode *current, *prev, *newnode = malloc(sizeof(*newnode));

	if(!newnode)
		return b_false;

	newnode->item =item;
	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->next;
	}

	if(current)
	{
		newnode->next = current;
		if(prev)
			prev->next = newnode;
		else
			ll->head = newnode;
	} else {
		ll->tail = newnode;
		if(index == 0)
			ll->head = newnode;
		newnode->next = NULL;
	}

	ll->length++;
	return b_true;
}

bool_t dll_insert(LinkedList* ll, size_t index, void* item)
{
	size_t i;
	DLnode *current, *newnode = malloc(sizeof(*newnode));

	if(!newnode)
		return b_false;

	newnode->item =item;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	if(current)
	{
		newnode->next = current;
		if(current->prev)
		{
			current->prev->next = newnode;
			newnode->prev =current;
		} else {
			ll->head = newnode;
			newnode->prev = NULL;
		}
	} else {
		ll->tail = newnode;
		if(index == 0)
			ll->head = newnode;
		newnode->next = NULL;
		newnode->prev = NULL;
	}

	ll->length++;
	return b_true;
}

void sll_remove(LinkedList* ll, size_t index, void (*rmv)(void*))
{
	size_t i;
	SLnode *current, *prev;

	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->next;
	}

	if(rmv)
		rmv(current->item);

	prev->next = current->next;
	free(current);
}

void dll_remove(LinkedList* ll, size_t index, void (*rmv)(void*))
{
	size_t i;
	DLnode* current;

	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	if(rmv)
		rmv(current->item);

	current->prev->next = current->next;
	current->next->prev = current->prev;
	free(current);
}

void sll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*))
{
	size_t i;
	SLnode *current, *tmp, *prev;

	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->next;
	}

	for(i = 0; i < length; i++)
	{
		if(rmv)
			rmv(current->item);
		tmp = current;
		free(current);
		current = tmp->next;
	}

	prev->next = current;
}

void dll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*))
{
	size_t i;
	DLnode *current, *prev;

	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->next;
	}

	for(i = 0; i < length; i++)
	{
		if(rmv)
			rmv(current->item);
		current = current->next;
		free(current->prev);
	}

	prev->next = current;
	current->prev = prev;
}

size_t* sll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*))
{
	size_t i, *ret;
	SLnode* current;

	current = haystack->head;

	for(i = 0; i < haystack->length; i++)
	{
		if(cmp(current->item, needle) == 0)
		{
			ret = malloc(sizeof(*ret));
			*ret = i;
			return ret;
		}
		current = current->next;
	}
	return NULL;
}

size_t* dll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*))
{
	size_t i, *ret;
	DLnode* current;

	current = haystack->head;

	for(i = 0; i < haystack->length; i++)
	{
		if(cmp(current->item, needle) == 0)
		{
			ret = malloc(sizeof(*ret));
			*ret = i;
			return ret;
		}
		current = current->next;
	}
	return NULL;
}

void sll_swap(LinkedList* ll, size_t item1, size_t item2)
{
	size_t i, first_index, second_index;
	SLnode *first, *second;

	first_index = item1 <= item2 ? item1 : item2;
	second_index = item1 <= item2 ? item2 : item1;

	first = NULL;
	second = ll->head;

	for(i = 0; i < second_index; i++)
	{
		if(i == first_index)
			first = second->next;
		second = second->next;
	}

	if(!first)
		first = second;

	memswap(&first->item, &second->item, sizeof(first->item));
}

void dll_swap(LinkedList* ll, size_t item1, size_t item2)
{
	size_t i, first_index, second_index;
	DLnode *first, *second;

	first_index = item1 <= item2 ? item1 : item2;
	second_index = item1 <= item2 ? item2 : item1;

	first = NULL;
	second = ll->head;

	for(i = 0; i < second_index; i++)
	{
		if(i == first_index)
			first = second->next;
		second = second->next;
	}

	if(!first)
		first = second;

	memswap(&first->item, &second->item, sizeof(first->item));
}
