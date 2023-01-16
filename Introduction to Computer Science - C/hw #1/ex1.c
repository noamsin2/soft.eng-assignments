/* Assignment: 1
 Author: Noam Karasso
 Score : 100
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//exchange rate and usd in float because both can include fractions for more precision
	float rate;
	float usd;
	
	printf("Please enter an exchange rate:\n");
	scanf("%f", &rate);
	printf("Please enter the sum in- USD\n");
	scanf("%f", &usd);
	float nis = rate * usd;
	printf("Up-to-date USD-NIS equivalency : %f USD = %f NIS\n", usd, nis);
	return 0;
}