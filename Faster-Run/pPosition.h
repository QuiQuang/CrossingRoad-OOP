#pragma once

class pPosition
{
private:
	int X, Y;

public:
	pPosition();
	pPosition(const int, const int);
	~pPosition();

	int GetX();
	int GetY();

	void SetPos(int, int);
};