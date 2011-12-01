#include "jeu/zatacka.h"
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main(int argc, char* argv[] ){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Erreur à l'initialisation de la SDL : " << SDL_GetError() << endl;;
		exit(EXIT_FAILURE);
	}
	SDL_EnableUNICODE(1);

	srand(time(NULL));

	try {
		Zatacka jeu(640,480);
		jeu.demarrer();
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
