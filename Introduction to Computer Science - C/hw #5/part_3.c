// Assignment: 5
// Author: Noam Karasso
// Score: 90, -10 points in part 1, not using recursion
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define N 11
#define M 5
#define P 8
#define R 9

void printDetails();
void insertDetails();
int numCmp(char* str1, char* str2);//compares numbers given in strings
int checkNumStr(char* str);//check how many numbers there are in a string
int onlyLetters(char* str);//check if a string contains only letters

////standard main to use
//int main() {
//	insertDetails();
//	printDetails();
//	return 0;
//}

int onlyLetters(char* str) {
	int counter = 0;
	if (strlen(str) > 1) {//model has to be bigger than 2 letters i think
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] < 65 || (str[i] > 90 && str[i] < 97) || str[i] > 122)
				counter++;
		}
		if (counter == 0)
			return 1;
	}
		return 0;
}

int checkNumStr(char* str) {
	int countNum = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 48 && str[i] <= 57)
			countNum++;
	}
	return countNum;
}

void insertDetails() {
	char model[N], year[M], price[P], carRegisPlate[R];

	FILE* carInsert;
	carInsert = fopen("cars.txt", "a");
	if (carInsert == NULL) {
		printf("ERROR! CAN'T OPEN FILE\n");
		exit(EXIT_FAILURE);
	}
	printf("Please enter registration plate(8 digits)\n");
	gets_s(carRegisPlate, R);
	printf("Please enter a car model:\n");
	gets_s(model, N);
	printf("Please enter year of manufacture:(4 digits)\n");
	gets_s(year, M);
	printf("Please enter price\n");
	gets_s(price, P);
	//check that the input taken from the user is valid
	//year length has to be 4 digits, Registration plate has to be 8 digits, car model is only letters, price is only numbers and its at least 4 digits
	if (checkNumStr(year) == 4 && checkNumStr(carRegisPlate) == 8 && onlyLetters(model) && !onlyLetters(price) && checkNumStr(price) > 3)
	{
		fprintf(carInsert, "\n%s ", carRegisPlate);
		fprintf(carInsert, "%s ", model);
		fprintf(carInsert, "%s ", year);
		fprintf(carInsert, "%s ", price);
	}
	fclose(carInsert);
}

int numCmp(char* str1, char* str2) {
	//check the size to use it for prices comparing aswell
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	if (size1 > size2)
		return 0;
	if (size1 < size2)
		return 1;
	else {//happens when the size is even
		for (int i = 0; str1[i] != '\0'; i++) {
			if (str1[i] > str2[i]) {
				return 0;//if the year given by the user is bigger
			}
		}
	}
	return 1;//if the years are equal
}



void printDetails() {
	char model[N], fileModel[N];
	char year[M], fileYear[M];
	char price[P], carRegisPlate[R];
	char filePrice[P] = "";
	int counter = 0;

	FILE* carFind;
	carFind = fopen("cars.txt", "r");
	if (carFind == NULL) {
		printf("ERROR! CAN'T OPEN FILE\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Please enter a car model:\n");
	gets_s(model, N);
	printf("%s", model);
	printf("Please enter year of manufacture:\n");
	gets_s(year, M);
	printf("Please enter price\n");
	gets_s(price, P);
	
	do {
		fscanf(carFind, "%s", carRegisPlate);
		fscanf(carFind,"%s", fileModel);
		fscanf(carFind, "%s", fileYear);
		fscanf(carFind, "%s", filePrice);
		if ((!strcmp(model, fileModel)) && (numCmp(year, fileYear)) && (!numCmp(price, filePrice))) {
			printf("Car registration plate: %s , Model: %s , Year: %s , Price: %s\n", carRegisPlate, model, fileYear, filePrice);
			counter++;
		}
	} while (!feof(carFind));
	if (counter == 0)
		printf("No cars found\n");
	fclose(carFind);
}