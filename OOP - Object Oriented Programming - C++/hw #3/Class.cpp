// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Class.h"

Class::Class(const char layer, const int classroom, Tutor* tutorPtr) : layer(layer), classroom(classroom), tutor(tutorPtr)
{
	pupils = nullptr;
}
Class::Class(const Class& other) : layer(other.layer), classroom(other.classroom), nofPupils(other.nofPupils), tutor(other.tutor) {
	if (nofPupils > 0) {
		pupils = new Pupil * [nofPupils];
		for (int i = 0; i < nofPupils; i++)
			pupils[i] = other.pupils[i];
	}
	else
		pupils = nullptr;
}
Class::~Class() {

	if (pupils != nullptr)
		delete[] pupils;
}
void Class::addPupil(Pupil* newPupil) {
	nofPupils++;
	int i = 0;
	Pupil** newPupils = new Pupil * [nofPupils];
	for (; i < nofPupils - 1; i++)
		newPupils[i] = pupils[i];//copy all the old pupils(not deep copy)
	newPupils[i] = newPupil;//add the new pupil
	delete[]pupils;
	pupils = newPupils;
}
Pupil* Class::getPupil(const int index)const {
	if (index >= nofPupils || index < 0)
		return nullptr;
	return pupils[index];
}