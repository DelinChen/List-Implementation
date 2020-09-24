#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main (){
	printf("Starting tests...\n");
	struct nodeStruct *head = NULL;
	List* ls = List_create();

	int s = List_count(ls);
	printf("%d\n",s);

	

	return 0;
}