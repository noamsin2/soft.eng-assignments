# Author: Noam Karasso
# Score: 100

# Question 1 #

class Item():
    """
    item class that consists of item name, price and calories
    """
    def __init__(self,name,price,calories):
        """
        item constructor
        """
        self.name = name
        self.price = price
        self.calories = calories
        
    def __repr__(self):
        """
        returns an unambiguous string representation of the item object
        """
        return 'Item(%r,%r,%r)' %  (self.name,self.price ,self.calories)
    
    def __str__(self):
        """
        returns a readable string representation of the item object
        """
        return '(%s:%s$:%scal)'% (self.name,str(self.price), str(self.calories))
    
class Order():
    """
    Order class that consists of name, and list of items
    """
    def __init__(self, name, menu = None, indexes = None):
        """
        Order constructor
        order_list default value is empty list
        """
        self.name = name
        self.order_list = []
        if menu != None and indexes != None:
            self.add_items(menu, indexes)
        
    def __repr__(self):
        """
        returns an unambiguous string representation of the Order object
        """
        #self.order_list as menu and range(len(self.order_list)) as indexes
        return 'Order(%r,%r,%r)' % (self.name,self.order_list,range(len(self.order_list)))
    
    def __str__(self):
        """
        returns a readable string representation of the Order object
        """
        itemStr = ''
        nofItems = len(self.order_list)#do this just to know if its the last item in the list to add ','
        for i in range(nofItems):
            itemStr += str(self.order_list[i]) #use the item object str function
            if i < nofItems - 1:
                itemStr += ','
            
        return '(%s, (%s) total:%s$,calories:%scal)' % (self.name, itemStr,self.total(),self.calories())
    
    def add_items(self,menu,indexes):
        """
        adds items from menu to list by indexes
        params:
        menu=[Item('McDouble',10,400),Item('Big_Mac',12,550),Item('McChicken',10,400),Item('Fries',5,320),
        Item('Cappuccino',3,160),Item('Coca-Cola',5,210)]
        indexes = (1,3,5)
        order_list = [Item('McDouble',10,400), Item('McChicken',10,400), Item('Cappuccino',3,160)]
        """
        if(type(indexes) == int):#if indexes is a single index
            indexes = (indexes,)#convert it to a tuple with a single element
        for i in indexes:
            if i in range(len(menu) + 1):
                self.order_list.append(menu[i-1])
        return self
    
    def remove_item(self,index):
        """
        removes an item from an order
        """
        if index-1 in range(len(self.order_list)+1):
            print('Remove item: %s' % self.order_list[index-1])
            self.order_list.remove(self.order_list[index-1])
        return self
    
    def total(self):
        """
        calculates the price of all items in an item list
        """
        return sum(map(lambda x:x.price,self.order_list))      
            
    def calories(self):
        """
        calculates all calories in an item list
        """
        return sum(map(lambda x:x.calories,self.order_list))
    
  
class Restaurant():
    """
    Restaurant class that consists of restaurant name, menu list and list of orders taken
    """
    def __init__(self, name, menu = None, orders = None):
        """
        constructor for restaurant with menu and orders default being empty lists
        menu comes before orders in the param list because you cant make orders with no menu
        """
        self.name=name
        if menu == None:
            menu = []
        self.menu=menu
        if orders == None:
            orders = []
        self.orders = orders
        
    def __repr__(self):
        """
        returns an unambiguous string representation of the Restaurant object
        """
        
        return 'Restaurant(%r,%r,%r)' % (self.name,self.menu,self.orders)
        
    def add_menu(self,item):
        """
        takes an item object and adds it to the menu list
        """
        self.menu.append(item)
        return self
    
    def remove_menu(self,index):
        """
        takes an index and removes the item with that index from the menu list
        """
        if index-1 in range(len(self.menu)+1):
            print('Remove Item from menu: %s' % self.menu[index-1])
            self.menu.remove(self.menu[index-1])
        return self
    
    def print_menu(self):
        """
        prints every item in the menu
        params: menu = [Item('McDouble',10,400),Item('Big_Mac',12,550),Item('McChicken',10,400),Item('Fries',5,320),
        Item('Cappuccino',3,160),Item('Coca-Cola',5,210),Item('Green_Salad',12,434)]
        prints:
        1) Big_Mac     12$ 550cal
        2) McChicken   10$ 400cal
        3) Fries        5$ 320cal
        4) Cappuccino   3$ 160cal
        5) Coca-Cola    5$ 210cal
        6) Green_Salad 12$ 434cal
        """
        i = 1
        #to print it as beautiful as in the example
        for item in self.menu:
            print('{0}) {1: <11} {2: >2}$ {3: >3}cal'.format(i, item.name,item.price,item.calories))
            i += 1
    
    def add_orders(self,orders):
        """
        takes an order object and add it to the restaurant's list of orders
        """
        if type(orders) == tuple:# if orders is a tuple of orders iterate through them to add to self.orders
            for order in orders:
                self.orders.append(order)
        else:#if its a single order
            self.orders.append(orders)#just add it
        return self
    
    def print_orders(self):
        """
        iterates through the order list and prints all orders in the order they were added to that order list
        fun fact: i typed order at least 119 times in this file
        """
        for order in self.orders:
            print(order)
    
