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
	}

}
int main (){
	printf("Starting tests...\n");

	List* ls = List_create();
	if (ls==NULL)
	{
		printf("List create failed.\n");
		return 0;
	}
	printf("List create succeed.\n");
	printf("There are %d nodes in the list.\n",List_count(ls));
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int k;
	
	k = List_add(ls, &a);
	k = List_add(ls, &b);
	//k = List_add(ls, &c);
	//k = List_add(ls, &d);
	printf("There are %d nodes in the list.\n",List_count(ls));
	//printList(ls);
	int* ad = List_first(ls);
	printf("The first node is %d.\n",*ad);
	ad = List_last(ls);
	printf("The last node is %d.\n",*ad);
	

	return 0;
}