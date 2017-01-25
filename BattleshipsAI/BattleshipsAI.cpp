// BattleshipsAI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "iostream"
#include <Windows.h>
#include "vector"
using namespace std;

int x=1;
int y=1;
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

class Punkt{
public:
	int x;
	int y;

	Punkt(){
		this->x = 0;
		this->y = 0;
		
	}

	Punkt(int x, int y){
		this->x = x;
		this->y = y;
		cout << "X";
	}
};

class Statek{
public:
	int maszty;
	int id;
	static int count;
	vector<Punkt> p;

	Statek(int m){
		this->maszty = m;
		this-> id = ++count;
		gotoxy(x, y);
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
				this->p.push_back(Punkt(x, y));
				maszty--;
				gotoxy(x, y);
				break;
			}
			}
		} while (maszty != 0);
	}
};

int Statek::count = 0;

int _tmain(int argc, _TCHAR* argv[]){
	rysujPlansze();
	_getch();
	return 0;
}