def min_calories(restaurant):
    """
    iterates through a restaurant's orders and returns the order with the minimum calories
    if there are no orders print a message and return
    """
    if restaurant.orders == []:#if there are no orders
        print('No orders at the moment')
        return
    else:
        min_cal_order = restaurant.orders[0]#make the first order the temporary min cal order which will be returned
        min_calories = min_cal_order.calories()
        for order in restaurant.orders:
            calories = order.calories()#make a variable to avoid calling the function twice
            if calories < min_calories:
                min_calories = calories
                min_cal_order = order
    return min_cal_order

# item1=Item('Big Mac',10,550)
# print(item1.price)
# print(item1)
# item2=eval(repr(item1))
# menu=[Item('McDouble',10,400),Item('Big_Mac',12,550),Item('McChicken',10,400),Item('Fries',5,320),
# Item('Cappuccino',3,160),Item('Coca-Cola',5,210)]
# order1 = Order('David')
# order1.add_items(menu,(1,3,5))
# print(order1)
# order1.remove_item(1)
# order2 = eval(repr(order1))
# order2.name = 'Tali'
# print(order2)
# order3 = Order('Jim', menu, (2,4,5,6))
# print(order3)

# rest1=Restaurant('BurgerPoint', menu)
# print(rest1)
# rest1.add_menu(Item('Green_Salad',12,434))
# rest1.remove_menu(1)
# rest2 = eval(repr(rest1))
# rest2.name = 'BurgerSheva'
# rest2
# rest1.print_menu()
# rest1.add_orders(Order('David',rest1.menu,(2,4,5,6)))
# rest1.add_orders((Order('Tali',rest1.menu,(1,3,5)),Order('Jim',rest1.menu,(1,2,3,5))))
# rest1.print_orders()
# print(min_calories(rest1))

# END Question 1 #

# Question 2 #

# Our custom OOP #
def make_class(attrs, base=None):
    """Return a new class (a dispatch dictionary) with given class attributes"""
    
    def get(name):
        """
        Getter: class attribute (looks in this class, then base)
        """
        if name in attrs: return attrs[name]
        elif base:        return base['get'](name)

    def set(name, value):
        """
        Setter: class attribute (always sets in this class)
        """
        attrs[name] = value

    def new(*args):
        """
        instance attributes (hides encapsulating function's attrs)
        """
        attrs = {}

        def get(name):
            """
            Getter: instance attribute (looks in object, then class (binds self if callable))
            """
            if name in attrs:       return attrs[name]
            else:
                value = cls['get'](name)
                if callable(value): return lambda *args: value(obj, *args)
                else:               return value

        def set(name, value):
            """
            Setter: instance attribute (always sets in object)
            """
            attrs[name] = value

        # instance dictionary
        obj = { 'get': get, 'set': set }

        # calls constructor if present
        init = get('__init__')
        if init: init(*args)

        return obj

    # class dictionary
    cls = { 'get': get, 'set': set, 'new': new }
    return cls

