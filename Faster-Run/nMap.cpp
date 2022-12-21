#include "nMap.h"

nMap::nMap() : width(115), height(36) {
	for (int i = 0; i <= width; i++) {
		map[0][i] = map[height + 1][i] = char(219);
	}
	map[0][width + 1] = map[height + 1][width + 1] = ' ';
	for (int i = 1; i <= height; ++i) {
		map[i][0] = map[i][width] = char(219);
		map[i][width + 1] = ' ';
		for (int j = 1; j < width; ++j) {
			map[i][j] = ' ';
		}
	}
}

void nMap::PrintBox() {
	SetColor(nColor::BorderColor);
	for (int i = width + 8; i < 167; ++i) {
		for (int j = 1; j < height + 1; j++) {
			GotoXY(i, j);
			cout << ' ';
		}
	}
	for (int i = width + 7; i < 168; ++i) {
		GotoXY(i, 0);			cout << char(219);
		GotoXY(i, height + 1);	cout << char(219);
	}
	for (int i = 0; i <= height + 1; ++i) {
		GotoXY(width + 7, i);	cout << char(219);
		GotoXY(166, i);			cout << char(219);
		GotoXY(width + 6, i);	cout << char(219);
		GotoXY(167, i);			cout << char(219);
	}
	for (int i = 1; i < height + 1; ++i) {
		GotoXY(width + 4, i);	cout << ' ';
		GotoXY(width + 5, i);	cout << ' ';
	}
	SetColor(240);
}
void nMap::PrintMap() {
	CLRSCR();
	HideCursor();
	SetColor(nColor::BorderColor);
	GotoXY(0, 0);
	for (int i = 0; i <= height + 1; ++i) {
		cout << "  ";
		for (int j = 0; j <= width + 1; ++j) {
			cout << map[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i <= height + 1; ++i) {
		GotoXY(LEFTMAP - 1, i);
		cout << char(219);
		GotoXY(RIGHTMAP + 60, i);
		cout << char(219);
	}
	SetColor(nColor::BorderColor);
	PrintBox();

	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	GotoXY(130, 3);		cout << u8"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄";
	GotoXY(130, 4);		cout << u8"█                           █";
	GotoXY(130, 5);		cout << u8"█                           █";
	GotoXY(130, 6);		cout << u8"█                           █";
	GotoXY(130, 7);		cout << u8"█                           █";
	GotoXY(130, 8);		cout << u8"▀▀                         ▀▀";

	SetColor(241);
	GotoXY(137, 2);		cout << u8"╔═╗╔╦╗╔═╗╔═╗╔═╗";
	GotoXY(137, 3);		cout << u8"╚═╗ ║ ╠═╣║ ╦║╣ ";
	GotoXY(137, 4);		cout << u8"╚═╝ ╩ ╩ ╩╚═╝╚═╝";

	SetColor(240);
	GotoXY(127, 13);	cout << u8"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄";
	GotoXY(127, 14);	cout << u8"█                                 █";
	GotoXY(127, 15);	cout << u8"█               ███               █";
	GotoXY(127, 16);	cout << u8"█      ██     ███████     ██      █";
	GotoXY(127, 17);	cout << u8"█    ████   ███████████   ████    █";
	GotoXY(127, 18);	cout << u8"█  ██████                 ██████  █";
	GotoXY(127, 19);	cout << u8"█    ████   ███████████   ████    █";
	GotoXY(127, 20);	cout << u8"█      ██     ███████     ██      █";
	GotoXY(127, 21);	cout << u8"█               ███               █";
	GotoXY(127, 22);	cout << u8"█                                 █";
	GotoXY(127, 23);	cout << u8"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀";
	GotoXY(127, 24);	cout << u8"            █         █";
	GotoXY(127, 25);	cout << u8"            █         █";
	GotoXY(127, 26);	cout << u8"            █         █";
	GotoXY(127, 27);	cout << u8"            █         █";
	GotoXY(127, 28);	cout << u8"            █         █";
	SetConsoleOutputCP(old_cp);
	SetColor(240);
	PrintStage(level.GetLevel());
	DrawTiredWorm();
	SetColor(240);
	DrawPlayer();
}
void nMap::DrawMap() {
	HideCursor();
	vector <mEnemy*> enemyList = rowsData.ListEnemy(); //enemyList = 0 
	for (int i = 0; i < (int)enemyList.size(); ++i) {
		if (player.Crash(enemyList[i]->GetPos(), enemyList[i]->GetWidth(), enemyList[i]->GetHeight())) {
			if (!constantVar::isMute2) enemyList[i]->Sound();
			player.KillPlayer();
			DeleteOldPlayer();
			DrawPlayer();
			Sleep(300);
			CLRSCR();
			PrintMap();
			DeleteOldPlayer();
			return;
		}
	}
}
int nMap::Draw(pPosition pos, char** shape, int w, int h) {
	HideCursor();
	int X = pos.GetX();
	int Y = pos.GetY();
	if (Y + w <= 0) return 0;
	if (Y > width) return 0;
	for (int i = 0; i < h; ++i) {
		for (int j = max(1, Y); j <= min(width, Y + w - 1); ++j) {
			GotoXY(Y + j, X + i);
			cout << shape[i][j - max(1, Y)];
		}
	}
	return 1;
}
void nMap::PrintBorder() {
	CLRSCR();
	HideCursor();
	SetColor(nColor::BorderColor);
	GotoXY(0, 0);
	for (int i = 0; i <= height + 1; ++i) {
		cout << "  ";
		for (int j = 0; j <= width + 1; ++j) {
			cout << map[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i <= height + 1; ++i) {
		GotoXY(LEFTMAP - 1, i);
		cout << char(219);
		GotoXY(RIGHTMAP + 60, i);
		cout << char(219);
	}
	SetColor(240);
}
void nMap::PrintMenu() {
	CLRSCR();
	HideCursor();
	SetColor(nColor::BorderColor);
	GotoXY(0, 0);
	for (int i = 0; i < 38; ++i)
		cout << ' ' << endl;
	for (int i = 0; i < 38; ++i) {
		for (int j = 1; j < 168; ++j) {
			if (i == 0 || i == 37 || j == 2 || j == 1 || j == 166 || j == 167) {
				GotoXY(j, i);
				cout << char(219);
			}
			else cout << " ";
		}
	}
	SetColor(240);
}

void nMap::DrawBingChillin() {
	int Black = 7;
	int Vani = 234;
	int Red = 204;
	int Brown = 102;
	int White = 240;

	GotoXY(15, 2);
	SetColor(Black);
	cout << "          "; //10

	GotoXY(12, 3);
	SetColor(Black); cout << "   "; //3
	SetColor(Vani);	cout << "          "; //10
	SetColor(Black); cout << "   "; //3

	GotoXY(10, 4);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani);	cout << "                "; //16
	SetColor(Black); cout << "  ";//2

	GotoXY(8, 5);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani);	cout << "                    "; //20
	SetColor(Black); cout << "  ";//2

	GotoXY(8, 6);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani); cout << "  "; //2
	SetColor(White); cout << "  "; //2
	SetColor(Black); cout << "  "; //2
	SetColor(Vani); cout << "        ";//8
	SetColor(White); cout << "  ";//2
	SetColor(Black); cout << "  ";//2
	SetColor(Vani); cout << "  ";//2
	SetColor(Black); cout << "  ";//2

	GotoXY(6, 7);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani); cout << "  "; //2
	SetColor(Red); cout << "  ";//2
	SetColor(Black); cout << "    "; //4
	SetColor(Vani); cout << "        ";//8
	SetColor(Black); cout << "    ";//4
	SetColor(Red); cout << "  ";//2
	SetColor(Vani); cout << "  ";//2
	SetColor(Black); cout << "  ";//2

	GotoXY(6, 8);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani); cout << "  "; //2
	SetColor(Red); cout << "    ";//4
	SetColor(Vani); cout << "    ";//4
	SetColor(Black); cout << "    "; //4
	SetColor(Vani); cout << "    ";//4
	SetColor(Red); cout << "    ";//4
	SetColor(Vani); cout << "  ";//2
	SetColor(Black); cout << "  ";//2

	GotoXY(6, 9);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani); cout << "                        "; //28
	SetColor(Black); cout << "  ";//2

	GotoXY(6, 10);
	SetColor(Black); cout << "  "; //2
	SetColor(Vani); cout << "                        "; //28
	SetColor(Black); cout << "  ";//2

	GotoXY(8, 11);
	SetColor(Black); cout << "    ";//4
	SetColor(Vani); cout << "    ";//4
	SetColor(Black); cout << "        ";//8
	SetColor(Vani); cout << "    ";//4
	SetColor(Black); cout << "    ";//4

	GotoXY(8, 12);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "  ";//2
	SetColor(Black); cout << "    ";//4
	SetColor(Brown); cout << "        ";//8
	SetColor(Black); cout << "    ";//4
	SetColor(Brown); cout << "  ";//2
	SetColor(Black); cout << "  ";//2

	GotoXY(8, 13);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "                    ";//20
	SetColor(Black); cout << "  ";//2

	GotoXY(10, 14);
	SetColor(Black); cout << "                    ";//20

	GotoXY(10, 15);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "                ";//16
	SetColor(Black); cout << "  ";//2

	GotoXY(12, 16);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "            ";//12
	SetColor(Black); cout << "  ";//2

	GotoXY(12, 17);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "            ";//12
	SetColor(Black); cout << "  ";//2

	GotoXY(14, 18);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "        ";//8
	SetColor(Black); cout << "  ";//2

	GotoXY(14, 19);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "        ";//8
	SetColor(Black); cout << "  ";//2

	GotoXY(16, 20);
	SetColor(Black); cout << "  ";//2
	SetColor(Brown); cout << "    ";//4
	SetColor(Black); cout << "  ";//2

	GotoXY(18, 21);
	SetColor(Black); cout << "    ";//4
}
void nMap::PrintBoxLoad() {
	int x_min = width / 2 - 19;
	int y_min = height - 26;
	int x_max = x_min + 101;
	int y_max = y_min + 20;

	CLRSCR();
	HideCursor();
	SetColor(nColor::BorderColor);
	GotoXY(0, 0);
	for (int i = 0; i < 38; ++i)
		cout << ' ' << endl;
	for (int i = 0; i < 38; ++i) {
		for (int j = 1; j < 168; ++j) {
			if (i == 0 || i == 37 || j == 2 || j == 1 || j == 166 || j == 167) {
				GotoXY(j, i);
				cout << char(219);
			}
			else cout << " ";
		}
	}
	SetColor(238);
	pPosition pd(83, 23);
	this->DrawDown(pd);
	pPosition pu(83, 17);
	this->DrawUp(pu);
	this->DrawBingChillin();

	SetColor(240);
	for (int x = x_min; x <= x_max; x++)
	{
		GotoXY(x, y_min);
		cout << char(219);
		GotoXY(x, y_max);
		cout << char(219);
		GotoXY(x, y_min + 2);
		cout << char(219);
		GotoXY(x, y_min + 1);
		cout << char(219);
	}

	for (int y = y_min; y <= y_max; y++)
	{
		GotoXY(x_min, y);
		cout << char(219);
		GotoXY(x_max, y);
		cout << char(219);
	}
	// góc phải trên
	GotoXY(x_min, y_max); cout << char(219);
	//góc trái trên
	GotoXY(x_min, y_min); cout << char(219);
	// góc trái dưới
	GotoXY(x_max, y_min); cout << char(219);
	// góc phải dưới
	GotoXY(x_max, y_max); cout << char(219);

	SetColor(7);
	GotoXY(x_min + 35, y_min + 1);
	cout << "PLEASE CHOOSE THE FILENAME TO LOAD";

	SetColor(246);
	GotoXY(10, 23);
	cout << "Press 'ECS' to escape";
}
void nMap::PrintBoxSave() {
	int x_max = 100;
	int y_max = 25;
	int x_min = 20;
	int y_min = 12;

	SetColor(112);
	for (int x = x_min; x <= x_max; x++) {
		for (int y = y_min; y <= y_max; y++)
		{
			GotoXY(x, y);
			if (y < y_min + 3)
			{
				SetColor(224);
			}
			else
			{
				SetColor(112);
			}
			cout << " ";
		}
	}


	SetColor(224);
	GotoXY(x_min + 30, y_min + 1);
	cout << "WHAT'S YOUR NAME BABY ? ";

	SetColor(112);
	for (int x = x_min; x <= x_max; x++) {
		GotoXY(x, y_max - 4);
		cout << char(196);
	}


	SetColor(271);
	GotoXY(x_max - 20, y_max - 2);
	cout << "  ESC  ";

	SetColor(39);
	GotoXY(x_min + 16, y_max - 2);
	cout << " ENTER ";
}

