#include <iostream>
#include <conio.h>
#include "myLib.h"
#include "myLib.cpp"


int main() {
	Estado();
	while (RUN() == 0) {
		while (MENU() == 0) {
			Menu();
			Teclado_Menu();
		}
		while (FIN() == 0) {
			Pantalla();
			delay();
			Teclado();
			Direccion();
			Direccion2();
		}
		while (GAMEOVER() == 0) {
			End();
			Teclado_End();
		}
	}
	return 0;
}
