#include "myLib.h"
#include <iostream>
#include <conio.h>

using namespace std;

bool cha = false, chb = false, colision = false;
const int width{ 8 }, height{ 8 };
int ax, ay, bx, by, Time{0}, x, y, vidas{0}, run, menu, fin, gameover ;
enum eDirectiona { LEFT, RIGHT, UP, DOWN };
enum eDirectionb { LEFTb, RIGHTb, UPb, DOWNb };
eDirectiona dira;
eDirectionb dirb;

int tailaX[100], tailaY[100];
int nTaila;

int tailbX[100], tailbY[100];
int nTailb;

char obs[width][height];

void Estado() {
	run = 1;
	menu = 1;
	ax = width / 2;
	ay = height - 3;
	bx = width / 2;
	by = 2;
}

void Reset() {
	vidas = 0;
	Time = 0;
	nTaila = 0;
	nTailb = 0;
	dira = UP;
	dirb = DOWNb;
	for (int m = 0; m < height; m++) {
		for (int n = 0; n < width; n++) {
			if (obs[m][n] == '#') {
				obs[m][n] = ' ';
			}
		}
	}
}

void Pantalla() {
	char pantalla[width][height];
	char jugador1 = '@';
	char jugador2 = '&';
	char a;

	Clear();
	Time++;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 && j == 0) {
				a = 201;
			}
			else if (i == height - 1 && j == 0) {
				a = 200;
			}
			else if (i == 0 && j == width - 1) {
				a = 187;
			}
			else if (i == height - 1 && j == width - 1) {
				a = 188;
			}
			else if (j == 0 || j == width - 1) {
				a = 186;
			}
			else if (i == 0 || i == height - 1) {
				a = 205;
			}
			else if (i == ay && j == ax) {
				a = jugador1;
			}
			else if (i == by && j == bx) {
				a = jugador2;
			}
			else {
				a = ' ';
			}

			for (int k = 0; k < nTaila; k++) {
				if (tailaX[k] == j && tailaY[k] == i) {
					a = '@';
				}
			}

			for (int l = 0; l < nTailb; l++) {
				if (tailbX[l] == j && tailbY[l] == i) {
					a = '&';
				}
			}

			for (int m = 0; m < height; m++) {
				for (int n = 0; n < width; n++) {
					if (obs[m][n] == '#' && i == m && j == n) {
						a = '#';
					}
				}
			}

			pantalla[i][j] = a;
			cout << pantalla[i][j];
		}
		cout << "\n";
	}
	cout << "Gusano 1 ( " << ax << " , " << ay << " )";
	cout << "    " << "Gusano 2 ( " << bx << " , " << by << " )";
	if (colision == true) {
		for (int e = 0; e < height; e++) {
			for (int f = 0; f < width; f++) {
				if (obs[e][f] == '#') {
					cout << "\nGusano 1 - ";
					cout << "Gusano 2";
					cout << " ---> Chocaron en ( " << e << " , " << f << " )";
				}
			}
		}
	}
}

void Teclado() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dira = LEFT;
			break;
		case 'd':
			dira = RIGHT;
			break;
		case 's':
			dira = DOWN;
			break;
		case 'w':
			dira = UP;
			break;
		case 'j':
			dirb = LEFTb;
			break;
		case 'l':
			dirb = RIGHTb;
			break;
		case 'k':
			dirb = DOWNb;
			break;
		case 'i':
			dirb = UPb;
			break;
		case 'q':
			gameover = 0;
			fin = 1;
			break;
		case 'Q':
			gameover = 0;
			fin = 1;
			break;
		}
	}
}

void Direccion() {

	int prevaX = tailaX[0];
	int prevaY = tailaY[0];
	int preva2X, preva2Y;
	tailaX[0] = ax;
	tailaY[0] = ay;

	for (int i = 1; i < nTaila; i++) {
		preva2X = tailaX[i];
		preva2Y = tailaY[i];
		tailaX[i] = prevaX;
		tailaY[i] = prevaY;
		prevaX = preva2X;
		prevaY = preva2Y;
	}

	switch (dira)
	{
	case LEFT:
		ax--;
		break;
	case RIGHT:
		ax++;
		break;
	case DOWN:
		ay++;
		break;
	case UP:
		ay--;
		break;
	}

	if (ax == 0 || ax == width - 1 || ay == 0 || ay == height - 1) {
		cha = true;
		gameover = 1;
        fin = 0;
	}

	if (Time % 20 == 0) {
		nTaila++;
	}

	for (int j = 0; j < nTaila; j++) {
		if (tailaX[j] == ax && tailaY[j] == ay) {
			ax = width / 2;
			ay = height - 3;
		}
		if (bx == tailaX[j] && by == tailaY[j]) {
			obs[by][bx] = '#';
			vidas++;
			colision = true;
			bx = width / 2;
			by = 2;
		}
	}

	if (vidas == 5) {
		gameover = 1;
        fin = 0;
	}

	if (obs[ay][ax] == '#') {
		ax = width / 2;
		ay = height - 3;
	}
}

