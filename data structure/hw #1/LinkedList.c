#define _CRT_SECURE_NO_WARNINGS
//Author: Noam Karasso
//Score: 100

#include<stdio.h>
#include<stdlib.h>

typedef struct Node node;
struct Node {
	int data;
	node* next;
};

node* BuildNode(int num1)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = num1;
	new_node->next = NULL;
	return new_node;
}
node* BuildList()
{
	node *head = NULL, *temp = head;
	int num;
	printf("Enter nmbers for list, enter -1 for end: ");
	scanf("%d", &num);
	while (num != -1)
	{
		if (head == NULL)
		{
			head = BuildNode(num);
			temp = head;
		}
		else
		{
			temp->next = BuildNode(num);
			temp = temp->next;
		}
		scanf("%d", &num);
	}
	return head;
}
void PrintList(node *head)
{
	node* temp = head;
	printf("\nThe list is: ");
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

node* addToSortList(node *head, node *node_new)
{
	node *temp;
	if (head == NULL)
		return node_new;
	if (node_new->data < head->data)
	{
		node_new->next = head;
		return node_new;
	}
	for (temp = head; temp->next != NULL && node_new->data >= temp->next->data; temp = temp->next);
	node_new->next = temp->next;
	temp->next = node_new;
	return head;
}

node* SortList(node *head)
{
	node* temp, * new_head = NULL;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		temp->next = NULL;
		new_head = addToSortList(new_head, temp);
	}
	return new_head;
}

int SumOddIndex(node* head)
{
	int sum = 0;
	node* temp = head;
	for (int i = 1; temp != NULL; i++) {//for loop until temp points to null 
		if (i % 2 == 1)//if index is odd add the value to sum
			sum += temp->data;
		temp = temp->next;//temp points to the next node
	}
	return sum;
}

int MinNode(node* head) 
{
	int min = head->data;
	node* temp = head->next;
	while (temp != NULL) {
		if (temp->data < min)
			min = temp->data;
		temp = temp->next;
	}
	return min;
}

void ReverseList(node** head) 
{
	node* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	node* tempTail = temp;//variable to hold the tail node(head = tempTail later)
	node* reverseNode = temp;//use this variable to go backwards in the list
	while (reverseNode != *head) {
		temp = *head;
		while (temp->next != reverseNode) {
			temp = temp->next;
		}
		reverseNode->next = temp;//next gonna point to previous node(to reverse the list)
		reverseNode = temp;
	}
	reverseNode->next = NULL;
	*head = tempTail;
}

int MiddleList(node* head)
{
	node* temp = head;
	int listSize = 0;
	int midList;
	for (; temp != NULL; listSize++) {//first find the list size
		temp = temp->next;
	}
	temp = head;
	if (listSize % 2 == 0)
		midList = listSize / 2;
	else
		midList = (listSize / 2) + 1;
	for (int i = 1; i != midList; i++)
		temp = temp->next;
	return temp->data;
}

int MultHeadTail(node* head)
{
	node* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	return head->data * temp->data;
}

void ifSorted(node* head) 
{
	node* temp = head;
	//int prevData = temp->data;
	while (temp->next != NULL) {
		if (temp->data > temp->next->data) {
			printf("The List is not sorted\n");
			return;
		}
		temp = temp->next;
	}
	printf("The List is sorted\n");
}

node* FreeList(node* head)
{
	node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}
