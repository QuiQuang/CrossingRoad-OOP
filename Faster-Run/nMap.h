#pragma once
#include <thread>
#include <cmath>
#include "pPlayer.h"
#include "pPosition.h"
#include "qRows.h"
#include "nLevel.h"
#include "mEnemy.h"
#include "nConsoleHandle.h"
using namespace std;

class nMap
{
private:
	const int width = 115, height = 36;
	char map[40][125];
	pPlayer player;
	qRows rowsData;
	nLevel level;
	int t = 0;

public:
	int color = 224;
	int highlight = 192;
	int defaultcolor = 255;

	nMap();
	~nMap() = default;

	void PrintMap(); 
	void DrawMap();
	void RedrawMap();
	void PrintBorder();
	void PrintBox();
	void PrintStage(int);
	void PrintMenu();

	void DrawBingChillin();
	void PrintBoxLoad();
	void PrintBoxSave();

	void DrawMus();
	void DrawLiveWorm();
	void DrawTiredWorm();
	void CleanWorm();
	void DrawLightning();
	void CleanLightning();
	void DrawInstruction();
	
	void DrawUp(pPosition);
	void DrawDown(pPosition);
	void DrawLeft();
	void DrawRight();

	void RandomNextState(); 
	void InitializeNewState(); 
				
	int Draw(pPosition pos, char** shape, int w, int h);
	void DrawPlayer();
	void DrawEnemies(mEnemy* enemy);
	void UpdatePosPlayer(char moving);
	void DeleteOldPlayer();

	void PrintInt(int x, ofstream& outfile);
	int ReadInt(ifstream& infile);
	void SaveGame(string file);
	bool LoadGame(string file);

	void PrintCongrats();
	bool PrintLevelUp();

	bool IsEnd();
	bool IsWin();
	void NextLevel();

	int GetWidth() { return width; }
	int GetHeight() { return height; }
};