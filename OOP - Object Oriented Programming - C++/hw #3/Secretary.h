#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Worker.h"

#define basis 4500

using namespace std;

class Secretary : public Worker {
private:
	int nofChild;
public:
	Secretary(const string name, const int id, const int seniorityYr, int nofChild);
	Secretary(const Secretary& other);
	~Secretary() {};
	int getSalary()const;
	bool isOutstanding()const;
	void print()const;
};