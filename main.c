#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main (){
	printf("Starting tests...\n");
	struct nodeStruct *head = NULL;
	List* ls = List_create();
	if (ls==NULL)
	{
		printf("List create failed.\n");
		return 0;
	}
	printf("List create succeed.\n");
	
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int k;
	k = List_add(ls, &a);
	k = List_add(ls, &b);
	k = List_add(ls, &c);
	k = List_append(ls, &d);
	printf("There are %d nodes in the list.\n",List_count(ls));
	int* ad = List_first(ls);
	printf("The first node is %d.\n",*ad);
	ad = List_last(ls);
	printf("The last node is %d.\n",*ad);
	

	return 0;
}