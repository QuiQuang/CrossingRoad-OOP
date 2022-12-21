//Import thư viện
#pragma once
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;

class constantVar {
public:
	static bool isMute1;
	static bool isMute2;

	static bool isHard;
};


class nColor {
public:
	static int BorderColor;
	static int EnemyColor;
	static int PlayerColor;

	static const int Loadline = 112;
};
//Global variable
#define Key_Up		1072
#define Key_Down	1080
#define Key_Left	1075
#define Key_Right	1077
#define Key_none	-1

void TextColor(int);						
void SetColor(WORD);				
void GotoXY(int, int);					
void HideCursor();							
void CLRSCR();								
void SetWindowSize(SHORT width, SHORT height);
void DisableMouse();				
int InputKey();								
void FixConsoleWindow();
void DisableSelection();					