void nMap::DrawMus() {
	int Green = 160;
	int Black = 7;
	int White = 240;
	int Pink = 224;
	GotoXY(40, 5); {
		SetColor(White);		cout << "          ";
		SetColor(Black);		cout << "              ";
	}
	GotoXY(40, 6); {
		SetColor(White);		cout << "      ";
		SetColor(Black);		cout << "    ";
		SetColor(White);		cout << "      ";
		SetColor(Green);		cout << "    ";
		SetColor(White);		cout << "    ";
		SetColor(Black);		cout << "    ";
	}
	GotoXY(40, 7); {
		SetColor(White);		cout << "    ";
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "  ";
		SetColor(White);		cout << "        ";
		SetColor(Green);		cout << "    ";
		SetColor(White);		cout << "        ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 8); {
		SetColor(White);		cout << "  ";
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "    ";
		SetColor(White);		cout << "      ";
		SetColor(Green);		cout << "        ";
		SetColor(White);		cout << "      ";
		SetColor(Green);		cout << "  ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 9); {
		SetColor(White);		cout << "  ";
		SetColor(Black);		cout << "  ";
		SetColor(White);		cout << "  ";
		SetColor(Green);		cout << "                        ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 10); {
		SetColor(Black);		cout << "  ";
		SetColor(White);		cout << "      ";
		SetColor(Green);		cout << "      ";
		SetColor(White);		cout << "        ";
		SetColor(Green);		cout << "      ";
		SetColor(White);		cout << "    ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 11); {
		SetColor(Black);		cout << "  ";
		SetColor(White);		cout << "      ";
		SetColor(Green);		cout << "    ";
		SetColor(White);		cout << "            ";
		SetColor(Green);		cout << "  ";
		SetColor(White);		cout << "      ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 12); {
		SetColor(Black);		cout << "  ";
		SetColor(White);		cout << "      ";
		SetColor(Green);		cout << "    ";
		SetColor(White);		cout << "            ";
		SetColor(Green);		cout << "  ";
		SetColor(White);		cout << "      ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 13); {
		SetColor(Black);		cout << "  ";
		SetColor(White);		cout << "    ";
		SetColor(Green);		cout << "      ";
		SetColor(White);		cout << "            ";
		SetColor(Green);		cout << "    ";
		SetColor(White);		cout << "    ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 14); {
		SetColor(White);		cout << "  ";
		SetColor(Black);		cout << "  ";
		SetColor(White);		cout << "  ";
		SetColor(Green);		cout << "        ";
		SetColor(White);		cout << "        ";
		SetColor(Green);		cout << "        ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 15); {
		SetColor(White);		cout << "    ";
		SetColor(Black);		cout << "    ";
		SetColor(Green);		cout << "                  ";
		SetColor(Black);		cout << "    ";
	}
	GotoXY(40, 16); {
		SetColor(White);		cout << "      ";
		SetColor(Black);		cout << "  ";
		SetColor(Pink);		cout << "    ";
		SetColor(Black);		cout << "   ";
		SetColor(Pink);		cout << "    ";
		SetColor(Black);		cout << "   ";
		SetColor(Pink);		cout << "    ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 17); {
		SetColor(White);		cout << "      ";
		SetColor(Black);		cout << "  ";
		SetColor(Pink);		cout << "    ";
		SetColor(Black);		cout << "   ";
		SetColor(Pink);		cout << "    ";
		SetColor(Black);		cout << "   ";
		SetColor(Pink);		cout << "    ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 18); {
		SetColor(White);		cout << "      ";
		SetColor(Black);		cout << "  ";
		SetColor(Pink);		cout << "                  ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(40, 19); {
		SetColor(White);		cout << "        ";
		SetColor(Black);		cout << "                  ";
	}
	SetColor(nColor::BorderColor);
}
void nMap::DrawLiveWorm() {
	int White = 240;
	int Black = 7;
	int Green = 160;
	GotoXY(136, 30); {
		SetColor(White);		cout << "    ";
		SetColor(Black);		cout << "          ";
	}
	GotoXY(136, 31); {
		SetColor(White);		cout << "  ";
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "          ";
		SetColor(Black);		cout << "  ";
	}
		GotoXY(136, 32); {
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "              ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(136, 33); {
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "  ";
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "  ";
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "        ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(136, 34); {
		SetColor(Black);		cout << "  ";
		SetColor(Green);		cout << "                  ";
		SetColor(Black);		cout << "  ";
	}
	GotoXY(136, 35); {
		SetColor(White);		cout << "  ";
		SetColor(Black);		cout << "                      ";
	}
	SetColor(240);
}
void nMap::DrawTiredWorm() {
	SetColor(240);
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	GotoXY(131, 30);	cout << u8"        ▄▄▄▄▄▄▄▄▄▄▄";
	GotoXY(131, 31);	cout << u8"      ██"; SetColor(160);	cout << u8"           ██";		SetColor(240);
	GotoXY(131, 32);	cout << u8"    ██";  SetColor(160);	cout << u8"               ██";		SetColor(240);
	GotoXY(131, 33);	cout << u8"  ██";  SetColor(160);		cout << u8"                   ██";	SetColor(240);
	GotoXY(131, 34);	cout << u8"██";  SetColor(160);		cout << u8"                       ██";	SetColor(240);
	GotoXY(131, 35);	cout << u8"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀";
	SetConsoleOutputCP(old_cp);
}
void nMap::DrawInstruction() {
	SetColor(240);
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	SetColor(240);
	GotoXY(127, 13);	cout << u8"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄";
	GotoXY(127, 14);	cout << u8"█                                 █";
	GotoXY(127, 15);	cout << u8"█               ███               █";
	GotoXY(127, 16);	cout << u8"█      ██     ███████     ██      █";
	GotoXY(127, 17);	cout << u8"█    ████   ███████████   ████    █";
	GotoXY(127, 18);	cout << u8"█  ██████                 ██████  █";
	GotoXY(127, 19);	cout << u8"█    ████   ███████████   ████    █";
	GotoXY(127, 20);	cout << u8"█      ██     ███████     ██      █";
	GotoXY(127, 21);	cout << u8"█               ███               █";
	GotoXY(127, 22);	cout << u8"█                                 █";
	GotoXY(127, 23);	cout << u8"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀";
	SetConsoleOutputCP(old_cp);
}

void nMap::DrawUp(pPosition p) {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	int x = p.GetX();
	int y = p.GetY();

	GotoXY(x, y); cout << u8"███████████";
	GotoXY(x + 2, y -= 1); cout << u8"███████";
	GotoXY(x + 4, y -= 1); cout << u8"███";

	SetConsoleOutputCP(old_cp);
}
void nMap::DrawDown(pPosition p) {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	int x = p.GetX();
	int y = p.GetY();
	GotoXY(x, y); cout << u8"███████████";
	GotoXY(x + 2, y += 1); cout << u8"███████";
	GotoXY(x + 4, y += 1); cout << u8"███";

	SetConsoleOutputCP(old_cp);
}
void nMap::DrawRight() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	GotoXY(153, 16); cout << u8"██";
	GotoXY(153, 17); cout << u8"████";
	GotoXY(153, 18); cout << u8"██████";
	GotoXY(153, 19); cout << u8"████";
	GotoXY(153, 20); cout << u8"██";

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleOutputCP(old_cp);
}
void nMap::DrawLeft() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	GotoXY(130, 16); cout << u8"    ██";
	GotoXY(130, 17); cout << u8"  ████";
	GotoXY(130, 18); cout << u8"██████";
	GotoXY(130, 19); cout << u8"  ████";
	GotoXY(130, 20); cout << u8"    ██";

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleOutputCP(old_cp);
}

