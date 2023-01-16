//Author: Noam Karasso
#include "LinkedList.h"

LinkedList* BuildNode(char* data) {
	LinkedList* newNode = (LinkedList*)malloc(sizeof(LinkedList));
	newNode->data = _strdup(data);//copy the data including memory allocation for it
	newNode->next = NULL;

	return newNode;
}

LinkedList* addToStart(LinkedList* head, char* data) {
	LinkedList* newNode = BuildNode(data);
	newNode->next = head;
	return newNode;
}

LinkedList* addToEND(LinkedList* head, char* data) {
	LinkedList* newNode = BuildNode(data);

	if (head == NULL) {
		return newNode;
	}

	LinkedList* current = head;
	while (current->next != NULL) {//iterate through the list to add it to the end
		current = current->next;
	}

	current->next = newNode;

	return head;
}

LinkedList* FreeList(LinkedList* head) {
	LinkedList* current = head;

	while (current != NULL) {
		LinkedList* next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	return NULL;
}

LinkedList* DeleteElement(LinkedList* head, char* data) {
	LinkedList* current = head;

	// if we want to delete the head
	if (!strcmp(current->data, data)) {
		LinkedList* next = current->next;
		free(current->data);
		free(current);
		return next;
	}

	while (current->next != NULL) {
		if (strcmp(current->next->data, data) == 0) {
			LinkedList* next = current->next->next;
			free(current->next->data);
			free(current->next);
			current->next = next;
			return head;
		}
		current = current->next;
	}

	// if element was not found
	return head;
}