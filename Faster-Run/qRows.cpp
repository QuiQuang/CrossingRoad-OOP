#include "qRows.h"

qRows::qRows() {
	subRows.reserve(100);
}

bool qRows::PushEnemy(int row, mEnemy* enemy) {
	if (row >= (int)subRows.size())  return false;
	return subRows[row]->PushEnemy(enemy);
}
void qRows::PushRow(qOneRow* row) {
	subRows.push_back(row);
}
void qRows::RedrawState() {
	for (int i = 0; i < (int)subRows.size(); ++i) {
		subRows[i]->RedrawState();
	}
}
int qRows::MoveToNextState(int t) {
	int nDelete = 0;
	for (int i = 0; i < (int)subRows.size(); ++i)
		nDelete += subRows[i]->MoveToNextState(t);
	return nDelete;
}

vector<mEnemy*> qRows::ListEnemy() {
	vector<mEnemy*> listEnemy, tmp;
	for (int i = 0; (unsigned)i < subRows.size(); i++) {
		tmp = subRows[i]->GetEnemy();
		listEnemy.insert(listEnemy.end(), tmp.begin(), tmp.end());
	}
	return listEnemy;
}
vector <qOneRow*> qRows::ListRow() {
	return subRows;
}