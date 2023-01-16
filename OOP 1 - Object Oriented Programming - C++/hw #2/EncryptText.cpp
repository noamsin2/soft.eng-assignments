// Author: Noam Karasso
// Score: 100
#include "EncryptText.h";

EncryptText::EncryptText(Text& text,const bool status) :status(status) {
	textPtr = addressof(text);//'&' is taken so we use addressof
	key = nullptr;
}
EncryptText::~EncryptText() {
	delete[] this->key;
}
EncryptText& EncryptText::operator +=(const int* k) {
	int count = 0;
	while (k[count] != E)//E(-2) is the last number in the array
		count++;
	count++;//we want to include the -2 in too
	this->key = new int[count];
	for (int i = 0; i < count; i++)
		this->key[i] = k[i];
	return *this;
}
EncryptText& EncryptText::operator !() {
	operateText();//encrypts
	return *this;
}
EncryptText& EncryptText::operator &() {
	reverseEncrypt();//reverses the order and operators
	operateText();//"encrypts"
	return *this;
}
void EncryptText::reverseEncrypt() {
	int numCount = 0;
	for (; this->key[numCount] != E; numCount += 3) {//'for loop' that goes through the operators, adjusts them to decryption and counts the amount of numbers in key
		if (key[numCount] == 3 || key[numCount] == 5)
			key[numCount]++;//if the operator is << it turns it to >> by adding 1 | if the operator is += it turns it to -= by adding 1
		else if (key[numCount] == 4)
			key[numCount]--;//if the operator is >> it turns it to << by substracting 1
	}
	int* newKey = new int[numCount+1];
	newKey[numCount] = E;
	numCount--;
	for (int j = 0; numCount >= 0; j += 3) {//reverses the order
		for (int k = j+2; k >= j; k--) {
			newKey[k] = this->key[numCount];
			numCount--;
		}
	}
	delete[] this->key;
	this->key = newKey;
}
void EncryptText::operateText() {
	bool text;//true for operation on text false for operation on word
	for (int i = 0; this->key[i] != E; i += 3) {// (i + 0 = operation) (i + 1 = word / text) (i + 2 = parameter)
		if (this->key[i + 1] == -1)
			text = true;
		else text = false;
		switch (this->key[i]) {
		case 1:
			if (text) !*this->textPtr;//if text == true do operation on test
			else !this->textPtr[0][key[i + 2]];//else do operation on word using the parameter that was given
			break;
		case 2:
			if (text) &*this->textPtr;
			else &this->textPtr[0][key[i + 2]];
			break;
		case 3:
			if (text) *this->textPtr << key[i + 2];
			else this->textPtr[0][key[i + 2] / 10] << key[i + 2] % 10;//key[i+2] / 10 gives the first 2 digits key[i+2] % 10 gives the third digit
			break;
		case 4:
			if (text) *this->textPtr >> key[i + 2];
			else this->textPtr[0][key[i + 2] / 10] >> key[i + 2] % 10;//key[i+2] / 10 gives the first 2 digits key[i+2] % 10 gives the third digit
			break;
		case 5:
			if (text) *this->textPtr += key[i + 2];//adds a random word to text in index key[i+2]
			else this->textPtr[0][key[i + 2] / 10] += key[i + 2] % 10;//adds a random char to word in index key[i+2]/10 and to a char in index key[i+2]%10
			break;
		case 6:
			if (text) *this->textPtr -= key[i + 2];//removes a random word from text in index key[i+2]
			else this->textPtr[0][key[i + 2] / 10] += key[i + 2] % 10;//removes a random char from word in index key[i+2]/10 and from a char in index key[i+2]%10
			break;
		default:cout << "No operation was chosen\n";
		}
	}
}
ostream& operator << (ostream& output, const EncryptText& object) {
	output << object.textPtr[0];
	output << endl;
	return output;
}
void EncryptText::setStatus(bool mode) {
	status = mode;
}