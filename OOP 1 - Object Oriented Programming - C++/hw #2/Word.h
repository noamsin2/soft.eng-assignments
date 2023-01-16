#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 100
#include <iostream>
#include <time.h>
#include <assert.h>

using namespace std;

class Word {
private:
	int arraySize;
	char* word;
public:
	Word(const int s, const char* str);
	Word(const Word& other);
	~Word();
	//(return by reference to allow chaining and avoid making copies unnecessarily)
	Word& operator !();//switch numbers to 9 - 'the number' and from lower case letters to upper case(and the way around) and their complement
	Word& operator &();//reverse the word
	Word& operator <<(int n);//moves characters 'n' to the left
	Word& operator >>(int n);//moves character 'n' to the right
	Word& operator +=(const int n);//add a random char in index 'n'
	Word& operator -=(const int n);//remove a char from index 'n'
	char operator [](int n) const;//return the character in index 'n'
	friend ostream& operator << (ostream&, const Word& object);//print a word
};
