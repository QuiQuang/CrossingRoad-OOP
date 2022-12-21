#pragma once
#include <algorithm>
#include "pPosition.h"
#include "mEnemy.h"
#include "mAnt.h"
#include "mCar.h"
#include "mBus.h"
class nLevel
{
private:
	int level;
	int maxEnemy, minSpeed, maxSpeed, nEnemy;
	int nRow;
	const int maxLevel = 5;

	void Initialize();

public: 
	nLevel();
	nLevel(int level, int nEnemy);
	~nLevel() = default;

	int GetLevel();
	bool NewLevel(int lv);
	bool NextLevel();
	int GetMaxSpeed();
	int GetMinSpeed();

	mEnemy* RandNewEnemy(pPosition pos);
	mEnemy* GetNewEnemy(pPosition pos, int type);
	void DecNEnemy(int d);
};