def make_item_class():
    """Return the item class which consists of item name,price and calories"""
    def __init__(self,name,price,calories):
        """item constructor"""
        self['set']('name',name)
        self['set']('price', price)
        self['set']('calories', calories)

    def __str__(self):
        return '('+self['get']('name') +':'+str(self['get']('price'))+'$:'+ str (self['get']('calories')) + 'cal' +')'
    
    return make_class(locals())

def make_order_class():
    """
    Return the order class which consists of the person's name and list of items
    and add_items, remove_items, total, calories, __str__ methods
    """
    def __init__(self,name, menu = None, indexes = None):
        self['set']('name',name)
        self['set']('order_list',[])
        if menu != None and indexes != None:
            self['get']('add_items')(menu, indexes)
     
    def __str__(self):
        """
        returns a readable string representation of the Order object
        """
        items = self['get']('order_list')
        itemStr = ''
        nofItems = len(items)#do this just to know if its the last item in the list to add ','
        for i in range(nofItems):
            itemStr += items[i]['get']('__str__')() #use the item object str function
            if i < nofItems - 1:
                itemStr += ','
        return '(%s,(%s), total:%s$,calories:%scal)' % (self['get']('name'), itemStr,self['get']('total')(),self['get']('calories')())
    
    def add_items(self,menu,indexes):
        """
        adds items from menu to list by indexes
        params:
        menu=[Item('McDouble',10,400),Item('Big_Mac',12,550),Item('McChicken',10,400),Item('Fries',5,320),
        Item('Cappuccino',3,160),Item('Coca-Cola',5,210)]
        indexes = (1,3,5)
        order_list = [Item('McDouble',10,400), Item('McChicken',10,400), Item('Cappuccino',3,160)]
        """
        if(type(indexes) == int):#if indexes is a single index
            indexes = (indexes,)#convert it to a tuple with a single element
        for i in indexes:
            #because our indexes start from 1, if the index is not in the menu then don't add anything
            if i-1 in range(len(menu)):
                self['get']('order_list').append(menu[i-1])
        return self['get']('order_list')
    
    def total(self):
        """
        calculates the price of all items in an item list
        """
        return sum(map(lambda x:x['get']('price'),self['get']('order_list')))      
            
    def calories(self):
        """
        calculates all calories in an item list
        """
        return sum(map(lambda x:x['get']('calories'),self['get']('order_list')))
    
    def remove_item(self,index):
        """
        removes an item from an order
        """
        order = self['get']('order_list')
        if index-1 in range(len(order)+1):
            print('Remove Item from order: %s' % order[index-1]['get']('__str__')())
            self['get']('order_list').remove(order[index-1])
        return self['get']('order_list')
    
    return make_class(locals())
        
