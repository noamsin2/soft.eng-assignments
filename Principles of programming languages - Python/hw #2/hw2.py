# Author: Noam Karasso
# Score: 100

import random as r


def cube(x):
    return x ** 3


def simpson_rule(f, a, b, n):
    """
    returns a value of an integral calculated using simpson rule
    :param f:cube
    :param a:0
    :param b:1
    :param n:100
    :return 0.25000000000000006:
    """
    h = (b - a) / n
    sigma = f(a) + f(a + n * h)  # add y0 and yn to the sum
    for k in range(1, n):
        if k % 2 == 1:
            sigma += 4 * (f(a + k * h))
        else:
            sigma += 2 * (f(a + k * h))
    return sigma * h / 3


#print(simpson_rule(cube,0,1,100))

def Game():
    """
    a guessing game:every turn the player will be given a hint and afterwards he will try to guess based on the hint
    if he guessed incorrectly 10 points will be reduced from the total score
    if he guessed correctly he'll be given a score and the game will end
    after 10 turns aka when the score reaches 0, the player will lose and the game will end
    """

    def printF1(msg, f):
        """
        prints a message and prints a function's return value
        :param msg:'ascending:'
        :param f:isAscending
        on num = 135
        prints:'ascending: True'
        """
        print(msg, end='')
        print(f(num))

    def printF2(msg, f):
        """
        prints a message and activates a function 3 times (on every digit)
        :param msg:'even digits: '
        :param f:evenDig
        """
        print(msg, end='')
        for i in range(2, -1, -1):
            f(num // 10 ** i)
        print()

    def evenDig(number):
        """
        checks the last digit of a number if its even print 'X' if its odd print '-'
        :param number: 125
        prints: '-'
        """
        if number % 10 % 2 == 0:
            print('X', end='')
        else:
            print('-', end='')

    def bigDig(number):
        """
        checks the last digit of a number if it's higher than 5 print 'X' if its 5 or lower print '-'
        :param number: 126
        prints: 'X'
        """
        if number % 10 > 5:
            print('X', end='')
        else:
            print('-', end='')

    def isAscending(number):
        """
        checks if a number is ascending, if it is return true, else return false
        :param number: 125
        :return: True
        """
        if number % 10 >= number // 10 % 10 >= number // 100 % 10:
            return True
        else:
            return False

    def primeDig(number):
        """
        checks the last digit of a number if it's a prime number print 'X' if it's not a prime number print '-'
        :param number:125
        prints:'X'
        """
        if number % 10 == 2 or number % 10 == 3 or number % 10 == 5 or number % 10 == 7:
            print('X', end='')
        else:
            print('-', end='')

    print('welcome to the game!')
    score = 100
    num = r.randrange(100, 1000)
    hint_list = [1, 2, 3, 4, 5, 6]
    for n in range(10):
        hint = r.choice(hint_list)
        match hint:
            case 1:
                printF1("sum: ", lambda x: x % 10 + (x // 10) % 10 + (x // 100) % 10)
            case 2:
                printF1("mul ", lambda x: x % 10 * (x // 10 % 10) * (x // 100 % 10))
            case 3:
                printF2("even digits: ", evenDig)
            case 4:
                printF2("big digits: ", bigDig)
            case 5:
                printF1("ascending: ", isAscending)
            case 6:
                printF2("prime digits: ", primeDig)
        user_input = input("enter number/Enter to finish :")
        if not user_input.isdigit():
            break
        guess = int(user_input)
        if guess == num:
            print("yes, correct! you win {:0} points".format(score))
            return
        score -= 10

    print("game over !!!")


Game()
