// Author: Noam Karasso
// Score: 100
#include "Employee.h"

Employee::Employee() : _id("00000000"), _firstName("david"), _lastName("davidov"), _salary(0), _hoursAmt(0) {}
Employee::Employee(const string id, const string firstName, const string lastName,const double salary,const float hoursAmt) {
	for (int i = 0; i < id.length(); i++)
		if (id[i] < '0' || id[i] > '9')
			throw invalid_argument("invalid id");
	for (int i = 0; i < firstName.length(); i++)
		if (!((firstName[i] >= 'a' && firstName[i] <= 'z') || (firstName[i] >= 'A' && firstName[i] <= 'Z'))) {
			throw invalid_argument("invalid first name");
		}
	for (int i = 0; i < lastName.length(); i++)
		if (!((lastName[i] >= 'a' && lastName[i] <= 'z') || (lastName[i] >= 'A' && lastName[i] <= 'Z'))) {
			throw invalid_argument("invalid last name");
		}
	if (salary < 0)
		throw invalid_argument("invalid salary");
	if (hoursAmt < 0)
		throw invalid_argument("invalid amount of hours");
	_id = id;
	_firstName = firstName;
	_lastName = lastName;
	_salary = salary;
	_hoursAmt = hoursAmt;
}
bool Employee::operator >(const Employee&other)const {
	return (_salary > other._salary);
}
ostream& operator <<(ostream& output, const Employee& object) {
	output << "the employee's full name is: " << object._firstName << " " << object._lastName << endl;
	output << "id: " << object._id << endl;
	output << "salary: " << object._salary << endl;
	output << "amount of hours: " << object._hoursAmt << endl;
	return output;
}
bool Employee::operator == (const Employee& object)const {
	return (_id == object._id);
}