def make_restaurant_class():
    """
    Restaurant class that consists of restaurant name, menu list and list of orders taken
    and add_menu, remove_menu, print_menu, add_orders, print_orders, __str__ methods
    """
    def __init__(self, name, menu = None, orders = None):
        """
        constructor for restaurant with menu and orders default being empty lists
        menu comes before orders in the param list because you cant make orders with no menu
        """
        self['set']('name', name)
        if menu == None:
            menu = []
        self['set']('menu', menu)
        if orders == None:
            orders = []
        self['set']('orders',orders)
        
    def __str__(self):
        """
        returns a readable string representation of the Restaurant object
        """
        menu = self['get']('menu')
        itemStr = ''
        nofItems = len(menu)#do this just to know if its the last item in the list to add ','
        for i in range(nofItems):
            itemStr += menu[i]['get']('__str__')() #use the item object str function
            if i < nofItems - 1:
                itemStr += ','
                
        orders = self['get']('orders')
        orderStr = ''
        nofItems = len(orders)#do this just to know if its the order in the list to add ','
        for i in range(nofItems):
            orderStr += orders[i]['get']('__str__')() #use the order object str function
            if i < nofItems - 1:
                orderStr += ','
        return '(%s,(%s),(%s))' % (self['get']('name'), itemStr ,orderStr)
    
    def add_menu(self,item):
        """
        takes an item object and adds it to the menu list
        """
        self['get']('menu').append(item)
        return self['get']('menu')
    
    def remove_menu(self,index):
        """
        takes an index and removes the item with that index from the menu list
        """
        menu = self['get']('menu')
        if index-1 in range(len(menu)+1):
            print('Remove Item from menu: %s' % menu[index-1]['get']('__str__')())
            self['get']('menu').remove(menu[index-1])
        return self['get']('menu')
    
    def print_menu(self):
        """
        prints every item in the menu
        params: menu = [ItemClass['new']('McDouble',10,400),ItemClass['new']('Big_Mac',12,550),ItemClass['new']('McChicken',10,400),
        ItemClass['new']('Fries',5,320),ItemClass['new']('Cappuccino',3,160),ItemClass['new']('Coca-Cola',5,210)]
        prints:
        1) Big_Mac     12$ 550cal
        2) McChicken   10$ 400cal
        3) Fries        5$ 320cal
        4) Cappuccino   3$ 160cal
        5) Coca-Cola    5$ 210cal
        6) Green_Salad 12$ 434cal
        """
        menuList = self['get']('menu')
        i = 1
        for item in menuList:
            #to print it as beautiful as in the example
            print('{0}) {1: <11} {2: >2}$ {3: >3}cal'.format(i, item['get']('name'),item['get']('price'),item['get']('calories')))
            i += 1
    
    def add_orders(self,orders):
        """
        takes an order object and add it to the restaurant's list of orders
        """
        if type(orders) == tuple:# if orders is a tuple of orders iterate through them to add to self.orders
            for order in orders:
                self['get']('orders').append(order)
        else:#if its a single order
            self['get']('orders').append(orders)#just add the single order
        return self['get']('orders')
    
    def print_orders(self):
        """
        iterates through the order list and prints all orders in the order they were added to that order list
        fun fact: i typed order at least 119 times in this file
        """
        orders = self['get']('orders')
        for order in orders:
            print(order['get']('__str__')())
    return make_class(locals())

def min_calories1(restaurant):
    """
    iterates through a restaurant's orders and returns the order with the minimum calories
    if there are no orders print a message and return
    """
    if restaurant['get']('orders') == []:#if there are no orders
        print('No orders at the moment')
        return
    else:
        restOrders = restaurant['get']('orders')
        min_cal_order = restOrders[0] #make the first order the temporary min cal order which will be returned
        min_calories = min_cal_order['get']('calories')()
        for order in restOrders:
            calories = order['get']('calories')()# take the amount of calories for that order
            if calories < min_calories:
                min_calories = calories
                min_cal_order = order
    return min_cal_order
       
# ItemClass = make_item_class()
# item1=ItemClass['new']('Big Mac',10,550)
# item1['get']('price')
# print(item1['get']('__str__')())
# menu1=[ItemClass['new']('McDouble',10,400),ItemClass['new']('Big_Mac',12,550),
# ItemClass['new']('McChicken',10,400),ItemClass['new']('Fries',5,320),ItemClass['new']('Cappuccino',3,160),ItemClass['new']('Coca-Cola',5,210)]
# OrderClass = make_order_class()
# order1=OrderClass['new']('David')
# order1['get']('add_items')(menu1,(1,3,5))
# print(order1['get']('__str__')())
# order1['get']('remove_item')(1)
# print(order1['get']('__str__')())
# order2=OrderClass['new']('Tali',menu1,(2,4,5,6))
# print(order2['get']('__str__')())
# RestaurantClass = make_restaurant_class()
# rest1 = RestaurantClass['new']('BurgerPoint',menu1)
# print(rest1['get']('__str__')())
# rest1['get']('add_menu')(ItemClass['new']('Green_Salad',12,434))
# rest1['get']('remove_menu')(1)

# rest1['get']('print_menu')()
# rest1['get']('add_orders')(OrderClass['new']('David',rest1['get']('menu'),(2,4,5,6)))
# rest1['get']('add_orders')((OrderClass['new']('Tali',rest1['get']('menu'),(1,3,5)),
# OrderClass['new']('Jim',rest1['get']('menu'),(1,2,3,5))))
# rest1['get']('print_orders')()
# print(min_calories1(rest1)['get']('__str__')())
# print(rest1['get']('__str__')())

