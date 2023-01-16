# Author: Noam Karasso
# Score: 100
# QUESTION 1 #
# WITHOUT USING DATETIME LIBRARY BECAUSE THEY SAID WE CAN'T UNTIL 3 DAYS BEFORE SUBMISSION #
# ****IF THEY TELL YOU TO DO THIS WITHOUT DATETIME LIBRARY GO BITCH ABOUT IT BECAUSE ITS FUCKING DUMB**** #
# ~~~~~~~~~~~~~~ HELPING FUNCTIONS ~~~~~~~~~~~~~~ #
def convertMonth(month):
    """
    FUNCTION TO HELP US CONVERT A MONTH NUMBER TO MONTH NAME (3 FIRST LETTERS)
    param:month = 1
    return: 'JAN'
    """
    if(month == 1):
        return 'JAN'
    elif(month == 2):
        return 'FEB'
    elif(month == 3):
        return 'MAR'
    elif(month == 4):
        return 'APR'
    elif(month == 5):
        return 'MAY'
    elif(month == 6):
        return 'JUN'
    elif(month == 7):
        return 'JUL'
    elif(month == 8):
        return 'AUG'
    elif(month == 9):
        return 'SEP'
    elif(month == 10):
        return 'OCT'
    elif(month == 11):
        return 'NOV'
    elif(month == 12):
        return 'DEC'

