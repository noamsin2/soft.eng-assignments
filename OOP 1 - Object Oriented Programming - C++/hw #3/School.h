#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include <typeinfo>
#include "Person.h"
#include "Worker.h"
#include "Pupil.h"
#include "Teacher.h"
#include "Tutor.h"
#include "Class.h"
#include "Layer.h"
#include "Manager.h"
#include "Secretary.h"

#define minLayer 'a'
#define maxLayer 'f'
#define minClass 1
#define maxClass 3
#define L 6

using namespace std;

class School {
private:
	Layer** layers = nullptr;
	int nofLayers = L;
	Person** people;
	int nofPeople;
	bool mgr;//true if the school has a manager already
	//all the functions that will be used in menu function
	void addPupil();
	void addTeacher();
	void addTutor();
	void addSecretary();
	void addManager();
	void printPeople()const;//prints all people in school
	void printOS()const;//prints outstanding people
	void printTutorsCL()const;//prints tutors' class
	void printMinSalary()const;//prints the worker if the lowest salary
	bool checkPerson(const int id)const;//checks if a person already exists by ID (returns true if exists)
public:
	School();
	~School();
	void Menu();
};
