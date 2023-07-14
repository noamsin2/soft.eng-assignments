// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Secretary.h"

Secretary::Secretary(const string name, const int id, const int seniorityYr, int nofChild) :Worker(name, id, seniorityYr)
{
	if (nofChild > 0)
		this->nofChild = nofChild;
	else
		this->nofChild = 0;
}
Secretary::Secretary(const Secretary& other) :Worker(other.getName(), other.getID(), other.getSeniorityYr()), nofChild(other.nofChild) {}
int Secretary::getSalary()const {
	return basis + nofChild * 250;
}
bool Secretary::isOutstanding()const {
	return getSeniorityYr() > 15;
}
void Secretary::print()const {
	Worker::print();
	cout << "---------------------------------------------\n";//for aesthetics
}