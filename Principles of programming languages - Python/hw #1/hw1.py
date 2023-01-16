# Authors: Noa and Noam!!
# Score: 100

def even_str(str):
    """
    exercise #1
    this function returns a new string that contains the letters from the old string in even places(starting from 1)
    :param str = 'Noa&Noam':
    :return o&om:
    """
    evenstr = ''
    for n in range(len(str)):
        if n % 2 == 1:
            evenstr += str[n]
    return evenstr

#print(even_str('Noa&Noam'))

def pattern(num):
    """
    exercise #2
    this function prints asterisks in a certain pattern
    :param num = 5:
    :return :
    *        *
    **      **
    ***    ***
    ****  ****
    **********
    """
    if num <= 0 or num >= 10:
        print("invalid input")
        return
    for i in range(num):
        for j in range(num*2):
            if j <= i or j >= num*2-1-i:
                print('*', end = '')
            else:
                print(' ', end = '')
        print()

#pattern(5)

def sort_num(num):
    """
    exercise #3
    this function returns true if the num is sorted, else returns false
    :param num = 24889:
    :return true:
    """
    if num == 0:
        return True
    elif num % 10 >= (num // 10) % 10:
        return sort_num(num//10)
    return False

#print(sort_num(24889))

def min_dig(num):
    """
    exercise #4
    this function returns the smallest digit in a number
    :param num = 98720:
    :return 0:
    """
    if num == 0:
        return 9
    min = min_dig(num // 10)
    if num % 10 <= min:
        return num % 10
    else:
        return min

#print(min_dig(98720))

def unique(str):
    """
    exercise #5
    this function takes a string and returns true if all the characters exist only once, else returns false
    :param str = '32453':
    :return false:
    """
    for i in range(len(str)):
        for j in range(i+1,len(str)):
            if str[i] == str[j]:
                return False
    return True

#print(unique('n&narethebest'))

def Xnor(bool1,bool2):
    """
    exercise #6
    this function takes 2 boolean parameters and returns their XNOR
    :param bool1 = true:
    :param bool2 = true:
    :return true:
    """
    if bool1 and bool2:
        return True
    elif not bool2 and not bool1:
        return True
    else:
        return False

#print(Xnor(False,False))