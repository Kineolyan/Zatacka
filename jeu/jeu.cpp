#include "jeu.h"

using namespace std;

Jeu::Jeu(int largeur, int hauteur):
		m_largeur(largeur), m_hauteur(hauteur),	m_ecran(NULL),
		m_policeCalligraphiee(NULL), m_policeBasique(NULL) {
	m_ecran = SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	if (NULL==m_ecran) {
		throw runtime_error("Impossible de creer l'ecran");
	}
	SDL_WM_SetCaption("Zatacka", NULL);

	TTF_Init();
	chargerPolices();

	afficherEcranPrincipal();
}

Jeu::~Jeu() {
	TTF_CloseFont(m_policeCalligraphiee);
	TTF_CloseFont(m_policeBasique);
	TTF_Quit();
	SDL_Quit();
}

void Jeu::chargerPolices() {
	m_policeCalligraphiee = TTF_OpenFont("MLSJN.TTF", 65);
	m_policeBasique = TTF_OpenFont("SANFW___.TTF", 65);
}

void Jeu::afficherEcranPrincipal() {
	SDL_Color blanc = { 255, 255, 255};
	TexteSDL texte("Achtung, die kurve !", m_policeCalligraphiee, &blanc);
	SDL_Rect position;
	position.x = (m_largeur - texte.largeur()) / 2;
	position.y = (m_hauteur - texte.hauteur()) / 2;
	texte.position(position);
	texte.afficher(m_ecran);
	SDL_Flip(m_ecran);

	// passer à l'étape suivante
	SDL_Event event;
	bool boucler = true;
	while (boucler) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				return;

			case SDLK_SPACE:
				boucler = false;
				afficherMenuPrincipal();

			default:
				break;
			}
		}
	}
}

void Jeu::afficherMenuPrincipal() {
	SDL_FillRect(m_ecran, NULL,
			SDL_MapRGB(m_ecran->format, 0, 0, 0));
	SDL_Color blanc = { 255, 255, 255 };
	Option optionTest("jouer", "oui", "non", m_policeBasique, &blanc);
	SDL_Rect position;
	position.x = 100;
	position.y = 100;
	optionTest.position(position);
	optionTest.afficher(m_ecran);
	SDL_Flip(m_ecran);

	// passer à l'étape suivante
	SDL_Event event;
	bool boucler = true;
	while (boucler) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				return;

			case SDLK_p:
				optionTest.echanger();
				optionTest.afficher(m_ecran);
				break;

			default:
				break;
			}
		}
		SDL_Flip(m_ecran);
	}
}
