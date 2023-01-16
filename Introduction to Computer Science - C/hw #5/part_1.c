// Assignment: 5
// Author: Noam Karasso
// Score: 90, -10 points in part 1 not using recursion
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

float getTheItemN(int n);
int isContainNumber(char* str);
int isSorted(int arr[], int size);
void printLatinsOnly(char* str);

int main() {
	float test = getTheItemN(4);
	printf("%f", test);
	return 0;
}
void printLatinsOnly(char* str) {
	if (str[0] == '\0') {
		return;
	}
	if ((str[0] >= 65 && str[0] <= 90) || (str[0] >= 97 && str[0] <= 122))
		printf(" %c", str[0]);
	str++;
	printLatinsOnly(str);
}

int isSorted(int arr[], int size) {
	size--;
	//if it went through the entire array it means the array is sorted and return 1
	if (size <= 0)
		return 1;
	//if the number is smaller than the previous number return 0
	else if (arr[size] < arr[size - 1]) {
		return 0;
	}
	isSorted(arr, size);
}

int isContainNumber(char* str) {
	//if there's a number in the string return 1
	if (str[0] >= 48 && str[0] <= 57)
		return 1;
	//if it went through the entire string it means there are no numbers in it and return 0
	else if (str[0] == '\0')
		return 0;
	str++;
	isContainNumber(str);
}

float getTheItemN(int n) {
	float num;
	if (n == 1)
		return 0;
	else if (n < 1)
		return -1;
	else {
		return 1 / (4 * (1 - getTheItemN(n - 1)));
	}
}