#include "mAnt.h"

mAnt::mAnt(pPosition pos) : mEnemy(pos) {
	shape = new char* [3];
	for (int i = 0; i < 3; i++)
		shape[i] = new char[5];

	shape[0][0] = '\\'; shape[0][1] = '('; shape[0][2] = '"'; shape[0][3] = ')'; shape[0][4] = '/';
	shape[1][0] = '-';  shape[1][1] = '('; shape[1][2] = ' '; shape[1][3] = ')'; shape[1][4] = '-';
	shape[2][0] = '//'; shape[2][1] = '('; shape[2][2] = '_'; shape[2][3] = ')'; shape[2][4] = '\\';
}
mAnt::mAnt() {
	shape = new char* [3];
	for (int i = 0; i < 3; i++)
		shape[i] = new char[5];

	shape[0][0] = '\\'; shape[0][1] = '('; shape[0][2] = '"'; shape[0][3] = ')'; shape[0][4] = '/';
	shape[1][0] = '-';  shape[1][1] = '('; shape[1][2] = ' '; shape[1][3] = ')'; shape[1][4] = '-';
	shape[2][0] = '//'; shape[2][1] = '('; shape[2][2] = '_'; shape[2][3] = ')'; shape[2][4] = '\\';
}
mAnt::~mAnt() {
	for (int i = 0; i < 3; ++i)
		delete shape[i];
	delete[] shape;
}

char** mAnt::GetShape() {
	return shape;
}
int mAnt::GetWidth() {
	return 5;
}
int mAnt::GetHeight() {
	return 3;
}
int mAnt::GetType() {
	return 0;
}
void mAnt::Sound() {
	PlaySound(TEXT("Oooo.wav"), NULL, SND_ASYNC);
};