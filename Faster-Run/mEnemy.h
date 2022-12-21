#pragma once
#include <Windows.h>
#include <iostream>
#include "nConsoleHandle.h"
#include <mmsystem.h>
#include "pPosition.h"

class mEnemy
{
private:
	pPosition point;
	bool outMap;

public:
	pPosition GetPos();
	int GetX();
	int GetY();

	mEnemy();
	mEnemy(pPosition st);

	virtual ~mEnemy() = default;
	virtual char** GetShape() = 0;
	virtual int GetType() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void Sound() = 0;

	void UpdatePosition(int dx, int dy);
	bool IsOutOfMap();
	void GoOutMap();
};

