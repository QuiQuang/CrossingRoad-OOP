#include "qOneRow.h"

qOneRow::qOneRow(int speed, bool direction, bool redLight, int currentRow) {
	this->speed = speed;
	this->direction = direction;
	this->redLight = redLight;
	this->currentRow = currentRow;
	enemy.reserve(100);
}

int qOneRow::MoveToNextState(int t) {
	int nDelete = 0;
	if ((redLight && (rand() % 8 == 0)) || (!redLight && (rand() % 15 == 0)) || (t == 0))
		ToggleRedLight();
	if (redLight)				SetColor(244);
	else						SetColor(242);

	if (direction)				GotoXY(RIGHTMAP + 61, currentRow);
	else						GotoXY(LEFTMAP - 2, currentRow);
	cout << (char)254;
	SetColor(nColor::EnemyColor);
	if (((t % speed) != 0) && t != 0) return nDelete; //test
	if (redLight) return nDelete;
	vector <mEnemy*> newEnemy;
	newEnemy.reserve(100);
	for (int i = 0; i < (int)enemy.size(); ++i) {
		mEnemy* curEnemy = enemy[i];
		int dy = -1;
		if (direction) dy = 1;
		DeleteOldEnemy(curEnemy->GetPos(), curEnemy->GetWidth(), curEnemy->GetHeight());
		curEnemy->UpdatePosition(0, dy);
		// Print Enemy
		bool canPrint = PrintNewEnemy(curEnemy->GetPos(), curEnemy->GetShape(), curEnemy->GetWidth(), curEnemy->GetHeight());
		if (!canPrint) {
			curEnemy->GoOutMap();
			++nDelete;
		}
		if (curEnemy->IsOutOfMap())
			delete curEnemy;
		else
			newEnemy.push_back(curEnemy);
	}
	enemy = newEnemy;
	return nDelete;
}
void qOneRow::RedrawState() {
	if (redLight)			SetColor(244);
	else					SetColor(242);

	if (direction)			GotoXY(RIGHTMAP + 61, currentRow);
	else					GotoXY(LEFTMAP - 2, currentRow);

	cout << (char)254;
	SetColor(nColor::EnemyColor);
	for (int i = 0; i < (int)enemy.size(); ++i) {
		mEnemy* curEnemy = enemy[i];
		PrintNewEnemy(curEnemy->GetPos(), curEnemy->GetShape(), curEnemy->GetWidth(), curEnemy->GetHeight());
	}
}
void qOneRow::ToggleRedLight() {
	redLight = !redLight;
}
void qOneRow::DeleteOldEnemy(pPosition pos, int w, int h) {
	SetColor(nColor::EnemyColor);
	int X = pos.GetX();
	int Y = pos.GetY();
	if (Y == LEFTMAP) return;
	if (Y > RIGHTMAP) return;
	for (int i = 0; i < h; ++i) {
		for (int j = max(1, Y); j <= min(RIGHTMAP, Y + w - 1); ++j) {
			GotoXY(Y + j, X + i);
			cout << ' ';
		}
	}
	SetColor(240);
}
bool qOneRow::PrintNewEnemy(pPosition pos, char** shape, int w, int h) {
	SetColor(nColor::EnemyColor);
	int X = pos.GetX();
	int Y = pos.GetY();
	if (Y == LEFTMAP) return 0;
	if (Y > RIGHTMAP) return 0;
	for (int i = 0; i < h; ++i) {
		for (int j = max(1, Y); j <= min(RIGHTMAP, Y + w - 1); ++j) {
			GotoXY(Y + j, X + i);
			cout << shape[i][j - max(1, Y)];
		}
	}
	SetColor(240);
	return 1;
}
bool qOneRow::PushEnemy(mEnemy* newEnemy) {
	if (!direction)			newEnemy->UpdatePosition(0, RIGHTMAP - newEnemy->GetY());
	if (newEnemy->GetY() > RIGHTMAP || newEnemy->GetY() <= 3 || (enemy.size() && abs(enemy.back()->GetY() - newEnemy->GetY()) <= 8))
		return false;
	enemy.push_back(newEnemy);
	PrintNewEnemy(newEnemy->GetPos(), newEnemy->GetShape(), newEnemy->GetWidth(), newEnemy->GetHeight());
	return true;
}

vector<mEnemy*> qOneRow::GetEnemy() {
	return enemy;
}
bool qOneRow::GetDirection() {
	return direction;
}
bool qOneRow::GetRedLight() {
	return redLight;
}
int qOneRow::GetSpeed() {
	return speed;
}
int qOneRow::GetCurrentRow() {
	return currentRow;
}