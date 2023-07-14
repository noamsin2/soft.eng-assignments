#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 100
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Employee {
private:
	string _id;
	string _firstName;
	string _lastName;
	double _salary;
	float _hoursAmt;

public:
	Employee();
	Employee(const string id, const string firstName, const string lastName, double salary, float hoursAmt);
	bool operator >(const Employee& object)const;
	bool operator == (const Employee& object)const;
	friend ostream& operator <<(ostream& output, const Employee& object);
};