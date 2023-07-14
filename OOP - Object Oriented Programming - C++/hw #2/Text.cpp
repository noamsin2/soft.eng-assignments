// Author: Noam Karasso
// Score: 100
#include "Text.h";
Text::Text(const int s,Word** wordsPtr) : nofWords(s) {
		text = wordsPtr;
}
Text::Text(const Text& other) /*: nofWords(other.nofWords) */{
	nofWords = other.nofWords;
	if (nofWords > 0) {
		text = new Word *[nofWords];
		for (int i = 0; i < nofWords; i++) {
			text[i] = new Word (*(other.text[i]));//sends to Word's copy constructor
		}
	}
	else
		text = nullptr;
}
Text::~Text() {
	for (int i = 0; i < nofWords; i++)
		delete text[i];
	delete[]text;
}
Text& Text::operator !() {
	for (int i = 0; i < this->nofWords; i++)
		!(*this->text[i]);//using the '!' operator from Word for each separate word
	return *this;
}
Text& Text::operator &() {
	int mirrorIndex = this->nofWords - 1;//takes the index of the last word and decreases it every iteration
	for (int i = 0; i < mirrorIndex; i++) {
		Word *tempPtr = this->text[i];
		this->text[i] = this->text[mirrorIndex];
		this->text[mirrorIndex] = tempPtr;//lines 33-35 swap the words
		mirrorIndex--;
	}
	return *this;
}
Text& Text::operator <<(int n) {
	while (n > this->nofWords - 1) {//added this loop to support 'n' thats bigger than the text size
		n -= (this->nofWords);
	}
	if (n == 0) {//if n == 0 it doesn't move it anywhere anyway 
		return *this;
	}
	Word** tempPtr = new Word * [this->nofWords];
	int index = 0;
	for (int i = 0; i < this->nofWords; i++) {//this loop always starts from the 'else' part on the first 'nofWords - n' iterations
		tempPtr[i] = this->text[i];
		if (i + n >= this->nofWords) {//if its beyond the text's limits from the right side
			this->text[i] = tempPtr[index];//takes the first word and so on
			index++;
		}
		else {//if its not beyond the limits
			this->text[i] = this->text[i + n];
		}
	}
	delete[] tempPtr;
	return *this;
}
Text& Text::operator >>(int n) {
	while (n > this->nofWords - 1) {//added this loop to support 'n' thats bigger than the text size
		n -= (this->nofWords);
	}
	if (n == 0) {//if n == 0 it doesn't move it anywhere anyway 
		return *this;
	}
	Word** tempPtr = new Word * [this->nofWords];
	int index = this->nofWords - n;//index of the word that goes to the new text's first word
	for (int i = 0; i < this->nofWords; i++) {//this loop always starts from the 'else' part on the first 'nofWords - n' iterations
		tempPtr[i] = this->text[i];
		if (i - n < 0) {//if its beyond the text's limits from the left side
			this->text[i] = text[index];
			index++;
		}
		else {//if its not beyond the limits
			this->text[i] = tempPtr[i - n];
		}
	}
	delete[] tempPtr;
	return *this;
}
Text& Text::operator +=(const int n) {
	if (n > this->nofWords) {
		cout << "out of boundaries, can't add\n";
		return *this;
	}
	this->nofWords++;
	Word** newText = new Word * [nofWords];
	int wordSize = 1 + rand() % 9;//generating random number from 1 to 9
	char* tempWord = new char[wordSize + 1];//+1 for '\0'
	for (int i = 0; i < wordSize; i++) {
		do {	//add a random character in the range of 0-z to the word not including symbols
			tempWord[i] = '0' + rand() % ('z' + 1 - '0');
		} while ((tempWord[i] > '9' && tempWord[i] < 'A') || (tempWord[i] > 'Z' && tempWord[i] < 'a') || tempWord[i] > 'z');
	}
	tempWord[wordSize] = '\0';
	newText[n] = new Word(wordSize + 1, tempWord);//sends to the Word CTor
	for (int i = 0; i < n; i++)//move the words before the 'n'
		newText[i] = this->text[i];
	for (int i = n + 1; i < this->nofWords; i++)//move the words after the 'n'
		newText[i] = this->text[i - 1];

	delete[] this->text;
	this->text = newText;
	delete[] tempWord;
	return *this;
}
Text& Text::operator -=(const int n) {
	if (n >= this->nofWords || this->nofWords == 0) {//if the index we got is not in the range or the text is empty
		cout << "out of boundaries, can't remove\n";
		return *this;
	}
	this->nofWords--;
	Word** newText = new Word * [nofWords];
	for (int i = 0; i < n; i++)//move the words before the 'n'
		newText[i] = this->text[i];
	for (int i = n; i < this->nofWords; i++)//move the words after the 'n'
		newText[i] = this->text[i + 1];
	delete this->text[n];
	delete[] this->text;
	this->text = newText;
	return *this;
}
Word& Text::operator [](int n) const {
	while (n < 0 || n >= this->nofWords) {//repeat until the index of the word is in the text's range
		cout << "the index you chose is not in range please enter a new one\n";
		cin >> n;
	}
	return *this->text[n];
}
ostream& operator << (ostream& output, const Text& object) {
	for (int i = 0; i < object.nofWords; i++)
		output << *object.text[i] << ' ';
	output << endl;
	return output;
}