def correctDate(month,day):
    """
    this functions takes month and day and corrects the date if the days are more than the days in a month
    params:day = 29, month = 2
    return '01MAR' (day = 1, month = 3)
    """
    if(day == 32 and month == 1):
        return '01FEB'
    elif(day == 29 and month == 2):
        return '01MAR'
    elif(day == 32 and month == 3):
        return '01APR'
    elif(day == 31 and month == 4):# list = [3,5,7,8,10,12] 31
        return '01MAY'
    elif(day == 32 and month == 5):
        return '01JUN'
    elif(day == 31 and month == 6):
        return '01JUL'
    elif(day == 32 and month == 7):
        return '01AUG'
    elif(day == 32 and month == 8):
        return '01SEP'
    elif(day == 31 and month == 9):
        return '01OCT'
    elif(day == 32 and month == 10):
        return '01NOV'
    elif(day == 31 and month == 11):
        return '01DEC'
    elif(day == 32 and month == 12):
        return '01JAN'
    if(day //10 == 0):
        return '0' + str(day) + convertMonth(month)
    else:
        return str(day) + convertMonth(month)

def calculateDays(month, day):
    """
    takes a month and day and returns the sum of days in all months up to the month given + day
    (NOT TAKING LEAP YEAR INTO ACCOUNT)
    param:month = 12 , day = 31
    return: 364
    param:month = 1 , day = 1
    return: 1
    """
    list = [3,5,7,8,10,12]
    if month == 1:
        return day
    elif month == 2:
        day += 28
    elif month in list:
        day += 31
    else:
        day += 30
    return calculateDays(month-1,day)

def daysToDate(days):
    """
    function to help us convert days to date by converting days to months and days first and then
    return the date as string
    """
    list = [1,3,5,7,8,10,12]
    m = 1
    while((days > 28 and m == 2) or (days > 31 and m in list) or (days>30 and (m not in list) and(m != 2))):
        if m == 2:
            days -= 28
        elif m in list:
            days -= 31
        else:
            days -= 30
        m+=1
    if(days //10 == 0):
        return '0' + str(days) + convertMonth(m)
    else:
        return str(days) + convertMonth(m)

def dateStringToDays(date):
    """
    this function will convert date string to days using calculateDays and convertBackMonth functions
    param: date = '31DEC'
    return: 365
    """
    day = int(date[:2:])
    month = date[2:]
    month = convertBackMonth(month)
    return calculateDays(month,day)
    
    
def convertBackMonth(month):
    """
    FUNCTION TO HELP US CONVERT A MONTH NAME (3 FIRST LETTERS) TO MONTH NUMBER
    """
    if(month == 'JAN'):
        return 1
    elif(month == 'FEB'):
        return 2
    elif(month == 'MAR'):
        return 3
    elif(month == 'APR'):
        return 4
    elif(month == 'MAY'):
        return 5
    elif(month == 'JUN'):
        return 6
    elif(month == 'JUL'):
        return 7
    elif(month == 'AUG'):
        return 8
    elif(month == 'SEP'):
        return 9
    elif(month == 'OCT'):
        return 10
    elif(month == 'NOV'):
        return 11
    elif(month == 'DEC'):
        return 12
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
def make_ticket(flightID,day,month,hour,mins):
    """
    makes a flight ticket using flight ticket number,date(day and month), hour,and mins
    """
    def dispatch(n):
        if(n == 0):
            return flightID
        if(n==1):
            return day
        if(n==2):
            return month
        if(n==3):
            return hour
        if(n==4):
            return mins
    return dispatch
            
def flight(ticket):
    """
    gets a flight ticket and returns the flight number
    """
    return ticket(0)
def date(ticket):
    """
    gets a flight ticket and returns the flight date
    """
    day = ticket(1)
    month = ticket(2)
    if(day//10==0):
        return '0' + str(day) + convertMonth(month)
    else:
        return str(day) + convertMonth(month)
def hour(ticket):
    """
    returns the hour
    """
    return ticket(3)
def minute(ticket):
    """
    returns the minutes
    """
    return ticket(4)

def print_ticket_info(ticket, msg):
    """
    prints a ticket info according to the requested format
    """
    hours = hour(ticket)
    minutes = minute(ticket)
    if(hours < 10):
        hours = '0' + str(hours)
    if(minutes < 10):
        minutes = '0' + str(minutes)
    if(msg == 'flight hh:mm'):
        print("{0} {1}:{2}".format(flight(ticket),hours,minutes))
    elif(msg == 'date hh:mm'):
        print("{0} {1}:{2}".format(date(ticket),hours,minutes))
    elif(msg == 'hh:mm'):
        print("{0}:{1}".format(hours,minutes))
    else:
        print("{0} {1} {2}:{3}".format(flight(ticket),date(ticket),hours,minutes))
        
def time_difference(t1,t2):
    """
    calculates the difference in minutes between two flight tickets
    params: t1('F0545', 30, 11, 23, 30), t2('TK0789',8, 1, 10, 55)
    return: 468755
    """
    #first we'll calculate the amount of days in each date using the beautiful functions that we made
    days1 = dateStringToDays(date(t1))
    days2 = dateStringToDays(date(t2))
    #now we calculate the difference
    minutes = minute(t1) - minute(t2)
    hours = hour(t1) - hour(t2)
    difference = (days1 - days2)*24*60 + hours*60 + minutes
    return abs(difference)

#i hate this function
def time_correction(t1, mins):
    """
    this function takes a flight ticket and returns a new flight ticket after adding / subtracting
    the minutes
    params:ticket1('F0545', 31, 12, 23, 30),  40
    return ticket2('F0545', 1, 1, 00, 10)
    """
    date1 = date(t1)
    days = int(date1[:2:])
    month = convertBackMonth((date1[2:]))
    hours = hour(t1)
    minutes = minute(t1) + mins
    if(minutes < 0):#if mins was negative and we need to substract from minutes
        minutes += hours*60
        if(minutes < 0 and days > 1):#if after adding the hours to minutes its still negative and its at least day 2
            days = dateStringToDays(date(t1))
            days -= 1
            minutes += 24*60
            date1 = daysToDate(days)
            days = int(date1[:2:])
            month = convertBackMonth((date1[2:]))
        elif (minutes < 0 and days == 1):#if minutes is negative and days equals 1
            days = dateStringToDays(date(t1))
            days -= 1
            if(days == 0):
                days = 364
            minutes += 24*60
            date1 = daysToDate(days)
            days = int(date1[:2:])
            days+=1
            month = convertBackMonth((date1[2:]))
    elif(minutes > 60):#if minutes is more than 60 and we need to convert it back to hours
        minutes += hour(t1)*60
        if(minutes >= 24*60):#if minutes is more than 1440 (a day) and we need to add 1 to day and substract the minutes
            minutes -= 24*60
            days+=1
            date1 = correctDate(month,days)
            days = int(date1[:2:])
            month = date1[2:]
            month = convertBackMonth(month)
    #(else) if 0<minutess<60 we dont need to do anything
    #at the end convert to hours and minutes and we're done
    hours = minutes // 60
    minutes = minutes % 60
    return make_ticket(flight(t1), days, month, hours, minutes)
    
# t1 = make_ticket('F0545', 1, 1, 0, 30)
# print_ticket_info(t1,'')
# t2 = make_ticket('TK0789',8, 1, 10, 55)
# print_ticket_info(t2,'')
# print(time_difference(t1,t2))
# print(dateStringToDays('31DEC'))
# t1 = time_correction(t1,-40)
# print_ticket_info(t1, '')
#END QUESTION 1#

#QUESTION 2#


def make_tree(value,left,right):
    """
    makes a tree using 'message passing' method
    """
    def dispatch(msg):
        if(msg == 'value'):
            return value
        if(msg == 'left'):
            return left
        if(msg == 'right'):
            return right
    return dispatch                        

def value(tree):
    """
    return the current node's value
    """
    return tree('value')

def left(tree):
    """
    returns the node's left son
    """
    return tree('left')

def right(tree):
    """
    return the node's right son
    """
    return tree('right')

        
def print_tree(tree):
    """
    recursive function to print a tree using the usual inorder algorithm
    params:preorder(tree) = [12,6,8,7,2,15]
    print inorder(tree): 8 6 12 2 7 15
    """
    if(tree != None):
        print_tree(left(tree))
        print(value(tree), end=' ')
        print_tree(right(tree))
        
def findMinVal(tree):
    """
    recursive function to find the min value in a tree
    param:preorder(tree) = [12,6,8,7,2,15]
    return: 2
    """
    if(tree != None):
        return min(value(tree),findMinVal(left(tree)),findMinVal(right(tree)))
    return 999

    
def min_value(tree):
    """
    a function to print the min value in a tree using findMinVal that finds it
    """
    print(findMinVal(tree))
    
def mirror_tree(tree):
    """
    this function returns a new tree that's the reflection of the original tree
    param:inorder tree = [8 6 12 2 7 15]
    return inorder tree = [15 7 2 12 6 8]
    """
    if tree is None:
        return None
    return make_tree(value(tree), mirror_tree(right(tree)), mirror_tree(left(tree)))
    
# tree = make_tree(12,make_tree(6,make_tree(8,None,None),None),
# make_tree(7,make_tree(2,None,None),make_tree(15,None,None)))

# print(value(tree))
# print(value(left(tree)))
# print(value(right(tree)))
# print(value(left(right(tree))))
# print_tree(tree)
# min_value(tree)
# print_tree(mirror_tree(tree))
#END QUESTION 2#

#QUESTION 3#
#3.1#
from functools import reduce

def avg_salary(seq):
    """
    this functions makes a new sequence but replacing the salaries for each list of salaries
    with a new one that's the average salary using computer_average function and multiple unpacking method
    """
    return(tuple(map(lambda x:tuple(compute_average(*x)),seq)))

#multiple unpacking
def compute_average(letter, salaries):
    # compute the average salary for a given letter
    return (letter, sum(salaries) / len(salaries))

# def avg_salary(seq):
#     return tuple(map(lambda x:(tuple(map(lambda y:reduce(add,y),x))),seq))

salaries = ('a', [12675, 7876, 8765]), ('b', [9500, 6987]), ('c', [7500, 4576]), ('d', [11654])
#print(avg_salary(salaries))


#3.2
# def Remove(tuples):
#     return filter(None, tuples)


def addbonus(letter,salaries,bletter,bonus):
    """
    we will use this function for multiple unpacking and extracting the letter out of the tuple
    """
    if(letter == bletter):
        return list(map(lambda x: x+bonus ,salaries))
    
def minMaxAvg(seq):
    """
    this function takes a sequence and converts it to the min, max and average values of the sequence
    """
    return (reduce(min,seq),reduce(max,seq),reduce(lambda a,b:a+b,seq)/len(seq))


    
def add_bonus(seq,bonusSeq):
    """
    first we'll add the bonus(a number inside a tuple in a sequence named 'bonus') to each list inside a tuple in the tuple salaries sequence,
    then we'll filter all the Nones from the map object and then transform it into a list then we'll replace each list with the min,max,avg salaries
    for that list,lastly we'll lose all the commas and unneeded tuples to format the list according to the example
    """
    return tuple(map (lambda x:x[0],tuple(map(lambda x:tuple(map(lambda y:minMaxAvg(y),filter(None,(map(lambda b:addbonus(*x,*b),bonusSeq))))),seq))))

bonus = [('a', 1000), ('b', 2000), ('c', 900), ('d', 3500)]
# print(add_bonus(salaries,bonus))

# print(minMaxAvg(addbonus('a', [12675, 7876, 8765], 'a', 1000)))

#END QUESTION 3#

#QUESTION 4#

def make_temperature(degrees,unit):
    """
    temperature data type using message passing method
    """
    def dispatch(msg):
        """
        dispatch function that redirects us to the right function using a string
        """
        if (msg == 'get_value'):
            return get_val
        elif (msg == 'set_value'):
            return set_val
        elif (msg == 'str'):
            print('{0} {1}'.format(degrees, unit))
        elif (msg == 'convert'):
            return convert
        else:
            return 'action does not exist'
    
    def get_val(msg):
        if(msg == 'degrees'):
            return degrees
        elif(msg == 'unit'):
            return unit
        else:
            return 'Error'
        
    def set_val(msg,value):
        if(msg == 'degrees'):
            nonlocal degrees 
            degrees = value
        elif(msg == 'unit'):
            nonlocal unit
            unit = value
        else:
            return "Error"
        
    def convert(func, newunit):
        nonlocal unit, degrees
        if newunit == unit:
            return
        else:
            degrees = func(degrees)
            unit = newunit

    return dispatch
        
def convertTemperatures(unit, newunit):
    if unit == 'C' and newunit == 'F':
        return lambda x: x*1.8 + 32
    elif unit == 'F' and newunit == 'C':
        return lambda x: (x-32) / 1.8
    elif unit == 'C' and newunit == 'K':
        return lambda x: x + 273.15
    elif unit == 'K' and newunit == 'C':
        return lambda x: x - 273.15
    elif unit == 'F' and newunit == 'K':
        return lambda x: (x+459.67) / 1.8
    elif unit == 'K' and newunit == 'F':
        return lambda x: x*1.8 - 459.67
    #if unit == newunit return a function that doesn't change the degrees
    return lambda x:x

#example for using convert function
# t = make_temperature(31, 'C')
# t('str')
# newunit = 'F'
# t('convert')(convertTemperatures(t('get_value')('unit'), newunit), newunit)
# t('str')

#END QUESTION 4#

#QUESTION 5#

def make_traveler_trip(name, id):
    """
    make a trip function using dispatch dictionary and store the data in
    a dictionary using the destination as the key and the other parameters as values
    params: name, id to use for the person that's making the trip    
    """
    destinations = {}
    
    
    def add_destination(destination, location, price, currency):
        """
        adds a destination as a key and other parameters as a list of values
        params: ('Vondelpark', 'Amsterdam', '15', 'EUR')
        destinations = {
            'Vondelpark': [Amsterdam, 15, EUR]
        }
        """
        destinations[destination] = [location , price ,  currency]
        
        
    def search_destination(destination):
        """
        given a destination(key) we print the destination and it's values
         params: ('Vondelpark', 'Amsterdam', '15', 'EUR')
        print:Vondelpark, Amsterdam, 15 EUR]
        """
        if(destination in destinations):
            print('{0}, {1}, {2} {3}'.format(destination,destinations[destination][0],destinations[destination][1],destinations[destination][2]))
        
        
    def delete_destination(destination):
        """
        given a destination(key) we delete it from the dictionary using del
        given the dictionary: destinations = {
            'Vondelpark': [Amsterdam, 15, EUR]
        } with the param: Vondelpark
        destinations = {}
        """
        del destinations[destination]
        
        
    def print_trip():
        """
        we can print a trip using both functions by making it a list first and we use index to not repeat the same destination twice
        """
        print('{0} {1}'.format(name,id))
        index = 0
        i_list = list(destinations.items())#making a list out of the dict_items object out of the dictionary
        
        def next():
            """
            print a destination and increasing the index by 1
            """
            nonlocal index
            #print it in the format that was shown in the example
            print('{0}, {1}, {2} {3}'.format(i_list[index][0], i_list[index][1][0], i_list[index][1][1], i_list[index][1][2]))
            index+=1
            
        def hasMore():
            """
            checks if the index is in the destination's list's range
            """
            nonlocal index
            if(index < len(i_list)):
                return True
            else:
                return False
            
        return {'next':next,'hasMore':hasMore}
    
    
    def view(msg):
        """
        call a function using message passing
        """
        def printAllDest():
            """
            prints all destinations by making a list out of the dictionary keys and then printing them
            as shown in the example
            """
            #make a list out of the dictionary keys so we can print them in a beautiful way
            d_list = list(destinations.keys())
            #print it in a nice way as was shown in the example
            for i in range(len(d_list)):
                if(i != len(d_list) - 1):
                    print(d_list[i], end= ', ')
                else:
                    print(d_list[i])
                    
        def printAllLoc():
            """
            prints all locations by making a list of all the values and extracting only the location out
            (in index [i][0] in the list)
            but first we'll make a dictionary out of the locations to get rid of duplicate locations
            """
            #make a list out of the dictionary values
            v_list = list(destinations.values())
            new_list = []
            #and then make a list out of the location part
            for i in range(len(v_list)):
                new_list += [v_list[i][0]]
            #remove duplicates in a non-efficient way (we could convert the list to a dictionary or a set aswell
            #and then convert it back)
            #second option would be:
            #new_list = list(set(new_list))
            for i in new_list:#for every element in the list
                while new_list.count(i) > 1:#while the element's count is greater than 1
                    new_list.remove(i)#remove it
           
            #then print it in a nice way as was shown in the example
            for i in range(len(new_list)):
                if(i != len(new_list) - 1):
                    print(new_list[i], end= ', ')
                else:
                    print(new_list[i])
        #MESSAGE PASSING
        if(msg == 'destinations'):
            printAllDest()
        elif(msg == 'locations'):
            printAllLoc() 
            
    def convert_currency(money,currency,newcurrency):
        """
        helping function to use in calculate_expenses function that converts the money
        depending on current currency and new currency
        """
        if(currency == newcurrency):
            return int(money)
        elif(currency == 'ILS' and newcurrency == 'USD'):
            return  int(money) /3.46
        elif(currency == 'ILS' and newcurrency == 'EUR'):
            return int(money) / 3.67
        elif(currency == 'USD' and newcurrency == 'EUR'):
            return int(money)*1.06
        elif(currency == 'USD' and newcurrency == 'ILS'):
            return int(money)*3.46
        elif(currency == 'EUR' and newcurrency == 'USD'):
            return  int(money) / 1.06
        elif(currency == 'EUR' and newcurrency == 'ILS'):
            return int(money)*3.67
          
    def calculate_expenses(currency):
        """
        first make a list out of the destination values and then extract the money
        and currency out to use in convert_currency function
        then we'll print the sum and return it
        """
    #make a list out of the destination values and take only the price and currency part out
        v_list = list(destinations.values())
        sum = 0
        for i in range(len(v_list)):
            sum += convert_currency(v_list[i][1],v_list[i][2],currency)
        return sum
        
    return {'add_destination':add_destination,'print_trip':print_trip ,'view':view, 'calculate_expenses':calculate_expenses,
            'delete_destination':delete_destination,'search_destination':search_destination}

# mt=make_traveler_trip('Shahar', 1)
# mt['add_destination']('Vondelpark', 'Amsterdam', '15', 'EUR')
# mt['add_destination']('ADAM Lookout', 'Amsterdam', '153', 'ILS')
# mt['add_destination']('Lauterbrunnen', 'Switzerland', '1000', 'ILS')
# mt['add_destination']('Greendelwald', 'Switzerland', '167', 'EUR')
# mt['add_destination']('Lake Como', 'Italy', '30', 'EUR')
# print(mt['calculate_expenses']('ILS'))
# mt['delete_destination']('ADAM Lookout')

# pt = mt['print_trip']()
# while(pt['hasMore']()):
#     pt['next']()
    
# mt['view']('destinations')
# mt['view']('locations')
# mt['search_destination']('Vondelpark')
#END QUESTION 5#