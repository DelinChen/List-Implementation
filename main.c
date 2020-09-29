#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void printList(List* pList){
	if (pList == NULL)
	{
		printf("NULL list!\n");
		return;
	}
	if (pList->size == 0)
	{
		printf("EMPTY list!\n");
		return;
	}
	Node* tmp = pList->head;
	for (int i = 0; i < pList->size; ++i)
	{
		printf("%s ", tmp->data);
		tmp = tmp->next;
	}

}
int main (){
	printf("Starting tests...\n");
	List* ls1;

	// Test 1
	printf("Testing List_create\n");
	ls1 = List_create();
	if (ls1==NULL){
		printf("List create failed.\n");
		return 0;
	}
	printf("List create succeed.\n");
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int k;
	
	k = List_add(ls1, &a);
	k = List_add(ls1, &b);
	k = List_add(ls1, &c);
	k = List_add(ls1, &d);
	printf("There are %d nodes in the list.\n",List_count(ls1));
	//printList(ls1);
	int* ad = List_first(ls1);
	printf("The first node is %d.\n",*ad);
	ad = List_last(ls1);
	printf("The last node is %d.\n",*ad);
	

	return 0;
}