// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Teacher.h";

Teacher::Teacher(const string name, const int id, const int seniorityYr, const string* subjectsArr, const int nofSubjects) :Worker(name, id, seniorityYr), nofSubjects(nofSubjects) {
	subjects = new string[this->nofSubjects];
	for (int i = 0; i < nofSubjects; i++)
		subjects[i] = subjectsArr[i];
}

Teacher::Teacher(const Teacher& other) : Worker(other.getName(), other.getID(), other.getSeniorityYr()), nofSubjects(other.nofSubjects)
{
	subjects = new string[nofSubjects];
	for (int i = 0; i < nofSubjects; i++)
		subjects[i] = other.subjects[i];
}
Teacher::~Teacher() {
	delete[]subjects;
}
int Teacher::getSalary()const {
	return basis * (1 + ((float)nofSubjects / 10)) + 200 * this->getSeniorityYr();
}
bool Teacher::isOutstanding()const {
	return nofSubjects > 5;
}
void Teacher::printSubjects()const {
	cout << "subjects: ";
	for (int i = 0; i < nofSubjects; i++)
		cout << subjects[i] << ", ";
	cout << endl;
}
void Teacher::print()const {
	Worker::print();
	printSubjects();
	cout << "---------------------------------------------\n";//for aesthetics
}