/*Assignment: 2
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//we want the function to return a value that is equal to the number of solutions
int equationSolutions(float a,float b, float c) {
   float delta = b * b - (4 * a * c);
   if (delta > 0) {
       return 2;
   }
   else if (delta < 0) {
       return 0;
   }
   else {
       return 1;
   }
       
}
void printSquareRoot() {
   float a, b, c;
   char ch;
   float x1, x2;
   float delta;
   printf("Would you like to continue?\n");
   scanf(" %c", &ch);
   if (ch == 89 || ch == 121) //lower case and upper case 'y' in ascii chart
   {
       printf("Please enter the equation parameters to check for the solutions\n");
       scanf("%f%f%f", &a, &b, &c);
       delta = b * b - (4 * a * c);
       if (equationSolutions(a, b, c) == 2) {
           x1 = (-b + sqrtf(delta)) / (2 * a);
           x2 = (-b - sqrtf(delta)) / (2 * a);
           printf("x1=%f, x2=%f\n", x1, x2);
       }
       else if (equationSolutions(a, b, c) == 1) {
           x1 = (-b + sqrtf(delta)) / (2 * a);
           printf("x1=%f\n", x1);
       }
       else {
           printf("The quadratic equation has no solution\n");
       }
   }
   else {  
       printf("goodbye");
   }
}


int main()
{
   printSquareRoot();//call the function
   return 0;
}