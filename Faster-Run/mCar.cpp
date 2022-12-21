#include "mCar.h"

mCar::mCar(pPosition pos) : mEnemy(pos) {
	shape = new char* [3];
	for (int i = 0; i < 3; i++)
		shape[i] = new char[14];

	//Row1
	for (int i = 0; i < 14; ++i) {
		if (i == 0 || i == 13)		shape[0][i] = ' ';
		else if (i < 3 || i > 10)	shape[0][i] = '_';
		else						shape[0][i] = '-';
	}
	shape[0][3] = '['; shape[0][10] = ']';

	//Row2
	for (int i = 1; i < 13; ++i) {
		if (i != 3 && i != 10)
			shape[1][i] = ' ';
		else shape[1][i] = '_';
	}
	shape[1][0] = shape[1][13] = '|';

	//Row3
	for (int i = 5; i < 9; ++i)
		shape[2][i] = '-';
	shape[2][0] = 192; shape[2][13] = char(217);
	shape[2][2] = shape[2][9] = '(';
	shape[2][4] = shape[2][11] = ')';
	shape[2][1] = shape[2][12] = ' ' ; shape[2][3] = shape[2][10] = '_';


}
mCar::mCar() {
	shape = new char* [3];
	for (int i = 0; i < 3; i++)
		shape[i] = new char[14];

	//Row1
	for (int i = 0; i < 14; ++i) {
		if (i == 0 || i == 13)		shape[0][i] = ' ';
		else if (i < 3 || i > 10)	shape[0][i] = '_';
		else						shape[0][i] = '-';
	}
	shape[0][3] = '['; shape[0][10] = ']';

	//Row2
	for (int i = 1; i < 13; ++i) {
		if (i != 3 && i != 10)
			shape[1][i] = ' ';
		else shape[1][i] = '_';
	}
	shape[1][0] = shape[1][13] = '|';

	//Row3
	for (int i = 5; i < 9; ++i)
		shape[2][i] = '-';
	shape[2][0] = 192; shape[2][13] = char(217);
	shape[2][2] = shape[2][9] = '(';
	shape[2][4] = shape[2][11] = ')';
	shape[2][1] = shape[2][12] = ' '; shape[2][3] = shape[2][10] = '_';
}
mCar::~mCar() {
	for (int i = 0; i < 3; ++i)
		delete shape[i];
	delete[] shape;
}

char** mCar::GetShape() {
	return shape;
}
int mCar::GetWidth() {
	return 14;
}
int mCar::GetHeight() {
	return 3;
}
int mCar::GetType() {
	return 1;
}
void mCar::Sound() {
	PlaySound(TEXT("Xe.wav"), NULL, SND_ASYNC);
};