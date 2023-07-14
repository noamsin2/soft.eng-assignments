#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Worker.h"

#define basis 4500

using namespace std;

class Manager : public Worker {
public:
	Manager(const string name, const int id, const int seniorityYr);
	Manager(const Manager& other);
	~Manager() {};
	int getSalary()const;
	bool isOutstanding()const;
	void print()const;
};