void nMap::CleanWorm() {
	GotoXY(131, 30); cout << "                                ";
	GotoXY(131, 31); cout << "                                ";
	GotoXY(131, 32); cout << "                                ";
	GotoXY(131, 33); cout << "                                ";
	GotoXY(131, 34); cout << "                                ";
	GotoXY(131, 35); cout << "                                ";
}
void nMap::DrawLightning() {
	SetColor(246);
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	GotoXY(142, 24); cout << u8"  █";
	GotoXY(142, 25); cout << u8" ██";
	GotoXY(142, 26); cout << u8"█████";
	GotoXY(142, 27); cout << u8"  ██";
	GotoXY(142, 28); cout << u8"  █";
	SetConsoleOutputCP(old_cp);
	SetColor(240);
}
void nMap::CleanLightning() {
	GotoXY(142, 24); cout << "     ";
	GotoXY(142, 25); cout << "     ";
	GotoXY(142, 26); cout << "     ";
	GotoXY(142, 27); cout << "     ";
	GotoXY(142, 28); cout << "     ";
}

void nMap::DrawEnemies(mEnemy* enemy) {
	HideCursor();
	SetColor(nColor::EnemyColor);
	int status = Draw(enemy->GetPos(), enemy->GetShape(), enemy->GetWidth(), enemy->GetHeight());
	if (status == 0) {
		enemy->GoOutMap();
	}
	if (status == -1) {
		player.KillPlayer();
	}
	SetColor(240);
}
void nMap::DrawPlayer() {
	HideCursor();
	SetColor(nColor::PlayerColor);
	int status = Draw(player.GetPos(), player.GetShape(), player.GetWidth(), player.GetHeight());
	if (status == -1) {
		player.KillPlayer();
	}
	SetColor(240);
}
void nMap::DeleteOldPlayer() {
	HideCursor();
	SetColor(nColor::PlayerColor);
	Draw(player.GetPos(), player.EmptyShape(), player.GetWidth(), player.GetHeight());
	SetColor(240);
}

void nMap::InitializeNewState() {
	player.~pPlayer();
	new(&player) pPlayer();
	rowsData.~qRows();
	new(&rowsData) qRows();
	int padding[6];
	for (int i = 0; i < 6; ++i) {
		padding[i] = 0;
		int speed = rand() % (level.GetMinSpeed() - level.GetMaxSpeed() + 1) + level.GetMaxSpeed();
		bool direction = rand() % 2;
		bool redLight = rand() % 2;
		rowsData.PushRow(new qOneRow(speed, direction, redLight, (i * 6) + 1));
	}
	mEnemy* newEnemy;
	pPosition pos;
	int tryCount = 10000;
	while (tryCount--) {
		int rRow = (rand() % 6);
		padding[rRow] += (rand() % 20) + 11;
		pos = pPosition((rRow * 6) + 1, padding[rRow]);
		newEnemy = level.RandNewEnemy(pos);
		if (!newEnemy) break;
		if (!rowsData.PushEnemy(rRow, newEnemy)) {
			level.DecNEnemy(1);
			delete newEnemy;
		};
	}
	Sleep(200);
	rowsData.MoveToNextState(0);
}
void nMap::RandomNextState() {
	srand(time(NULL));
	mEnemy* newEnemy;
	pPosition pos;
	int tryCount = 10000;
	while (tryCount--) {
		int rRow = (rand() % 6);
		pos = pPosition((rRow * 6) + 1, 4);
		newEnemy = level.RandNewEnemy(pos);
		if (!newEnemy) break;
		if (!rowsData.PushEnemy(rRow, newEnemy)) {
			level.DecNEnemy(1);
			delete newEnemy;
		};
	}
	++t;
	int tmp = rowsData.MoveToNextState(t);
	level.DecNEnemy(tmp);
	DrawMap();
}

void nMap::RedrawMap() {
	SetColor(nColor::BorderColor);
	PrintMap();
	int tmp = rowsData.MoveToNextState(t);
	level.DecNEnemy(tmp);
	DrawMap();
	SetColor(240);
}
void nMap::UpdatePosPlayer(char moving) {
	DeleteOldPlayer();
	if (moving == 'a' || moving == 'A') player.Left();
	else if (moving == 'w' || moving == 'W') player.Up();
	else if (moving == 'd' || moving == 'D') player.Right();
	else if (moving == 's' || moving == 'S') player.Down();
	else return;
}

bool nMap::IsEnd(){
	return player.CheckIsDead();
}
bool nMap::IsWin() {
	if (player.GetX() == 1) {
		if (!constantVar::isMute1)PlaySound(TEXT("Endgame.wav"), NULL, SND_ASYNC);
		return true;
	}
	return false;
}
void nMap::NextLevel() {
	level.NextLevel();
}

void nMap::PrintInt(int x, ofstream& outfile) {
	outfile.write((char*)&x, sizeof(int));
}
int nMap::ReadInt(ifstream& infile) {
	int x;
	infile.read((char*)&x, sizeof(int));
	return x;
}
void nMap::SaveGame(string file)
{
	ofstream outfile("./data/" + file + ".bin", ios::out | ios::binary);
	PrintInt(level.GetLevel(), outfile);
	PrintInt(player.GetX(), outfile);
	PrintInt(player.GetY(), outfile);

	vector <qOneRow*> rows(rowsData.ListRow());
	for (int i = 0; i < 6; ++i) {
		PrintInt(rows[i]->GetCurrentRow(), outfile);
		PrintInt((int)rows[i]->GetDirection(), outfile);
		PrintInt(rows[i]->GetSpeed(), outfile);
		PrintInt((int)rows[i]->GetRedLight(), outfile);

		vector <mEnemy*> enemy(rows[i]->GetEnemy());
		PrintInt((int)enemy.size(), outfile);

		for (int j = 0; j < (int)enemy.size(); ++j) {
			PrintInt(enemy[j]->GetX(), outfile);
			PrintInt(enemy[j]->GetY(), outfile);
			PrintInt(enemy[j]->GetType(), outfile);
		}
	}
	outfile.close();
}
bool nMap::LoadGame(string file) {
	ifstream infile("./data/" + file, ios::in | ios::binary);
	if (!infile.is_open()) {
		return false;
	}
	int lv = ReadInt(infile);
	level.~nLevel();
	new(&level) nLevel(lv, 0);
	int playerX, playerY;
	playerX = ReadInt(infile);
	playerY = ReadInt(infile);
	player.~pPlayer();
	new(&player) pPlayer(pPosition(playerX, playerY));

	int nEnemy = 0;

	rowsData.~qRows();
	new(&rowsData) qRows();

	for (int i = 0; i < 6; ++i) {
		int currentRow, direction, speed, redLight;
		currentRow = ReadInt(infile);
		direction = ReadInt(infile);
		speed = ReadInt(infile);
		redLight = ReadInt(infile);

		rowsData.PushRow(new qOneRow(speed, direction, redLight, currentRow));

		int enemySize = ReadInt(infile);
		nEnemy += enemySize;

		for (int j = 0; j < enemySize; ++j) {
			int eX, eY, eType;
			eX = ReadInt(infile);
			eY = ReadInt(infile);
			eType = ReadInt(infile);
			rowsData.PushEnemy(i, level.GetNewEnemy(pPosition(eX, eY), eType));
		}
	}
	infile.close();
	return true;
}