void Direccion2() {
	int prevbX = tailbX[0];
	int prevbY = tailbY[0];
	int prevb2X, prevb2Y;
	tailbX[0] = bx;
	tailbY[0] = by;

	for (int i = 1; i < nTailb; i++) {
		prevb2X = tailbX[i];
		prevb2Y = tailbY[i];
		tailbX[i] = prevbX;
		tailbY[i] = prevbY;
		prevbX = prevb2X;
		prevbY = prevb2Y;
	}

	switch (dirb)
	{
	case LEFTb:
		bx--;
		break;
	case RIGHTb:
		bx++;
		break;
	case DOWNb:
		by++;
		break;
	case UPb:
		by--;
		break;
	}
	if (bx == 0 || bx == width - 1 || by == 0 || by == height - 1) {
		chb = true;
		gameover = 1;
        fin = 0;
	}

	if (Time % 20 == 0) {
		nTailb++;
	}

	for (int j = 0; j < nTailb; j++) {
		if (tailbX[j] == bx && tailbY[j] == by) {
			bx = width / 2;
			by = 2;
		}
		if (ax == tailbX[j] && ay == tailbY[j]) {
			obs[ay][ax] = '#';
			vidas++;
			colision = true;
			ax = width / 2;
			ay = height - 3;
		}
	}

	if (vidas == 5) {
		gameover = 1;
        fin = 0;
	}

	if (obs[by][bx] == '#') {
		bx = width / 2;
		by = 2;
	}
}

void Menu() {
	Clear();
	cout << "\n\n\n\n";
	cout << "================ " << "SNAKE 3.0" << " ==================" << endl;
	cout << "\n\n";
	cout << "     " << "Presionar [p] para empezar a jugar" << endl;
}

void Teclado_Menu() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'p':
			fin = 1;
			menu = 0;
			break;
		case 'P':
			fin = 1;
			menu = 0;
			break;
		}
	}
}

void Teclado_End() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'x':
			menu = 1;
			Estado();
			Reset();
			gameover = 0;
			break;
		case 'X':
			menu = 1;
			Estado();
			Reset();
			gameover = 0;
			break;
		case 'q':
			gameover = 0;
			run = 0;
			break;
		case 'Q':
			gameover = 0;
			run = 0;
			break;
		}
	}
}

void End() {
	Clear();
	cout << "\n\n\n";
	cout << "================ " << "Game Over" << " ==================";
	cout << "\n1) Estadisticas: " << endl;
	cout << endl;

	cout << "Gusano 1";
	if (cha == true) {
		cout << " --> Choco";
	}
	else {
		cout << " --> Intacto";
	}
	cout << "    " << "Gusano 2";
	if (chb == true) {
		cout << " --> Choco";
	}
	else {
		cout << " --> Intacto";
	}
	cout << endl;
	cout << "2) Colisiones: " << endl;
	if (colision == true) {
		for (int e = 0; e < height; e++) {
			for (int f = 0; f < width; f++) {
				if (obs[e][f] == '#') {
					cout << "\nGusano 1 - ";
					cout << "Gusano 2";
					cout << " ---> Chocaron en ( " << e << " , " << f << " )";
				}
			}
		}
	}

	cout << "\n\n";
	cout << "     " << "Presionar [x] para regresar a Menu" << endl;
	cout << "    " << "Presionar [q] para terminar de jugar" << endl;
}

void Clear() {
	system("cls");
}

void delay() {
	for (int c = 1; c <= 15000; c++) {
		for (int d = 1; d <= 15000; d++) {
		}
	}
}

int RUN(){
	if (run == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int MENU() {
	if (menu == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int FIN() {
	if (fin == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int GAMEOVER() {
	if (gameover == 1) {
		return 0;
	}
	else {
		return 1;
	}
}