# END QUESTION 2 #

# QUESTION 3 #

def make_class1(attrs, base=None):
    """Return a new class (a dispatch dictionary) with given class attributes"""
    
    def get(name):
        """
        Getter: class attribute (looks in this class, then base)
        """
        if name in attrs: return attrs[name]
        elif base:        return base['get'](name)

    def set(name, value):
        """
        Setter: class attribute (always sets in this class)
        """
        attrs[name] = value

    def copy(other):
        return cls['new'](other['get']('owner'))
    
    def new(*args):
        """
        instance attributes (hides encapsulating function's attrs)
        """
        attrs = {}
            
        def get(name):
            """
            Getter: instance attribute (looks in object, then class (binds self if callable))
            """
            if name in attrs:       return attrs[name]
            else:
                value = cls['get'](name)
                if callable(value): return lambda *args: value(obj, *args)
                else:               return value

        def set(name, value):
            """
            Setter: instance attribute (always sets in object)
            """
            try:
                if (name in attrs and type(value) != type(attrs[name])):
                    raise TypeError('The %s attribute can be given a new value of type %s' % (name ,type(obj['get'](name))))
                attrs[name] = value
            except TypeError as e:
                print(e)

        # instance dictionary
        obj = { 'get': get, 'set': set}

        # calls constructor if present
        init = get('__init__')
        if init: init(*args)

        return obj
    def list():
        if base:
            return 'this is not a base class'
        
    # class dictionary
    cls = { 'get': get, 'set': set, 'new': new, 'copy': copy  }
    return cls

def make_account_class():
    return make_class1({'interest' : 0.05})

def make_save_account_class():
    def init(self, owner):
        self['set']('owner',owner)
        self['set']('balance',0)
    return make_class1({'__init__' : init, 'interest' : 0.03}, Account)
Account = make_account_class()
SaveAccount = make_save_account_class()

#3.1
b = SaveAccount['new']('Bob')
b['get']('shmython')
b['get']('something')
b['get']('owner')

b['set']('bank', 'Leumi')
b['set']('balance','Bob')
b['set']('bank',5)
b['set']('interest',1)
b['set']('interest',0.75)

3.2
b = SaveAccount['new']('Bob')
b['set']('balance', 100)
b['set']('bank','Leumi')
b['get']('owner')
b['get']('balance')
c=SaveAccount['copy'](b)
c['get']('owner')
c['set']('owner','Jim')
b['get']('owner')
c['get']('owner')
c['set']('balance',100)
b['get']('balance')
c['get']('balance')
c['set']('bank','Discount')
b['get']('bank')
c['get']('bank')


# END QUESTION 3 #

# QUESTION 4 #
#4.1#
class Shekel():
    
    def __init__(self,amount):
        """Constructor for the Shekel object"""
        self.amount = amount
    
    def __str__(self):
        """
        returns a readable string representation of the Shekel object
        with only 1 number after decimal point as shown in the example in 4.2
        """
        return '%.1f₪' % self.amount
    
    def __add__(self,other):
        """
        for question 4.4 to support + operator
        """
        return(coerce_apply('add',self,other))
    
    def __sub__(self,other):
        """
        for question 4.4 to support - operator
        """
        return(coerce_apply('sub',self,other))
    
class Dollar():
    
    def __init__(self,amount):
        """Constructor for the Dollar object"""
        self.amount = amount
        
    def __str__(self):
        """
        returns a readable string representation of the Dollar object
        with only 1 number after decimal point as shown in the example in 4.2
        """
        return '%.1f$' % self.amount
    
    def __add__(self,other):
        """
        for question 4.4 to support + operator
        """
        return(coerce_apply('add',self,other))
    
    def __sub__(self,other):
        """
        for question 4.4 to support - operator
        """
        return(coerce_apply('sub',self,other))
        
