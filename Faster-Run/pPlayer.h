#pragma once

#define RIGHTMAP 58
#define LEFTMAP 2

#include "nConsoleHandle.h"
#include "pPosition.h"
#include "mEnemy.h"
#include <cmath>

class pPlayer
{
private:
	pPosition pos;
	bool isDead;
	char** shape;
	char** emptyPlayer;
	int width = 5, height = 3;

public:
	pPlayer();
	pPlayer(pPosition pos);
	~pPlayer();

	void Up();
	void Down();
	void Right();
	void Left();
	bool CheckIsDead();
	void KillPlayer();

	char** GetShape();
	char** EmptyShape();
	pPosition GetPos();
	int GetWidth();
	int GetHeight();
	int GetX();
	int GetY();

	bool Crash(pPosition pos, int w, int h);
};

