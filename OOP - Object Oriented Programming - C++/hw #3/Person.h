#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include <string.h>

using namespace std;

class Person {//abstract class
private:
	string name;
	int id;
public:
	Person(const string name, const int id);
	Person(const Person& other);
	virtual ~Person() {};//virtual to delete right in case of upcasting!!
	virtual void print()const = 0;//all the classes that inherit from this class must use this function
	virtual bool isOutstanding() const = 0;//all the classes that inherit from this class must use this function
	string getName()const { return name; }
	int getID() const { return id; }
};