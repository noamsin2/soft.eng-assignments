#define _CRT_SECURE_NO_WARNINGS
// Author: Noam Karasso
// Score: 97: -2 for not using constant variables, -1 for not using meaningful names in some functions for variables
#include <iostream>
#include <cstring>
#include "Course.h";

using namespace std; 

class Student {
private:
	char stuName[20];
	Course** courseList = nullptr;
	int numOfCourses;

public:
	Student();//default ctor
	Student(const char* str);//ctor
	Student(const Student& obj);//copy ctor
	~Student();
	void addCourse(const char* str);
	void updateHwCourse(const char* str, const int* arr);
	void updateTestCourse(const char* str, const bool test, const int grade);
	void printStu()const;
};
