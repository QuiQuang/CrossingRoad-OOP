#pragma once
#include "mEnemy.h"

class mAnt : public mEnemy
{
private:
	char** shape;

public:
	mAnt();
	mAnt(pPosition pos);
	~mAnt();

	void Sound();
	char** GetShape();
	int GetWidth();
	int GetHeight();
	int GetType();
};

