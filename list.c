#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// General Error Handling:
// Client code is assumed never to call these functions with a NULL List pointer, or 
// bad List pointer. If it does, any behaviour is permitted (such as crashing).
// HINT: Use assert(pList != NULL); just to add a nice check, but not required.

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.

static Node All_Nodes[LIST_MAX_NUM_NODES];
static List All_Heads[LIST_MAX_NUM_HEADS];
static int freed_nodes[LIST_MAX_NUM_NODES];
static int freed_heads[LIST_MAX_NUM_HEADS];
static int nodeCount = 0;
static int headCount = 0;
static int nodePos = 0; // used to check if node out of bound;
static int headPos = 0; // used to check if head out of bound;

List* List_create(){
	if (headCount >= LIST_MAX_NUM_HEADS){
		return NULL;
	}
	if (headPos < 10){
		List* pList = &All_Heads[headCount];
		headCount++;
		pList->index = headCount;
		pList->size = 0;
		pList->head = NULL;
		pList->curr = NULL;
		pList->tail = NULL;
		return pList;
	}
	else{
		List* pList = &All_Heads[freed_heads[headCount]];
		headCount++;
		pList->index = freed_heads[headCount];
		pList->size = 0;
		pList->head = NULL;
		pList->curr = NULL;
		pList->tail = NULL;
		return pList;
	}
}

// Returns the number of items in pList.
int List_count(List* pList){
	return pList->size;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
	if (pList->size == 0)
	{
		return NULL;
	}
	pList->curr = pList->head;
	return pList->head->data;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
	if (pList->size == 0)
	{
		return NULL;
	}
	pList->curr = pList->tail;
	return pList->tail->data;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
	if (pList->curr == NULL){
		if (pList->curr == pList->head->prev){
			pList->curr = pList->head;
			return pList->head->data;
		}
		return NULL;
	}
	else if(pList->curr->next == NULL){
		pList->curr = pList->curr->next;
		pList->curr = NULL;
		return NULL;
	}
	pList->curr = pList->curr->next;
	return pList->curr->data;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
	if (pList->curr == NULL){
		if (pList->curr == pList->tail->next){
			pList->curr = pList->tail;
			return pList->tail->data;
		}
		return NULL;
	}
	else if(pList->curr->prev == NULL){
		pList->curr = pList->curr->prev;
		pList->curr = NULL;
		return NULL;
	}
	pList->curr = pList->curr->prev;
	return pList->curr->data;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
	if (pList->curr == NULL)
	{
		return NULL;
	}
	return pList->curr->data;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_add(List* pList, void* pItem){
	if (nodeCount >= LIST_MAX_NUM_NODES){
		return -1;
	}
	
	// dealing with the node first
	nodeCount++;
	int tempIndex;
	// node within the bound
	if (nodePos<LIST_MAX_NUM_NODES){
		tempIndex = nodeCount;
		All_Nodes[tempIndex].data = pItem;
		All_Nodes[tempIndex].index = tempIndex;
		All_Nodes[tempIndex].next = NULL;
		All_Nodes[tempIndex].prev = NULL;
	}
	// node out of bound
	else{
		tempIndex = freed_nodes[nodeCount];
		All_Nodes[tempIndex].data = pItem;
		All_Nodes[tempIndex].index = tempIndex;
		All_Nodes[tempIndex].next = NULL;
		All_Nodes[tempIndex].prev = NULL;
	}

	// dealing with the list
	pList->size++;
	// empty list
	if (pList->head == NULL){
		pList->head = &All_Nodes[tempIndex];
		pList->curr = &All_Nodes[tempIndex];
		pList->tail = &All_Nodes[tempIndex];
	}
	else if (pList->curr == NULL){
		if (pList->curr == pList->head->prev){
			All_Nodes[tempIndex].next = pList->head;
			All_Nodes[tempIndex].prev = pList->head->prev;
			pList->head = &All_Nodes[tempIndex];
			pList->curr = &All_Nodes[tempIndex];

		}
		else{
			All_Nodes[tempIndex].prev = pList->tail;
			pList->tail->next = &All_Nodes[tempIndex];
			pList->tail = &All_Nodes[tempIndex];
			pList->curr = &All_Nodes[tempIndex];
		}
	}
	else{
		if (pList->curr == pList->tail){
			All_Nodes[tempIndex].prev = pList->tail;
			pList->tail->next = &All_Nodes[tempIndex];
			pList->tail = &All_Nodes[tempIndex];
			pList->curr = &All_Nodes[tempIndex];
		}
		else{
			All_Nodes[tempIndex].next = pList->curr->next;
			All_Nodes[tempIndex].prev = pList->curr;
			pList->curr->next->prev = &All_Nodes[tempIndex];
			pList->curr->next = &All_Nodes[tempIndex];
		}
	}
	return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem){
	if (nodeCount >= LIST_MAX_NUM_NODES){
		return -1;
	}
	
	// dealing with the node first
	nodeCount++;
	int tempIndex;
	// node within the bound
	if (nodePos<LIST_MAX_NUM_NODES){
		tempIndex = nodeCount;
		All_Nodes[tempIndex].data = pItem;
		All_Nodes[tempIndex].index = tempIndex;
		All_Nodes[tempIndex].next = NULL;
		All_Nodes[tempIndex].prev = NULL;
	}
	// node out of bound
	else{
		tempIndex = freed_nodes[nodeCount];
		All_Nodes[tempIndex].data = pItem;
		All_Nodes[tempIndex].index = tempIndex;
		All_Nodes[tempIndex].next = NULL;
		All_Nodes[tempIndex].prev = NULL;
	}

	// dealing with the list
	pList->size++;
	// empty list
	if (pList->head == NULL){
		pList->head = &All_Nodes[tempIndex];
		pList->curr = &All_Nodes[tempIndex];
		pList->tail = &All_Nodes[tempIndex];
	}

	else if (pList->curr == NULL){
		if (pList->curr == pList->head->prev){
			All_Nodes[tempIndex].next = pList->head;
			All_Nodes[tempIndex].prev = pList->head->prev;
			pList->head = &All_Nodes[tempIndex];
			pList->curr = &All_Nodes[tempIndex];

		}
		else{
			All_Nodes[tempIndex].prev = pList->tail;
			pList->tail->next = &All_Nodes[tempIndex];
			pList->tail = &All_Nodes[tempIndex];
			pList->curr = &All_Nodes[tempIndex];
		}
	}
	else{
		if (pList->curr == pList->head){
			All_Nodes[tempIndex].next = pList->head;
			pList->head = &All_Nodes[tempIndex];
			pList->curr = &All_Nodes[tempIndex];
		}
		else{
			All_Nodes[tempIndex].next = pList->curr;
			All_Nodes[tempIndex].prev = pList->curr->prev;
			pList->curr->prev->next = &All_Nodes[tempIndex];
			pList->curr->prev = &All_Nodes[tempIndex];
		}
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
	pList->size++;
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
	pList->size++;
	return 0;
}


// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
	if (pList->curr == NULL){
		return NULL;
	}
	void* ptr = pList->curr;
	pList->curr = NULL;
	pList->curr = pList->curr->next;
	return ptr;
}


// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
	if (pList1->size + pList2->size >100)
	{
		return;
	}
	pList1->tail->next = pList2->head;
	pList1->tail = pList2->tail;
	pList1->size += pList2->size;
}
/*

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