class Euro():
    
    def __init__(self,amount):
        """Constructor for the Euro object"""
        self.amount = amount
        
    def __str__(self):
        """
        returns a readable string representation of the Euro object
        with only 1 number after decimal point as shown in the example in 4.2
        """
        return '%.1f€' % self.amount

    def __add__(self,other):
        """
        for question 4.4 to support + operator
        """
        return(coerce_apply('add',self,other))

    def __sub__(self,other):
        """
        for question 4.4 to support - operator
        """
        return(coerce_apply('sub',self,other))

#4.2#
# ~this code is given~ #
rates ={('dollar', 'nis'): 3.45,('euro','nis'): 3.67}
rates[('euro','dollar')]=rates[('euro','nis')]/rates[('dollar', 'nis')]
def type_tag(x):
 return type_tag.tags[type(x)]
type_tag.tags = {Shekel: 'nis',Dollar: 'dollar', Euro: 'euro'}
# ~~~~~~~~~~~~~~~~~~~~ #

# add functions #
def add_dollar_and_nis(dollar,nis):
    """Returns a Shekel object with the amount of the two objects added together after conversion"""
    tags = (type_tag(dollar), type_tag(nis))
    return Shekel(nis.amount + dollar.amount*rates[tags])

def add_nis(nis1,nis2):
    """Returns a Shekel object with the amount of the two objects added together"""
    return Shekel(nis1.amount + nis2.amount)

def add_dollar(dollar1,dollar2):
    """Returns a Dollar object with the amount of the two objects added together"""
    return Dollar(dollar1.amount + dollar2.amount)

def add_euro(euro1,euro2):
    """Returns a Euro object with the amount of the two objects added together"""
    return Euro(euro1.amount + euro2.amount)

def add_euro_and_nis(euro,nis):
    """Returns a Shekel object with the amount of the two objects added together after conversion"""
    tags = (type_tag(euro), type_tag(nis))
    return Shekel(nis.amount + euro.amount*rates[tags])

def add_euro_and_dollar(euro,dollar):
    """Returns a Dollar object with the amount of the two objects added together after conversion"""
    tags = (type_tag(euro), type_tag(dollar))
    return Dollar(dollar.amount + euro.amount*rates[tags])

# base apply function #
def apply(operator_name, x, y):
    tags = (type_tag(x), type_tag(y))
    key = (operator_name, tags)
    return apply.implementations[key](x, y)

#use lambdas to reverse the order
apply.implementations = {('add',('dollar','nis')): add_dollar_and_nis,('add',('nis','dollar')):lambda x,y:add_dollar_and_nis(y,x),
                         ('add',('nis','nis')):add_nis,('add',('dollar','dollar')):add_dollar,
                         ('add',('euro','nis')):add_euro_and_nis,('add',('nis','euro')):lambda x,y:add_euro_and_nis(y,x),
                         ('add',('euro','euro')):add_euro,('add',('euro','dollar')):add_euro_and_dollar,
                         ('add',('dollar','euro')):lambda x,y:add_euro_and_dollar(y,x)}


# print(Shekel(200),Dollar(50),Euro(100))
# print(apply('add',Euro(100),Shekel(200)))
# print(apply('add',Dollar(30),Shekel(50)))
# print(apply('add',Euro(30),Dollar(50)))

#4.3#
# conversion functions #
def dollar_to_nis(dollar):
    """convert dollar to sheks"""
    return Shekel(rates[('dollar', 'nis')] * dollar.amount)

def euro_to_nis(euro):
    """convert euro to sheks"""
    return Shekel(rates[('euro', 'nis')] * euro.amount)

def euro_to_dollar(euro):
    """convert euro to dollar"""
    return Dollar(rates[('euro', 'dollar')] * euro.amount)

# sub functions #
def sub_nis(nis1,nis2):
    """
    returns a Shekel object with amount equal to the subtraction of one with the other
    """
    return Shekel(nis1.amount - nis2.amount)

def sub_dollar(dollar1,dollar2):
    """
    returns a Dollar object with amount equal to the subtraction of one with the other
    """
    return Dollar(dollar1.amount - dollar2.amount)

