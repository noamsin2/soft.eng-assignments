/*Assignment: 2
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printMaxCountDivisors(int low, int high) {
   int divisors = 0;
   int lowTemp = low;
   int divisorsTemp = 0;
   int i, j, k;
   while (lowTemp <= high) {
       for (i = 2; i <= lowTemp; i++) {
           if (lowTemp % i == 0) {
               divisors++;//count the amount of divisors for each number
           }
       }
       if (divisors > divisorsTemp) {
           divisorsTemp = divisors;//temp variable to find the maximal divisors in that range
       }
       lowTemp++;
       divisors = 0;//reset the divisors variable
   }
   lowTemp = low;
   while (lowTemp <= high) {
       for (j = 2; j <= lowTemp; j++) {
           if (lowTemp % j == 0) {
               divisors++;
           }
       }
       //to get the numbers that their amount of divisors is equal to the amount of max divisors.
       if (divisors == divisorsTemp) {
           printf("The number with maximal divisors in the range of %d and %d is: %d \nit has %d divisors\n and it divides by : ", low, high, lowTemp, divisors);
           //to find all the numbers it divides by.
           for (k = 2; k <= lowTemp; k++) {
               if (lowTemp % k == 0) {
                   printf("%d, ", k);
               }
           }
           printf("\n");
       }
       lowTemp++;
       divisors = 0;
   }
}

void maxCountDivisors() {
   int high, low;
   int temp;
   printf("Please enter ranges:\n");
   scanf("%d%d", &high, &low);
   while (high<0 || low <0) {
       printf("ERROR\nPlease enter the ranges again.\n");
       scanf("%d%d", &high, &low);
   }
   if (low > high) {
       temp = high;
       high = low;
       low = temp;
   }
   printMaxCountDivisors(low, high);
}

int main()
{
   maxCountDivisors();

   return 0;
}