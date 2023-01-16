// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Tutor.h"

Tutor::Tutor(const string name, const int id, const int seniorityYr, const string* subjectsArr, const int nofSubjects, Class* cPtr) :Teacher(name, id, seniorityYr, subjectsArr, nofSubjects)
{
	classPtr = cPtr;
}
Tutor::Tutor(const Tutor& other) : Teacher(other.getName(), other.getID(), other.getSeniorityYr(), other.getSubjects(), other.getNofSubjects()) {
	classPtr = other.classPtr;
}
int Tutor::getSalary()const {
	return 1200 + Teacher::getSalary();
}
bool Tutor::isOutstanding()const {
	int counter = 0;
	int nofPupils = this->classPtr->getNofPupils();
	for (int i = 0; i < nofPupils; i++) {//check the amount of outstanding pupils
		Pupil* pupilTemp = this->classPtr->getPupil(i);
		if (pupilTemp->isOutstanding())
			counter++;
	}
	return ((float)counter / nofPupils > 0.6);//if more than 60% pupils are outstanding return true,else returns false
}
void Tutor::printPupils()const {
	cout << "list of the tutor's pupils:\n";
	for (int i = 0; i < classPtr->getNofPupils(); i++) {
		Pupil* pupilTemp = classPtr->getPupil(i);
		pupilTemp->print();
		if (pupilTemp->isOutstanding())
			cout << "the student is outstanding!!\n";
	}
	cout << "---------------------------------------------\n";//for aesthetics
}
void Tutor::print()const {
	Teacher::print();
	cout << "layer: " << classPtr->getLayer() << endl << "classroom: " << classPtr->getClassroom() << endl;
}
void Tutor::detailedPrint()const {
	print();
	printPupils();
}