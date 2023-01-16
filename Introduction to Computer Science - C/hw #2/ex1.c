/*Assignment: 2
 Author: Noam Karasso
 Score : 100
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void squareRoot(int number) {
   // we'll use a "for" loop that will add 1 to 'i' everytime to check if i*i equals number.
   for (int i = 0; i < number; i++) {
       if (i * i == number) {
           printf("%d\n", i);
           break; //break to stop the loop after we found the square root.
       }
   }
}


int main()
{
   int num;
   printf("Enter a number please.\n");
   scanf("%d", &num);
   squareRoot(num);//call the function
   return 0;
}