// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Person.h"

Person::Person(const string name, const int id) :name(name), id(id){}
Person::Person(const Person& other) :name(other.name), id(other.id){}
void Person::print()const {
	cout << "name is: " << name << endl << "id is: " << id << endl;
}