// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Worker.h"

Worker::Worker(const string name, const int id, const int seniorityYr) :Person(name, id), seniorityYr(seniorityYr){}
Worker::Worker(const Worker& other) : Person(other.getName(), other.getID()), seniorityYr(other.seniorityYr) {}
void Worker::print()const {
	Person::print();
	cout << "years of seniority: " << seniorityYr << endl << "Salary: " << getSalary() << endl;
}