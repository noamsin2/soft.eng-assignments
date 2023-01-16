// Assignment: 5
// Author: Noam Karasso
// Score: 90, -10 points in part 1, not using recursion
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define N 15

typedef struct Data {
	int arr[N];
	float avg;
	int mid;
} Data;

typedef struct Node {
	Data data;
	struct Node* next;
}Node;

typedef struct LinkedList{
	Node * head;
	Node * tail;
}LinkedList;

void insertArray(int arr[], int size);
void insertNode(Node* node);
void sortArray(int arr[], int size);//a simple function to sort the array
Node* findNode(float number, LinkedList list);
void addNode(Node* node, LinkedList* list);
void deleteNode(int number, LinkedList* list);
void buildLinkedList(int number, LinkedList* list);
void freeLinkedList(LinkedList* list);//free up all the memory we allocated for the nodes

//example for main to use
int main() {
	LinkedList list1;
	Node* nPtr = NULL;
	buildLinkedList(2, &list1);
	nPtr = findNode(10, list1);
	printf("\n%f\n", nPtr->data.avg);
	deleteNode(1, &list1);
	freeLinkedList(&list1);
}

void freeLinkedList(LinkedList* list) {
	Node* nPtrTemp;
	while (list->head != NULL) {
		nPtrTemp = list->head;//temp pointer to point to the head of the list
		list->head = list->head->next;//move the head pointer to make the next one the head
		free(nPtrTemp);//free the prvious head
	}//repeat until we freed everything
	list->head = NULL;
	list->tail = NULL;
}

void buildLinkedList(int number, LinkedList* list) {
	Node* nPtrTemp = NULL;
	Node* node1 = (Node*)malloc(sizeof(Node));//make the first node in the list
	if (node1 == NULL) {
		printf("Error! memory not allocated\n");
		exit(EXIT_FAILURE);
	}
	list->head = node1;
	list->tail = node1;
	insertNode(node1);
	for (int i = 1; i < number; i++) {//make the rest of the nodes
		nPtrTemp = (Node*)malloc(sizeof(Node));
		if (nPtrTemp == NULL) {
			printf("Error! memory not allocated\n");
			exit(EXIT_FAILURE);
		}
		insertNode(nPtrTemp);
		addNode(nPtrTemp, list);
	}
}

void addNode(Node* node, LinkedList* list) {
	list->tail->next = node;//make the last node point to this node
	list->tail = node;//make the tail point to this node so this one becomes the last node
}

void deleteNode(int number, LinkedList* list) {
	Node* nPtr = list->head;
	Node* nPtrTemp = NULL;
	int count = 0;
	if (number == 1) {
		list->head = list->head->next;//make the head point to the next node in the list(if its the only node then it points to NULL)
		free(nPtr);//delete the node
	}
	else {
		for (int i = 1; i < number - 1; i++)
			nPtr = nPtr->next;
		nPtrTemp = nPtr->next;//point the temp to the node we want to delete
		nPtr->next = nPtr->next->next;//"skip over" the node we want to delete
		free(nPtrTemp);//delete it
	}
}

Node* findNode(float number, LinkedList list) {
	float minDif;//a variable that acts as the minimum difference between all nodes' avg and the needed avg
	float tempDif;
	Node* nPtr = list.head;
	Node* nPtrTemp = list.head;
	minDif = (float)nPtr->data.avg - number;//mindif set it the the first one
	if (minDif < 0)//we want the absolute value of the number so we do that if its a negative num
		minDif *= -1;
	while (nPtr->next != NULL) {
		nPtr = nPtr->next;//we do it to go through all the nodes in the list
		tempDif = (float)nPtr->data.avg - number;
		if (tempDif < 0)
			tempDif *= -1;
		if (tempDif < minDif) {
			nPtrTemp = nPtr;
			minDif = tempDif;
		}
	}
	return nPtrTemp;
}

void insertNode(Node* node) {
	int sum = 0;
	insertArray(node->data.arr, N);
	sortArray(node->data.arr, N);
	for (int i = 0; i < N; i++)
		sum += node->data.arr[i];
	node->data.avg = (float)sum / N;
	node->data.mid = node->data.arr[N/2];
	node->next = NULL;
}

void insertArray(int arr[], int size) {
	printf("Please enter the array\n");
	for (int i = 0; i < size; i++)
		scanf("%d", &arr[i]);
}

void sortArray(int arr[], int size) {
	int min, temp, index = 0;
	for (int j = 0; j < size - 1; j++) {
		min = arr[j];
		for (int i = j; i < size - 1; i++) {
			if (min > arr[i + 1]) {
				min = arr[i + 1];
				index = i + 1;
			}
		}
		temp = arr[j];
		arr[j] = min;
		if (index > 0)
		arr[index] = temp;
		index = 0;
	}
}