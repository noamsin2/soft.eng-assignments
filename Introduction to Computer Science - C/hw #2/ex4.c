/*Assignment: 2
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printArmstrong() {
   unsigned int high;
   int numLength = 0;
   int digit;
   int sum = 0;
   int multiply = 1;
   int temp;
   
   do {
       printf("Please enter the upper range number:\n");
       scanf("%u", &high);
   } while (high < 100);//repeat the loop if the user entered a number that's below 100
   //'for' loop to print all armstrong numbers from 0 to high variable.
   for (int i = 0; i <= high; i++) {
       temp = i;//temp variable to take the i value
       while (temp > 0) {
           numLength++;//to check how many digits there are in the number
           temp /= 10;
       }
       temp = i;//temp variable to take the i value again
       while (temp > 0) {
           digit = temp % 10;
           //'for' loop to find digit in the power of the number length
           for (int j = 0; j < numLength;j++){
               multiply *= digit;
           }
           sum += multiply;
           temp /= 10;
           multiply = 1;//to reset the multiply variable after its done with the digit
       }
       if (sum == i) {
           printf("%d, ", i);//print armstrong numbers
       }
       numLength = 0;//to reset the numLength variable after its done with the number
       sum = 0;//to reset the sum variable after its done with the number
   }
}


int main()
{
   printArmstrong();// call the function
   return 0;
}