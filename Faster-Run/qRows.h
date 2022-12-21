#pragma once
#include <vector>
#include "qOneRow.h"

using namespace std;

class qRows
{
private:
	vector <qOneRow*> subRows;

public:
	qRows();
	~qRows() = default;

	bool PushEnemy(int row, mEnemy* enemy); 
	void PushRow(qOneRow*);
	vector <mEnemy*> ListEnemy();
	vector <qOneRow*> ListRow();
	int MoveToNextState(int t);
	void RedrawState();
};