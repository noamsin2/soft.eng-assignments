#define _CRT_SECURE_NO_WARNINGS
#pragma once
// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include <iostream>
#include "Class.h"
#include <assert.h>
#define minLayer 'a'
#define maxLayer 'f'
#define minClass 1
#define maxClass 3

using namespace std;

class Layer {
private:
	char layer;
	Class** classes = nullptr;
	const int nofClasses = maxClass;

public:
	Layer(const char layer);
	~Layer();
	Class* getClass(const int index)const;

};
