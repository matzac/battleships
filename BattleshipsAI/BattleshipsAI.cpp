// BattleshipsAI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "iostream"
#include <Windows.h>
using namespace std;

int x;
int y;
const int GORA = 72, DOL = 80, LEWO = 75, PRAWO = 77, ENTER = 13, ESC = 27;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void sterowanie(char znak){
	
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


void ustawStatki(){
	int maszty;
	gotoxy(1, 15);
	cout << "Ilu masztowy statek chcesz ustawic? (1-4)";
	cin >> maszty;
	gotoxy(1, 1);
	do{
		switch (_getch()){
		case GORA: {
			if (y > 1)
				gotoxy(x, --y);
			break;
		}
		case DOL: {
			if (y < 10)
				gotoxy(x, ++y);
			break;
		}
		case LEWO: {
			if (x > 1)
				gotoxy(--x, y);
			break;
		}
		case PRAWO: {
			if (x < 10)
				gotoxy(++x, y);
			break;
		}
		case ENTER: {
			cout << "X";
			maszty--;
			break;
		}
		}
		gotoxy(x, y);
	} while (maszty != 0);
}

void rysujPlansze(){
	cout << " ";
	for (int i = 0; i < 10; i++){
		cout << (char)(65 + i);
	}
	cout << endl;
	for (int i = 0; i < 10; i++){
		cout << i << endl;
	}
}

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



int _tmain(int argc, _TCHAR* argv[]){
	rysujPlansze();
	ustawStatki();
	_getch();
	return 0;
}

