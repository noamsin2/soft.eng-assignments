// Author: Noam Karasso
// Score: 97: -2 for not using constant variables, -1 for not using meaningful names in some functions for variables
#include "Course.h"

Course::Course() {
	strcpy(courseName, "unknown");
	resetGrades(true);
	resetGrades(false);
}

Course::Course(const char* str) {
	strcpy(courseName, str);
	resetGrades(true);
	resetGrades(false);
}

Course::~Course(){}

void Course::resetGrades(const bool grades) {
	if (grades)
		for (int i = 0; i < 2; i++) {
			testGrades[i] = -1;
		}
	else
		for (int i = 0; i < 4; i++)
			hwGrades[i] = -1;
}

Course::Course(const Course& obj) {
	strcpy(courseName, obj.courseName);//copy course name
	setTestGrades(obj.getTestGrades());//copy test grades
	setHwGrades(obj.getHwGrades());//copy assignments grades
	/*for (int i = 0; i < 2; i++)
		testGrades[i] = obj.testGrades[i];
	for (int i = 0; i < 4; i++)
		hwGrades[i] = obj.hwGrades[i];*/
}

void Course::setCourseName(const char* str) {
	strcpy(courseName, str);
}

void Course::setTestGrades(const int* arr) {
	for (int i = 0; i < 2; i++)
		testGrades[i] = arr[i];
}

void Course::setHwGrades(const int* arr) {
	for (int i = 0; i < 4; i++)
		hwGrades[i] = arr[i];
}

void Course::updateHwGrade(const int* arr) {
	for (int i = 0; i < 4; i++) {
		if (arr[i] < 0 || arr[i] > 100)
			return;//if the grades aren't valid dont do anything
	}
	setHwGrades(arr);//if all grades are in the 0-100 range update the hw grades to the new ones
}
void Course::updateTestGrade(bool test,const int grade) {
	if (grade < 0 || grade > 100)//check if the grade is valid
		return;
	if (test) {//if true, set the first test's grade to the new one, else set the second test's grade
		testGrades[0] = grade;
	}
	else {
		if (testGrades[0] == -1)
			testGrades[0] = 0;
		testGrades[1] = grade;
	}
}

double Course::courseGrade() const {
	double hwAvg = 0;
	if (testGrades[0] == -1)//if the first test is missing dont calculate the course grade
		return -1;
	for (int i = 0; i < 4; i++) {
		if (hwGrades[i] >= 0 && hwGrades[i] <= 100)
			hwAvg += hwGrades[i];
		else {//happens if missing a grade for an assignment
			cout << "can't calculate grade\n";
			return -1;
		}
	}
	hwAvg = (hwAvg / 4) * 0.4;
	if (testGrades[1] == -1) {// if the second test's score is -1 choose the first test
		if (testGrades[0] <= 55)//if the first test's score is lower than 56 dont add in grades, else add in grades
			return testGrades[0];
		else
			return testGrades[0] * 0.6 + hwAvg;
	}
	else {//if the 2nd test's score isn't -1 choose the 2nd test
		if (testGrades[1] <= 55)//if the second test's score is lower than 56 dont add in grades, else add in grades
			return testGrades[1];
		else
			return testGrades[1] * 0.6 + hwAvg;
	}
}