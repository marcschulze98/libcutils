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


	if(index == 0) /*first item*/
	{
		ll->head = newnode;
		if(ll->length == 0) /* only item*/
		{
			ll->tail = newnode;
			if(ll->circularly_linked)
				newnode->next = newnode;
			else
				newnode->next = NULL;
		} else { /*at least one other item after this*/
			newnode->next = current;
			if(ll->circularly_linked)
				((SLnode*)ll->tail)->next = ll->head;
		}
	} else if(index < ll->length) { /*middle*/
		prev->next = newnode;
		newnode->next = current;
	} else { /*end*/
		ll->tail = newnode;
		prev->next = newnode;

		if(ll->circularly_linked)
			newnode->next = ll->head;
		else
			newnode->next = NULL;
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

	if(index == 0) /*first item*/
	{
		ll->head = newnode;
		if(ll->length == 0) /* only item*/
		{
			ll->tail = newnode;
			if(ll->circularly_linked)
			{
				newnode->prev = newnode;
				newnode->sl.next = newnode;
			} else {
				newnode->prev = NULL;
				newnode->sl.next = NULL;
			}
		} else { /* at least one other item after this*/
			newnode->sl.next = current;
			current->prev = newnode;
			if(ll->circularly_linked)
			{
				((DLnode*)ll->tail)->sl.next = ll->head;
				newnode->prev = ll->tail;
			} else {
				newnode->prev = NULL;
			}
		}
	} else if(index < ll->length) { /*middle*/
		prev->sl.next = newnode;
		newnode->prev = prev;
		newnode->sl.next = current;
		current->prev = newnode;
	} else { /*end*/
		ll->tail = newnode;
		prev->sl.next = newnode;
		newnode->prev = prev;

		if(ll->circularly_linked)
		{
			newnode->sl.next = ll->head;
			((DLnode*)ll->head)->prev = newnode;
		} else {
			newnode->sl.next = NULL;
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

	if(index == 0) /*beginning*/
	{
		if(ll->length == 1) /*only item*/
		{
			ll->head = ll->tail = NULL;
		} else {
			ll->head = current->next;
			if(ll->circularly_linked && ll->tail) ((SLnode*)ll->tail)->next = ll->head;
		}
	} else { /*middle or ned*/
		prev->next = current->next;
		if(index == ll->length-1) /*at end*/
			ll->tail = prev;
	}

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

	if(index == 0) /* beginning*/
	{
		if(ll->length == 1) /*only item*/
		{
			ll->head = ll->tail = NULL;
		} else {
			ll->head = current->sl.next;
			if(ll->circularly_linked && ll->tail)
			{
				((DLnode*)(current->sl.next))->prev = ll->tail;
				((DLnode*)ll->tail)->sl.next = ll->head;
			} else {
				((DLnode*)(current->sl.next))->prev = NULL;
			}
		}
	} else { /*middle or end*/
		prev->sl.next = current->sl.next;
		if(index == ll->length-1) /*at end*/
		{
			ll->tail = prev;
			if(ll->circularly_linked)
				((DLnode*)(ll->head))->prev = ll->tail;
		}
	}

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

	if(index == 0) /* beginning */
		ll->head = current;

	if(index+length == ll->length) /* removed last item */
	{
		if(index == 0)
		{
			ll->head = NULL;
			ll->tail = NULL;
		} else {
			ll->tail = prev;
			if(ll->circularly_linked)
			{
				prev->next = ll->head;
			} else {
				prev->next = NULL;
			}
		}
	} else {
		if(index == 0)
		{
			ll->head = current;
			if(ll->circularly_linked) ((SLnode*)(ll->tail))->next = ll->head;
		} else {
			prev->next = current;
		}
	}

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

	if(index == 0) /* beginning */
	{
		ll->head = current;
		current->prev = ll->circularly_linked ? ll->tail : NULL;
	}

	if(index+length == ll->length) /* removed last item */
	{
		if(index == 0)
		{
			ll->head = NULL;
			ll->tail = NULL;
		} else {
			ll->tail = prev;
			if(ll->circularly_linked)
			{
				prev->sl.next = ll->head;
				((DLnode*)(ll->head))->prev = ll->tail;
			} else {
				prev->sl.next = NULL;
			}
		}
	} else {
		if(index == 0)
		{
			ll->head = current;
			if(ll->circularly_linked)
			{
				((SLnode*)(ll->tail))->next = ll->head;
				current->prev = ll->tail;
			} else {
				current->prev = NULL;
			}
		} else {
			prev->sl.next = current;
			current->prev = prev;
		}
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
