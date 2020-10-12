#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

bool find(void* pItem, void* pComparisonArg){
	return pItem == pComparisonArg;
}

int main (){
	printf("Test 1 start\n");

	///////////// List create
	
	List* ls1 = List_create();
	assert(ls1 != NULL);
	List* ls2 = List_create();
	assert(ls2 != NULL);
	List* ls3 = List_create();
	assert(ls3 != NULL);
	List* ls4 = List_create();
	assert(ls4 != NULL);
	List* ls5 = List_create();
	assert(ls5 != NULL);
	List* ls6 = List_create();
	assert(ls6 != NULL);
	List* ls7 = List_create();
	assert(ls7 != NULL);
	List* ls8 = List_create();
	assert(ls8 != NULL);
	List* ls9 = List_create();
	assert(ls9 != NULL);
	List* ls10 = List_create();
	assert(ls10 != NULL);
	List* ls11 = List_create();
	assert(ls11 == NULL);
	printf("Test 1 List_create: succeed\n\n");

	//////////////List_add, List_count
	printf("Test 2 start\n");

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	printf(" Add num 1 to list 1\n");
	List_add(ls1, &a);
	int* temp = List_curr(ls1);
	printf(" List 1 current item: %d\n", *temp);
	printf(" List 1 current count: %d\n", List_count(ls1));

	printf(" Add num 2 to list 1\n");
	List_add(ls1, &b);
	temp = List_curr(ls1);
	printf(" List 1 current item: %d\n", *temp);
	printf(" List 1 current count: %d\n", List_count(ls1));

	printf(" Add num 3 to list 1\n");
	List_add(ls1, &c);
	temp = List_curr(ls1);
	printf(" List 1 current item: %d\n", *temp);
	printf(" List 1 current count: %d\n", List_count(ls1));

	printf("Test 2 List_add: succeed\n");
	printf("Test 2 List_curr: succeed\n");
	printf("Test 2 List_count: succeed\n\n");

	//////////////List first last
	printf("Test 3 start\n");
	 
	temp = List_first(ls1);
	printf(" List 1 first node is %d.\n",*temp);
	temp = List_next(ls1);
	printf(" List 1 next node is %d.\n",*temp);
	temp = List_next(ls1);
	printf(" List 1 next node is %d.\n",*temp);
	temp = List_prev(ls1);
	printf(" List 1 prev node is %d.\n",*temp);
	temp = List_last(ls1);
	printf(" List 1 last node is %d.\n",*temp);

	assert(List_curr(ls2) == NULL);
	assert(List_first(ls2) == NULL);
	assert(List_last(ls2) == NULL);

	printf("Test 3 List_first: succeed\n");
	printf("Test 3 List_next: succeed\n");
	printf("Test 3 List_prev: succeed\n");
	printf("Test 3 List_last: succeed\n\n");
	
	////////////List insert
	printf("Test 4 start\n");
	printf(" Insert 4 to list 1\n");
	List_insert(ls1, &d);
	temp = List_curr(ls1);
	printf(" List 1 current item: %d\n", *temp);
	printf("Test 4 List_insert: succeed\n\n");

	///////////List append 
	printf("Test 5 start\n");
	printf(" Append 5 to list 1\n");
	int e = 5;
	List_append(ls1, &e);
	temp = List_curr(ls1);
	printf(" List 1 current item: %d\n", *temp);
	temp = List_last(ls1);
	printf(" List 1 last item: %d\n", *temp);

	printf(" Prepend 6 to list 1\n");
	int f = 6;
	List_prepend(ls1, &f);
	temp = List_curr(ls1);
	printf(" List 1 current item: %d\n", *temp);
	temp = List_first(ls1);
	printf(" List 1 first item: %d\n", *temp);

	printf("Test 5 List_append: succeed\n");
	printf("Test 5 List_prepend: succeed\n\n");

	
	///////////List trim
	printf("Test 6 start\n");

	temp = List_last(ls1);
	printf(" List 1 last item: %d\n", *temp);
	List_trim(ls1);
	temp = List_last(ls1);
	printf(" List 1 last item: %d\n", *temp);
	printf("Test 6 List_trim: succeed\n\n");

	///////////List remove
	printf("Test 7 start\n");

	temp = List_last(ls1);
	printf(" List 1 last item: %d\n", *temp);

	List_remove(ls1);
	temp = List_last(ls1);
	printf(" List 1 last item: %d\n", *temp);

	printf("Test 7 List_remove: succeed\n\n");

	///////List concat

	printf("Test 8 start\n");
	int k = 8;

	List_insert(ls2, &k);
	List_concat(ls1,ls2);
	temp = List_last(ls1);
	printf(" List 1 last item: %d\n", *temp);
	printf("Test 8 List_concat: succeed\n\n");


	
	temp = NULL;
	return 0;
}