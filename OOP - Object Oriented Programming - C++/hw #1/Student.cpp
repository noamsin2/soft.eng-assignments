// Author: Noam Karasso
// Score: 97: -2 for not using constant variables, -1 for not using meaningful names in some functions for variables
#include "Student.h";


Student::Student() :numOfCourses(0) {
	strcpy(stuName, "unknown");
	courseList = nullptr;
}

Student::Student(const char* str) :numOfCourses(0) {
	strcpy(stuName, str);
	courseList = nullptr;
}

Student::Student(const Student& obj) :numOfCourses(obj.numOfCourses) {
	strcpy(stuName, obj.stuName);
	courseList = new Course * [numOfCourses];
	for (int i = 0; i < numOfCourses; i++) {
		courseList[i] = new Course;
		courseList[i]->setCourseName(obj.courseList[i]->getCourseName());//DEEP COPY to the course
		courseList[i]->setHwGrades(obj.courseList[i]->getHwGrades());
		courseList[i]->setTestGrades(obj.courseList[i]->getTestGrades());
	}
}

	Student::~Student() {
		for (int i = 0; i < numOfCourses; i++) {
			delete courseList[i];
		}
		delete[] courseList;
	}
	void Student::addCourse(const char* str) {
		for (int i = 0; i < numOfCourses; i++) {
			if (!strcmp(courseList[i]->getCourseName(), str))//if the names are equal strcmp function returns '0' -> '1' and exits the function
				return;
		}
		int nofCourses = numOfCourses;//temp variable that takes the number of courses before adding the new one
		numOfCourses++;
		Course** newCourselist = new Course * [numOfCourses];//make a new list with a +1 size for the new course
		for (int i = 0; i < nofCourses; i++) {//copy every course from the old list
			newCourselist[i] = new Course;
			newCourselist[i]->setCourseName(courseList[i]->getCourseName());
			newCourselist[i]->setHwGrades(courseList[i]->getHwGrades());
			newCourselist[i]->setTestGrades(courseList[i]->getTestGrades());
			delete courseList[i];//delete the old course
		}
		newCourselist[nofCourses] = new Course;//allocate memory for the new course
		newCourselist[nofCourses]->setCourseName(str);//add in the new course
		delete courseList;
		courseList = newCourselist;
	}

	void Student::updateHwCourse(const char* str, const int* arr) {
		for (int i = 0; i < numOfCourses; i++)
			if (!strcmp(courseList[i]->getCourseName(), str)) {//check if the course exists
				courseList[i]->updateHwGrade(arr);//updateHwGrade function checks if the grades are valid and updates them if all grades are in the 0-100 range
				break;
			}
	}
	void Student::updateTestCourse(const char* str, const bool test, const int grade) {
		for (int i = 0; i < numOfCourses; i++)
			if (!strcmp(courseList[i]->getCourseName(), str)) {//check if the course exists
				courseList[i]->updateTestGrade(test, grade);//updateTestGrade function checks if the grade is valid and updates the test to be equal to it
				break;
			}
	}
	void Student::printStu()const {
		cout << "Student name:" << stuName << endl;
		cout << "List of courses:" << endl;
		for (int i = 0; i < numOfCourses; i++) {
			cout <<"Course name:" << courseList[i]->getCourseName() << endl;
			cout << "Assignment grades:" << endl;
			for (int j = 0; j < 4; j++)
				cout << courseList[i]->getHwGrades()[j] << " ";
			
			cout << "\nTest grades:" << endl;
			for (int j = 0; j < 2; j++)
				cout << courseList[i]->getTestGrades()[j] << " ";
			cout << "\nAverage grades: " << courseList[i]->courseGrade() << endl;
		}
	}
