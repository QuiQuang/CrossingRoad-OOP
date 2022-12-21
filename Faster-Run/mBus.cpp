#include "mBus.h"

mBus::mBus(pPosition pos) : mEnemy(pos) {
	shape = new char* [3];
	for (int i = 0; i < 3; i++)
		shape[i] = new char[11];

	//Row1
	for (int i = 1; i < 10; ++i)
		shape[0][i] = '-';
	shape[0][0] = char(218); shape[0][10] = char(191);

	//Row2
	shape[1][0] = shape[1][10] = '|';
	shape[1][1] = shape[1][4] = shape[1][7] = '[';
	shape[1][3] = shape[1][6] = shape[1][9] = ']';
	shape[1][2] = shape[1][5] = shape[1][8] = '-';
	
	//Row3
	for (int i = 1; i < 10; ++i) {
		if (i == 2 || i == 8)	shape[2][i] = 'o';
		else						shape[2][i] = '-';
	}
	shape[2][10] = char(217);
	shape[2][0] = char(192);
}
mBus::mBus() {
	shape = new char* [3];
	for (int i = 0; i < 3; i++)
		shape[i] = new char[11];

	//Row1
	for (int i = 1; i < 10; ++i)
		shape[0][i] = '-';
	shape[0][0] = char(218); shape[0][10] = char(191);

	//Row2
	shape[1][0] = shape[1][10] = '|';
	shape[1][1] = shape[1][4] = shape[1][7] = '[';
	shape[1][3] = shape[1][6] = shape[1][9] = ']';
	shape[1][2] = shape[1][5] = shape[1][8] = '-';

	//Row3
	for (int i = 1; i < 10; ++i) {
		if (i == 2 || i == 8)	shape[2][i] = 'o';
		else						shape[2][i] = '-';
	}
	shape[2][10] = char(217);
	shape[2][0] = char(192);
}
mBus::~mBus() {
	for (int i = 0; i < 3; ++i)
		delete shape[i];
	delete[] shape;
}

char** mBus::GetShape() {
	return shape;
}
int mBus::GetWidth() {
	return 11;
}
int mBus::GetHeight() {
	return 3;
}
int mBus::GetType() {
	return 0;
}
void mBus::Sound() {
	PlaySound(TEXT("Oizoioi.wav"), NULL, SND_ASYNC);
};