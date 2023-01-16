// Author: Noam Karasso
// Score: 100
#include "Word.h";

Word::Word(const int s, const char* str) :arraySize(s) {
	//assert(strlen(str) + 1 == arraySize);//string must match the size
	if (arraySize > 1) {//size must be at least 2 for 1 char + '\0'
		word = new char[arraySize];
		strcpy(word, str);
	}
	else
		word = nullptr;
}
Word::~Word() {
	delete[] word;
}
Word::Word(const Word& other):arraySize(other.arraySize) {
	if (arraySize > 1) {//string being copied must have at least 1 char
		word = new char[arraySize];
		strcpy(word, other.word);
	}
	else
		word = nullptr;
}
Word& Word::operator !() {
for (int i = 0; i < arraySize; i++) {
		if (this->word[i] >= '0' && this->word[i] <= '9')
			this->word[i] = '9' + '0' - this->word[i];
		else if (this->word[i] >= 'a' && this->word[i] <= 'z')
			this->word[i] = ('a' + 'z') - this->word[i] - ('a' - 'A');//complement and then switch to upper case
		else if (this->word[i] >= 'A' && this->word[i] <= 'Z')
			this->word[i] = ('A' + 'Z') - this->word[i] + ('a' - 'A');//complement and then switch to lower case		
	}
	return *this;
}
Word& Word::operator &() {
	char temp;
	int mirrorIndex = this->arraySize - 2;//takes the index of the last character and decreases it every iteration
	for (int i = 0; i < mirrorIndex; i++) {
		temp = this->word[i];
		this->word[i] = this->word[mirrorIndex];
		this->word[mirrorIndex] = temp;//lines 33-35 swap the characters
		mirrorIndex--;
	}
	return *this;
}
Word& Word::operator <<(int n) {
	while (n > this->arraySize - 2) {//added this loop to support 'n' thats bigger than the string size
		n -= (this->arraySize - 1);
	}
	if (n == 0) {//if n == 0 it doesn't move it anywhere anyway 
		return *this;
	}
	char* temp = new char[arraySize];//temp string to take the characters from the original string
	strcpy(temp, this->word);
	int index = 0;
	for (int i = 0; i < this->arraySize - 1; i++) {
		if (i + n >= this->arraySize - 1) {//if its beyond the string's limits from the right side
			this->word[i] = temp[index];//takes the value from the first spot
			index++;//next time it takes the value from the second spot
		}
		else//if its not beyond the limits
			this->word[i] = temp[i + n];
	}
	delete[] temp;
	return *this;
}
Word& Word::operator >>(int n) {
	while (n > this->arraySize - 2) {//added this loop to support 'n' thats bigger than the string size
		n -= this->arraySize - 1;
	}
	if (n == 0) {//if n == 0 it doesn't move it anywhere anyway 
		return *this;
	}
	char* temp = new char[arraySize];//temp string to take the characters from the original string
	strcpy(temp, this->word);
	int index = this->arraySize - 1 - n;//index of the value that goes to the new string's first index
	for (int i = 0; i < this->arraySize - 1; i++) {
		if (i - n < 0) {//if its beyond the string's limits from the left side
			this->word[i] = temp[index];
			index++;
		}
		else//if its not beyond the limits
			this->word[i] = temp[i - n];
	}
	delete[] temp;
	return *this;
}
char Word::operator [](int n) const {
	while (n < 0 || n >this->arraySize - 2) {
		cout << "the index you chose is not in range please enter a new one\n";
		cin >> n;
	}
	return this->word[n];
}
Word& Word::operator +=(const int n) {
	if (this->arraySize == 0) {//incase the word is empty and we want to add a character
		this->arraySize = 2;
		this->word = new char[2];
		do {//add a random character in the range of 0-z to the word not including symbols
			this->word[0] = '0' + rand() % ('z' + 1 - '0');
		} while ((this->word[0] > '9' && this->word[0] < 'A') || (this->word[0] > 'Z' && this->word[0] < 'a') || this->word[0] > 'z');
		this->word[1] = '\0';
		return *this;
	}
	if (n > this->arraySize - 1) {
		cout << "out of boundaries, can't add\n";
		return *this;
	}
	int j = n;// use it later to add the '\0'
	this->arraySize += 1;
	char* newWord = new char[this->arraySize];
	for (int i = 0; i < n; i++)//copy the characters before the one we want to add
		newWord[i] = this->word[i];
	do {	//add a random character in the range of 0-z to the word not including symbols
		newWord[n] = '0' + rand() % ('z'+1 - '0');
	} while ((newWord[n] > '9' && newWord[n] < 'A') || (newWord[n] > 'Z' && newWord[n] < 'a') || newWord[n] > 'z');
	
	for (; j < this->arraySize - 2; j++)//copy the rest of the characters from the old string
		newWord[j + 1] = this->word[j];
	newWord[j + 1] = '\0';
	delete[] this->word;
	this->word = newWord;
	return *this;
}
Word& Word::operator -=(const int n) {
	int j = n;// use it later to add the '\0'
	if (n > this->arraySize - 2) {
		cout << "out of boundaries, can't remove\n";
		return *this;
	}
	char* newWord = new char[this->arraySize - 1];
	for (int i = 0; i < n; i++)//copy the characters before the one we want to remove
		newWord[i] = this->word[i];
	for (; j < this->arraySize - 2; j++)//copy the rest of the characters from the old string
		newWord[j] = this->word[j + 1];
	newWord[j] = '\0';
	delete[] this->word;
	this->word = newWord;
	return *this;
}
ostream& operator << (ostream& output, const Word& object) {
	for (int i = 0; i < object.arraySize - 1; i++)
		output << object.word[i];
	return output;
}