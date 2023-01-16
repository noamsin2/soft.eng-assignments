// Assignment: 3
// Author: Noam Karasso
// Score : 100
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define M 81

char* buildString();
void freeString(char** str);
char* reduceString(char* str1, char* str2);
int sizeOfString(char* str);

int main()
{
    char** str = (char**)malloc(3 * sizeof(char*));
    if (str == NULL) {
        printf("Error! memory not allocated!\n");
        exit(EXIT_FAILURE);
    }
    *(str) = buildString();
    *(str + 1) = buildString();
    *(str + 2) = reduceString(*(str), *(str + 1));
    //print new string
    for (int i = 0; *(*(str + 2) + i) != '\0'; i++)
        printf(" %c", *(*(str + 2) + i));
    for (int j = 0; j < 3; j++) {
        freeString(*(str + j));
        *(str + j) = NULL;
    }
    free(str);
    str = NULL;
    exit(EXIT_SUCCESS);
}

void freeString(char** str) {
    free(str);
}

//function to find the length of a string
int sizeOfString(char* str) {
    int counter = 0;
    while (*(str + counter) != '\0')
        counter++;
    return counter;
}

char* buildString() {
    int str1c = 0;
    char* str = (char*)malloc(M * sizeof(char));
    if (str == NULL) {
        printf("Error! memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    printf("Please enter a string\n");
    gets_s(str, M - 1);

    str1c = sizeOfString(str);
    str1c++;//add 1 for the '\0' because we use it for the realloc
    str = realloc(str, (str1c) * sizeof(char));
    if (str == NULL) {
        printf("Error! memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    return str;
}

char* reduceString(char* str1, char* str2) {
    int str1c = 0;
    int str2c = 0;
    int index = 0, j = 0, i = 0;
    str1c = sizeOfString(str1);
    str2c = sizeOfString(str2);
    char* str3 = (char*)calloc(str2c + 1, sizeof(char));//str3 will never be bigger than str2 (+1 for '\0')
    if (str3 == NULL) {
        printf("Error! memory not allocated.\n");
        exit(EXIT_FAILURE);
    }
    char* temp = (char*)calloc(str1c + 1, sizeof(char));//temp will never be bigger than str1 (+1 for '\0')
    if (temp == NULL) {
        printf("Error! memory not allocated.\n");
        exit(EXIT_FAILURE);
    }
    //a very sofishticated code that took me a few hours to think of and put together
    while (i < str2c) {
        *(temp + j) = *(str2 + i);
        if (*(str2 + i) == *(str1 + j)) {
            j++;
            i++;
        }
        else {
            for (int k = 0; *(temp + k) != '\0'; k++) {
                *(str3 + index) = *(temp + k);
                index++;
                *(temp + k) = '\0';
            }
            j = 0;
            i++;
        }
        if (j == str1c) {
            for (int k = 0; k < j; k++)
                *(temp + k) = '\0';
            j = 0;
        }
        //condition for when it reaches the last chars so we don't lose them
        if (i == str2c) {
            for (int k = 0; *(temp + k) != '\0'; k++) {
                *(str3 + index) = *(temp + k);
                index++;
                *(temp + k) = '\0';
            }
        }
    }
    //no more use for that
    free(temp);
    temp = NULL;
    //the string has shrunk so we have to realloc it
    str3 = realloc(str3, (index + 1) * sizeof(char));
    if (str3 == NULL) {
        printf("Error! memory not allocated.\n");
        exit(EXIT_FAILURE);
    }
    return str3;
}