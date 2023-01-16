// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "School.h"

School::School() :nofPeople(0)
{
	layers = new Layer * [nofLayers];
	for (int i = 0; i < nofLayers; i++) {
		layers[i] = new Layer('a' + i);//make all layers starting with layer 'a' up to layer 'f'
	}
	people = nullptr;
	mgr = false;
}
School::~School() {
	for (int i = 0; i < nofLayers; i++)
		delete layers[i];
	for (int i = 0; i < nofPeople; i++)
		delete people[i];
	delete[] people;
	delete[]layers;//layers will always be initialized
}
void School::Menu() {
	int options;
	do {
		cout << "choose an operation\n" << "1-Add pupil\n" << "2-Add teacher\n" << "3-Add tutor\n" << "4-Add manager\n" << "5-Add secretary\n" << "6-Print workers and pupil details\n" << "7-Print outstanding people\n" << "8-Print tutor's class\n" << "9-Print worker details with smallest salary\n" << "10-Exit\n";
		cin >> options;
		switch (options) {
		case 0:cout << "illegal operation, terminating"; break;//in case the user gives letter / symbol as input to avoid infinite loops
		case 1: addPupil(); break;
		case 2: addTeacher(); break;
		case 3: addTutor(); break;
		case 4: addManager(); break;
		case 5: addSecretary(); break;
		case 6: printPeople(); break;
		case 7: printOS(); break;
		case 8: printTutorsCL(); break;
		case 9: printMinSalary(); break;
		case 10: cout << "exiting"; break;
		default:cout << "invalid input, enter again\n";
		}
	} while (options != 10 && options != 0);
}
void School::addPupil() {
	char layer;
	int classroom;
	string name;
	int id;
	int nofGrades;
	int* gradesArr;
	int i = 0;
	do {
		cout << "enter a layer\n";
		cin >> layer;
	} while (layer < 'a' || layer > 'f');
	do {
		cout << "enter a classroom\n";
		cin >> classroom;
	} while (classroom < minClass || classroom > maxClass);
	cout << "enter a name, id and number of grades\n";
	cin >> name >> id >> nofGrades;
	if (checkPerson(id))//checks if the pupil exists, if it does, return from the function
		return;
	
	gradesArr = new int[nofGrades];
	cout << "enter grades\n";
	for (int i = 0; i < nofGrades; i++)
		cin >> gradesArr[i];//take grades
	nofPeople++;
	Person** newPeople = new Person * [nofPeople];
	for (; i < nofPeople - 1; i++)
		newPeople[i] = people[i];//copy the people that were in the array(not deep copy)
	newPeople[i] = new Pupil(name, id, gradesArr, nofGrades, layer, classroom);//make a new pupil and add the new pupil to the array
	layers[layer - 'a']->getClass(classroom - 1)->addPupil((Pupil*)newPeople[i]);//add the new pupil to the Class
	delete[] gradesArr;
	delete[]people;
	people = newPeople;
}
void School::addTeacher() {
	int seniorityYr;
	int nofSubjects;
	string name;
	int id;
	string* subjectsArr;
	int i = 0;
	cout << "enter a name, id, number of subjects, and years of seniority\n";
	cin >> name >> id >> nofSubjects >> seniorityYr;
	if (checkPerson(id))//checks if the teacher exists, if it does, return from the function
		return;
	subjectsArr = new string[nofSubjects];
	cout << "enter subjects names\n";
	for (int i = 0; i < nofSubjects; i++)
		cin >> subjectsArr[i];//take subjects' names
	nofPeople++;
	Person** newPeople = new Person * [nofPeople];
	for (; i < nofPeople - 1; i++)
		newPeople[i] = people[i];//copy the people that were in the array(not deep copy)
	newPeople[i] = new Teacher(name, id, seniorityYr, subjectsArr, nofSubjects);//make a new teacher and add the new teacher to the people array
	delete[] subjectsArr;
	delete[]people;
	people = newPeople;
}
void School::addTutor() {
	char layer;
	int classroom;
	int seniorityYr;
	int nofSubjects;
	string name;
	int id;
	string* subjectsArr;
	int i = 0;
	do {
		cout << "enter a layer\n";
		cin >> layer;
	} while (layer < 'a' || layer > 'f');
	do {
		cout << "enter a classroom\n";
		cin >> classroom;
	} while (classroom < minClass || classroom > maxClass);
	cout << "enter a name, id, number of subjects, and years of seniority\n";
	cin >> name >> id >> nofSubjects >> seniorityYr;
	if (checkPerson(id))//checks if the tutor exists, if it does, return from the function
		return;
	subjectsArr = new string[nofSubjects];
	cout << "enter subjects' names\n";
	for (int i = 0; i < nofSubjects; i++)
		cin >> subjectsArr[i];//take subjects' names
	nofPeople++;
	Person** newPeople = new Person * [nofPeople];
	for (; i < nofPeople - 1; i++)
		newPeople[i] = people[i];//copy the people that were in the array(not deep copy)
	newPeople[i] = new Tutor(name, id, seniorityYr, subjectsArr, nofSubjects, layers[layer - 'a']->getClass(classroom - 1));//make a tutor and add the new tutor to the array
	layers[layer - 'a']->getClass(classroom - 1)->setTutor((Tutor*)newPeople[i]);//add the tutor to the class
	delete[] subjectsArr;
	delete[]people;
	people = newPeople;
}
void School::addManager() {
	int seniorityYr;
	string name;
	int id;
	int i = 0;
	cout << "enter a name, id, and years of seniority\n";
	cin >> name >> id >> seniorityYr;
	if (checkPerson(id) || mgr == true)//checks if the person exists or if the school has a manager already
		return;
	
	nofPeople++;
	Person** newPeople = new Person * [nofPeople];
	for (; i < nofPeople - 1; i++)
		newPeople[i] = people[i];//copy the people that were in the array(not deep copy)
	newPeople[i] = new Manager(name, id, seniorityYr);//make a manager and add the new manager to the people array
	mgr = true;
	delete[]people;
	people = newPeople;
}
void School::addSecretary() {
	int seniorityYr;
	string name;
	int id;
	int nofChild;
	int i = 0;
	cout << "enter a name, id, number of children in school, and years of seniority\n";
	cin >> name >> id >> nofChild >> seniorityYr;
	if (checkPerson(id))//checks if the secretary exists
		return;
	nofPeople++;
	Person** newPeople = new Person * [nofPeople];
	for (; i < nofPeople - 1; i++)
		newPeople[i] = people[i];//copy the people that were in the array(not deep copy)
	newPeople[i] = new Secretary(name, id, seniorityYr, nofChild);//make a secretary and add the new secretary to the people array

	delete[]people;
	people = newPeople;
}
bool School::checkPerson(const int id)const {
	for (int i = 0; i < nofPeople; i++)
		if (people[i]->getID() == id) {
			cout << "this person already exists\n";
			return true;
		}
	return false;
}
void School::printPeople()const {
	for (int i = 0; i < nofPeople; i++) {
		people[i]->print();
	}
}
void School::printOS()const {
	for (int i = 0; i < nofPeople; i++) {
		if (people[i]->isOutstanding())
			people[i]->print();
	}
}

