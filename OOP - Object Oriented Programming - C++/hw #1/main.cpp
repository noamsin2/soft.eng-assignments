// Author: Noam Karasso
// Score: 97: -2 for not using constant variables, -1 for not using meaningful names in some functions for variables
#include <iostream>
#include "Student.h";

using namespace std;

void createCourses(Student& obj);
void updateGrades(Student& obj);

int main() {
	char str[20];
	cout << "Enter student name" << endl;
	cin >> str;
	Student stu1(str);//non default ctor
	Student stu2;//default ctor
	createCourses(stu1);
	updateGrades(stu1);
	Student stu3(stu1);//copy ctor
	cout << "~~~~~~~~~~~~~~~~STUDENT 1~~~~~~~~~~~~~~~" << endl;
	stu1.printStu();
	cout << "~~~~~~~~~~~~~~~~STUDENT 2~~~~~~~~~~~~~~~" << endl;
	stu2.printStu();
	cout << "~~~~~~~~~~~~~~~~STUDENT 3~~~~~~~~~~~~~~~" << endl;
	stu3.printStu();
	
	return 0;
}

void createCourses(Student& obj) {
	int nofCourses;
	cout << "Enter the number of courses you want to add\n";
	cin >> nofCourses;
	for (int i = 0; i < nofCourses; i++) {
		char courseName[20];
		cout << "Enter a course name\n";
		cin >> courseName;
		obj.addCourse(courseName);//add the course to the list
	}
}

void updateGrades(Student& obj) {
	int nofCourses;
	cout << "Enter the number of courses you want to update\n";
	cin >> nofCourses;
	for (int i = 0; i < nofCourses; i++) {
		bool test = true;
		char courseName[20];
		cout << "enter the name of the course you want to update\n";
		cin >> courseName;
		int hwGrades[4];
		cout << "Enter the assignment grades\n";
		for (int j = 0; j < 4; j++)
			cin >> hwGrades[j];
		obj.updateHwCourse(courseName, hwGrades);//updates hw grades
		cout << "Enter the test grades\n";
		for (int j = 0; j < 2; j++) {
			int grade;
			cin >> grade;
			obj.updateTestCourse(courseName, test, grade);//on first iteration it updates the first test(test = true)
			test = false;//on the second iteration it updates the second test
		}
	}
}