#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Teacher.h"
#include "Class.h"

using namespace std;

class Class;

class Tutor : public Teacher {
private:
	 Class* classPtr = nullptr;
	 void printPupils()const;//prints only pupils details (private because used only by the class methods)
public:
	Tutor(const string name, const int id, const int seniorityYr, const string* subjectsArr, const int nofSubjects, Class* cPtr);
	Tutor(const Tutor& other);
	~Tutor() {};
	int getSalary()const;
	bool isOutstanding()const;
	void print() const;//prints only tutor's details (not private because will be used outside of class)
	void detailedPrint()const;//prints the tutor's details and pupils details altogether
};