void School::printTutorsCL() const
{
	int id;
	cout << "enter tutor's id\n";
	cin >> id;
	for (int i = 0; i < nofPeople; i++) {
		if (people[i]->getID() == id) {//check if the id matches
			if (Tutor* tutorPtr = dynamic_cast<Tutor*>(people[i]))//check if its a tutor
					tutorPtr->detailedPrint();
			else {//if its not a tutor break to avoid going through all people
				cout << "its not a tutor\n";
				break;
			}
		}
	}
}
void School::printMinSalary()const {
	int minSalary = 50000;//starting min salary (all salaries should be lower than this)
	int salary;//temp variable to avoid sending to functions many times
	string name;//name and id of the lowest salary employee
	int id = 0;
	int index = 0;//index of the person with the lowest salary
	for (int i = 0; i < nofPeople; i++) {
		if (Pupil* pupilPtr = dynamic_cast<Pupil*>(people[i])) {//checks if pupil, pupil doesn't have a salary
			continue;
		}//if its not a pupil then its a worker
		Worker* workerPtr = (Worker*)people[i];
		if (workerPtr != NULL) {
			salary = workerPtr->getSalary();
			if (salary < minSalary) {
				minSalary = salary;
				index = i;
			}
		}
	}
	if (people[index] != NULL)
	cout << "name of the employee with the lowest salary: " << people[index]->getName() << endl << "id: " << people[index]->getID() << endl << "salary: " << minSalary << endl;
}