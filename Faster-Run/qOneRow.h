#pragma once
#define RIGHTMAP 58
#define LEFTMAP 2

#include <vector>
#include "mEnemy.h"

using namespace std;

class qOneRow
{
private:
	vector <mEnemy*> enemy;
	bool direction;
	bool redLight = false;
	int speed;
	int currentRow;

public:
	qOneRow() = default;
	qOneRow(int speed, bool direction, bool redLight, int currentRow);
	~qOneRow() = default;

	bool PushEnemy(mEnemy* newEnemy); 
	int MoveToNextState(int t);
	void RedrawState();
	void ToggleRedLight();
	void DeleteOldEnemy(pPosition pos, int w, int h);
	bool PrintNewEnemy(pPosition pos, char** shape, int w, int h);

	vector<mEnemy*> GetEnemy();
	bool GetDirection();
	bool GetRedLight();
	int GetSpeed();
	int GetCurrentRow();
};