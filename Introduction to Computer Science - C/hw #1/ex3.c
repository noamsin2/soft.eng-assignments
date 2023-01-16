/* Assignment: 1
 Author: Noam Karasso
 Score : 100
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int num;
	printf("Please enter a 3 digit number\n");
	scanf("%d", &num);
	int digit1 = num % 10;
	int digit2 = num / 10 % 10;
	int digit3 = num / 100;
	//we want the number to be 3 digits so we'll make sure it's in the range of 100-999
	if (num >= 100 && num <= 999) {
		if (digit1 >= digit2 && digit1 >= digit3) {
			printf("Max digit is: %d\n", digit1);
			//we already know digit1 is bigger than digit2 and digit3 so we'll check which of the two is smaller
			if (digit2 < digit3) {
				printf("Min digit is: %d\n", digit2);
			}
			//if digit2 isn't smaller then it means digit3 is smaller than digit2 (or equal) so it will print digit3
			else {
				printf("Min digit is: %d\n", digit3);
			}
		}
		else if (digit2 >= digit1 && digit2 >= digit3) {
			printf("Max digit is: %d\n", digit2);
			if (digit1 < digit3) {
				printf("Min digit is: %d\n", digit1);
			}
			else {
				printf("Min digit is: %d\n", digit3);
			}
		}
		// if digit3 is bigger than digit2 and digit1 (the above conditions are false)
		else {
			printf("Max digit is: %d\n", digit3);
			if (digit2 < digit1) {
				printf("Min digit is: %d\n", digit2);
			}
			else {
				printf("Min digit is: %d\n", digit1);
			}
		}
	}
	// if the number isn't 3 digits we'll make it print an error message
	else {
		printf("ERROR\n");
	}
	return 0;
}