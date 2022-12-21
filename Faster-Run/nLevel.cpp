#include "nLevel.h"

nLevel::nLevel() {
	level = 1;
	nEnemy = 0;
	Initialize();
}
nLevel::nLevel(int level, int nEnemy) {
	this->level = level;
	this->nEnemy = nEnemy;
	Initialize();
}
void nLevel::Initialize() {
	int difficulty = 50, maxE = 10;
	if (constantVar::isHard) difficulty = 5, maxE = 20;
	nRow = 6;
	maxEnemy = min(maxE, nRow * 6);
	maxSpeed = difficulty - level * 2;
	minSpeed = difficulty - level * 1;
}
void nLevel::DecNEnemy(int d) {
	nEnemy -= d;
}

bool nLevel::NewLevel(int lv) {
	if (lv > maxLevel) return false;
	level = lv;
	nEnemy = 0;
	Initialize();
	return true;
}
bool nLevel::NextLevel() {
	if (level == maxLevel) return false;
	++level;
	nEnemy = 0;
	return true;
}

int nLevel::GetMaxSpeed() {
	return maxSpeed;
}
int nLevel::GetMinSpeed() {
	return minSpeed;
}
int nLevel::GetLevel() {
	return level;
}

mEnemy* nLevel::RandNewEnemy(pPosition pos) {
	if (nEnemy == maxEnemy) return NULL;
	if ((nEnemy < (maxEnemy / 2)) || (rand() % 3)) {
		++nEnemy;
		mEnemy* mEnemy = NULL;
		int type = rand() % 3;
		switch (type)
		{
			case 0: {
				mEnemy = new mAnt(pos);
				break;
			}
			case 1: {
				mEnemy = new mCar(pos);
				break;
			}
			
			case 2: {
				mEnemy = new mBus(pos);
				break;
			}
		}
		return mEnemy;
	}
	return NULL;
}
mEnemy* nLevel::GetNewEnemy(pPosition pos, int type) {
	++nEnemy;
	mEnemy* mEnemy = NULL;
	switch (type)
	{
	case 0: {
		mEnemy = new mAnt(pos);
		break;
	}
	case 1: {
		mEnemy = new mCar(pos);
		break;
	}
	case 2: {
		mEnemy = new mBus(pos);
		break;
	}
	}
	//    pEnemy = new cEnemy(pos); //choose a random type of enemy
	return mEnemy;
}