/*Assignment: 2
 Author: Noam Karasso
 Score : 100
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int checkChar(char ch) {
    bool boolarr[2] = { false, true };
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
        return boolarr[1];
    }
    else {
        return boolarr[0];
    }
}
int checkLetters() {
    char ch;
    int counter = 0;
    int i = 0;
    int tempCh = 0;
    printf("enter your string pls:\n");
    do {
        ch = getchar();
        if (checkChar(ch)) {
            i++;
            //if the condition is met it adds 1 to counter
            if (((ch >= 65 && ch <= 90) && (tempCh >= 97 && tempCh <= 122)) || ((ch <= 122 && ch >= 97) && (tempCh <= 90 && tempCh >= 65))) {
                counter++;
            }
        }
        //if the char isn't a latin char it adds 2 to i which makes the (counter >= i) condition impossible to be met
        else {
            i += 2;
        }
        tempCh = ch;
    } while (ch != '\n' && ch != 32);
    //printf("%d, %d", counter, i);// <-- use this line to check the condition
    //when no characters are entered i = 2, when a latin letter is entered i = 3, when a different character is entered i = 4, therefore counter >= (i-3)
    if (counter >= (i - 3)) {
        return 1;
    }
    else {
        return 0;
    }

}
void proofreading() {
    int truwu = checkLetters();//truwu (true) takes the return value from checkLetters function
    if (truwu) {
        printf("Correct.\n");
    }
    else {
        printf("Incorrect.\n");
    }
}

int main()
{
    proofreading();
    return 0;
}