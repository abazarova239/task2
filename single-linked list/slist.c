/*
 * This file is slist.c
 * Single linked list implementation
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "slist.h"

pslist slist_new(void)
{
	pslist list = malloc(sizeof(struct slist)); //allocate memory
	if (NULL == list) //check
		return NULL;
	list->size = 0;
	list->head = NULL;

	return list;
}

pslist_entry slist_pop(pslist list)
{
	pslist_entry p = list->head;
	if (NULL == p) //check
		return NULL;
	list->head = p->next;
	list->size--; //decrease size
	return p;
}

/* Now for earch element free memory */
void slist_delete(pslist list)
{
	pslist_entry head;
	while (NULL != (head = slist_pop(list)))
	{
		free(head);
	}

	free(list);
}

/* Allocate the element
   Put at the end */
int slist_insert(pslist list, int value)
{
	struct slist_entry *pnew = malloc(sizeof(struct slist_entry)); //allocate memory
	if (pnew == NULL) //check errors
		return -1;
	pnew->next = list->head;
	pnew->value = value;
	printf("New element: %d\n", pnew->value); //check by printing
	list->head = pnew;
	list->size++;
	return 0;
}

/* Go through the list, remove if value is equal */
int slist_remove(pslist list, int value)
{
	int start_size = list->size;
	pslist_entry tail = list->head; // tail - current element
	while  ((tail->value == value) && (NULL != tail)) //delete heads
	{
		list->size--;
		tail = slist_pop(list)->next;
	}
	while (NULL != tail->next) //check next
	{
		if (tail->next->value == value)
		{
			pslist_entry p = tail->next; //additional variable to free memory clear
			tail->next = tail->next->next;
			free(p);
			list->size--;
		}
		else
		{
			tail = tail->next;
		}
	}
		
	return start_size - list->size; //amount of the removed elements
}

/* For each element print in value */
void slist_print(pslist list)
{
	pslist_entry pcurrent = list->head;
	printf("List: \n");
	while (pcurrent != NULL)
	{
		printf("> %d\n", pcurrent->value);
		pcurrent = pcurrent->next;
	}
}
