#define _CRT_SECURE_NO_WARNINGS
//Author: Noam Karasso
//Score: 100
#include<stdio.h>
#include<stdlib.h>
#include"LinkedList.h"

int main()
{
	node* head = NULL;
	int num_min, mult_res, middle, sum_odd_ind;
	head = BuildList();
	PrintList(head);
	ifSorted(head);
	num_min = MinNode(head);
	printf("\nThe min value is: %d\n", num_min);
	mult_res = MultHeadTail(head);
	printf("\n(head->data)*(tail->data) = %d\n", mult_res);
	middle = MiddleList(head);
	printf("\nThe middle value is %d\n", middle);
	sum_odd_ind = SumOddIndex(head);
	printf("\nSum of Odd index = %d\n", sum_odd_ind);
	printf("\nSorted List: ");
	head = SortList(head);
	PrintList(head);
	ifSorted(head);
	printf("\nReversed list: ");
	ReverseList(&head);
	PrintList(head);
	head = FreeList(head);
	return 0;
}