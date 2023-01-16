// Assignment: 3
// Author: Noam Karasso
// Score : 100
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 81

char* buildString();
void printString(char* str);
char* changeString(char* str);
int sizeOfString(char* str);

int main()
{
   char** str = (char**)malloc(2 * sizeof(char*));
   *(str) = buildString();;
   *(str + 1) = changeString(*(str));
   printString(*(str+1));
   free(*(str));
   *(str) = NULL;
   free(*(str + 1));
   *(str + 1) = NULL;
   free(str);
   str = NULL;

   exit(EXIT_SUCCESS);
}

//function to find the length of a string
int sizeOfString(char* str) {
   int counter = 0;
   while (*(str + counter) != '\0')
       counter++;
   return counter;
}

void printString(char* str) {
   for (int i = 0; *(str + i) != '\0'; i++)
       printf(" %c", *(str + i));
}

char* changeString(char* str) {
   int str1c = sizeOfString(str);
   int index = 0;//index counter, increases each time we put a char in newStr
   str1c *= 9;//multiply by 9 incase the user filled it with only 9's
   char* newStr = (char*)malloc(str1c * sizeof(char));
   if (newStr == NULL) {
       printf("Error! memory not allocated!\n");
       exit(EXIT_FAILURE);
   }
   //for numbers between 0 an 9
   for (int i = 0; *(str + i) != '\0'; i++) {
       if (*(str + i) >= 48 && *(str + i) <= 57) {
           for (int j = 48; j < *(str + i); j++) {
               *(newStr + index) = *(str + i);
               index++;
           }       
       }
       if (*(str + i) == ' ' && *(str + i - 1) != ' ') {
           *(newStr + index) = '-';
           index++;
       }
       if ((*(str + i) >= 65 && *(str + i) <= 90) || (*(str + i) >= 97 && *(str + i) <= 122)) {//if *(str+i)is a letter
           if (!((*(str + i - 1) >= 65 && *(str + i - 1) <= 90) || (*(str + i - 1) >= 97 && *(str + i - 1) <= 122))) {//if *(str+1-1) is not a letter
               *(newStr + index) = '*';
               index++;
           }
       }
   }
   //realloc new string
   newStr = realloc(newStr, (index+1) * sizeof(char));
   if (str == NULL) {
       printf("Error! memory not allocated!\n");
       exit(EXIT_FAILURE);
   }
   *(newStr + index) = '\0';

   return newStr;
}

char* buildString() {
   int str1c = 0;
   char* str = (char*)malloc(M * sizeof(char));
   if (str == NULL) {
       printf("Error! memory not allocated\n");
       exit(EXIT_FAILURE);
   }
   gets_s(str, M - 1);

   str1c = sizeOfString(str);
   str1c++;//add 1 for the '\0' because we use it for the realloc
   str = realloc(str, str1c * sizeof(char));
   if (str == NULL) {
       printf("Error! memory not allocated\n");
       exit(EXIT_FAILURE);
   }
   return str;
}