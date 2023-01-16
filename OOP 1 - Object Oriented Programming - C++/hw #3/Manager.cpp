// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Manager.h";

Manager::Manager(const string name, const int id, const int seniorityYr) :Worker(name, id, seniorityYr) {}
Manager::Manager(const Manager& other) : Worker(other.getName(), other.getID(), other.getSeniorityYr()) {}
int Manager::getSalary()const {
	return basis * 3 + getSeniorityYr() * 500;
}
bool Manager::isOutstanding()const {
	return getSeniorityYr() > 4;
}
void Manager::print()const{
	Worker::print();
	cout << "---------------------------------------------\n";//for aesthetics
}