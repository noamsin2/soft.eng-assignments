#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Worker.h"

#define basis 4500

using namespace std;

class Teacher : public Worker {
private:
	string* subjects;
	int nofSubjects;
	void printSubjects()const;
public:
	Teacher(const string name, const int id, const int seniorityYr, const string* subjectsArr, const int nofSubjects);
	Teacher(const Teacher& other);
	~Teacher();
	int getSalary()const;
	bool isOutstanding()const;
	void print()const;
	string* getSubjects()const { return subjects; }
	int getNofSubjects()const { return nofSubjects; }
};