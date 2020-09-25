#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// General Error Handling:
// Client code is assumed never to call these functions with a NULL List pointer, or 
// bad List pointer. If it does, any behaviour is permitted (such as crashing).
// HINT: Use assert(pList != NULL); just to add a nice check, but not required.

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
	static List pList;
	
	struct Node_s nodes[LIST_MAX_NUM_NODES];
	pList.size = 0;
	pList.head = &nodes[0];
	pList.curr = pList.head->prev;
	pList.tail = &nodes[0];
	nodes[0].prev = NULL;
	nodes[0].data = NULL;
	nodes[0].next = &nodes[1];
	nodes[LIST_MAX_NUM_NODES-1].prev = &nodes[LIST_MAX_NUM_NODES-2];
	nodes[LIST_MAX_NUM_NODES-1].data = NULL;
	nodes[LIST_MAX_NUM_NODES-1].next = NULL;
	for (int i = 1; i < LIST_MAX_NUM_NODES-1; ++i)
	{
		nodes[i].prev = &nodes[i-1];
		nodes[i].data = NULL;
		nodes[i].next = &nodes[i+1];
	}
	return &pList;
}

// Returns the number of items in pList.
int List_count(List* pList){
	return pList->size;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
	return pList->head;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
	return pList->tail;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
	if (pList->curr == pList->tail)
	{
		return NULL;
	}
	void* ptr = pList->curr->next;
	return ptr;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
	if (pList->curr == pList->head){
		return NULL;
	}
	void* ptr = pList->curr->prev;
	return ptr;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
	return pList->curr;
}


// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_add(List* pList, void* pItem){
	if (pList->curr == pList->head->prev){
		pList->curr = pList->head;
		pList->head = pItem;
		pList->size++;
		return 0;
	}
	else if (pList->curr == pList->tail->next){
		pList->curr = pList->tail;
		pList->tail = pItem;
		pList->size++;
		return 0;
	}
	pList->curr = pList->curr->next;
	pList->curr = pItem;
	pList->tail = pItem;
	pList->size++;
	return 0;
	if (pList->curr != pItem)
	{
		return -1;
	}
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem){
	if (pList->curr == pList->head->prev){
		pList->curr = pList->head;
		pList->head = pItem;
		pList->size++;
		return 0;
	}
	else if (pList->curr == pList->tail->next){
		pList->curr = pList->tail;
		pList->tail = pItem;
		pList->size++;
		return 0;
	}
	pList->curr = pList->curr->prev;
	pList->curr = pItem;
	pList->size++;
	if (pList->curr != pItem){
		return -1;
	}
	return 0;
	
}


// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
	pList->tail = pList->tail->next;
	pList->tail = pItem;
	if (pList->tail != pItem){
		return -1;
	}
	return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
	pList->head = pList->head->prev;
	pList->head = pItem;
	if (pList->head != pItem){
		return -1;
	}
	return 0;
}
/*

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList);

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2);

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn);

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList);

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg);
*/