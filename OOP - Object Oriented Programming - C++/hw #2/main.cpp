// Author: Noam Karasso
// Score: 100
//#include <iostream>
//#include "EncryptText.h";
//#include "Text.h";
//#include "Word.h";
//#include <time.h>
//
//using namespace std;
//
//Text *buildText();//builds a text object and returns by pointer
//void encryptText(EncryptText& obj);//encrypts or decrypts using the object's status
//
//int main() {
//    Word w1(4, "thefsdg");
//    srand(time(NULL));
//    int arr[16] = { 3,-1,4, 1,-1,0, 1,0,4, 4,-1,2, 5,-1,2, -2 };//example for key to use
//    Text *textptr = buildText();
//    bool status = false;//start with encryption
//    EncryptText encrypt(*textptr, status);//build an EncryptText object using the text and status
//    encrypt += arr;//add the encryption / decryption key to the object
//    for (int i = 0; i < 2; i++) {//encrypt on first iteration
//        encryptText(encrypt);
//        encrypt.setStatus(!encrypt.getStatus());//change the status to 'decrypt' for second iteration
//    }
//    delete textptr;
//    return 0;
//}
//
//void encryptText(EncryptText& obj) {
//    if (obj.getStatus()) {
//        &obj;
//        cout << "The text after decryption is:\n" << obj << endl;
//    }
//    else {
//        !obj;
//        cout << "The text after encryption is:\n" << obj << endl;
//    }
//}
//Text* buildText() {
//int textSize;
//int wordSize;
//cout << "Enter the amount of words in the text(recommended 5 or more)\n";//recommended 5 to match the key example in main
//cin >> textSize;
//Word** wordsArr = new Word * [textSize];
//for (int i = 0; i < textSize; i++) {
//    char temp[10];
//    cout << "Enter a word\n";
//    cin >> temp;
//    wordsArr[i] = new Word(strlen(temp) + 1, temp);//sends to word ctor
//}
//Text* textPtr = new Text(textSize, wordsArr);
//cout << "The text is:\n" << *textPtr << endl;
//    return textPtr;//return by pointer to avoid sending to copy ctor and dtor
//}