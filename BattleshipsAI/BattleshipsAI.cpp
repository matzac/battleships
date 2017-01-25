// BattleshipsAI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "iostream"
#include <Windows.h>
#include "vector"
#include <ctime>
#include <stdlib.h>
#include <stdio.h> 
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

char getxy(int x, int y)
{
	gotoxy(x, y);
	char c = '\0';
	CONSOLE_SCREEN_BUFFER_INFO con;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hcon != INVALID_HANDLE_VALUE &&GetConsoleScreenBufferInfo(hcon, &con))
	{
		DWORD read = 0;
		if (!ReadConsoleOutputCharacterA(hcon, &c, 1, con.dwCursorPosition, &read) || read != 1)
			c = '\0';
	}
	return c;
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
				if (getxy(x, y) == 'X' || getxy(x + 1, y) == 'X' || getxy(x + 1, y + 1) == 'X' || getxy(x, y + 1) == 'X'|| 
					getxy(x - 1, y + 1) == 'X' || getxy(x - 1, y) == 'X' || getxy(x - 1, y - 1) == 'X' || getxy(x, y - 1) == 'X' || getxy(x + 1, y - 1) == 'X'){
					if (getxy(x + 1, y + 1) == 'X' || getxy(x - 1, y + 1) == 'X' || getxy(x - 1, y - 1) == 'X' || getxy(x + 1, y - 1) == 'X'){
						gotoxy(30, 1);
						cout << "blad";
					}
					else {
						if (p.size() != 0){
							if (getxy(p.back().x, p.back().y) == getxy(x + 1, y) || getxy(p.back().x, p.back().y) == getxy(x - 1, y) ||
								getxy(p.back().x, p.back().y) == getxy(x, y + 1) || getxy(p.back().x, p.back().y) == getxy(x, y - 1)){
								gotoxy(x, y);
								this->p.push_back(Punkt(x, y));
								maszty--;
								gotoxy(x, y);
								break;
							}
							else {
								gotoxy(30, 1);
								cout << "blad";
							}
						}
						else {
							gotoxy(30, 1);
							cout << "blad";
						}
					}
				}
				else{
					if (p.size() == 0){
						gotoxy(x, y);
						this->p.push_back(Punkt(x, y));
						maszty--;
						gotoxy(x, y);
						break;
					}
					else{
						gotoxy(30, 1);
						cout << "blad";
					}
				}
			}
			}
		} while (maszty != 0);
	}

	void wyswietl(){
		for (int i = 0; i < p.size(); i++){
			gotoxy(p[i].x, p[i].y);
			cout << "X";
		}
	}
};

class Plansza{
public:
	int wynik[10][10];


	Plansza(){

		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				wynik[i][j] = 0;
			}
		}

		int yr;
		int xr;
		bool poziomo;
		int ship[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		gotoxy(0, 20);
		for (int i = 0; i < 10; i++){
			do{
				xr = (rand() % 10);
				yr = (rand() % 10);
				yr = yr % 10;
				if (rand() % 2){
					//poziomo
					if (10 - xr >= ship[i]){
						do{
							wynik[yr][xr] = 1;
							xr++;
							ship[i]--;
						} while (ship[i] != 0);
					}

					else {
						cout << "blad: " << xr << " " << yr << endl;
					}
				}

				else {
					//pionowo
					if (10 - yr >= ship[i]){
						do{
							wynik[yr][xr] = 1;
							yr++;
							ship[i]--;
						} while (ship[i] != 0);
					}
					else {
						cout << "blad: " << xr << " " << yr << endl;
					}
				}
			} while (ship[i] != 0);
			cout << "PETLA " << i << endl;
			//_getch();
		}

		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				cout << wynik[i][j];
			//	_getch();
			}
			cout << endl;
		}
	}

	Plansza(vector<Statek> s){
		int dx;
		int dy;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				wynik[i][j] = 0;
			}
		}

		for (int i = 0; i < s.size(); i++){
			for (int j = 0; j < s[i].p.size(); j++){
				dy = s[i].p[j].y;
				dx = s[i].p[j].x;
				//cout << "dx = " << dx << ", dy = " << dy << endl;
				wynik[dy-1][dx-1] = 1;
			//	cout << "wynik[dy][dx] = " << wynik[dy][dx] << endl;
			}
		}
	}


	void show(int y){
		cout << "WCHODZE";
		gotoxy(0, 0);
		rysujPlansze();
		for (int i = 0; i < 10; i++){
			
			gotoxy(y, i+1);
			for (int j = 0; j < 10; j++){
				if (wynik[i][j] == 0){
					cout << " ";
				}
				if (wynik[i][j] == 1){
					cout << "S";
				}
			}
			cout << endl;
		}
	}
};

int Statek::count = 0;

int _tmain(int argc, _TCHAR* argv[]){
	srand(time(NULL));
/*	int m1 = 4;
	int m2 = 3;
	int m3 = 2;
	int m4 = 1;
	int n;
	vector<Statek> ships;

	do{
		gotoxy(0, 0);
		system("cls");
		
		rysujPlansze();
		for (int i = 0; i < ships.size(); i++){
			ships[i].wyswietl();
		}

		gotoxy(1, 15);

		

		cout << "Pozostale statki do rozstawienia: " << endl;
		cout << "1-masztowe: " << m1 <<  endl;
		cout << "2-masztowe: " << m2 << endl;
		cout << "3-masztowe: " << m3 << endl;
		cout << "4-masztowe: " << m4 << endl;

		cout << "Wybierz, ktory statek chcesz rozstawic (1-4): ";
		cin >> n;

		switch (n){
			case 1: { 
				if (m1){
					m1--;
					ships.push_back(Statek(1));
				}
				break;

			}
			case 2: {
				if (m2){
					m2--;
					ships.push_back(Statek(2));
				}
				break;
			}
			case 3: {
				if (m3){
					m3--;
					ships.push_back(Statek(3));
				}
				break;
			}
			case 4: {
				if (m4){
					m4--;
					ships.push_back(Statek(4));
				}
				break;
			}
		}
	} while ((m1 != 0) || (m2 != 0) || (m3 != 0) || (m4 != 0));

	system("cls");



	Plansza plansza = Plansza(ships);
	plansza.show(1);
	gotoxy(0, 0);
	*/

	

	Plansza komp = Plansza();
	komp.show(1);
	_getch();
	return 0;
}
