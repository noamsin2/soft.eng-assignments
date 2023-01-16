#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 100
#include <iostream>
#include <stdexcept>
#include <typeinfo>

using namespace std;

template<class T>
class Set {
private:
	int _arrSize;
	T* _setArray;
public:
	Set();
	Set(const int size,const T* array);
	Set(const Set& other);
	~Set();
	Set& operator = (const Set& object);
	bool operator == (const Set& object)const;
	Set& operator += (const T& element);
	Set operator + (const Set& object)const;//take the two objects and make a new one that is gonna be the union of them
	Set& operator -= (const T& element);
	Set operator - (const Set& object)const;
	bool operator >(const Set& object)const;
	void getType()const;
	template <class U>
	friend ostream& operator << (ostream& output, const Set<U>& object);
};

template<class T>
Set<T>::Set() :_arrSize(0)
{
	_setArray = nullptr;//initialized
}
template<class T>
Set<T>::Set(const int size,const T* array) : _arrSize(size) {
	T* tempArr = new T[_arrSize];
	int index = 0;
	bool consistsElement = false;
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (array[i] == array[j]) {//if our array consists an element of array[i] then dont add it
				consistsElement = true;
				break;
			}
		}
		if (!consistsElement) {
			tempArr[index] = array[i];
			index++;
		}
		else
			consistsElement = false;
	}
	tempArr[index] = array[size - 1];
	index++;
	_arrSize = index;
	_setArray = new T[_arrSize];
	for (int i = 0; i < index; i++)
		_setArray[i] = tempArr[i];
	delete[] tempArr;
}
template<class T>
Set<T>::Set(const Set& other):_arrSize(other._arrSize) {
	*this = other;
}
template<class T>
Set<T>::~Set(){
	delete[] _setArray;
}
template<class T>
Set<T>& Set<T>::operator = (const Set& object) {
	_arrSize = object._arrSize;
	if (_setArray)
		delete[]_setArray;
	_setArray = new T[_arrSize];
	for (int i = 0; i < _arrSize; i++)
		_setArray[i] = object._setArray[i];

	return *this;
}
template<class T>
bool Set<T>::operator == (const Set& object)const {
	if (_arrSize != object._arrSize)//it means they dont consist the same elements
		return false;
	bool consistsElement = false;
	for (int i = 0; i < _arrSize; i++) {
		for (int j = 0; j < _arrSize; j++) {
			if (_setArray[i] == object._setArray[j]) {
				consistsElement = true;
				break;
			}
		}
		if (!consistsElement)
			return false;
		consistsElement = false;
	}
	return true;
}
template <class T>
Set<T>& Set<T>::operator += (const T& element) {
	for (int i = 0; i < _arrSize; i++) {
		if (_setArray[i] == element) {
			cout << "it already exists in the array!, didn't add\n";
			return *this;
		}
	}
	_arrSize++;
	T* newArr = new T[_arrSize];
	for (int i = 0; i < _arrSize - 1; i++)
		newArr[i] = _setArray[i];
	newArr[_arrSize - 1] = element;
	delete[] _setArray;
	_setArray = newArr;

	return *this;
}
template<class T>
Set<T> Set<T>::operator + (const Set<T>& object) const {
	bool consistsElement = false;
	T* tempArr = new T[_arrSize];//array to hold all the elements that exist only in the first set(this->_setArray)
	int index = 0;
	for (int i = 0; i < _arrSize; i++) {
		for (int j = 0; j < object._arrSize; j++) {
			if (_setArray[i] == object._setArray[j]){
				consistsElement = true;
				break;
		}
		}
		if (!consistsElement) {
			tempArr[index] = _setArray[i];
			index++;
		}
		else
			consistsElement = false;
	}
	T* newArr = new T[index + object._arrSize];
	for (int i = 0; i < index; i++)//copy the elements that exist only in first set
		newArr[i] = tempArr[i];
	for (int i = 0; i < object._arrSize; i++) {//copy all the elements from the second set
		newArr[index] = object._setArray[i];
		index++;
	}
	Set set3(index, newArr);//make a new set
	delete[]tempArr;
	delete[]newArr;
	return set3;
	
}
template<class T>
Set<T>& Set<T>::operator -= (const T& element) {
	int index;
	bool consistsElement = false;
	for (index = 0; index < _arrSize; index++) {
		if (_arrSize[index] == element) {
			consistsElement = true;
			break;
		}
	}
	if (!consistsElement)
		throw invalid_argument("element doesn't exist");
	_arrSize--;
	T* newArr = new T[_arrSize];
	for (int i = 0; i < _arrSize + 1; i++)
		if (i != index)
			newArr[i] = _setArray[i];
	delete[]_setArray;
	_setArray = newArr;
	return *this;
}
template <class T>
Set<T> Set<T>::operator - (const Set& object)const {
	bool consistsElement = false;
	T* tempArr = new T[_arrSize];//array to hold all the elements that exist only in the first set(this->_setArray)
	int index = 0;
	for (int i = 0; i < _arrSize; i++) {
		for (int j = 0; j < object._arrSize; j++) {
			if (_setArray[i] == object._setArray[j]) {
				consistsElement = true;
				break;
			}
		}
		if (!consistsElement) {
			tempArr[index] = _setArray[i];
			index++;
		}
		else
			consistsElement = false;
	}
	if (index == 0) {
		delete[] tempArr;
		throw "empty set!";
	}
	T* newArr = new T[index];
	for (int i = 0; i < index; i++)//copy the elements that exist only in first set
		newArr[i] = tempArr[i];
	Set set3(index, newArr);//make a new set
	delete[]tempArr;
	delete[]newArr;
	return set3;
}
template<class T>
bool Set<T>::operator >(const Set& object)const {
	if (_arrSize < object._arrSize)//if the set size is smaller it necessarily means that it doesn't contain all the elements in set2
		return false;
	bool consistsElement = false;
	for (int i = 0; i < _arrSize; i++) {
		for (int j = 0; j < _arrSize; j++) {
			if (_setArray[i] == object._setArray[i]) {
				consistsElement = true;
				break;
			}
		}
		if (!consistsElement)
			return false;
		consistsElement = false;
	}
	return true;
}
template<class T>
ostream& operator << (ostream & output, const Set<T>& object) {
	object.getType();
	output << "the size of the set: " << object._arrSize << endl;
	output << "the set members: ";
	for (int i = 0; i < object._arrSize; i++)
		output << object._setArray[i] << " ";
	output << endl;
	return output;
}
template<class T>
void Set<T>::getType()const {
	cout << "type name: " << typeid(T).name() << endl;
}