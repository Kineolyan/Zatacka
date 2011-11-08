#include "jeu/jeu.h"
#include <iostream>

using namespace std;

#ifdef WIN32
//windows need their WinMain :-/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    StoreHinstance(hInstance);
#else
int main(int argc, char* argv[] ){
#endif
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Erreur à l'initialisation de la SDL : " << SDL_GetError() << endl;;
		exit(EXIT_FAILURE);
	}

	try {
		Jeu jeu(800,600);
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}
