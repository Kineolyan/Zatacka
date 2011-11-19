#include "jeu/zatacka.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[] ){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Erreur à l'initialisation de la SDL : " << SDL_GetError() << endl;;
		exit(EXIT_FAILURE);
	}
	SDL_EnableUNICODE(1);

	try {
		Zatacka jeu(800,600);
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
