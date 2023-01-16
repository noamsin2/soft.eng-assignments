/*
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main() {
	char ch;
	printf("Please enter any character\n");
	scanf("%c", &ch);
	//we'll use values from the ascii chart to convert lower case letters to UPPER CASE letters
	if (ch >= 65 && ch <= 90) {
		printf("%c\n", ch + 32);
	}
	else if (ch >= 97 && ch <= 122) {
		printf("%c\n", ch - 32);
	}
	//if both of the above are false print the character 
	else {
		printf("%c\n", ch);
	}
	return 0;
}