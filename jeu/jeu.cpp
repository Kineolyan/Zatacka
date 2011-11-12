#include "jeu.h"

using namespace std;

Jeu::Jeu(int largeur, int hauteur):
		m_largeur(largeur), m_hauteur(hauteur),	m_ecran(NULL),
		m_policeCalligraphiee(NULL), m_policeBasique(NULL) {
	m_ecran = SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
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
	m_policeBasique = TTF_OpenFont("SANFW___.TTF", 30);
}

void Jeu::initialiserCouleurs() {
	//#ifdef MINGW32
	SDL_Color blanc = { 255, 255, 255 },
		jaune = { 250, 225, 0 },
		bleu = { 0, 191, 249 },
		rouge = { 254, 1, 1 },
		vert = { 1, 236, 8 },
		violet = { 199, 8, 167 },
		orange = { 254, 151, 16 };
	m_couleurs["blanc"] = SDL_Color(blanc);
	m_couleurs["jaune"] = SDL_Color(jaune);
	m_couleurs["bleu"] = SDL_Color(bleu);
	m_couleurs["rouge"] = SDL_Color(rouge);
	m_couleurs["vert"] = SDL_Color(vert);
	m_couleurs["violet"] = SDL_Color(violet);
	m_couleurs["orange"] = SDL_Color(orange);
	/*#else
	m_couleurs["blanc"] = { 255, 255, 255 };
	m_couleurs["jaune"] = { 250, 225, 0 };
	m_couleurs["bleu"] = { 0, 191, 249 };
	m_couleurs["rouge"] = { 254, 1, 1 };
	m_couleurs["vert"] = { 1, 236, 8 };
	m_couleurs["violet"] = { 199, 8, 167 };
	m_couleurs["orange"] = { 254, 151, 16 };
	#endif*/
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
			&(m_couleurs["blanc"])),
			optionJoueur1("1 A", "READY", " ", m_policeBasique,
				&(m_couleurs["rouge"])),
			optionJoueur2("W X", "READY", " ", m_policeBasique,
				&(m_couleurs["jaune"])),
			optionJoueur3(", ;", "READY", " ", m_policeBasique,
				&(m_couleurs["vert"])),
			optionJoueur4("LARROW DARROW", "READY", " ", m_policeBasique,
				&(m_couleurs["violet"])),
			optionJoueur5("/ *", "READY", " ", m_policeBasique,
				&(m_couleurs["orange"])),
			optionJoueur6("LCLICK RCLICK", "READY", " ", m_policeBasique,
				&(m_couleurs["bleu"]));
	SDL_Rect position = {50, 50},
			positionEtat = {450, 50};
	optionJoueur1.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur2.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur3.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur4.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur5.position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	optionJoueur6.position(position, positionEtat);
	position.y+= 100;
	optionTest.position(position);
	optionJoueur1.afficher(m_ecran);
	optionJoueur2.afficher(m_ecran);
	optionJoueur3.afficher(m_ecran);
	optionJoueur4.afficher(m_ecran);
	optionJoueur5.afficher(m_ecran);
	optionJoueur6.afficher(m_ecran);
	optionTest.afficher(m_ecran);
	SDL_Flip(m_ecran);

	// passer à l'étape suivante
	SDL_Event event;
	bool boucler = true;
	while (boucler) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.unicode) {
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

			case SDLK_LEFT:
				optionJoueur4.activer();
				optionJoueur4.afficher(m_ecran);
				break;

			case SDLK_DOWN:
				optionJoueur4.desactiver();
				optionJoueur4.afficher(m_ecran);
				break;

			case SDLK_SLASH:
				optionJoueur5.activer();
				optionJoueur5.afficher(m_ecran);
				break;

			case SDLK_ASTERISK:
				optionJoueur5.desactiver();
				optionJoueur5.afficher(m_ecran);
				break;

			case SDLK_p:
				optionTest.echanger();
				optionTest.afficher(m_ecran);
				break;

			default:
				break;
			}

			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				optionJoueur4.activer();
				optionJoueur4.afficher(m_ecran);
				break;

			case SDLK_DOWN:
				optionJoueur4.desactiver();
				optionJoueur4.afficher(m_ecran);
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				optionJoueur6.activer();
				optionJoueur6.afficher(m_ecran);
				break;

			case SDL_BUTTON_RIGHT:
				optionJoueur6.desactiver();
				optionJoueur6.afficher(m_ecran);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		SDL_Flip(m_ecran);
	}
}
