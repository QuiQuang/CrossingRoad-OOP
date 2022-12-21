#pragma once
#include "mEnemy.h"

class mBus : public mEnemy
{
private:
	char** shape;

public:
	mBus();
	mBus(pPosition pos);
	~mBus();

	void Sound();
	char** GetShape();
	int GetWidth();
	int GetHeight();
	int GetType();
};

