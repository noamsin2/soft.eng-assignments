#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 100
#include "Word.h";
#include <iostream>
#include <time.h>
#include <assert.h>
#define N 11

using namespace std;

class Text {
private:
	Word** text;
	int nofWords;

public:
	Text(const int s, Word** wordsPtr);//ctor
	Text(const Text& other);//copy ctor
	~Text();//dtor
	//(return by reference to allow chaining and avoid making copies unnecessarily)
	Text& operator !();//switch numbers to 9 - 'the number' and from lower case letters to upper case(and the way around) and their complement
	Text& operator &();//reverse the word
	Text& operator <<(int n);//moves words 'n' to the left
	Text& operator >>(int n);//moves words 'n' to the right
	Text& operator +=(const int n);//add a random word in index 'n' with random size
	Text& operator -=(const int n);//remove a word from index 'n'
	Word& operator [](int n) const;//return the word in index 'n'
	friend ostream& operator << (ostream&, const Text& object);//print a text
};