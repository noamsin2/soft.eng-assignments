/*Assignment: 2
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int guessYourNumber(int a, int b) {
   char ch;
   int score = 0;
   int num;
   int rivalNum;
   printf("would you like to play?\n");
   scanf(" %c", &ch);
   while(ch == 89 || ch == 121) {
       printf("Enter the number your rival needs to guess:\n");
       scanf("%d", &num);
       while (num < a || num > b) {
           printf("The number is out of range\n");
           printf("Enter the number your rival needs to guess:\n");
           scanf("%d", &num);
       }
       int temp = num;//temp variable for num so we can divide it by 10 everytime without changing the original number
       printf("What is your guess?\n");
       scanf("%d", &rivalNum);
       while (rivalNum != num) {
           printf("Wrong!! let me give you a hint.\n The digit is: %d\n", temp % 10);
           printf("What is your guess?\n");
           scanf("%d", &rivalNum);
           temp /= 10;
       }
       printf("Good job!!\n");
       score += 5;
       printf("Do you want to continue playing??\n");
       scanf(" %c", &ch);
   }
       return score;
}



int main()
{
   int finalScore = guessYourNumber(345, 999);//declaring a variable in main to take the return value from the function
   printf("your score is: %d\n", finalScore);
   return 0;
}