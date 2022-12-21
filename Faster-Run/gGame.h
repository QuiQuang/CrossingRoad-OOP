#pragma once
#include <iostream>
#include <fstream>
#include <thread>

#include "nConsoleHandle.h"
#include "pPlayer.h"
#include "mEnemy.h"
#include "qRows.h"
#include "nMap.h"

using namespace std;

class gGame
{
	bool isLoaded = false;
	nMap map;
	bool isPausing = false;

public:
	gGame() = default;
	~gGame() = default;

	void GameSettings();
	void Menu(bool& isFinish);
	bool NewGame();
	bool ContinueGame();
	bool LoadGameMenu();
	void SaveGameMenu();
	void PauseMenu(int cmd);

	void ToggleMute();
	void ToggleMute2();
	void ToggleMute3();

	void TogglePauseGame();
	void ToggleHard();

	void GameOver();

	void PlayGame(bool& is_finish);
	void TestThread();
	void Loading();

	vector<string> GetAllFilename(const std::string& name);

	void Menu();
	bool ContinueMenu();
};
