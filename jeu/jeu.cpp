#include "jeu.h"

using namespace std;

Jeu::Jeu(int largeur, int hauteur):
		m_largeur(largeur), m_hauteur(hauteur),
		m_largeurScores(100), m_ecran(NULL),
		m_policeCalligraphiee(NULL), m_policeBasique(NULL),
		m_optionJoueurs(6), m_options() {
	m_ecran = SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_SWSURFACE | SDL_DOUBLEBUF/* | SDL_FULLSCREEN*/);
	if (NULL==m_ecran) {
		throw ExceptionGenerale("Impossible de creer l'ecran");
	}
	SDL_WM_SetCaption("Zatacka", NULL);

	TTF_Init();
	chargerPolices();
	initialiserCouleurs();
	initialiserScores();

	creerMenuPrincipal();
	creerMenuOptions();

	afficherEcranPrincipal();
}

Jeu::~Jeu() {
	TTF_CloseFont(m_policeCalligraphiee);
	TTF_CloseFont(m_policeBasique);


    for (map<string, SDL_Color*>::iterator it = m_couleurs.begin(),
        end = m_couleurs.end() ; it!=end; it++) {
        delete it->second;
    }

    for (vector<Option*>::iterator it = m_options.begin(),
            end = m_options.end(); it!=end; it++) {
    	delete *it;
    }

    for (vector<Option*>::iterator it = m_optionJoueurs.begin(),
            end = m_optionJoueurs.end(); it!=end; it++) {
    	delete *it;
    }

	TTF_Quit();
	SDL_Quit();
}

void Jeu::chargerPolices() {
	m_policeCalligraphiee = TTF_OpenFont("SCORE.TTF", 65);
	m_policeBasique = TTF_OpenFont("MENU.TTF", 25);

	if (NULL==m_policeBasique || NULL==m_policeCalligraphiee) {
        throw ParametreManquant("Une des polices n'a pas ete creee.");
	}
}

void Jeu::initialiserCouleurs() {
	m_couleurs["blanc"] = new SDL_Color({255, 255, 255});
    m_couleurs["jaune"] = new SDL_Color({250, 225, 0 });
	m_couleurs["bleu"] = new SDL_Color({0, 191, 249});
	m_couleurs["rouge"] = new SDL_Color({254, 1, 1});
	m_couleurs["vert"] = new SDL_Color({1, 236, 8});
	m_couleurs["violet"] = new SDL_Color({199, 8, 167});
	m_couleurs["orange"] = new SDL_Color({254, 151, 16});
}

void Jeu::initialiserScores() {
    m_scores[0].couleur(m_couleurs["rouge"]);
    m_scores[1].couleur(m_couleurs["jaune"]);
    m_scores[2].couleur(m_couleurs["orange"]);
    m_scores[3].couleur(m_couleurs["vert"]);
    m_scores[4].couleur(m_couleurs["violet"]);
    m_scores[5].couleur(m_couleurs["bleu"]);

    SDL_Rect position = {m_largeur - m_largeurScores +10, 10};
    int pas = (m_hauteur-20)/6;
    for (int i=0; i<6; i++) {
        m_scores[i].police(m_policeCalligraphiee);
    	m_scores[i].position(position);
    	position.y+= pas;
    }
}

void Jeu::afficherEcranPrincipal() {
	effacer();

	TexteSDL texte("Achtung, die Kurve !", m_policeCalligraphiee, m_couleurs["blanc"]);
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

			default:
				break;
			}
		}
	}
	afficher(MENU_PRINCIPAL);
}

void Jeu::creerMenuPrincipal() {
	m_optionJoueurs[0] = new Option("(1 A)", "READY", "", m_policeBasique,
				m_couleurs["rouge"]);
	m_optionJoueurs[1] = new Option("(X C)", "READY", "", m_policeBasique,
				m_couleurs["jaune"]);
	m_optionJoueurs[2] = new Option("(, ;)", "READY", "", m_policeBasique,
				m_couleurs["orange"]);
	m_optionJoueurs[3] = new Option("(L.Arrow D.Arrow)", "READY", "", m_policeBasique,
				m_couleurs["vert"]);
	m_optionJoueurs[4] = new Option("(/ *)", "READY", "", m_policeBasique,
				m_couleurs["violet"]);
	m_optionJoueurs[5] = new Option("(L.Mouse R.Mouse)", "READY", "", m_policeBasique,
				m_couleurs["bleu"]);

	SDL_Rect position = {50, 50},
			positionEtat = {450, 50};
	m_optionJoueurs[0]->position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	m_optionJoueurs[1]->position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	m_optionJoueurs[2]->position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	m_optionJoueurs[3]->position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	m_optionJoueurs[4]->position(position, positionEtat);
	position.y+= 50;
	positionEtat.y+= 50;
	m_optionJoueurs[5]->position(position, positionEtat);
}

