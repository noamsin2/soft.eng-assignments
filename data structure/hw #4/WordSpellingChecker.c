//Author: Noam Karasso
#include "WordSpellingChecker.h"

int isWordInDictionary(HashTable* dictionaryTable, char* word) {
	if (word == NULL)
		return 0;
	if (search(dictionaryTable, word))//use the search function to check if its in the dictionary
		return 1;
	return 0;
}

LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word) {
	int i;
	LinkedList* head = NULL;
	LinkedList* temp = NULL;
	for (i = 1; i < strlen(word); i++) {
		char* word1 = (char*)malloc((i + 1) * sizeof(char));
		int index = 0;
		strncpy(word1, word, i);//copy the first i characters to word1
		word1[i] = '\0';
		char* word2 = (char*)malloc((strlen(word) - i + 1) * sizeof(char));
		for (int j = i; j < strlen(word); j++) {//copy the rest to word2
			word2[index] = word[j];
			index++;
		}
		word2[index] = '\0';
		if (isWordInDictionary(dictionaryTable, word1) && isWordInDictionary(dictionaryTable, word2))
		{//the size of the words merge is the size of the original word + end of string char + space
			char* wordsMerge = (char*)malloc((strlen(word) + 2) * sizeof(char));
			strncpy(wordsMerge, word1, i);//copy the first 'i' chars
			wordsMerge[i] = ' ';//add a space
			int index = i + 1;
			for (int j = i; j < strlen(word); j++) {
				wordsMerge[index] = word[j];//add word2
				index++;
			}
			wordsMerge[index] = '\0';
			head = addToEND(head, wordsMerge);
			free(wordsMerge);//free the memory for the word we duplicated in BuildNode function
		}
		free(word1);//no longer in use
		free(word2);//no longer in use
	}
	return head;
}

LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word) {
	LinkedList* head = NULL;
	LinkedList* temp = NULL;
	char* newword = (char*)malloc((strlen(word) + 1) * sizeof(char));//alloc mem
	strcpy(newword, word);//copy the original word
	for (int i = 0; i < strlen(word); i++) {//for loop to iterate through all letters in the word
		for (int j = 0; j < 'z' - 'a'; j++) {//for loop to iterate through all letters in english alphabet
			newword[i] = 'a' + j;
			if (!strcmp(newword, word))//so we dont save the original word in the list
				continue;
			if (isWordInDictionary(dictionaryTable, newword))
			{
				head = addToEND(head, newword);
			}
		}
		newword[i] = word[i];//reverse the word to the original word after its done with a letter
	}
	free(newword);
	return head;
}

LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word) {
	LinkedList* head = NULL;
	LinkedList* temp = NULL;
	char* newword = (char*)malloc(strlen(word) * sizeof(char));//size of word - 1 + '\0'
	for (int i = 0; i < strlen(word); i++) {//iterate every letter in the word
		int index = 0;
		for (int j = 0; j < strlen(word); j++) {//copy the word except for the 'i' letter
			if (j != i) {
				newword[index] = word[j];
				index++;
			}
		}
		newword[index] = '\0';
		if (isWordInDictionary(dictionaryTable, newword))
		{
			head = addToEND(head, newword);
		}
	}
	free(newword);
	return head;
}

LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word) {
	LinkedList* head = NULL;
	LinkedList* temp = NULL;
	char* newword = (char*)malloc((strlen(word) + 2) * sizeof(char));//alloc mem for word size + 1 + '\0'
	for (int i = 0; i < strlen(word) + 1; i++) {//for loop to iterate through all letters in the word
		int index = 0;
		for (int j = 0; j < strlen(newword); j++) {//for loop to copy all letters from original word to the new word
			if (j != i) {
				newword[j] = word[index];
				index++;
			}
			else
				newword[j] = ' ';//this isn't necessary but easier to think of it this way, the new letter should go here
		}
		for (int j = 0; j < 'z' - 'a'; j++) {//for loop to iterate through all letters in english alphabet
			newword[i] = 'a' + j;
			if (isWordInDictionary(dictionaryTable, newword))
			{
				head = addToEND(head, newword);
			}
		}
	}
	free(newword);
	return head;
}

LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word) {
	LinkedList* head = NULL;
	LinkedList* temp = NULL;
	char* newword = (char*)malloc((strlen(word) + 1) * sizeof(char));//alloc mem
	for (int i = 0; i < strlen(word) - 1; i++) {//for loop to iterate through all letters in the word
		strcpy(newword, word);//copy the original word
		newword[i] = word[i + 1];
		newword[i + 1] = word[i];
		if (isWordInDictionary(dictionaryTable, newword)){
			head = addToEND(head, newword);
		}
	}
	free(newword);
	return head;
}

/*helping functions for the getWordSuggestions() function below*/

//function to chain all the suggestions to one list
LinkedList* makeSuggestionList(HashTable* dictionaryTable, char* word) {
	//a very boring function...
	LinkedList* head = addSpaceCheck(dictionaryTable, word);
	LinkedList* temp = NULL;
	if (head == NULL)
		head = replaceCharacterCheck(dictionaryTable, word);
	else {
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = replaceCharacterCheck(dictionaryTable, word);
	}
	if (head == NULL)
		head = deleteCharacterCheck(dictionaryTable, word);
	else {
		if (temp == NULL)
			temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = deleteCharacterCheck(dictionaryTable, word);
	}
	if (head == NULL)
		head = addCharacterCheck(dictionaryTable, word);
	else {
		if (temp == NULL)
			temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = addCharacterCheck(dictionaryTable, word);
	}
	if (head == NULL)
		head = switchAdjacentCharacterCheck(dictionaryTable, word);
	else {
		if (temp == NULL)
			temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = switchAdjacentCharacterCheck(dictionaryTable, word);
	}
	return head;
}

//function that gets a list and deletes all duplicates in it
LinkedList* deleteDups(HashTable* list, char* word) {
	LinkedList* temp1 = list;
	LinkedList* temp2 = NULL;
	//while loops to iterate through temp1 and temp2 to check if there are duplicates
	while (temp1 != NULL) {
		temp2 = temp1->next;
		while (temp2 != NULL) {
			if (!strcmp(temp1->data, temp2->data) || !strcmp(temp2->data,word)) {
				LinkedList* tempNode = temp1;
				while (tempNode->next != temp2)
					tempNode = tempNode->next;
				tempNode->next = temp2->next;//"skip over temp2's node"
				free(temp2);
				temp2 = tempNode->next;
			}
			else {
				temp2 = temp2->next;
			}
		}
		temp1 = temp1->next;
	}
	return list;
}

LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word) {
	LinkedList* list = NULL;
	if (dictionaryTable == NULL || word == "" || word == NULL)
		return list;
	list = makeSuggestionList(dictionaryTable, word);//get all suggestions for each word
	list = deleteDups(list, word);//delete all duplicate suggestions
	return list;
}
