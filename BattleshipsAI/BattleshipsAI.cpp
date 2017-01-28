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

int x = 1;
int y = 1;
int dx = 20;
int dy = 1;
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

void rysujPlansze(int x){

	cout << " ";
	for (int i = 0; i < 10; i++){
		cout << (char)(65 + i);
	}
	cout << endl;
	for (int i = 0; i < 10; i++){
		gotoxy(x - 1, i + 1);
		cout << i << endl;
	}
}

void duzyK(bool rozmiar){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	int size;
	if (rozmiar){
		size = 100;
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
	int wartosc;

	Punkt(){
		this->x = 0;
		this->y = 0;
		this->wartosc = 0;

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
		this->id = ++count;
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
				if (getxy(x, y) == 'X' || getxy(x + 1, y) == 'X' || getxy(x + 1, y + 1) == 'X' || getxy(x, y + 1) == 'X' ||
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
	int shipCounter;


	Plansza(){

		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				wynik[i][j] = 0;
			}
		}

		int yr;
		int xr;
		int temp;
		bool przerwij;
		int ship[10] = { 5, 4, 3, 2 };
		gotoxy(0, 20);
		for (int i = 0; i < 4; i++){
			do{
				przerwij = false;
				xr = (rand() % 10);
				yr = (rand() % 10);
				yr = yr % 10;
				if (rand() % 2){
					//poziomo
					if (10 - xr >= ship[i]){
						temp = ship[i];
						do{
							if (wynik[yr][xr + temp] == 1 || wynik[yr][xr + temp + 1] == 1 || wynik[yr + 1][xr + temp + 1] == 1 || wynik[yr + 1][xr + temp] == 1 ||
								wynik[yr + 1][xr + temp - 1] == 1 || wynik[yr][xr + temp - 1] == 1 || wynik[yr - 1][xr + temp - 1] == 1 || wynik[yr - 1][xr + temp] == 1 ||
								wynik[yr - 1][xr + temp + 1] == 1){
								przerwij = true;
								break;
							}
							else {
								temp--;
							}
						} while (temp != 0);
						do{
							if (przerwij){
								break;
							}
							else {
								wynik[yr][xr] = 1;
								xr++;
								ship[i]--;
							}
						} while (ship[i] != 0);
					}

					else {
						cout << "blad: " << xr << " " << yr << endl;
					}
				}

				else {
					//pionowo
					if (10 - yr >= ship[i]){
						temp = ship[i];
						do{
							if (wynik[yr + temp][xr] == 1 || wynik[yr + temp][xr + 1] == 1 || wynik[yr + temp + 1][xr + 1] == 1 || wynik[yr + temp + 1][xr] == 1 ||
								wynik[yr + temp + 1][xr - 1] == 1 || wynik[yr + temp][xr - 1] == 1 || wynik[yr + temp - 1][xr - 1] == 1 || wynik[yr + temp - 1][xr] == 1 ||
								wynik[yr + temp - 1][xr + 1] == 1){
								przerwij = true;
								break;
							}
							else {
								temp--;
							}
						} while (temp != 0);
						do{
							if (przerwij){
								break;
							}
							else{
								wynik[yr][xr] = 1;
								yr++;
								ship[i]--;
							}
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

	}

	Plansza(vector<Statek> s){
		int dx;
		int dy;
		shipCounter = 0;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				wynik[i][j] = 0;
			}
		}

		for (int i = 0; i < s.size(); i++){
			for (int j = 0; j < s[i].p.size(); j++){
				dy = s[i].p[j].y;
				dx = s[i].p[j].x;
				shipCounter++;
				//cout << "dx = " << dx << ", dy = " << dy << endl;
				wynik[dy - 1][dx - 1] = 1;
				//	cout << "wynik[dy][dx] = " << wynik[dy][dx] << endl;
			}
		}
	}


	/*void show(int y){
	gotoxy(y-1, 0);
	rysujPlansze(y);
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
	}*/

	void show(int y){
		gotoxy(y - 1, 0);
		rysujPlansze(y);
		for (int i = 0; i < 10; i++){

			gotoxy(y, i + 1);
			for (int j = 0; j < 10; j++){
				if (wynik[i][j] == 0){
					cout << "0";
				}
				if (wynik[i][j] == 1){
					cout << "1";
				}
				if (wynik[i][j] == 2){
					cout << "2";
				}
				if (wynik[i][j] == 3){
					cout << "3";
				}
			}
			cout << endl;
		}
	}

	void showHidden(int y){
		gotoxy(y - 1, 0);
		rysujPlansze(y);
		for (int i = 0; i < 10; i++){

			gotoxy(y, i + 1);
			for (int j = 0; j < 10; j++){
				if (wynik[i][j] == 0){
					cout << " ";
				}
				if (wynik[i][j] == 1){
					cout << " ";
				}
				if (wynik[i][j] == 2){
					cout << "X";
				}
				if (wynik[i][j] == 3){
					cout << "*";
				}
			}
			cout << endl;
		}
	}
};

vector<Statek> rozstawStatki(){

	int m2 = 1;
	int m3 = 1;
	int m4 = 1;
	int m5 = 1;
	int n;
	vector<Statek> ships;

	do{
		gotoxy(0, 0);
		system("cls");

		rysujPlansze(1);
		for (int i = 0; i < ships.size(); i++){
			ships[i].wyswietl();
		}

		gotoxy(1, 15);



		cout << "Pozostale statki do rozstawienia: " << endl;
		cout << "2-masztowe: " << m2 << endl;
		cout << "3-masztowe: " << m3 << endl;
		cout << "4-masztowe: " << m4 << endl;
		cout << "5-masztowe: " << m5 << endl;

		cout << "Wybierz, ktory statek chcesz rozstawic (1-4): ";
		cin >> n;

		switch (n){
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
		case 5: {
			if (m5){
				m5--;
				ships.push_back(Statek(5));
			}
			break;
		}
		}
	} while ((m2 != 0) || (m3 != 0) || (m4 != 0) || (m5 != 0));
	return ships;
}

int Statek::count = 0;

void poluj(Plansza &p){
	bool isNotDone = true;
	int py;
	int px;
	do{
		gotoxy(dx, dy);
		switch (_getch()){
		case GORA: {
			if (dy > 1)
				gotoxy(dx, --dy);
			break;
		}
		case DOL: {
			if (dy < 10)
				gotoxy(dx, ++dy);
			break;
		}
		case LEWO: {
			if (dx > 20)
				gotoxy(--dx, dy);
			break;
		}
		case PRAWO: {
			if (dx < 29)
				gotoxy(++dx, dy);
			break;
		}
		case ENTER: {
			py = dy - 1;
			px = dx - 20;
			do{
				if (p.wynik[py][px] == 1){
					gotoxy(35, 14);
					p.wynik[py][px] = 2;
					cout << "trafiony! " << p.wynik[py][px];
					isNotDone = false;

				}
				if (p.wynik[py][px] == 0){
					gotoxy(35, 14);
					cout << "pudlo!";
					p.wynik[py][px] = 3;
					isNotDone = false;


				}
				break;
			} while (1);

			gotoxy(dx, dy);
			break;
		}
		}
	} while (isNotDone);
}



void wyswietl(Plansza p){
	for (int y = 0; y < 10; y++){
		for (int x = 0; y < 10; x++){
			cout << p.wynik[x][y];
		}
		cout << endl;
	}
}



Punkt polujKomp(Plansza &p, bool &mode){
	Punkt pole[100];
	int counter = 0;
	int boardsize = 10;
	for (int y = 0; y < 10; y++){
		for (int x = 0; x < 10; x++){
			pole[counter].x = x;
			pole[counter].y = y;
			counter++;
		}
	}
	int ships[5] = { 5, 4, 3, 2 };
	int licz;
	for (int s = 0; s < 4; s++){
		for (int y = 0; y < 10; y++){
			for (int x = 0; x < 10; x++){
				if (ships[s] + x <= boardsize){
					licz = 0;
					for (int i = 0; i < ships[s]; i++){
						if (p.wynik[y][x + i] != 2 && p.wynik[y][x + i] != 3){
							licz++;
						}
					}
					for (int i = 0; i < ships[s]; i++){
						if (licz == ships[s]){
							for (int n = 0; n < 100; n++){
								if ((pole[n].x == x + i) && (pole[n].y == y)){
									pole[n].wartosc += 1;
								}
							}
						}
					}
				}
			}
		}

		for (int y = 0; y < 10; y++){
			for (int x = 0; x < 10; x++){
				if (ships[s] + y <= boardsize){
					licz = 0;
					for (int i = 0; i < ships[s]; i++){
						if (p.wynik[y + i][x] != 2 && p.wynik[y + i][x] != 3){
							licz++;
						}
					}
					for (int i = 0; i < ships[s]; i++){
						if (licz == ships[s]){
							for (int n = 0; n < 100; n++){
								if ((pole[n].x == x) && (pole[n].y == y + i)){
									pole[n].wartosc += 1;
								}
							}
						}
					}
				}
			}
		}
		/*
		for (int y = 0; y < 10; y++){
		for (int x = 0; x < 10; x++){
		if (ships[s] + y <= boardsize){
		licz = 0;
		for (int i = 0; i < ships[s]; i++){
		if (p.wynik[y + i][x] != 1){
		licz++;
		if (licz == ships[s]){
		for (int n = 0; n < 100; n++){
		if ((pole[n].x == x) && (pole[n].y == y + i)){
		pole[n].wartosc += 1;
		}
		}
		}
		}
		}
		}
		}
		}*/
	}

	for (int s = 0; s < 4; s++){
		for (int y = 0; y < 10; y++){
			for (int x = 0; x < 10; x++){

			}
		}
	}


	//	for (int i = 0; i < 100; i++){
	//		 cout << "Punkt.x = " << pole[i].x << ", Punkt.y = " << pole[i].y << ", wartosc = " << pole[i].wartosc << endl;
	//	}


	Punkt max;
	for (int i = 0; i < 100; i++){
		if (pole[i].wartosc > max.wartosc){
			max = pole[i];
		}
	}

	if (p.wynik[max.y][max.x] == 1){
		p.wynik[max.y][max.x] = 2;
		mode = false;
		p.shipCounter--;
	}
	if (p.wynik[max.y][max.x] == 0){
		p.wynik[max.y][max.x] = 3;
		mode = true;

	}
	gotoxy(1, 14);
	cout << "WAS HIT: x = " << max.x << ", y = " << max.y << ", wartosc = " << max.wartosc;
	return max;
}

bool MaWolnegoSasiada(Plansza p, Punkt pkt){
	int x = pkt.x;
	int y = pkt.y;

	//pobierz gornego sasiada
	if (p.wynik[y - 1][x] == 0 || p.wynik[y - 1][x] == 1){
		return true;
	}

	//pobierz dolnego sasiada
	if (p.wynik[y + 1][x] == 0 || p.wynik[y + 1][x] == 1){
		return true;
	}

	//pobierz lewego sasiada
	if (p.wynik[y][x - 1] == 0 || p.wynik[y][x - 1] == 1){
		return true;
	}

	//pobierz prawego sasiada
	if (p.wynik[y][x + 1] == 0 || p.wynik[y][x + 1] == 1){
		return true;
	}
	return false;
}

Punkt pobierzWolnegoSasiada(Plansza p, Punkt pole){
	Punkt sasiad;
	int x = pole.x;
	int y = pole.y;

	//pobierz gornego sasiada
	if (p.wynik[y - 1][x] == 0 || p.wynik[y - 1][x] == 1){
		sasiad.x = x;
		sasiad.y = y - 1;
		return sasiad;
	}

	//pobierz dolnego sasiada
	 if (p.wynik[y + 1][x] == 0 || p.wynik[y + 1][x] == 1){
		sasiad.x = x;
		sasiad.y = y + 1;
		return sasiad;
	}

	//pobierz lewego sasiada
	 if (p.wynik[y][x - 1] == 0 || p.wynik[y][x - 1] == 1){
		sasiad.x = x - 1;
		sasiad.y = y;
		return sasiad;
	}

	//pobierz prawego sasiada
	if (p.wynik[y][x + 1] == 0 || p.wynik[y][x + 1] == 1){
		sasiad.x = x + 1;
		sasiad.y = y;
		return sasiad;
	}
	if (1){
		cout << "zwracam pole x = " << pole.x << ", y = " << pole.y;
		_getch();
		return pole;
	}
}


void polujSasiada(Plansza &p, Punkt firsthit, Punkt &lasthit, bool &mode){
	Punkt sasiadPola = pobierzWolnegoSasiada(p, lasthit);
	int x = sasiadPola.x;
	int y = sasiadPola.y;

	if (p.wynik[y][x] == 0){
		p.wynik[y][x] = 3;
		if (MaWolnegoSasiada(p, lasthit)){
			mode = false;
		}
		else{
			lasthit = firsthit;
			if (!MaWolnegoSasiada(p, lasthit)){
				mode = true;
			}
		}
	}
	if (p.wynik[y][x] == 1){
		p.wynik[y][x] = 2;
		lasthit = sasiadPola;
		p.shipCounter--;
	}
}


int _tmain(int argc, _TCHAR* argv[]){
	srand(time(NULL));


	vector<Statek> ships = rozstawStatki();

	system("cls");



	Plansza plansza = Plansza(ships);
	//Plansza komp = Plansza();
	/*duzyK(true);
	do{
	system("cls");
	plansza.show(1);
	komp.showHidden(20);
	komp.show(32);
	poluj(komp);
	gotoxy(1, 15);
	cout << "ruch komputera...";
	_getch();
	//	gotoxy(30, 1);
	//	wyswietl(komp);
	} while (1);*/

	bool kompMode = true;

	
	Punkt lasthit;
	Punkt firsthit;

	
		do {
			system("cls");
			if (kompMode){
				firsthit = polujKomp(plansza, kompMode);
				lasthit = firsthit;
			}
			else{
				polujSasiada(plansza, firsthit, lasthit, kompMode);
			}
			plansza.showHidden(1);
			gotoxy(1, 20);
			cout << "pozostalo masztow" << plansza.shipCounter;
			_getch();
		} while (plansza.shipCounter > 0);

	_getch();
	return 0;


}

/*for (int y = 0; y < 10; y++){
for (int x = 0; x < 10; x++){
licz = 0;
for (int i = 0; i < ships[s]; i++){
if (p.wynik[y][x + i] == 0 || p.wynik[y][x + i] == 1){
licz += 1;
}
}
if (licz == ships[s]){
for (int i = 0; i < ships[s]; i++){
for (int n = 0; n < 100; n++){
if ((pole[n].x == x + i) && (pole[n].y == y)){
pole[n].wartosc += 1;
}
}
}
}
else{
for (int i = 0; i < ships[s]; i++){
for (int n = 0; n < 100; n++){
if ((pole[n].x == x + i) && (pole[n].y == y)){
pole[n].wartosc -= 1;
}
}
}
}
}
}
*/