// Assignment: 3
// Author: Noam Karasso
// Score : 100
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define N 5
#define M 33
#define L 9
char XOR(char bit1, char bit2);

void decimalToBinary(char digit, char str[]);

void grayCode(char str[], char gray[]);

int passwordIsValid(char password[]);

void convertDecimalStringToBinaryString(char password[], char binaryPass[]);

int verificationPerformance(char password[], char code[]);

void shuffleArray(int arr[], int size);

int isPrime(int num);

int isBorderPrime(int mat[][N]);

void printSumColumnRow(int mat[][N]);

int main() {
	printf("#### QUESTION 1 ####\n");
	char password1[L], password2[L];
	char  binaryPass1[M] = "";
	char code1[M] = "";
	do {
		printf("Enter a password please:\nA valid password contains only digits and is %d in length\n", L - 1);
		gets_s(password1, L);
	} while (!passwordIsValid(password1));
	do {
		printf("Enter the password again for verification please:\n");
		gets_s(password2, L);
	} while (!passwordIsValid(password2));
	convertDecimalStringToBinaryString(password1, binaryPass1);
	grayCode(binaryPass1, code1);
	if (verificationPerformance(password2, code1))
		printf("Verification succeed\n");
	else
		printf("ERROR!\n");
	printf("#### QUESTION 2 ####\n");
	int arr[] = { 256, 16, 36 ,12 ,75 ,15 ,32, 24 ,121 ,11 };
	shuffleArray(arr, 10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("#### QUESTION 3 ####\n");
	int mat[N][N];
	for (int i = 0; i < N; i++)
	{
		printf("Enter %d numbers please\n", N);
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &mat[i][j]);
		}
	}
	if (isBorderPrime(mat))
		printf("PRIME BORDER!\n");
	else
		printf("ERROR!\n");
	printSumColumnRow(mat);
	printf("\n#### THE END ####\n");
	return 0;
}

char XOR(char bit1, char bit2) {
	if ((bit1 == 48 && bit2 == 49) || (bit2 == 48 && bit1 == 49)) {
		return '1';
	}
	else {
		return '0';
	}
}

int passwordIsValid(char password[]) {
	int counter = 0;
	int digitCount = 0;
	if (strlen(password) == 8) {
		for (int i = 0; i < 8; i++) {
			if (password[i] >= 48 && password[i] <= 57) {
				counter++;//count digits
			}
		}
	}

	if (counter == 8) {
		//for loop to check the frequency of each number
		for (int ch = 48; ch < 58; ch++) {
			for (int i = 0; i < 8; i++) {
				if (password[i] == ch) {
					digitCount++;
				}
			}
			if (digitCount > 1) {
				break;//if digit count is bigger than 1 it gets out of the loop and returns 0.
			}
			digitCount = 0;
		}
	}
	if (digitCount == 0 && counter == 8) {
		return 1;
	}
	else {
		return 0;
	}
}

void decimalToBinary(char digit, char str[]) {
	int binaryDig[N - 1];
	int decimalDig = 0;
	for (char temp = 48; temp != digit; temp++) {
		decimalDig++;
	}
	for (int j = 3; j >= 0; j--) {
		if (decimalDig % 2 == 1) {
			binaryDig[j] = 49;
		}
		else {
			binaryDig[j] = 48;
		}
		decimalDig /= 2;
	}
	char strtemp[] = { binaryDig[0],binaryDig[1],binaryDig[2],binaryDig[3],'\0' };//temp string to take values from the array
	strcpy(str, strtemp);
}

void grayCode(char str[], char gray[]) {
	strncat(gray, str, 1);
	char one[] = { 49,'\0' };
	char zero[] = { 48 , '\0' };

	for (int i = 1; i < M - 1; i++) {
		if (str[i] != str[i - 1]) {
			strcat(gray, one);
		}
		else {
			strcat(gray, zero);
		}
	}
}

void convertDecimalStringToBinaryString(char password[], char binaryPass[]) {
	char binaryPWTemp[N];
	for (int i = 0; i < 8; i++) {
		decimalToBinary(password[i], binaryPWTemp);
		strncat(binaryPass, binaryPWTemp, 4);//add the value of binaryPWTemp to the end of binaryPass
	}
}

int verificationPerformance(char password[], char code[]) {
	char tempBinary[M] = "";
	char tempGray[M] = "";
	convertDecimalStringToBinaryString(password, tempBinary);
	grayCode(tempBinary, tempGray);
	puts(code);
	puts(tempGray);
	if (!strcmp(tempGray, code))
		return 1;
	else
		return 0;
}

void shuffleArray(int arr[], int size) {
	int temp;
	for (int i = 0; i < size; i++) {
		if (i % 2 == 0) {
			if (arr[i] % arr[i + 1] == 0) {
				temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
			}
		}
	}
}

int isPrime(int num) {
	int counter = 0;
	for (int i = 1; i < num; i++) {
		if (num % i == 0) {
			counter++;
		}
	}
	if (counter == 1)
		return 1;
	else
		return 0;
}

int isBorderPrime(int mat[][N]) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
				printf("%d", mat[i][j]);
				if (isPrime(mat[i][j])) {
					counter++;
				}
			}
		}
	}
	if (counter == ((N - 1) * (N - 1)))//(N-1) * (N-1) is the amount of numbers around the border (16)
		return 1;
	else
		return 0;
}

void printSumColumnRow(int mat[][N]) {
	int sumColumn = 0;
	int sumRow = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sumRow += mat[i][j];
		}
		printf("The sum of Row %d is: %d\n", i, sumRow);
		sumRow = 0;
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			sumColumn += mat[i][j];
		}
		printf("The sum of Column %d is: %d\n", j, sumColumn);
		sumColumn = 0;
	}
}