#include "pPlayer.h"

pPlayer::pPlayer() : isDead(false) {
	pos.SetPos(34, 28);
	shape = new char* [3];
	emptyPlayer = new char* [3];
	for (int i = 0; i < 3; ++i) {
		emptyPlayer[i] = new char[5];
		shape[i] = new char[5];
		for (int j = 0; j < 5; ++j)
			emptyPlayer[i][j] = ' ';
	}
	//Row1
	shape[0][2] = char(3);
	shape[0][1] = char(187);
	shape[0][3] = char(201);
	shape[0][0] = shape[0][4] = char(205);
	//Row2
	for (int i = 0; i < 5; i++) {
		if (i == 0)	shape[1][i] = char(205);
		if (i == 1)	shape[1][i] = char(206);
		if (i == 2)	shape[1][i] = char(206);
		if (i == 3)	shape[1][i] = char(206);
		if (i == 4)	shape[1][i] = char(205);
	}
	//Row3
	shape[2][1] = char(188);
	shape[2][3] = char(200);
	shape[2][2] = ' ';
	shape[2][0] = shape[2][4] = char(205);
}
pPlayer::pPlayer(pPosition pos) : isDead(false), pos(pos) {
	shape = new char* [3];
	emptyPlayer = new char* [3];
	for (int i = 0; i < 3; ++i) {
		emptyPlayer[i] = new char[5];
		shape[i] = new char[5];
		for (int j = 0; j < 5; ++j)
			emptyPlayer[i][j] = ' ';
	}
	//Row1
	shape[0][2] = char(3);
	shape[0][1] = char(187);
	shape[0][3] = char(201);
	shape[0][0] = shape[0][4] = char(205);
	//Row2
	for (int i = 0; i < 5; i++) {
		if (i == 0)	shape[1][i] = char(205);
		if (i == 1)	shape[1][i] = char(206);
		if (i == 2)	shape[1][i] = char(206);
		if (i == 3)	shape[1][i] = char(206);
		if (i == 4)	shape[1][i] = char(205);
	}
	//Row3
	shape[2][1] = char(188);
	shape[2][3] = char(200);
	shape[2][2] = ' ';
	shape[2][0] = shape[2][4] = char(205);
}
pPlayer::~pPlayer() {
	for (int i = 0; i < 3; i++) {
		delete[] shape[i];
		delete[] emptyPlayer[i];
	}
	delete[] shape;
	delete[] emptyPlayer;
}

void pPlayer::KillPlayer() {
	isDead = true;
}

char** pPlayer::GetShape() {
	return shape;
}
char** pPlayer::EmptyShape() {
	return emptyPlayer;
}
pPosition pPlayer::GetPos() {
	return pos;
}
int pPlayer::GetX() {
	return pos.GetX();
}
int pPlayer::GetY() {
	return pos.GetY();
}
int pPlayer::GetHeight() {
	return height;
}
int pPlayer::GetWidth() {

	return width;
}
bool pPlayer::CheckIsDead() {
	return isDead;
}

void pPlayer::Up() {
	if (pos.GetX() <= 3) return;
	pos.SetPos(pos.GetX() - 3, pos.GetY());
}
void pPlayer::Down() {
	if (pos.GetX() + 3 > 34) return;
	pos.SetPos(pos.GetX() + 3, pos.GetY());
}
void pPlayer::Left() {
	if (pos.GetY() <= LEFTMAP) return;
	pos.SetPos(pos.GetX(), pos.GetY() - 1);
}
void pPlayer::Right() {
	if (pos.GetY() + 2 >= RIGHTMAP) return;
	pos.SetPos(pos.GetX(), pos.GetY() + 1);
}

bool pPlayer::Crash(pPosition pos, int w, int h) {
	int magicConst;
	if (this->GetX() == pos.GetX()) {
		if (w == 5) {
			magicConst = 3;
			if (this->GetY() <= pos.GetY() && max(GetY(), pos.GetY()) <= min(GetY() + GetWidth() - magicConst, pos.GetY() + w - magicConst))
				return true;
			if (this->GetY() >= pos.GetY() && this->GetY() - pos.GetY() <= 2)
				return true;
			return false;
		}

		else {
			if (w == 11)	magicConst = 6;
			else			magicConst = 8;

			if (this->GetY() >= pos.GetY() && pos.GetY() + w - magicConst >= this->GetY())
				return true;
			if (GetY() <= pos.GetY() && pos.GetY() - GetY() <= 2)
				return true;
		}
	}
	return false;
}