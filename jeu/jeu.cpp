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
	initialiserCouleurs();

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
	m_policeBasique = TTF_OpenFont("SANFW___.TTF", 35);
}

void Jeu::initialiserCouleurs() {
	m_couleurs["blanc"] = { 255, 255, 255 };
	m_couleurs["jaune"] = { 250, 225, 0 };
	m_couleurs["bleu"] = { 0, 191, 249 };
	m_couleurs["rouge"] = { 254, 1, 1 };
	m_couleurs["vert"] = { 1, 236, 8 };
	m_couleurs["violet"] = { 199, 8, 167 };
	m_couleurs["orange"] = { 254, 151, 16 };
}

void Jeu::afficherEcranPrincipal() {
	TexteSDL texte("Achtung, die kurve !", m_policeCalligraphiee, &(m_couleurs["blanc"]));
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
	Option optionTest("jouer", "oui", "non", m_policeBasique,
			&(m_couleurs["bleu"])),
			optionJoueur1("1 A", "READY", " ", m_policeBasique,
				&(m_couleurs["rouge"])),
			optionJoueur2("W X", "READY", " ", m_policeBasique,
				&(m_couleurs["jaune"])),
			optionJoueur3(", ;", "READY", " ", m_policeBasique,
				&(m_couleurs["vert"]));
	SDL_Rect position = {50, 50},
			positionEtat = {350, 50};
	optionJoueur1.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur2.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur3.position(position, positionEtat);
	position.y+= 75;
	optionTest.position(position);
	optionJoueur1.afficher(m_ecran);
	optionJoueur2.afficher(m_ecran);
	optionJoueur3.afficher(m_ecran);
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

			case SDLK_AMPERSAND:
				optionJoueur1.activer();
				optionJoueur1.afficher(m_ecran);
				break;

			case SDLK_a:
				optionJoueur1.desactiver();
				optionJoueur1.afficher(m_ecran);
				break;

			case SDLK_w:
				optionJoueur2.activer();
				optionJoueur2.afficher(m_ecran);
				break;

			case SDLK_x:
				optionJoueur2.desactiver();
				optionJoueur2.afficher(m_ecran);
				break;

			case SDLK_COMMA:
				optionJoueur3.activer();
				optionJoueur3.afficher(m_ecran);
				break;

			case SDLK_SEMICOLON:
				optionJoueur3.desactiver();
				optionJoueur3.afficher(m_ecran);
				break;

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
