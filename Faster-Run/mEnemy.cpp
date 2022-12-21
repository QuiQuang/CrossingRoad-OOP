#include "mEnemy.h"

mEnemy::mEnemy() : outMap(false) {}
mEnemy::mEnemy(pPosition pos) : point(pos), outMap(false) {}

pPosition mEnemy::GetPos() {
	return point;
}
int mEnemy::GetX() {
	return point.GetX();
}
int mEnemy::GetY() {
	return point.GetY();
}
bool mEnemy::IsOutOfMap() {
	return outMap;
}

void mEnemy::GoOutMap() {
	outMap = true;
}
void mEnemy::UpdatePosition(int dx, int dy) {
	point.SetPos(point.GetX() + dx, point.GetY() + dy);
}