void nMap::PrintCongrats()
{
	CLRSCR();
	HideCursor();
	PrintMap();
	DeleteOldPlayer();
	int x = 28, y1 = 5;
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	if (!constantVar::isMute1)PlaySound(TEXT("Endgame.wav"), NULL, SND_ASYNC);
	TextColor(10); GotoXY(x, y1); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y1); cout << u8"████"; TextColor(4); GotoXY(x + 7, y1); cout << u8"█";
	TextColor(10); GotoXY(x + 8, y1); cout << u8"    █"; TextColor(0); GotoXY(x + 13, y1); cout << u8"████"; TextColor(4); GotoXY(x + 17, y1); cout << u8"█";
	TextColor(10); GotoXY(x + 18, y1); cout << u8"       █"; TextColor(0); GotoXY(x + 26, y1); cout << u8"██████"; TextColor(4); GotoXY(x + 32, y1); cout << u8"█";
	TextColor(10); GotoXY(x + 33, y1); cout << u8"      █"; TextColor(0); GotoXY(x + 40, y1); cout << u8"████"; TextColor(4); GotoXY(x + 44, y1); cout << u8"█";
	TextColor(10); GotoXY(x + 45, y1); cout << u8"    █"; TextColor(0); GotoXY(x + 50, y1); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 1); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y1 + 1); cout << u8"████"; TextColor(4); GotoXY(x + 7, y1 + 1); cout << u8"██";
	TextColor(10); GotoXY(x + 9, y1 + 1); cout << u8"    █"; TextColor(0); GotoXY(x + 14, y1 + 1); cout << u8"███"; TextColor(4); GotoXY(x + 17, y1 + 1); cout << u8"█";
	TextColor(10); GotoXY(x + 18, y1 + 1); cout << u8"     █"; TextColor(0); GotoXY(x + 24, y1 + 1); cout << u8"███"; TextColor(4); GotoXY(x + 27, y1 + 1); cout << u8"█";
	TextColor(10); GotoXY(x + 28, y1 + 1); cout << u8"  █"; TextColor(0); GotoXY(x + 31, y1 + 1); cout << u8"███"; TextColor(4); GotoXY(x + 34, y1 + 1); cout << u8"█";
	TextColor(10); GotoXY(x + 35, y1 + 1); cout << u8"    █"; TextColor(0); GotoXY(x + 40, y1 + 1); cout << u8"████"; TextColor(4); GotoXY(x + 44, y1 + 1); cout << u8"██";
	TextColor(10); GotoXY(x + 46, y1 + 1); cout << u8"   █"; TextColor(0); GotoXY(x + 50, y1 + 1); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 1); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 2); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y1 + 2); cout << u8"████"; TextColor(4); GotoXY(x + 7, y1 + 2); cout << u8"█";
	TextColor(10); GotoXY(x + 8, y1 + 2); cout << u8"    █"; TextColor(0); GotoXY(x + 13, y1 + 2); cout << u8"████"; TextColor(4); GotoXY(x + 17, y1 + 2); cout << u8"█";
	TextColor(10); GotoXY(x + 18, y1 + 2); cout << u8"   █"; TextColor(0); GotoXY(x + 22, y1 + 2); cout << u8"████"; TextColor(4); GotoXY(x + 26, y1 + 2); cout << u8"█";
	TextColor(10); GotoXY(x + 27, y1 + 2); cout << u8"    █"; TextColor(0); GotoXY(x + 32, y1 + 2); cout << u8"████"; TextColor(4); GotoXY(x + 36, y1 + 2); cout << u8"█";
	TextColor(10); GotoXY(x + 37, y1 + 2); cout << u8"  █"; TextColor(0); GotoXY(x + 40, y1 + 2); cout << u8"████"; TextColor(4); GotoXY(x + 44, y1 + 2); cout << u8"█";
	TextColor(10); GotoXY(x + 45, y1 + 2); cout << u8"    █"; TextColor(0); GotoXY(x + 50, y1 + 2); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 2); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 3); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y1 + 3); cout << u8"███";
	TextColor(10); GotoXY(x + 6, y1 + 3); cout << u8"      █"; TextColor(0); GotoXY(x + 13, y1 + 3); cout << u8"████"; TextColor(4); GotoXY(x + 17, y1 + 3); cout << u8"█";
	TextColor(10); GotoXY(x + 18, y1 + 3); cout << u8"   █"; TextColor(0); GotoXY(x + 22, y1 + 3); cout << u8"████"; TextColor(4); GotoXY(x + 26, y1 + 3); cout << u8"███";
	TextColor(10); GotoXY(x + 29, y1 + 3); cout << u8"  █"; TextColor(0); GotoXY(x + 32, y1 + 3); cout << u8"████"; TextColor(4); GotoXY(x + 36, y1 + 3); cout << u8"█";
	TextColor(10); GotoXY(x + 37, y1 + 3); cout << u8"  █"; TextColor(0); GotoXY(x + 40, y1 + 3); cout << u8"████"; TextColor(4); GotoXY(x + 44, y1 + 3); cout << u8"█";
	TextColor(10); GotoXY(x + 45, y1 + 3); cout << u8"    █"; TextColor(0); GotoXY(x + 50, y1 + 3); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 3); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 4); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y1 + 4); cout << u8"████"; TextColor(4); GotoXY(x + 7, y1 + 4); cout << u8"█";
	TextColor(10); GotoXY(x + 8, y1 + 4); cout << u8"    █"; TextColor(0); GotoXY(x + 13, y1 + 4); cout << u8"████"; TextColor(4); GotoXY(x + 17, y1 + 4); cout << u8"█";
	TextColor(0); GotoXY(x + 18, y1 + 4); cout << u8"     ███"; TextColor(4); GotoXY(x + 26, y1 + 4); cout << u8"█";
	TextColor(10); GotoXY(x + 27, y1 + 4); cout << u8"    █"; TextColor(0); GotoXY(x + 32, y1 + 4); cout << u8"████"; TextColor(4); GotoXY(x + 36, y1 + 4); cout << u8"█";
	TextColor(10); GotoXY(x + 37, y1 + 4); cout << u8"  █"; TextColor(0); GotoXY(x + 40, y1 + 4); cout << u8"██";
	TextColor(10); GotoXY(x + 42, y1 + 4); cout << u8"       █"; TextColor(0); GotoXY(x + 50, y1 + 4); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 4); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 5); cout << u8" █"; TextColor(0); GotoXY(x + 2, y1 + 5); cout << u8"████"; TextColor(4); GotoXY(x + 6, y1 + 5); cout << u8"█";
	TextColor(10); GotoXY(x + 7, y1 + 5); cout << u8"    █"; TextColor(0); GotoXY(x + 12, y1 + 5); cout << u8"████"; TextColor(4); GotoXY(x + 16, y1 + 5); cout << u8"█";
	TextColor(10); GotoXY(x + 17, y1 + 5); cout << u8"    █"; TextColor(0); GotoXY(x + 22, y1 + 5); cout << u8"████"; TextColor(4); GotoXY(x + 26, y1 + 5); cout << u8"█";
	TextColor(10); GotoXY(x + 27, y1 + 5); cout << u8"    █"; TextColor(0); GotoXY(x + 32, y1 + 5); cout << u8"████"; TextColor(4); GotoXY(x + 36, y1 + 5); cout << u8"█";
	TextColor(10); GotoXY(x + 37, y1 + 5); cout << u8"  █"; TextColor(0); GotoXY(x + 40, y1 + 5); cout << u8"████"; TextColor(4); GotoXY(x + 44, y1 + 5); cout << u8"█";
	TextColor(10); GotoXY(x + 45, y1 + 5); cout << u8"    █"; TextColor(0); GotoXY(x + 50, y1 + 5); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 5); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 6); cout << u8"     █"; TextColor(0); GotoXY(x + 6, y1 + 6); cout << u8"██████"; TextColor(4); GotoXY(x + 12, y1 + 6); cout << u8"█";
	TextColor(10); GotoXY(x + 13, y1 + 6); cout << u8"       █"; TextColor(0); GotoXY(x + 21, y1 + 6); cout << u8"████"; TextColor(4); GotoXY(x + 25, y1 + 6); cout << u8"█";
	TextColor(10); GotoXY(x + 26, y1 + 6); cout << u8"    █"; TextColor(0); GotoXY(x + 31, y1 + 6); cout << u8"████"; TextColor(4); GotoXY(x + 35, y1 + 6); cout << u8"█";
	TextColor(10); GotoXY(x + 36, y1 + 6); cout << u8"  █"; TextColor(0); GotoXY(x + 39, y1 + 6); cout << u8"████"; TextColor(4); GotoXY(x + 43, y1 + 6); cout << u8"█";
	TextColor(10); GotoXY(x + 44, y1 + 6); cout << u8"    █"; TextColor(0); GotoXY(x + 49, y1 + 6); cout << u8"████"; TextColor(4); GotoXY(x + 53, y1 + 6); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 7); cout << u8"       █"; TextColor(0); GotoXY(x + 8, y1 + 7); cout << u8"██"; TextColor(4); GotoXY(x + 10, y1 + 7); cout << u8"█";
	TextColor(10); GotoXY(x + 11, y1 + 7); cout << u8"         █"; TextColor(0); GotoXY(x + 21, y1 + 7); cout << u8"████"; TextColor(4); GotoXY(x + 25, y1 + 7); cout << u8"█";
	TextColor(10); GotoXY(x + 26, y1 + 7); cout << u8"    █"; TextColor(0); GotoXY(x + 31, y1 + 7); cout << u8"████"; TextColor(4); GotoXY(x + 35, y1 + 7); cout << u8"█";
	TextColor(10); GotoXY(x + 36, y1 + 7); cout << u8"  █"; TextColor(0); GotoXY(x + 39, y1 + 7); cout << u8"███"; TextColor(4); GotoXY(x + 42, y1 + 7); cout << u8"█";
	TextColor(10); GotoXY(x + 43, y1 + 7); cout << u8"     █"; TextColor(0); GotoXY(x + 49, y1 + 7); cout << u8"████"; TextColor(4); GotoXY(x + 53, y1 + 7); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 8); cout << u8"       █"; TextColor(0); GotoXY(x + 8, y1 + 8); cout << u8"██"; TextColor(4); GotoXY(x + 10, y1 + 8); cout << u8"███";
	TextColor(10); GotoXY(x + 13, y1 + 8); cout << u8"     ██  █"; TextColor(0); GotoXY(x + 23, y1 + 8); cout << u8"███"; TextColor(4); GotoXY(x + 26, y1 + 8); cout << u8"█";
	TextColor(10); GotoXY(x + 27, y1 + 8); cout << u8"  █"; TextColor(0); GotoXY(x + 30, y1 + 8); cout << u8"███"; TextColor(4); GotoXY(x + 33, y1 + 8); cout << u8"█";
	TextColor(10); GotoXY(x + 34, y1 + 8); cout << u8"    █"; TextColor(0); GotoXY(x + 39, y1 + 8); cout << u8"██████████████"; TextColor(4); GotoXY(x + 53, y1 + 8); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 9); cout << u8"       █"; TextColor(0); GotoXY(x + 8, y1 + 9); cout << u8"██"; TextColor(4); GotoXY(x + 10, y1 + 9); cout << u8"█  ██";
	TextColor(10); GotoXY(x + 15, y1 + 9); cout << u8"         █"; TextColor(0); GotoXY(x + 25, y1 + 9); cout << u8"██████"; TextColor(4); GotoXY(x + 31, y1 + 9); cout << u8"█  ██";
	TextColor(10); GotoXY(x + 36, y1 + 9); cout << u8"  █"; TextColor(0); GotoXY(x + 39, y1 + 9); cout << u8"████████████"; TextColor(4); GotoXY(x + 51, y1 + 9); cout << u8"█  ██";

	//Win
	TextColor(10); GotoXY(x, y1 + 11); cout << u8"█"; TextColor(0); GotoXY(x + 1, y1 + 11); cout << u8"██"; TextColor(4); GotoXY(x + 3, y1 + 11); cout << u8"█";
	TextColor(10); GotoXY(x + 4, y1 + 11); cout << u8"                █"; TextColor(0); GotoXY(x + 21, y1 + 11); cout << u8"██"; TextColor(4); GotoXY(x + 23, y1 + 11); cout << u8"█";
	TextColor(10); GotoXY(x + 24, y1 + 11); cout << u8"  █"; TextColor(0); GotoXY(x + 27, y1 + 11); cout << u8"████████"; TextColor(4); GotoXY(x + 35, y1 + 11); cout << u8"█";
	TextColor(10); GotoXY(x + 36, y1 + 11); cout << u8"   █"; TextColor(0); GotoXY(x + 40, y1 + 11); cout << u8"████"; TextColor(4); GotoXY(x + 44, y1 + 11); cout << u8"█";
	TextColor(10); GotoXY(x + 45, y1 + 11); cout << u8"    █"; TextColor(0); GotoXY(x + 50, y1 + 11); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 11); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 12); cout << u8"█"; TextColor(0); GotoXY(x + 1, y1 + 12); cout << u8"███"; TextColor(4); GotoXY(x + 4, y1 + 12); cout << u8"█";
	TextColor(10); GotoXY(x + 5, y1 + 12); cout << u8"              █"; TextColor(0); GotoXY(x + 20, y1 + 12); cout << u8"███"; TextColor(4); GotoXY(x + 23, y1 + 12); cout << u8"█";
	TextColor(10); GotoXY(x + 24, y1 + 12); cout << u8"    █"; TextColor(0); GotoXY(x + 29, y1 + 12); cout << u8"████"; TextColor(4); GotoXY(x + 33, y1 + 12); cout << u8"█";
	TextColor(10); GotoXY(x + 34, y1 + 12); cout << u8"     █"; TextColor(0); GotoXY(x + 40, y1 + 12); cout << u8"█████"; TextColor(4); GotoXY(x + 45, y1 + 12); cout << u8"█";
	TextColor(10); GotoXY(x + 46, y1 + 12); cout << u8"    █"; TextColor(0); GotoXY(x + 51, y1 + 12); cout << u8"████"; TextColor(4); GotoXY(x + 55, y1 + 12); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 13); cout << u8"█"; TextColor(0); GotoXY(x + 1, y1 + 13); cout << u8"████"; TextColor(4); GotoXY(x + 5, y1 + 13); cout << u8"█";
	TextColor(0); GotoXY(x + 6, y1 + 13); cout << u8"    ████    ";
	TextColor(10); GotoXY(x + 18, y1 + 13); cout << u8"█"; TextColor(0); GotoXY(x + 19, y1 + 13); cout << u8"████"; TextColor(4); GotoXY(x + 23, y1 + 13); cout << u8"█";
	TextColor(10); GotoXY(x + 24, y1 + 13); cout << u8"    █"; TextColor(0); GotoXY(x + 29, y1 + 13); cout << u8"███         █████";
	TextColor(4); GotoXY(x + 46, y1 + 13); cout << u8"█";
	TextColor(10); GotoXY(x + 47, y1 + 13); cout << u8"  █"; TextColor(0); GotoXY(x + 50, y1 + 13); cout << u8"█████"; TextColor(4); GotoXY(x + 55, y1 + 13); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 14); cout << u8"█"; TextColor(0); GotoXY(x + 1, y1 + 14); cout << u8"████"; TextColor(4); GotoXY(x + 5, y1 + 14); cout << u8"█";
	TextColor(0); GotoXY(x + 6, y1 + 14); cout << u8"    ████    ";
	TextColor(10); GotoXY(x + 18, y1 + 14); cout << u8"█"; TextColor(0); GotoXY(x + 19, y1 + 14); cout << u8"████"; TextColor(4); GotoXY(x + 23, y1 + 14); cout << u8"█";
	TextColor(10); GotoXY(x + 24, y1 + 14); cout << u8"    █"; TextColor(0); GotoXY(x + 29, y1 + 14); cout << u8"█████"; TextColor(4); GotoXY(x + 34, y1 + 14); cout << u8"█";
	TextColor(10); GotoXY(x + 35, y1 + 14); cout << u8"    █"; TextColor(0); GotoXY(x + 40, y1 + 14); cout << u8"██████████████"; TextColor(4); GotoXY(x + 54, y1 + 14); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 15); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y1 + 15); cout << u8"████"; TextColor(4); GotoXY(x + 7, y1 + 15); cout << u8"█";
	TextColor(0); GotoXY(x + 8, y1 + 15); cout << u8"  ████  ";
	TextColor(10); GotoXY(x + 16, y1 + 15); cout << u8"█"; TextColor(0); GotoXY(x + 17, y1 + 15); cout << u8"████"; TextColor(4); GotoXY(x + 21, y1 + 15); cout << u8"█";
	TextColor(10); GotoXY(x + 22, y1 + 15); cout << u8"      █"; TextColor(0); GotoXY(x + 29, y1 + 15); cout << u8"████"; TextColor(4); GotoXY(x + 33, y1 + 15); cout << u8"█";
	TextColor(10); GotoXY(x + 34, y1 + 15); cout << u8"     █"; TextColor(0); GotoXY(x + 40, y1 + 15); cout << u8"██████████████"; TextColor(4); GotoXY(x + 54, y1 + 15); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 16); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y1 + 16); cout << u8"████████████████"; TextColor(4); GotoXY(x + 20, y1 + 16); cout << u8"█";
	TextColor(10); GotoXY(x + 21, y1 + 16); cout << u8"       █"; TextColor(0); GotoXY(x + 29, y1 + 16); cout << u8"████"; TextColor(4); GotoXY(x + 33, y1 + 16); cout << u8"█";
	TextColor(10); GotoXY(x + 34, y1 + 16); cout << u8"     █"; TextColor(0); GotoXY(x + 40, y1 + 16); cout << u8"███"; TextColor(4); GotoXY(x + 43, y1 + 16); cout << u8"█";
	TextColor(10); GotoXY(x + 44, y1 + 16); cout << u8"  █"; TextColor(0); GotoXY(x + 47, y1 + 16); cout << u8"███████"; TextColor(4); GotoXY(x + 54, y1 + 16); cout << u8"██";

	TextColor(10); GotoXY(x, y1 + 17); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y1 + 17); cout << u8"████████████████"; TextColor(4); GotoXY(x + 20, y1 + 17); cout << u8"█";
	TextColor(10); GotoXY(x + 21, y1 + 17); cout << u8"      █"; TextColor(0); GotoXY(x + 28, y1 + 17); cout << u8"████"; TextColor(4); GotoXY(x + 32, y1 + 17); cout << u8"█";
	TextColor(10); GotoXY(x + 33, y1 + 17); cout << u8"      █"; TextColor(0); GotoXY(x + 40, y1 + 17); cout << u8"███"; TextColor(4); GotoXY(x + 43, y1 + 17); cout << u8"█";
	TextColor(10); GotoXY(x + 44, y1 + 17); cout << u8"   █"; TextColor(0); GotoXY(x + 48, y1 + 17); cout << u8"██████"; TextColor(4); GotoXY(x + 54, y1 + 17); cout << u8"██";

	TextColor(10); GotoXY(x, y1 + 18); cout << u8"    █"; TextColor(0); GotoXY(x + 5, y1 + 18); cout << u8"██████████████"; TextColor(4); GotoXY(x + 19, y1 + 18); cout << u8"█";
	TextColor(10); GotoXY(x + 20, y1 + 18); cout << u8"       █"; TextColor(0); GotoXY(x + 28, y1 + 18); cout << u8"████"; TextColor(4); GotoXY(x + 32, y1 + 18); cout << u8"█";
	TextColor(10); GotoXY(x + 33, y1 + 18); cout << u8"     █"; TextColor(0); GotoXY(x + 39, y1 + 18); cout << u8"███"; TextColor(4); GotoXY(x + 42, y1 + 18); cout << u8"█";
	TextColor(10); GotoXY(x + 43, y1 + 18); cout << u8"     █"; TextColor(0); GotoXY(x + 49, y1 + 18); cout << u8"█████"; TextColor(4); GotoXY(x + 54, y1 + 18); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 19); cout << u8"    █"; TextColor(0); GotoXY(x + 5, y1 + 19); cout << u8"█████"; TextColor(4); GotoXY(x + 10, y1 + 19); cout << u8"█";
	TextColor(10); GotoXY(x + 11, y1 + 19); cout << u8"  █"; TextColor(0); GotoXY(x + 14, y1 + 19); cout << u8"█████"; TextColor(4); GotoXY(x + 19, y1 + 19); cout << u8"█";
	TextColor(10); GotoXY(x + 20, y1 + 19); cout << u8"       █"; TextColor(0); GotoXY(x + 28, y1 + 19); cout << u8"████"; TextColor(4); GotoXY(x + 32, y1 + 19); cout << u8"█";
	TextColor(10); GotoXY(x + 33, y1 + 19); cout << u8"     █"; TextColor(0); GotoXY(x + 39, y1 + 19); cout << u8"█████"; TextColor(4); GotoXY(x + 44, y1 + 19); cout << u8"█";
	TextColor(10); GotoXY(x + 45, y1 + 19); cout << u8"    █"; TextColor(0); GotoXY(x + 50, y1 + 19); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 19); cout << u8"█";

	TextColor(10); GotoXY(x, y1 + 20); cout << u8"     █"; TextColor(0); GotoXY(x + 6, y1 + 20); cout << u8"███"; TextColor(4); GotoXY(x + 9, y1 + 20); cout << u8"█";
	TextColor(10); GotoXY(x + 10, y1 + 20); cout << u8"    █"; TextColor(0); GotoXY(x + 15, y1 + 20); cout << u8"███"; TextColor(4); GotoXY(x + 18, y1 + 20); cout << u8"█ ██";
	TextColor(10); GotoXY(x + 22, y1 + 20); cout << u8"   █"; TextColor(0); GotoXY(x + 26, y1 + 20); cout << u8"████████"; TextColor(4); GotoXY(x + 34, y1 + 20); cout << u8"█";
	TextColor(10); GotoXY(x + 35, y1 + 20); cout << u8"   █"; TextColor(0); GotoXY(x + 39, y1 + 20); cout << u8"███"; TextColor(4); GotoXY(x + 42, y1 + 20); cout << u8"█";
	TextColor(10); GotoXY(x + 43, y1 + 20); cout << u8"      █"; TextColor(0); GotoXY(x + 50, y1 + 20); cout << u8"████"; TextColor(4); GotoXY(x + 54, y1 + 20); cout << u8"█";
	SetConsoleOutputCP(old_cp);
	const char* choice[2] = { "<YES>", "<OF COURSE>" };
	int pos = 0, x1 = 30, y = 27, x2 = 65;
	SetColor(240);

	while (1) {
		SetColor(240);
		for (int i = 0; i < 2; i++) {
			if (pos == 0) {
				UINT old_cp = GetConsoleOutputCP();
				SetConsoleOutputCP(CP_UTF8);
				TextColor(0); GotoXY(x1, y); cout << u8"                ██";
				TextColor(0); GotoXY(x1, y + 1); cout << u8"              ██"; TextColor(10); GotoXY(x1 + 16, y + 1); cout << u8"██"; TextColor(0); GotoXY(x1 + 18, y + 1); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 2); cout << u8"    ██      ██"; TextColor(10); GotoXY(x1 + 14, y + 2); cout << u8"██████"; TextColor(0); GotoXY(x1 + 20, y + 2); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 3); cout << u8"  ██"; TextColor(10); GotoXY(x1 + 4, y + 3); cout << u8"██"; TextColor(0); GotoXY(x1 + 6, y + 3); cout << u8"██  ██"; TextColor(10); GotoXY(x1 + 12, y + 3); cout << u8"██████"; TextColor(0); GotoXY(x1 + 18, y + 3); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 4); cout << u8"██"; TextColor(10); GotoXY(x1 + 2, y + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 8, y + 4); cout << u8"██"; TextColor(10); GotoXY(x1 + 10, y + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 16, y + 4); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 5); cout << u8"  ██"; TextColor(10); GotoXY(x1 + 4, y + 5); cout << u8"██████████"; TextColor(0); GotoXY(x1 + 14, y + 5); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 6); cout << u8"    ██"; TextColor(10); GotoXY(x1 + 6, y + 6); cout << u8"██████"; TextColor(0); GotoXY(x1 + 12, y + 6); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 7); cout << u8"      ██"; TextColor(10); GotoXY(x1 + 8, y + 7); cout << u8"██"; TextColor(0); GotoXY(x1 + 10, y + 7); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 8); cout << u8"        ██";


				TextColor(0); GotoXY(x2, y); cout << u8"    ██      ██    ";
				TextColor(0); GotoXY(x2, y + 1); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y + 1); cout << u8"██  ██"; TextColor(8); GotoXY(x2 + 12, y + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y + 1); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 2); cout << u8"██"; TextColor(8); GotoXY(x2 + 2, y + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y + 2); cout << u8"██"; TextColor(8); GotoXY(x2 + 10, y + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y + 2); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 3); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y + 3); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y + 3); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 4); cout << u8"    ██"; TextColor(8); GotoXY(x2 + 6, y + 4); cout << u8"██████"; TextColor(0); GotoXY(x2 + 12, y + 4); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 5); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y + 5); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y + 5); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 6); cout << u8"██"; TextColor(8); GotoXY(x2 + 2, y + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y + 6); cout << u8"██"; TextColor(8); GotoXY(x2 + 10, y + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y + 6); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 7); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y + 7); cout << u8"██  ██"; TextColor(8); GotoXY(x2 + 12, y + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y + 7); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 8); cout << u8"    ██      ██    ";

				SetConsoleOutputCP(old_cp);
			}

			else {
				UINT old_cp = GetConsoleOutputCP();
				SetConsoleOutputCP(CP_UTF8);
				TextColor(0); GotoXY(x2, y); cout << u8"    ██      ██    ";
				TextColor(0); GotoXY(x2, y + 1); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y + 1); cout << u8"██  ██"; TextColor(4); GotoXY(x2 + 12, y + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y + 1); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 2); cout << u8"██"; TextColor(4); GotoXY(x2 + 2, y + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y + 2); cout << u8"██"; TextColor(4); GotoXY(x2 + 10, y + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y + 2); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 3); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y + 3); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y + 3); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 4); cout << u8"    ██"; TextColor(4); GotoXY(x2 + 6, y + 4); cout << u8"██████"; TextColor(0); GotoXY(x2 + 12, y + 4); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 5); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y + 5); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y + 5); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 6); cout << u8"██"; TextColor(4); GotoXY(x2 + 2, y + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y + 6); cout << u8"██"; TextColor(4); GotoXY(x2 + 10, y + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y + 6); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 7); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y + 7); cout << u8"██  ██"; TextColor(4); GotoXY(x2 + 12, y + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y + 7); cout << u8"██";
				TextColor(0); GotoXY(x2, y + 8); cout << u8"    ██      ██    ";

				TextColor(0); GotoXY(x1, y); cout << u8"                ██";
				TextColor(0); GotoXY(x1, y + 1); cout << u8"              ██"; TextColor(8); GotoXY(x1 + 16, y + 1); cout << u8"██"; TextColor(0); GotoXY(x1 + 18, y + 1); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 2); cout << u8"    ██      ██"; TextColor(8); GotoXY(x1 + 14, y + 2); cout << u8"██████"; TextColor(0); GotoXY(x1 + 20, y + 2); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 3); cout << u8"  ██"; TextColor(8); GotoXY(x1 + 4, y + 3); cout << u8"██";  TextColor(0); GotoXY(x1 + 6, y + 3); cout << u8"██  ██"; TextColor(8); GotoXY(x1 + 12, y + 3); cout << u8"██████"; TextColor(0); GotoXY(x1 + 18, y + 3); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 4); cout << u8"██"; TextColor(8); GotoXY(x1 + 2, y + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 8, y + 4); cout << u8"██"; TextColor(8); GotoXY(x1 + 10, y + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 16, y + 4); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 5); cout << u8"  ██"; TextColor(8); GotoXY(x1 + 4, y + 5); cout << u8"██████████"; TextColor(0); GotoXY(x1 + 14, y + 5); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 6); cout << u8"    ██"; TextColor(8); GotoXY(x1 + 6, y + 6); cout << u8"██████"; TextColor(0); GotoXY(x1 + 12, y + 6); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 7); cout << u8"      ██"; TextColor(8); GotoXY(x1 + 8, y + 7); cout << u8"██"; TextColor(0); GotoXY(x1 + 10, y + 7); cout << u8"██";
				TextColor(0); GotoXY(x1, y + 8); cout << u8"        ██";
				SetConsoleOutputCP(old_cp);
			}
		}

		switch (InputKey()) {
		case 'a': case 'A':
			pos--;
			pos = abs(pos);
			pos %= 2;
			if (!constantVar::isMute1) PlaySound(TEXT("Move.wav"), NULL, SND_ASYNC);
			break;
		case 'd': case 'D':
			pos++;
			pos %= 2;
			if (!constantVar::isMute1) PlaySound(TEXT("Move.wav"), NULL, SND_ASYNC);
			break;
		case 13:
			if (!constantVar::isMute1) PlaySound(TEXT("Ring.wav"), NULL, SND_ASYNC);
			return;
		}
	}
}

