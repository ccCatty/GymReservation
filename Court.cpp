#include "Court.h"
using namespace std;

Court::Court() {
	sports = ID = cap = 0;
}

int Court::getSports() {
	return sports;
}

void Court::setSports(int s) {
	sports = s;
}

int Court::getID() {
	return ID;
}

void Court::setID(int i) {
	ID = i;
}

int Court::getCap() {
	return cap;
}

void Court::setCap(int c) {
	cap = c;
}
