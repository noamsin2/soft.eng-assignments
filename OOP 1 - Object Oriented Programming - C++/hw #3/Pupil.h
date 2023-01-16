#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Person.h"
#include <iostream>
#define minLayer 'a'
#define maxLayer 'f'
#define minClass 1
#define maxClass 3
using namespace std;

class Pupil: public Person {
private:
	int* grades = nullptr;
	int nofGrades;
	char layer;
	int classroom;
	float calcAvg()const;
public:
	Pupil(const string name, const int id, const int* gradesArr, const int nofGrades, const char layer, const int classroom);
	Pupil(const Pupil& other);
	~Pupil();
	bool isOutstanding()const;
	void print()const;
};