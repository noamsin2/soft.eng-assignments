#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 100
#include "Text.h";
#include "Word.h";
#include <iostream>
#include <time.h>

#define E -2

class EncryptText {
private:
	Text* textPtr;
	bool status;//false for encrypt, true for decrypt
	int* key;
	void operateText();//function that will be used by the encrypt / decrypt functions
	void reverseEncrypt();//function that takes the key and reverses it's order turning it from encryption to decryption
public:
	EncryptText(Text& text,const bool status);//CTor
	~EncryptText();//DTor
	bool getStatus() { return status; };//get func for status
	void setStatus(bool mode);//set func for status
	EncryptText& operator +=(const int* k);//add a key
	EncryptText& operator !();//encrypt text
	EncryptText& operator &();//decrypt text
	friend ostream& operator << (ostream&, const EncryptText& object);//print an encrypted text
};