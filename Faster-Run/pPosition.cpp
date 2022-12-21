#include "pPosition.h"

pPosition::pPosition() {
	X = 0;
	Y = 0;
}
pPosition::pPosition(const int x, const int y) {
	X = x;
	Y = y;
}
pPosition::~pPosition(){}

int pPosition::GetX() {
	return X;
}
int pPosition::GetY() {
	return Y;
}

void pPosition::SetPos(int x, int y) {
	X = x;
	Y = y;
}