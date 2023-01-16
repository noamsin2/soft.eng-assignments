// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Pupil.h"

Pupil::Pupil(const string name, const int id, const int* gradesArr, const int nofGrades, const char layer, const int classroom) :Person(name, id), nofGrades(nofGrades), classroom(classroom), layer(layer)
{
	grades = new int[this->nofGrades];
	for (int i = 0; i < this->nofGrades; i++)
		grades[i] = gradesArr[i];
}
Pupil::Pupil(const Pupil& other) :Person(other.getName(), other.getID()),nofGrades(other.nofGrades), layer(other.layer), classroom(other.classroom) {
	grades = new int[nofGrades];
	for (int i = 0; i < nofGrades; i++)
		grades[i] = other.grades[i];
}
Pupil::~Pupil() {
	delete[] grades;
}
float Pupil::calcAvg()const {
	int sum = 0;
	for (int i = 0; i < nofGrades; i++)
		sum += grades[i];
	
	return (float)sum / nofGrades;
}
bool Pupil::isOutstanding()const {
	for (int i = 0; i < nofGrades; i++)
		if (grades[i] < 70)//if at least 1 grade is below 70 return false
			return false;
	return calcAvg() > 85;//if avg is above 85 pupil is outstanding
}
void Pupil::print()const {
	Person::print();
	cout << "layer: " << layer << endl << "classroom: " << classroom << endl << "grades: ";
	for (int i = 0; i < nofGrades; i++)
		cout << grades[i] << " ";
	cout << endl << "grades average: " << calcAvg() << endl;
	cout << "---------------------------------------------\n";//for aesthetics
}