def sub_euro(euro1,euro2):
    """
    returns a Euro object with amount equal to the subtraction of one with the other
    """
    return Euro(euro1.amount - euro2.amount)

# base coerce function #
def coerce_apply(operator_name, x, y):
    """Attempts to coerce arguments into values of the same type, and only then applies an operator"""
    tx, ty = type_tag(x), type_tag(y)
    if tx != ty:
        if (tx, ty) in coercions:
            #converting x to y and changing the type of x (tx) to be the type of y
            tx, x = ty, coercions[(tx, ty)](x)
        elif (ty, tx) in coercions:
            #converting y to x and changing the type of y (ty) to be the type of x
            ty, y = tx, coercions[(ty, tx)](y)
        else:
            return 'No coercion possible.'
    key = (operator_name, tx)
    return coerce_apply.implementations[key](x, y)

coercions = {('dollar', 'nis'):dollar_to_nis,('euro','nis'):euro_to_nis,('euro','dollar'):euro_to_dollar}
coerce_apply.implementations = {('add','nis'):add_nis,('add','dollar'):add_dollar,('add','euro'):add_euro,
                                ('sub','nis'):sub_nis,('sub','dollar'):sub_dollar,('sub','euro'):sub_euro}

# print(coerce_apply('add',Euro(100), Euro (200)))
# print(coerce_apply('add',Dollar(30),Shekel(50)))
# print(coerce_apply('add',Euro(30),Dollar(50)))
# print(coerce_apply('sub',Euro(100),Shekel(200)))
# print(coerce_apply('sub',Shekel(200),Dollar(100)))
# print(coerce_apply('add',Euro(50),Dollar(30)))


# print(Euro(100) + Euro (200))
# print(Dollar(30) + Shekel(50))
# print(Shekel(200) + Euro(100))
# print(Euro(30) + Dollar(50))
# print(Euro(100) - Shekel(200))
# print(Shekel(200) - Dollar(100))
# END QUESTION 4 #

# QUESTION 5 #

class Tree():
    """Tree class that consists of value and nodes as the tree's sub trees"""
    def __init__(self, value, nodes=None):
        self.value = value
        self.nodes = nodes
 
    def __repr__(self):
        """recursive repr function"""
        args = repr(self.value)
        if self.nodes != None:#if the current tree has sub trees
            args += ', %r' % self.nodes#activate __repr__ on them
        return 'Tree({0})'.format(args)
    
def BuildTree(tree):
    """
    given a tree tuple, makes a new tree instance where every inside node's value is the sum of it's two sons
    params: tree = (((2, 3), (4, (5, 6, (8, 2)))))
    return:Tree(30, [Tree(5, [Tree(2), Tree(3)]), Tree(25, [Tree(4), Tree(21, [Tree(5), Tree(6), Tree(10, [Tree(8), Tree(2)])])])])
    """
    if type(tree) != tuple:#if it's not a tuple
        return Tree(tree)#make a Tree object with value of the tree and return it
    tree = Tree(sum(map(lambda x:x.value, map(BuildTree,tree))),list(map(BuildTree,tree)))
    return tree

def MaxValue(tree):
    """
    given a tree the function returns the highest value out of all the leaves
    params:tree = Tree(30, [Tree(5, [Tree(2), Tree(3)]), Tree(25, [Tree(4), Tree(21, [Tree(5), Tree(6), Tree(10, [Tree(8), Tree(2)])])])])
    return:8
    """
    if tree.nodes == None:
        return tree.value
    return max(map(MaxValue ,tree.nodes))
    

# t = BuildTree((((2, 3), (4, (5, 6, (8, 2))))))
# print(t)
# print(MaxValue(t))

# END QUESTION 5 #

# QUESTION 6 #

from operator import add,mul
from functools import reduce

class Exp(object):
    
    def __init__(self, operator, operands):
        self.operator = operator
        self.operands = operands
    def __repr__(self):
        return 'Exp({0},{1})'.format(repr(self.operator), repr(self.operands))
    def __str__(self):
        operand_strs = ', '.join(map(str, self.operands))
        return '{0}({1})'.format(self.operator, operand_strs)

