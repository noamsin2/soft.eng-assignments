// Author: Noam Karasso
// Score: 97 : -3 for not using constant for some variables lol..
#include "Layer.h";

Layer::Layer(const char layer) :layer(layer)
{
	assert(layer >= minLayer && layer <= maxLayer);
	classes = new Class * [nofClasses];
	for (int i = 0; i < nofClasses; i++) {
		int tempClassroom = i + 1;
		classes[i] = new Class(this->layer, tempClassroom, nullptr);
	}
}
Layer::~Layer() {
	for (int i = 0; i < nofClasses; i++)
		delete classes[i];
	delete[]classes;
}
Class* Layer::getClass(const int index)const {//index = 0 returns the first Class
	assert(index >= 0 && index <= maxClass - 1 );
	return classes[index];
}
