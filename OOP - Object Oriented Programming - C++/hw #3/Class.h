#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Pupil.h"
#include "Tutor.h"

using namespace std;

class Tutor;

class Class {
private:
	char layer;
	int classroom;
	Pupil** pupils;
	int nofPupils = 0;
	Tutor* tutor;
public:
	Class(const char layer, const int classroom, Tutor* tutorPtr);
	Class(const Class& other);
	~Class();
	void addPupil(Pupil* newPupil);//add a pupil to the pupils array
	Pupil* getPupil(const int index)const;
	int getNofPupils()const { return nofPupils; }//used in tutor's functions
	void setTutor(Tutor* tutorPtr) { tutor = tutorPtr; }
	//get functions will be used to print the tutor's layer and classroom
	int getClassroom() { return classroom; }
	char getLayer() { return layer; }
};