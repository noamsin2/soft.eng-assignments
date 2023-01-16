#define _CRT_SECURE_NO_WARNINGS
// Author: Noam Karasso
// Score: 100
#include <iostream>
#include "Employee.h"
#include "Set.h"
#include <string>
#include <stdexcept>
#include <typeinfo>

#define N 2//number of sets

using namespace std;

int main() {
	Set<int>** numSets = new Set<int>*[N];
	Set<Employee>** empSets = new Set<Employee>*[N];
	cout << "set type : int\n";
	for (int i = 0; i < N; i++) {
		int setSize;
		cout << "enter the amount of members in set " << i + 1 << endl;
		cin >> setSize;
		int* setArray = new int[setSize];
		cout << "enter " << setSize << " members\n";
		for (int j = 0; j < setSize; j++)
			cin >> setArray[j];
		numSets[i] = new Set<int>(setSize, setArray);//set constructor
		Set<int>settest(setSize, setArray);
		delete[]setArray;
	}
	for (int i = 0; i < N; i++)
		empSets[i] = new Set<Employee>;//default constructor for set<employee>
	cout << "set type : employee\n";
	for (int i = 0; i < N; i++) {
		int setSize;
		cout << "enter the amount of members you want to add to set " << i + 1 << endl;
		cin >> setSize;
		cout << "enter " << setSize << " members\n";
		for (int j = 0; j < setSize; j++) {
			string id, firstName, lastName;
			double salary;
			float hoursAmt;
			cout << "enter id\n";
			cin >> id;
			cout << "enter first name\n";
			cin >> firstName;
			cout << "enter last name\n";
			cin >> lastName;
			cout << "enter salary\n";
			cin >> salary;
			cout << "enter amount of hours\n";
			cin >> hoursAmt;
			try {
				Employee employee(id, firstName, lastName, salary, hoursAmt);
				empSets[i][0] += employee;
			}
			catch (const invalid_argument const& e) {
				cout << "error!! could not make Employee!\n";
				cout << "reason: " << e.what() << endl;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		int num;
		cout << *numSets[i];
		cout << "enter a new element for set" << i + 1 << endl;
		cin >> num;
		*numSets[i] += num;
	}

	for (int i = 0; i < N; i++) {
		cout << "Set" << i + 1 << " after adding an element\n";
		cout << *numSets[i];
	}

	cout << "the result of the union of set1 and set2 is:\n";
	Set<int> set3 = *numSets[0] + *numSets[1];//copy constructor
	cout << set3 << endl;
	try {
		cout << "the result of the difference of set1 and set2 is(set1 - set2):\n";
		Set<int>set4 = *numSets[0] - *numSets[1];
		cout << set4 << endl;
	}
	catch (const char* msg) {
		cout << "error!!(set<int>)\n";
		cout << msg << endl;
	}
	for (int i = 0; i < N; i++) {
		cout << "enter a new element for set" << i + 1 << endl;
		string id, firstName, lastName;
		double salary;
		float hoursAmt;
		cout << "enter id\n";
		cin >> id;
		cout << "enter first name\n";
		cin >> firstName;
		cout << "enter last name\n";
		cin >> lastName;
		cout << "enter salary\n";
		cin >> salary;
		cout << "enter amount of hours\n";
		cin >> hoursAmt;
		cout << *empSets[i];
		try {
			Employee employee(id, firstName, lastName, salary, hoursAmt);
			*empSets[i] += employee;
		}
		catch (const invalid_argument const& e) {
			cout << "error!! could not make Employee!\n";
			cout << "reason: " << e.what() << endl;
		}
	}

	for (int i = 0; i < N; i++) {
		cout << "Set" << i + 1 << " after adding an element\n";
		cout << *empSets[i];
	}

	cout << "the result of the union of set1 and set2 is:\n";
	Set<Employee> set5 = *empSets[0] + *empSets[1];//copy constructor
	cout << set5 << endl;
	try {
		cout << "the result of the difference of set1 and set2 is(set1 - set2):\n";
		Set<Employee>set6 = *empSets[0] - *empSets[1];
		cout << set6 << endl;
	}
	catch (const char* msg) {
		cout << "error!!(set<employee>)\n";
		cout << msg << endl;
	}
	for (int i = 0; i < N; i++) {
		delete numSets[i];
		delete empSets[i];
	}
	delete[]numSets;
	delete[]empSets;
	return 0;
}