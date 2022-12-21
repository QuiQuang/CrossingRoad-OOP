#pragma once
#include "mEnemy.h"

class mCar : public mEnemy
{
private:
	char** shape;

public:
	mCar();
	mCar(pPosition pos);
	~mCar();

	void Sound();
	char** GetShape();
	int GetWidth();
	int GetHeight();
	int GetType();
};

