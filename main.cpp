#include "myLib.cpp"

int main(){
	Estado();
	while(run == true){
		while(menu == true){
			Menu();
			Teclado_Menu();
		}
		while(fin == true){
			Pantalla();
			delay();
			Teclado();
			Direccion();
			Direccion2();
		}
		while(gameover == true){
			End();
			Teclado_End();
		}
	}
	return 0;
}