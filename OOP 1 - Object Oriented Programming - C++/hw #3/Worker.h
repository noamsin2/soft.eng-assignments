#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Person.h"

using namespace std;

class Worker : public Person {//worker is an abstract class
private:
	int seniorityYr;

public:
	Worker(const string name, const int id, const int seniorityYr);
	Worker(const Worker& other);
	~Worker() {};
	virtual int getSalary()const = 0;//all the classes that inherit from this class must use this function
	void print()const;
	int getSeniorityYr()const { return seniorityYr; }//get function to use in the derived classes' copy ctor

};