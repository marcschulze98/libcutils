#include <cutils/linked-list.h>
#include <cutils/misc.h>

LinkedList* new_ll(bool doubly_linked, bool circularly_linked)
{
	LinkedList* ret = malloc(sizeof(*ret));
	ret->head = NULL;
	ret->tail = NULL;
	ret->length = 0;
	ret->doubly_linked = doubly_linked;
	ret->circularly_linked = circularly_linked;
	return ret;
}

void delete_ll(LinkedList* ll, void(*rmv) (void*))
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
	free(ll);
}

void* llnode_at(const LinkedList* ll, size_t index)
{
	size_t i;
	SLnode* current;

	current = ll->head;

	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current;
}


void* ll_pop_at(LinkedList* ll, size_t index)
{
	SLnode* node;
	void* tmp;

	node = llnode_at(ll ,index);

	tmp = node->item;
	ll_remove(ll, index, NULL);
	return tmp;
}



bool sll_insert(LinkedList* ll, size_t index, void* item)
{
	size_t i;
	SLnode *current, *prev, *newnode = malloc(sizeof(*newnode));

	if(!newnode)
		return false;

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
		if(index == 0)
			ll->head = newnode;
		else
			prev->next = newnode;
	} else {
		ll->tail = newnode;
		newnode->next = NULL;
		if(index == 0)
			ll->head = newnode;
		if(prev)
			prev->next = newnode;
	}

	ll->length++;
	return true;
}

bool dll_insert(LinkedList* ll, size_t index, void* item)
{
	size_t i;
	DLnode *current, *prev, *newnode = malloc(sizeof(*newnode));

	if(!newnode)
		return false;

	newnode->sl.item = item;
	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->sl.next;
	}

	if(current)
	{
		newnode->sl.next = current;
		if(index == 0)
		{
			ll->head = newnode;
			newnode->prev = NULL;
		} else {
			prev->sl.next = newnode;
			newnode->prev = prev;
		}
		current->prev = newnode;
	} else {
		ll->tail = newnode;
		newnode->sl.next = NULL;
		if(index == 0)
		{
			ll->head = newnode;
			newnode->prev = NULL;
		}
		if(prev)
		{
			prev->sl.next = newnode;
			newnode->prev = prev;
		}

	}

	ll->length++;
	return true;
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

	if(!current->next)
		ll->tail = prev;

	if(prev)
		prev->next = current->next;
	else
		ll->head = current->next;

	free(current);
	ll->length--;
}

void dll_remove(LinkedList* ll, size_t index, void (*rmv)(void*))
{
	size_t i;
	DLnode *current, *prev;

	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->sl.next;
	}

	if(rmv)
		rmv(current->sl.item);

	if(current->sl.next)
		((DLnode*)(current->sl.next))->prev = prev;
	else
		ll->tail = prev;

	if(prev)
		prev->sl.next = current->sl.next;
	else
		ll->head = current->sl.next;

	free(current);
	ll->length--;
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
		tmp = current->next;
		free(current);
		current = tmp;
	}

	if(!current)
		ll->tail = prev;

	if(prev)
		prev->next = current;
	else
		ll->head = current;
	ll->length -= length;
}

void dll_remove_range(LinkedList* ll, size_t index, size_t length, void (*rmv)(void*))
{
	size_t i;
	DLnode *current, *tmp, *prev;

	prev = NULL;
	current = ll->head;

	for(i = 0; i < index; i++)
	{
		prev = current;
		current = current->sl.next;
	}

	for(i = 0; i < length; i++)
	{
		if(rmv)
			rmv(current->sl.item);
		tmp = current->sl.next;
		free(current);
		current = tmp;
	}
	if(current)
		current->prev = prev;
	else
		ll->tail = prev;

	if(prev)
	{
		prev->sl.next = current;
	} else {
		ll->head = current;
	}
	ll->length -= length;
}


size_t* ll_find(const LinkedList* haystack, const void* needle, int (*cmp)(const void*, const void*))
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
			first = second;
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
			first = second;
		second = second->sl.next;
	}

	if(!first)
		first = second;

	memswap(&first->sl.item, &second->sl.item, sizeof(first->sl.item));
}
