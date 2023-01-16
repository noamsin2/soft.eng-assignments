/* Assignment: 1
Author: Noam Karasso
 Score : 100
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//constant variable for pi
	const float PI = 3.14159;
	int shape;
	float base;
	float height;
	float radius;
	
	printf("Please choose a shape:\n");
	printf("1 - Triangle\n");
	printf("2 - Rectangle\n");
	printf("3 - Square\n");
	printf("4 - Cycle\n");
	scanf("%d", &shape);
	switch (shape) {
		case 1:
			printf("Please enter a base value\n");
			scanf("%f", &base);
			printf("Please enter a height value\n");
			scanf("%f", &height);
			printf("Your shape's area is: %f\n", (base * height) / 2); break;
		case 2:
			printf("Please enter a base value\n");
			scanf("%f", &base);
			printf("Please enter a height value\n");
			scanf("%f", &height);
			printf("Your shape's area is: %f\n", base * height); break;
		case 3:
			printf("Please enter a base value\n");
			scanf("%f", &base);
			printf("Your shape's area is: %f\n", base * base); break;
		case 4:
			printf("Please enter a radius value\n");
			scanf("%f", &radius);
			printf("Your shape's area is: %f\n", radius * radius * PI); break;
		default:
			printf("ERROR\n");
	}
	return 0;
}