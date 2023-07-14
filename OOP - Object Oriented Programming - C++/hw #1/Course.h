#define _CRT_SECURE_NO_WARNINGS
// Author: Noam Karasso
// Score: 97: -2 for not using constant variables, -1 for not using meaningful names in some functions for variables
#include <iostream>
#include <cstring>

using namespace std;

class Course {
private:
	char courseName[20];
	int testGrades[2];
	int hwGrades[4];//hw for homework
	void resetGrades(const bool grades);//function to set the grades to -1 (true value changes test grades and false value changes hw grades)

public:
	Course();//default ctor
	Course(const char* str);//ctor
	Course(const Course& obj);//copy ctor
	~Course();//dtor
	const char* getCourseName()const { return courseName; };
	const int* getTestGrades() const { return testGrades; };
	const int* getHwGrades() const { return hwGrades; };
	void setCourseName(const char* str);
	void setTestGrades(const int* arr);
	void setHwGrades(const int* arr);
	void updateHwGrade(const int* arr);
	void updateTestGrade(const bool test,const int grade);
	double courseGrade()const;//calculate course grade
};