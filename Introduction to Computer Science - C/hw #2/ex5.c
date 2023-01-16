/*Assignment: 2
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int isPositive(int num) {
   bool boolarr[2] = { false, true };
   if (num > 0) {
       return boolarr[1];
   }
   else {
       return boolarr[0];
   }
}

void printFigure(int size, char symbol) {
   for (int i = 0; i < size; i++) {
       for (int j = 1; j <= size; j++) {
           if (j==(i+1) || j==(size-i)) {
               printf("%c", symbol);
           }
           else {
               printf("*");
           }
       }
       printf("\n");
   }
}
void figure() {
   int size;
   char ch;
   do{
       printf("Please enter a number\n");
       scanf("%d", &size);
   } while (!isPositive(size));//loop to ask for a new number if the number isn't positive by using the "isPositive" function
   printf("Please enter any character\n");
   scanf(" %c", &ch);
   printFigure(size, ch);//call the printFigure function
}


int main()
{
   figure();//call the figure function
   return 0;
}