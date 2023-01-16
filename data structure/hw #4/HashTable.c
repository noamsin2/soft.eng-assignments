//Author: Noam Karasso
#include "HashTable.h"
int constantStringHashFunction(char* str) {
	//for every string return 3 and we assume the string is not null
	return 3;
}
int accumulateStringHashFunction(char* str) {
	int sum = 0;
	for (int i = 0; str[i] != '\0'; i++)//until reaches end of string
		sum += str[i];//this is gonna convert the ascii value of the letter and add it to sum
	return sum;
}

int improvedHashFunction(char* str) {
	int sum = 0;
	double length = strlen(str);//length of str
	//for until it reaches end of string
	for (int i = 0; str[i] != '\0'; i++) {
		sum += str[i] * pow(31, length - 1 - i);//according to the formula sum of the ascii value multiply by 31 in the power of (length - 1 - i)
	}
	return sum;
}
HashTable* initTable(int tableSize, int hashFunction) {
	//create a table
	HashTable* ourHash = (HashTable*)malloc(sizeof(HashTable));
	//allocate memory for the cells
	ourHash->hashTable = (HashTableElement*)malloc(sizeof(HashTableElement) * tableSize);
	for (int i = 0; i < tableSize; i++) {
		ourHash->hashTable[i].chain = NULL;//initialize them to NULL
		ourHash->hashTable[i].key = i;
	}
	ourHash->tableSize = tableSize;
	ourHash->hashFunction = hashFunction;
	ourHash->cellsTaken = 0;
	ourHash->numOfElements = 0;
	return ourHash;
	
}
int hash(char* str, HashTable* ht) {
	int index;
	
	//choose a function to use according to the value of ht->hashFunction
	switch (ht->hashFunction) {
	case 1://constant hash function
		index = fmod(fabs(constantStringHashFunction(str)), ht->tableSize);//fmod function returns the remainder of
		//fabs(constantStringHashFunction(str)) divided by the table size
		//fabs function returns the absolute value of constantStringHashFunction(str)
		break;
	case 2://accumulate hash function
		index = fmod(fabs(accumulateStringHashFunction(str)), ht->tableSize);
		break;
	case 3://improved hash function
		index = fmod(fabs(improvedHashFunction(str)), ht->tableSize);
	}
	return index;
}
int insert(HashTable* ht, char* str) {
	if (str == NULL || search(ht,str))
		return 0;//if invalid string or the string is already in the hashtable dont do anything and return 0
	//else we put the string in the correct key in the hashtable
	int index = hash(str, ht);
	//makes a node with the string given
	LinkedList* newNode = BuildNode(str);

	//make the node point at the current head of the chain
	newNode->next = ht->hashTable[index].chain;
	//make the new node the head of the chain
	ht->hashTable[index].chain = newNode;

	ht->numOfElements++;
	//if the cell was empty before, add 1 to cellsTaken
	if (ht->hashTable[index].chain->next == NULL) {
		ht->cellsTaken++;
	}

	return 1;
}
int search(HashTable* ht, char* str) {
	if (str == NULL)
		return 0;
	int index = hash(str, ht);//find the index of the string
	LinkedList* chain = ht->hashTable[index].chain;//get the chain of elements for this index
	//search for the string
	while (chain != NULL) {
		if (!strcmp(chain->data, str))
			return 1;//found string
		chain = chain->next;
	}
	//couldn't find string
	return 0;
}
int deleteElement(HashTable* ht, char* str) {
	if (str == NULL || !search(ht, str))//if the string doesnt exist in the table dont do anything and return 0
		return 0;
	int index = hash(str, ht);
	LinkedList* chain = ht->hashTable[index].chain;//get the chain of elements for this index
	if (DeleteElement(chain, str) == NULL)//if the delete node is the only one in the list
		ht->hashTable[index].chain = NULL;
	return 1;
}