def calc_eval(exp):
    if type(exp) in (int, float):
        return exp
    if type(exp) == Exp:
        if exp.operator == 'type':#if the operator is 'type'
            return type(exp.operands.pop())#return the operands' type
        arguments = list(map(calc_eval, exp.operands))
    return calc_apply(exp.operator, arguments)

def calc_apply(operator, args):
    if operator in ('add', '+'):
        return sum(args)
    if operator in ('sub', '-'):
        if len(args) == 0:
            raise TypeError(operator + 'requires at least 1 argument')
        if len(args) == 1:
            return -args[0]
        return sum(args[:1] + [-arg for arg in args[1:]])
    if operator in ('mul', '*'):
        return reduce(mul, args, 1)
    if operator in ('div', '/'):
        if len(args) != 2:
            raise TypeError(operator + ' requires exactly 2 arguments')
        numer, denom = args
        return numer/denom
    if operator == 'ror':
        if len(args) != 2:#must get 2 arguments
            raise TypeError(operator + ' requires exactly 2 arguments')
        if type(args[1]) != int:#the amount of rotates must be an integer
            raise TypeError('%s is not <class int>' % (args[1]))
        if args[0] < 0 :#the number must be positive
            raise ValueError('%d is not positive number' % args[0])
        if(type(args[0]) == float):#if the number is a float
            x,y = (str(args[0]).split('.'))#unpack it to x and y and convert to str
            if len(x) <= args[1] or len(y) <= args[1]:#their length must be bigger than the rotating parameter
                raise ValueError('The number %d is not possible for rotate' % args[0])
        elif(type(args[0]) == int):#if the number is an int
            if len(str(args[0])) <= args[1]:#just check the length
                raise ValueError('The number %d is not possible for rotate' % args[0])
        #rotate using pipeline by separating the decimal number by the decimal point and converting to str
        #then rotate, add back the decimal point and convert to float
        return float('.'.join(map(lambda num: num[-args[1]:] + num[:-args[1]],str(args[0]).split('.'))))
   
    

def read_eval_print_loop():
    while True:
        try:
            expression_tree = calc_parse(input('calc> '))
            print(calc_eval(expression_tree))
            #add ValueError here to catch the new exception
        except (SyntaxError, TypeError, ZeroDivisionError, ValueError) as err:
            print(type(err).__name__ + ':', err)
        except (KeyboardInterrupt, EOFError): # <Control>-D, etc.
            print('Calculation completed.')
            return
        
def calc_parse(line):
	"""Parse a line of calculator input and return an expression tree."""
	tokens = tokenize(line)
	expression_tree = analyze(tokens)
	if len(tokens) > 0:
		raise SyntaxError('Extra token(s): ' + ' '.join(tokens))
	return expression_tree

def tokenize(line):
	"""Convert a string into a list of tokens."""
	spaced = line.replace('(',' ( ').replace(')',' ) ').replace(',', ' , ')
	return spaced.split()

def analyze(tokens):
    assert_non_empty(tokens)
    token = analyze_token(tokens.pop(0))
    if type(token) in (int, float):
        return token
    if token in known_operators:
        if len(tokens) == 0 or tokens.pop(0) != '(':
            raise SyntaxError('expected ( after ' + token)
        return Exp(token, analyze_operands(tokens))
    else:
        raise SyntaxError('unexpected ' + token)

def analyze_operands(tokens):
    assert_non_empty(tokens)
    operands = []
    while tokens[0] != ')':
        if operands and tokens.pop(0) != ',':
            raise SyntaxError('expected ,')
        operands.append(analyze(tokens))
        assert_non_empty(tokens)
    tokens.pop(0)  # Remove )
    return operands

def analyze_token(token):
    try:
        return int(token)
    except (TypeError, ValueError):
        try:
            return float(token)
        except (TypeError, ValueError):
            return token

def assert_non_empty(tokens):
    if len(tokens) == 0:
        raise SyntaxError('unexpected end of line')
    
#add the new operators to here
known_operators = ['add', 'sub', 'mul', 'div', '+', '-', '*', '/', 'type', 'ror']

#read_eval_print_loop()

# END QUESTION 6 #