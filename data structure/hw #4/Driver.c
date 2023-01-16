#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

int parseWordsToTable(char* path, HashTable* ht);
SpellingSuggestion* spellingCheck(char* text);
LinkedList* textToWords(HashTable* dictionary, char* text);
void printSpellingSuggestions(SpellingSuggestion* spellingSuggestions);

void printSpellingSuggestions(SpellingSuggestion* spellingSuggestions) {
	if (spellingSuggestions->originalWord == NULL)//if the spellingSuggestions object is empty
		return;
	while (spellingSuggestions != NULL) {//iterate through all misspelled words
		if (spellingSuggestions->suggestions == NULL) {//if no suggestions were found for the word
			printf("The word '%s' was misspelled. No suggestions found for this word.\n", spellingSuggestions->originalWord);

		}
		else {//if there are suggestions iterate through all of them and print
			printf("The word '%s' was misspelled. Did you mean:\n", spellingSuggestions->originalWord);
			LinkedList* temp = spellingSuggestions->suggestions;//save the suggestions to a temp before iterating through them
			while (spellingSuggestions->suggestions != NULL) {
				printf("%s\n", spellingSuggestions->suggestions->data);
				spellingSuggestions->suggestions = spellingSuggestions->suggestions->next;
			}
			spellingSuggestions->suggestions = temp;//this is important to do so we don't lose the suggestions
		}
		if (spellingSuggestions->next != NULL)//if there are more words in the object print a comma
			printf(", ");
		spellingSuggestions = spellingSuggestions->next;//go to next misspelled word
	}
}

int parseWordsToTable(char* path, HashTable* ht) {
	if (ht == NULL)
		return 0;
	FILE* fptr = fopen(path, "r");//open file to reading
	if (fptr == NULL) {//if couldn't open
		printf("COULD NOT OPEN FILE\n");
		return 0;
	}
	char* word = (char*)malloc(20 * sizeof(char));
	while (fscanf(fptr, "%s", word) != EOF)
		//we assume all the words in the text are unique
		if (!insert(ht, word))//insert the word into the table and if it didn't insert for some reason leave the function
			return 0;
	free(word);
	fclose(fptr);//close the file
	return 1;
}

SpellingSuggestion* spellingCheck(char* text) {
	SpellingSuggestion* head = NULL;
	SpellingSuggestion* temp = NULL;
	if (text == NULL || text == "")
		return head;
	HashTable* dictionary = initTable(3000, 3);//initialize empty hash table
	parseWordsToTable("dictionary.txt", dictionary);//move dictionary text to hash table
	
	LinkedList* textList = textToWords(dictionary,text);//transform all the words in the text to list of words
	
	if (textList == NULL) {//if no incorrect words were found
		head = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
		head->originalWord = NULL;
		head->suggestions = NULL;
		head->next = NULL;
	}
	else {
		textList = deleteDups(textList, "");//function to remove duplicates
		LinkedList* tempText = textList;

		//loop to iterate through the list of words and get suggestions for each
		while (tempText != NULL) {
			if (head == NULL) {
				head = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
				temp = head;
			}
			else {
				temp->next = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
				temp = temp->next;
			}
			temp->originalWord = tempText->data;
			temp->suggestions = getWordSuggestions(dictionary, temp->originalWord);

			tempText = tempText->next;
		}
		temp->next = NULL;
	}
	//free all the memory that was allocated in the proccess and we dont use anymore
	for (int i = 0; i < 3000; i++) {
		if (dictionary->hashTable[i].chain != NULL) {
			FreeList(dictionary->hashTable[i].chain);
		}
	}
	free(dictionary->hashTable);
	free(dictionary);
	//FreeList(textList);
	return head;
}

//helping function that breaks a string into words(only incorrectly spelled words) and returns it as a linked list
LinkedList* textToWords(HashTable* dictionary,char* text) {
	LinkedList* textList = NULL;
	int counter = 1;
	//separate the text to words
	for (int i = 0; text[i] != '\0'; i++) {
		if (text[i+1] == ' ' || text[i+1] == '\0') {
			char* word = (char*)malloc((counter+1) * sizeof(char));
			int index = 0;
			
			for (; counter > 0; counter--) {//copy the word
				word[index] = text[i - counter+1];
				index++;
			}
			word[index] = '\0';
			if (isWordInDictionary(dictionary, word)) {//if its a valid word no need to add it to the list
				free(word);
				continue;
			}
			textList = addToEND(textList, word);//chain it to the end of the list
			free(word);
			continue;
		}
		counter++;//count how many letters in every word

	}
	return textList;
}
//function to free suggestions memory
void freeSuggestions(SpellingSuggestion* head) {
	SpellingSuggestion* current = head;

	while (current != NULL) {
		SpellingSuggestion* next = current->next;
		FreeList(current->suggestions);//free the suggestions list using the linkedlist freelist function
		free(current->originalWord);
		free(current);//free a node in the SpellingSuggestion object
		current = next;//move to next
	}

	return NULL;
}
int main()
{
	char* text = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	//portal is a really good game
	SpellingSuggestion* spellingSuggestions = spellingCheck(text);
	printSpellingSuggestions(spellingSuggestions);
	freeSuggestions(spellingSuggestions);
	return 0;
}