bool nMap::PrintLevelUp() {
	if (level.GetLevel() == 5)
	{
		PrintCongrats();
		return false;
	}
	else {
		CLRSCR();
		HideCursor();
		PrintMap();
		DeleteOldPlayer();
		int x = 15, y = 7;
		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		TextColor(10); GotoXY(x, y); cout << u8"   ██  █"; TextColor(0); GotoXY(x + 8, y); cout << u8"████████"; TextColor(4); GotoXY(x + 16, y); cout << u8"█";
		TextColor(10); GotoXY(x + 17, y); cout << u8"           █"; TextColor(0); GotoXY(x + 29, y); cout << u8"██████"; TextColor(4); GotoXY(x + 35, y); cout << u8"█";
		TextColor(10); GotoXY(x + 36, y); cout << u8"             █"; TextColor(0); GotoXY(x + 50, y); cout << u8"██████"; TextColor(4); GotoXY(x + 56, y); cout << u8"█";
		TextColor(10); GotoXY(x + 57, y); cout << u8"           █"; TextColor(0); GotoXY(x + 69, y); cout << u8"██████████"; TextColor(4); GotoXY(x + 79, y); cout << u8"█";

		TextColor(10); GotoXY(x, y + 1); cout << u8"     █"; TextColor(0); GotoXY(x + 6, y + 1); cout << u8"████████████"; TextColor(4); GotoXY(x + 18, y + 1); cout << u8"█";
		TextColor(10); GotoXY(x + 19, y + 1); cout << u8"       █"; TextColor(0); GotoXY(x + 27, y + 1); cout << u8"███"; TextColor(4); GotoXY(x + 30, y + 1); cout << u8"█";
		TextColor(10); GotoXY(x + 31, y + 1); cout << u8"  █"; TextColor(0); GotoXY(x + 34, y + 1); cout << u8"███"; TextColor(4); GotoXY(x + 37, y + 1); cout << u8"█";
		TextColor(10); GotoXY(x + 37, y + 1); cout << u8"         █"; TextColor(0); GotoXY(x + 47, y + 1); cout << u8"███"; TextColor(4); GotoXY(x + 50, y + 1); cout << u8"█";
		TextColor(10); GotoXY(x + 51, y + 1); cout << u8"  █"; TextColor(0); GotoXY(x + 54, y + 1); cout << u8"███"; TextColor(4); GotoXY(x + 57, y + 1); cout << u8"█";
		TextColor(10); GotoXY(x + 58, y + 1); cout << u8"       █"; TextColor(0); GotoXY(x + 66, y + 1); cout << u8"██████████████"; TextColor(4); GotoXY(x + 80, y + 1); cout << u8"█  ██";

		TextColor(10); GotoXY(x, y + 2); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y + 2); cout << u8"████"; TextColor(4); GotoXY(x + 8, y + 2); cout << u8"█";
		TextColor(10); GotoXY(x + 9, y + 2); cout << u8"               █"; TextColor(0); GotoXY(x + 25, y + 2); cout << u8"████"; TextColor(4); GotoXY(x + 29, y + 2); cout << u8"█";
		TextColor(10); GotoXY(x + 30, y + 2); cout << u8"    █"; TextColor(0); GotoXY(x + 35, y + 2); cout << u8"████"; TextColor(4); GotoXY(x + 39, y + 2); cout << u8"█";
		TextColor(10); GotoXY(x + 40, y + 2); cout << u8"     █"; TextColor(0); GotoXY(x + 46, y + 2); cout << u8"████"; TextColor(4); GotoXY(x + 50, y + 2); cout << u8"█";
		TextColor(10); GotoXY(x + 51, y + 2); cout << u8"    █"; TextColor(0); GotoXY(x + 56, y + 2); cout << u8"████"; TextColor(4); GotoXY(x + 60, y + 2); cout << u8"█";
		TextColor(10); GotoXY(x + 61, y + 2); cout << u8"     █"; TextColor(0); GotoXY(x + 67, y + 2); cout << u8"████"; TextColor(4); GotoXY(x + 71, y + 2); cout << u8"█";
		TextColor(10); GotoXY(x + 72, y + 2); cout << u8"     █"; TextColor(0); GotoXY(x + 78, y + 2); cout << u8"█████"; TextColor(4); GotoXY(x + 83, y + 2); cout << u8"█";

		TextColor(10); GotoXY(x, y + 3); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y + 3); cout << u8"██";
		TextColor(10); GotoXY(x + 6, y + 3); cout << u8"                  █"; TextColor(0); GotoXY(x + 25, y + 3); cout << u8"████"; TextColor(4); GotoXY(x + 29, y + 3); cout << u8"███";
		TextColor(10); GotoXY(x + 32, y + 3); cout << u8"  █"; TextColor(0); GotoXY(x + 35, y + 3); cout << u8"████"; TextColor(4); GotoXY(x + 39, y + 3); cout << u8"█";
		TextColor(10); GotoXY(x + 40, y + 3); cout << u8"     █"; TextColor(0); GotoXY(x + 46, y + 3); cout << u8"████"; TextColor(4); GotoXY(x + 50, y + 3); cout << u8"███";
		TextColor(10); GotoXY(x + 53, y + 3); cout << u8"  █"; TextColor(0); GotoXY(x + 56, y + 3); cout << u8"████"; TextColor(4); GotoXY(x + 60, y + 3); cout << u8"█";
		TextColor(10); GotoXY(x + 61, y + 3); cout << u8"  ████"; TextColor(0); GotoXY(x + 67, y + 3); cout << u8"████"; TextColor(4); GotoXY(x + 71, y + 3); cout << u8"█";
		TextColor(10); GotoXY(x + 72, y + 3); cout << u8"     █"; TextColor(0); GotoXY(x + 78, y + 3); cout << u8"████";

		TextColor(10); GotoXY(x, y + 4); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y + 4); cout << u8"████"; TextColor(4); GotoXY(x + 8, y + 4); cout << u8"█";
		TextColor(0); GotoXY(x + 9, y + 4); cout << u8"                 ███"; TextColor(4); GotoXY(x + 29, y + 4); cout << u8"█";
		TextColor(10); GotoXY(x + 30, y + 4); cout << u8"    █"; TextColor(0); GotoXY(x + 35, y + 4); cout << u8"████"; TextColor(4); GotoXY(x + 39, y + 4); cout << u8"█";
		TextColor(0); GotoXY(x + 40, y + 4); cout << u8"       ███"; TextColor(4); GotoXY(x + 50, y + 4); cout << u8"█";
		TextColor(10); GotoXY(x + 51, y + 4); cout << u8"    █"; TextColor(0); GotoXY(x + 56, y + 4); cout << u8"████"; TextColor(4); GotoXY(x + 60, y + 4); cout << u8"█";
		TextColor(10); GotoXY(x + 61, y + 4); cout << u8"     █"; TextColor(0); GotoXY(x + 67, y + 4); cout << u8"████"; TextColor(4); GotoXY(x + 71, y + 4); cout << u8"█";
		TextColor(10); GotoXY(x + 72, y + 4); cout << u8"     █"; TextColor(0); GotoXY(x + 78, y + 4); cout << u8"█████"; TextColor(4); GotoXY(x + 83, y + 4); cout << u8"█";

		TextColor(10); GotoXY(x, y + 5); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 8, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 9, y + 5); cout << u8"  █"; TextColor(0); GotoXY(x + 12, y + 5); cout << u8"██████"; TextColor(4); GotoXY(x + 18, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 19, y + 5); cout << u8"     █"; TextColor(0); GotoXY(x + 25, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 29, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 30, y + 5); cout << u8"    █"; TextColor(0); GotoXY(x + 35, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 39, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 40, y + 5); cout << u8"     █"; TextColor(0); GotoXY(x + 46, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 50, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 51, y + 5); cout << u8"    █"; TextColor(0); GotoXY(x + 56, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 60, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 61, y + 5); cout << u8"     █"; TextColor(0); GotoXY(x + 67, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 71, y + 5); cout << u8"█";
		TextColor(10); GotoXY(x + 72, y + 5); cout << u8"     █"; TextColor(0); GotoXY(x + 78, y + 5); cout << u8"████"; TextColor(4); GotoXY(x + 82, y + 5); cout << u8"█";

		TextColor(10); GotoXY(x, y + 6); cout << u8"   █"; TextColor(0); GotoXY(x + 4, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 8, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 9, y + 6); cout << u8"    █"; TextColor(0); GotoXY(x + 14, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 18, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 19, y + 6); cout << u8"    █"; TextColor(0); GotoXY(x + 24, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 28, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 29, y + 6); cout << u8"    █"; TextColor(0); GotoXY(x + 34, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 38, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 39, y + 6); cout << u8"     █"; TextColor(0); GotoXY(x + 45, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 49, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 50, y + 6); cout << u8"    █"; TextColor(0); GotoXY(x + 55, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 59, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 60, y + 6); cout << u8"     █"; TextColor(0); GotoXY(x + 66, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 70, y + 6); cout << u8"█";
		TextColor(10); GotoXY(x + 71, y + 6); cout << u8"     █"; TextColor(0); GotoXY(x + 77, y + 6); cout << u8"████"; TextColor(4); GotoXY(x + 81, y + 6); cout << u8"█";

		TextColor(10); GotoXY(x, y + 7); cout << u8"  █"; TextColor(0); GotoXY(x + 3, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 7, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 8, y + 7); cout << u8"    █"; TextColor(0); GotoXY(x + 13, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 17, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 18, y + 7); cout << u8"     █"; TextColor(0); GotoXY(x + 24, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 28, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 29, y + 7); cout << u8"    █"; TextColor(0); GotoXY(x + 34, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 38, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 39, y + 7); cout << u8"     █"; TextColor(0); GotoXY(x + 45, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 49, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 50, y + 7); cout << u8"    █"; TextColor(0); GotoXY(x + 55, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 59, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 60, y + 7); cout << u8"     █"; TextColor(0); GotoXY(x + 66, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 70, y + 7); cout << u8"█";
		TextColor(10); GotoXY(x + 71, y + 7); cout << u8"     █"; TextColor(0); GotoXY(x + 77, y + 7); cout << u8"████"; TextColor(4); GotoXY(x + 81, y + 7); cout << u8"█";

		TextColor(10); GotoXY(x, y + 8); cout << u8"██  █"; TextColor(0); GotoXY(x + 5, y + 8); cout << u8"████"; TextColor(4); GotoXY(x + 9, y + 8); cout << u8"█";
		TextColor(10); GotoXY(x + 10, y + 8); cout << u8"  █"; TextColor(0); GotoXY(x + 13, y + 8); cout << u8"████"; TextColor(4); GotoXY(x + 17, y + 8); cout << u8"█";
		TextColor(10); GotoXY(x + 18, y + 8); cout << u8"   ██  █"; TextColor(0); GotoXY(x + 26, y + 8); cout << u8"███"; TextColor(4); GotoXY(x + 29, y + 8); cout << u8"█";
		TextColor(10); GotoXY(x + 30, y + 8); cout << u8"  █"; TextColor(0); GotoXY(x + 33, y + 8); cout << u8"███"; TextColor(4); GotoXY(x + 36, y + 8); cout << u8"█";
		TextColor(10); GotoXY(x + 37, y + 8); cout << u8"     ██  █"; TextColor(0); GotoXY(x + 47, y + 8); cout << u8"███"; TextColor(4); GotoXY(x + 50, y + 8); cout << u8"█";
		TextColor(10); GotoXY(x + 51, y + 8); cout << u8"  █"; TextColor(0); GotoXY(x + 54, y + 8); cout << u8"███"; TextColor(4); GotoXY(x + 57, y + 8); cout << u8"█";
		TextColor(10); GotoXY(x + 58, y + 8); cout << u8"       █"; TextColor(0); GotoXY(x + 66, y + 8); cout << u8"███████████████"; TextColor(4); GotoXY(x + 81, y + 8); cout << u8"█";

		TextColor(10); GotoXY(x, y + 9); cout << u8"      █"; TextColor(0); GotoXY(x + 7, y + 9); cout << u8"████████"; TextColor(4); GotoXY(x + 15, y + 9); cout << u8"█";
		TextColor(10); GotoXY(x + 16, y + 9); cout << u8"           █"; TextColor(0); GotoXY(x + 28, y + 9); cout << u8"██████"; TextColor(4); GotoXY(x + 34, y + 9); cout << u8"█  ██";
		TextColor(10); GotoXY(x + 39, y + 9); cout << u8"         █"; TextColor(0); GotoXY(x + 49, y + 9); cout << u8"██████"; TextColor(4); GotoXY(x + 55, y + 9); cout << u8"█  ██";
		TextColor(10); GotoXY(x + 60, y + 9); cout << u8"     █"; TextColor(0); GotoXY(x + 66, y + 9); cout << u8"████████████"; TextColor(4); GotoXY(x + 78, y + 9); cout << u8"█   ██";
		SetConsoleOutputCP(old_cp);
		int pos = 0, x1 = 30, y1 = 20, x2 = 65;
		SetColor(240);
		while (1) {
			SetColor(240);
			for (int i = 0; i < 2; i++) {
				if (pos == 0) {
					UINT old_cp = GetConsoleOutputCP();
					SetConsoleOutputCP(CP_UTF8);
					TextColor(0); GotoXY(x1, y1); cout << u8"                ██";
					TextColor(0); GotoXY(x1, y1 + 1); cout << u8"              ██"; TextColor(10); GotoXY(x1 + 16, y1 + 1); cout << u8"██"; TextColor(0); GotoXY(x1 + 18, y1 + 1); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 2); cout << u8"    ██      ██"; TextColor(10); GotoXY(x1 + 14, y1 + 2); cout << u8"██████"; TextColor(0); GotoXY(x1 + 20, y1 + 2); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 3); cout << u8"  ██"; TextColor(10); GotoXY(x1 + 4, y1 + 3); cout << u8"██"; TextColor(0); GotoXY(x1 + 6, y1 + 3); cout << u8"██  ██"; TextColor(10); GotoXY(x1 + 12, y1 + 3); cout << u8"██████"; TextColor(0); GotoXY(x1 + 18, y1 + 3); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 4); cout << u8"██"; TextColor(10); GotoXY(x1 + 2, y1 + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 8, y1 + 4); cout << u8"██"; TextColor(10); GotoXY(x1 + 10, y1 + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 16, y1 + 4); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 5); cout << u8"  ██"; TextColor(10); GotoXY(x1 + 4, y1 + 5); cout << u8"██████████"; TextColor(0); GotoXY(x1 + 14, y1 + 5); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 6); cout << u8"    ██"; TextColor(10); GotoXY(x1 + 6, y1 + 6); cout << u8"██████"; TextColor(0); GotoXY(x1 + 12, y1 + 6); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 7); cout << u8"      ██"; TextColor(10); GotoXY(x1 + 8, y1 + 7); cout << u8"██"; TextColor(0); GotoXY(x1 + 10, y1 + 7); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 8); cout << u8"        ██";


					TextColor(0); GotoXY(x2, y1); cout << u8"    ██      ██    ";
					TextColor(0); GotoXY(x2, y1 + 1); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y1 + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y1 + 1); cout << u8"██  ██"; TextColor(8); GotoXY(x2 + 12, y1 + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y1 + 1); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 2); cout << u8"██"; TextColor(8); GotoXY(x2 + 2, y1 + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y1 + 2); cout << u8"██"; TextColor(8); GotoXY(x2 + 10, y1 + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y1 + 2); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 3); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y1 + 3); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y1 + 3); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 4); cout << u8"    ██"; TextColor(8); GotoXY(x2 + 6, y1 + 4); cout << u8"██████"; TextColor(0); GotoXY(x2 + 12, y1 + 4); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 5); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y1 + 5); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y1 + 5); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 6); cout << u8"██"; TextColor(8); GotoXY(x2 + 2, y1 + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y1 + 6); cout << u8"██"; TextColor(8); GotoXY(x2 + 10, y1 + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y1 + 6); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 7); cout << u8"  ██"; TextColor(8); GotoXY(x2 + 4, y1 + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y1 + 7); cout << u8"██  ██"; TextColor(8); GotoXY(x2 + 12, y1 + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y1 + 7); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 8); cout << u8"    ██      ██    ";

					SetConsoleOutputCP(old_cp);
				}

				else {
					UINT old_cp = GetConsoleOutputCP();
					SetConsoleOutputCP(CP_UTF8);
					TextColor(0); GotoXY(x2, y1); cout << u8"    ██      ██    ";
					TextColor(0); GotoXY(x2, y1 + 1); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y1 + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y1 + 1); cout << u8"██  ██"; TextColor(4); GotoXY(x2 + 12, y1 + 1); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y1 + 1); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 2); cout << u8"██"; TextColor(4); GotoXY(x2 + 2, y1 + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y1 + 2); cout << u8"██"; TextColor(4); GotoXY(x2 + 10, y1 + 2); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y1 + 2); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 3); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y1 + 3); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y1 + 3); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 4); cout << u8"    ██"; TextColor(4); GotoXY(x2 + 6, y1 + 4); cout << u8"██████"; TextColor(0); GotoXY(x2 + 12, y1 + 4); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 5); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y1 + 5); cout << u8"██████████"; TextColor(0); GotoXY(x2 + 14, y1 + 5); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 6); cout << u8"██"; TextColor(4); GotoXY(x2 + 2, y1 + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 8, y1 + 6); cout << u8"██"; TextColor(4); GotoXY(x2 + 10, y1 + 6); cout << u8"██████"; TextColor(0); GotoXY(x2 + 16, y1 + 6); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 7); cout << u8"  ██"; TextColor(4); GotoXY(x2 + 4, y1 + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 6, y1 + 7); cout << u8"██  ██"; TextColor(4); GotoXY(x2 + 12, y1 + 7); cout << u8"██"; TextColor(0); GotoXY(x2 + 14, y1 + 7); cout << u8"██";
					TextColor(0); GotoXY(x2, y1 + 8); cout << u8"    ██      ██    ";

					TextColor(0); GotoXY(x1, y1); cout << u8"                ██";
					TextColor(0); GotoXY(x1, y1 + 1); cout << u8"              ██"; TextColor(8); GotoXY(x1 + 16, y1 + 1); cout << u8"██"; TextColor(0); GotoXY(x1 + 18, y1 + 1); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 2); cout << u8"    ██      ██"; TextColor(8); GotoXY(x1 + 14, y1 + 2); cout << u8"██████"; TextColor(0); GotoXY(x1 + 20, y1 + 2); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 3); cout << u8"  ██"; TextColor(8); GotoXY(x1 + 4, y1 + 3); cout << u8"██";  TextColor(0); GotoXY(x1 + 6, y1 + 3); cout << u8"██  ██"; TextColor(8); GotoXY(x1 + 12, y1 + 3); cout << u8"██████"; TextColor(0); GotoXY(x1 + 18, y1 + 3); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 4); cout << u8"██"; TextColor(8); GotoXY(x1 + 2, y1 + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 8, y1 + 4); cout << u8"██"; TextColor(8); GotoXY(x1 + 10, y1 + 4); cout << u8"██████"; TextColor(0); GotoXY(x1 + 16, y1 + 4); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 5); cout << u8"  ██"; TextColor(8); GotoXY(x1 + 4, y1 + 5); cout << u8"██████████"; TextColor(0); GotoXY(x1 + 14, y1 + 5); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 6); cout << u8"    ██"; TextColor(8); GotoXY(x1 + 6, y1 + 6); cout << u8"██████"; TextColor(0); GotoXY(x1 + 12, y1 + 6); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 7); cout << u8"      ██"; TextColor(8); GotoXY(x1 + 8, y1 + 7); cout << u8"██"; TextColor(0); GotoXY(x1 + 10, y1 + 7); cout << u8"██";
					TextColor(0); GotoXY(x1, y1 + 8); cout << u8"        ██";
					SetConsoleOutputCP(old_cp);
				}
			}

			switch (InputKey()) {
			case 'a': case 'A':
				pos--;
				pos = abs(pos);
				pos %= 2;
				if (!constantVar::isMute1) PlaySound(TEXT("Move.wav"), NULL, SND_ASYNC);
				break;
			case 'd': case 'D':
				pos++;
				pos %= 2;
				if (!constantVar::isMute1) PlaySound(TEXT("Move.wav"), NULL, SND_ASYNC);
				break;
			case 13:
				if (!constantVar::isMute1) PlaySound(TEXT("Ring.wav"), NULL, SND_ASYNC);
				return !pos;
			}
		}
	}
}