void Jeu::afficherMenuPrincipal() {
	effacer();

	TexteSDL options("Configurer les options de jeu (O)", m_policeBasique,
			m_couleurs["blanc"]);
	SDL_Rect position = {50, 400};
	options.position(position);

    for (int i=0; i<6; i++) {
        m_optionJoueurs[i]->afficher(m_ecran);
    }
	options.afficher(m_ecran);
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

			case SDLK_SPACE:
				m_ecranAAfficher = JEU;
				boucler = false;
				break;

			case SDLK_AMPERSAND:
				m_optionJoueurs[0]->activer();
				m_optionJoueurs[0]->afficher(m_ecran);
				break;

			case SDLK_a:
				m_optionJoueurs[0]->desactiver();
				m_optionJoueurs[0]->afficher(m_ecran);
				break;

			case SDLK_x:
				m_optionJoueurs[1]->activer();
				m_optionJoueurs[1]->afficher(m_ecran);
				break;

			case SDLK_c:
				m_optionJoueurs[1]->desactiver();
				m_optionJoueurs[1]->afficher(m_ecran);
				break;

			case SDLK_COMMA:
				m_optionJoueurs[2]->activer();
				m_optionJoueurs[2]->afficher(m_ecran);
				break;

			case SDLK_SEMICOLON:
				m_optionJoueurs[2]->desactiver();
				m_optionJoueurs[2]->afficher(m_ecran);
				break;

			case SDLK_SLASH:
				m_optionJoueurs[4]->activer();
				m_optionJoueurs[4]->afficher(m_ecran);
				break;

			case SDLK_ASTERISK:
				m_optionJoueurs[4]->desactiver();
				m_optionJoueurs[4]->afficher(m_ecran);
				break;

			case SDLK_o:
				m_ecranAAfficher = MENU_OPTIONS;
				boucler = false;
				break;

			default:
				break;
			}

			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				m_optionJoueurs[3]->activer();
				m_optionJoueurs[3]->afficher(m_ecran);
				break;

			case SDLK_DOWN:
				m_optionJoueurs[3]->desactiver();
				m_optionJoueurs[3]->afficher(m_ecran);
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				m_optionJoueurs[5]->activer();
				m_optionJoueurs[5]->afficher(m_ecran);
				break;

			case SDL_BUTTON_RIGHT:
				m_optionJoueurs[5]->desactiver();
				m_optionJoueurs[5]->afficher(m_ecran);
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
	afficher(m_ecranAAfficher);
}

void Jeu::creerMenuOptions() {
	Option *option1 = new Option("jouer (P)", "oui", "non",
			m_policeBasique, m_couleurs["blanc"]),
			*option2 = new Option("jouer par equipe (E)", "oui", "non",
					m_policeBasique, m_couleurs["blanc"]),
			*info = new Option("jouer par equipe (T)", "oui", "non",
					m_policeBasique, m_couleurs["blanc"]);
	SDL_Rect position = {100, 50};
	option1->position(position);
	position.y+= 50;
	option2->position(position);
	position.y+= 50;
	info->position(position);

	m_options.push_back(option1);
	m_options.push_back(option2);
	m_options.push_back(info);SDL_FillRect(m_ecran, NULL,
			SDL_MapRGB(m_ecran->format, 0, 0, 0));
}

void Jeu::afficherMenuOptions() {
	effacer();

	vector<Option*>::iterator it = m_options.begin(),
			end = m_options.end();
	for ( ; it!=end; it++) {
		(*it)->afficher(m_ecran);
	}

	TexteSDL retour("Retour au menu principal (space)",
			m_policeBasique, m_couleurs["blanc"]);
	SDL_Rect position = {100, 200};
	retour.position(position);
	retour.afficher(m_ecran);

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

			case SDLK_SPACE:
				m_ecranAAfficher = MENU_PRINCIPAL;
				boucler = false;
				break;

			case SDLK_p:
				m_options[0]->echanger();
				m_options[0]->afficher(m_ecran);
				break;

			case SDLK_e:
				m_options[1]->echanger();
				m_options[1]->afficher(m_ecran);
				break;

			case SDLK_t:
				m_options[2]->echanger();
				m_options[2]->afficher(m_ecran);
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
	afficher(m_ecranAAfficher);
}

void Jeu::afficherJeu() {
	effacer();

	m_ecranScores = SDL_CreateRGBSurface(SDL_HWSURFACE,
				m_largeurScores, m_hauteur, 32, 0, 0, 0, 0);
	m_ecranJeu = SDL_CreateRGBSurface(SDL_HWSURFACE,
				m_largeur - m_largeurScores, m_hauteur, 32, 0, 0, 0, 0);

	SDL_FillRect(m_ecranJeu, NULL,
		SDL_MapRGB(m_ecran->format, 0, 0, 0));
	SDL_FillRect(m_ecranScores, NULL,
		SDL_MapRGB(m_ecran->format, 128, 128, 128));

	SDL_Rect position = {0,0};
	SDL_BlitSurface(m_ecranJeu, NULL, m_ecran, &position);
	position.x = m_largeur - m_largeurScores;
	SDL_BlitSurface(m_ecranScores, NULL, m_ecran, &position);

	for (int i=0; i<6; i++) {
		m_scores[i].contenu("99");
		m_scores[i].afficher(m_ecran);
	}
	SDL_Flip(m_ecran);

	SDL_Event event;
	bool boucler = true;
	int utilisationRetour = 0;
	while (boucler) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.unicode) {
			case SDLK_ESCAPE:
				return;

			case SDLK_BACKSPACE:
				if (++utilisationRetour>2) {
					boucler = false;
					m_ecranAAfficher = ACCUEIL;
				}
				break;

			default:
				break;
			}

		default:
			break;
		}
	}
	afficher(m_ecranAAfficher);
}

void Jeu::afficher(NomEcran ecran) {
	switch(ecran) {
	case ACCUEIL:
		afficherEcranPrincipal();
		break;

	case MENU_PRINCIPAL:
		afficherMenuPrincipal();
		break;

	case MENU_OPTIONS:
		afficherMenuOptions();
		break;

	case JEU:
		afficherJeu();
		break;

	default:
		break;
	}
}

void Jeu::effacer() {
	SDL_FillRect(m_ecran, NULL,
		SDL_MapRGB(m_ecran->format, 0, 0, 0));
}
