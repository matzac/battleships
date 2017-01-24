// BattleshipsAI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "iostream"
#include <Windows.h>
using namespace std;

int x = 0;
int y = 0;

void duzyK(bool rozmiar){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;          
	int size;
	if (rozmiar){
		size == 100;
	}
	else {
		size = 0;
	}
	info.dwSize = size;                         
	SetConsoleCursorInfo(consoleHandle, &info); 
}


void gotoxy(int x, int y)
{
	COORD coord;              
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void sterowanie(char znak){
	const int GORA = 72, DOL = 80, LEWO = 75, PRAWO = 77, ENTER = 13, ESC = 27;
	switch (znak){
	case GORA: {
		if (y > 0)
			gotoxy(x, --y);
		break;
	}
	case DOL: {
		gotoxy(x, ++y);
		break;
	}
	case LEWO: {
		if (x > 0)
			gotoxy(--x, y);
		break;
	}
	case PRAWO: {
		gotoxy(++x, y);
		break;
	}
	case ENTER: {
		cout << "X";
		gotoxy(x, y);
		break;
	}
	}
}

int _tmain(int argc, _TCHAR* argv[]){
	duzyK(false);
	do {
		sterowanie(_getch());
	} while (1);
	_getch();
	return 0;
}