void nMap::PrintStage(int lv) {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	switch (lv)
	{
	case 1:
		GotoXY(134, 6);		cout << u8"██╗    ██╗   ██╗  ██╗";
		GotoXY(134, 7);		cout << u8"██║    ██║   ██║ ███║";
		GotoXY(134, 8);		cout << u8"██║    ██║   ██║ ╚██║";
		GotoXY(134, 9);		cout << u8"██║    ╚██╗ ██╔╝  ██║";
		GotoXY(134, 10);	cout << u8"███████╗╚████╔╝   ██║";
		GotoXY(134, 11);	cout << u8"╚══════╝ ╚═══╝    ╚═╝";
		break;
	case 2:
		GotoXY(132, 6);		cout << u8"██╗    ██╗   ██╗ ██████╗ ";
		GotoXY(132, 7);		cout << u8"██║    ██║   ██║ ╚════██╗";
		GotoXY(132, 8);		cout << u8"██║    ██║   ██║  █████╔╝";
		GotoXY(132, 9);		cout << u8"██║    ╚██╗ ██╔╝ ██╔═══╝ ";
		GotoXY(132, 10);	cout << u8"███████╗╚████╔╝  ███████╗";
		GotoXY(132, 11);	cout << u8"╚══════╝ ╚═══╝   ╚══════╝";
		break;
	case 3:
		GotoXY(132, 6);		cout << u8"██╗    ██╗   ██╗ ██████╗ ";
		GotoXY(132, 7);		cout << u8"██║    ██║   ██║ ╚════██╗";
		GotoXY(132, 8);		cout << u8"██║    ██║   ██║  █████╔╝";
		GotoXY(132, 9);		cout << u8"██║    ╚██╗ ██╔╝  ╚═══██╗";
		GotoXY(132, 10);	cout << u8"███████╗╚████╔╝  ██████╔╝";
		GotoXY(132, 11);	cout << u8"╚══════╝ ╚═══╝   ╚═════╝ ";
		break;
	case 4:
		GotoXY(132, 6);		cout << u8"██╗    ██╗   ██╗ ██╗  ██╗";
		GotoXY(132, 7);		cout << u8"██║    ██║   ██║ ██║  ██║";
		GotoXY(132, 8);		cout << u8"██║    ██║   ██║ ███████║";
		GotoXY(132, 9);		cout << u8"██║    ╚██╗ ██╔╝ ╚════██║";
		GotoXY(132, 10);	cout << u8"███████╗╚████╔╝       ██║";
		GotoXY(132, 11);	cout << u8"╚══════╝ ╚═══╝        ╚═╝";
		break;
	case 5:
		GotoXY(132, 6);		cout << u8"██╗    ██╗   ██╗ ███████╗";
		GotoXY(132, 7);		cout << u8"██║    ██║   ██║ ██╔════╝";
		GotoXY(132, 8);		cout << u8"██║    ██║   ██║ ███████╗";
		GotoXY(132, 9);		cout << u8"██║    ╚██╗ ██╔╝ ╚════██║";
		GotoXY(132, 10);	cout << u8"███████╗╚████╔╝  ███████║";
		GotoXY(132, 11);	cout << u8"╚══════╝ ╚═══╝   ╚══════╝";
		break;
	}

	SetConsoleOutputCP(old_cp);
}