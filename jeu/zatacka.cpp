#include "zatacka.h"
#include <iostream>

using namespace std;

Zatacka::Zatacka(int largeur, int hauteur):
		m_largeur(largeur), m_hauteur(hauteur),
		m_largeurScores(100), m_ecran(NULL),
		m_ecranJeu(*this, largeur - m_largeurScores, m_largeurScores, hauteur, m_audio),
		m_points(8),
		m_policeCalligraphiee(NULL),
		m_policeBasique(NULL),
		m_couleurs(8), m_optionJoueurs(6), m_options(),
		m_nombreJoueurs(6) {
	m_ecran = SDL_SetVideoMode(m_largeur, m_hauteur, 32,
			SDL_SWSURFACE | SDL_DOUBLEBUF/* | SDL_FULLSCREEN*/);
	if (NULL==m_ecran) {
		throw InstanceManquante("Impossible de creer l'ecran");
	}
	SDL_WM_SetCaption("Zatacka", NULL);
	reglerRepetition(2000);

	TTF_Init();
	chargerPolices();
	initialiserCouleurs();
	initialiserJeu();

  m_audio.initialiserAudio();

	creerMenuPrincipal();
	creerMenuOptions();

	afficherAccueil();
}

Zatacka::~Zatacka() {
	TTF_CloseFont(m_policeCalligraphiee);
	TTF_CloseFont(m_policeBasique);


    for (vector<SDL_Color*>::iterator it = m_couleurs.begin(),
        end = m_couleurs.end() ; it!=end; it++) {
        delete *it;
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

void Zatacka::chargerPolices() {
	m_policeCalligraphiee = TTF_OpenFont("SCORE.TTF", 65);
	m_policeBasique = TTF_OpenFont("MENU.TTF", 25);

	if (NULL==m_policeBasique || NULL==m_policeCalligraphiee) {
        throw InstanceManquante("Une des polices n'a pas ete creee.");
	}
}

/**
 * Crée une couleur
 * Le but de cette méthode est d'éviter le warning du compilateur
 *
 * @param r: composante rouge de la couleur
 * @param g: composante verte de la couleur
 * @param b: composante bleue de la couleur
 *
 * @return: la couleur demandée
 */
SDL_Color* Zatacka::creerCouleur(Uint8 r, Uint8 g, Uint8 b) throw() {
    SDL_Color* couleur = new SDL_Color;
    couleur->r = r;
    couleur->g = g;
    couleur->b = b;

    return couleur;
}

void Zatacka::initialiserCouleurs() {
	m_couleurs[BLANC] = creerCouleur(255, 255, 255);
    m_couleurs[JAUNE] = creerCouleur(250, 225, 0);
	m_couleurs[BLEU] = creerCouleur(0, 191, 249);
	m_couleurs[ROUGE] = creerCouleur(254, 1, 1);
	m_couleurs[VERT] = creerCouleur(1, 236, 8);
	m_couleurs[VIOLET] = creerCouleur(254, 47, 254);
	m_couleurs[ORANGE] = creerCouleur(254, 151, 16);
	m_couleurs[NOIR] = creerCouleur(0, 0, 0);
	m_couleurs[GRIS] = creerCouleur(128, 128, 128);
}

void Zatacka::initialiserJeu() {
    m_ecranJeu.colorerElements();
    m_ecranJeu.initialiserJoueurs();
    m_ecranJeu.initialiserScores();
}

void Zatacka::afficherAccueil() {
	effacer();

	TexteSDL texte("Achtung, die Kurve !", m_policeCalligraphiee, m_couleurs[BLANC]);
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
		case SDL_QUIT:
			return;

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

void Zatacka::creerMenuPrincipal() {
	m_optionJoueurs[0] = new Option("(1 A)", "READY", "", m_policeBasique,
				m_couleurs[ROUGE]);
	m_optionJoueurs[1] = new Option("(X C)", "READY", "", m_policeBasique,
				m_couleurs[JAUNE]);
	m_optionJoueurs[2] = new Option("(, ;)", "READY", "", m_policeBasique,
				m_couleurs[ORANGE]);
	m_optionJoueurs[3] = new Option("(L.Arrow D.Arrow)", "READY", "", m_policeBasique,
				m_couleurs[VERT]);
	m_optionJoueurs[4] = new Option("(/ *)", "READY", "", m_policeBasique,
				m_couleurs[VIOLET]);
	m_optionJoueurs[5] = new Option("(L.Mouse R.Mouse)", "READY", "", m_policeBasique,
				m_couleurs[BLEU]);

	int margeHaut = 30, margeBas = 90, margeGauche = 50;
	SDL_Rect position = {margeGauche, margeHaut},
			positionEtat = {m_largeur/2, margeHaut};
	int pas = (m_hauteur - margeHaut - margeBas)/m_optionJoueurs.size();
	for (vector<Option*>::iterator option = m_optionJoueurs.begin(),
			end = m_optionJoueurs.end(); option!=end; ++option) {
		(*option)->position(position, positionEtat);
		position.y+= pas;
		positionEtat.y+= pas;
	}
}

void Zatacka::afficherMenuPrincipal() {
	effacer();

	TexteSDL options("Configurer les options de jeu (O)", m_policeBasique,
			m_couleurs[BLANC]);
	SDL_Rect position = {50, m_hauteur - 80};
	options.position(position);

    for (vector<Option*>::iterator it = m_optionJoueurs.begin(),
            end = m_optionJoueurs.end(); it!=end; it++) {
    	(*it)->afficher(m_ecran);
    }
	options.afficher(m_ecran);
	SDL_Flip(m_ecran);

	// passer à l'étape suivante
	SDL_Event event;
	bool boucler = true;
	while (boucler) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			return;

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

void Zatacka::creerMenuOptions() {
	Option *option1 = new Option("jouer (P)", "oui", "non",
			m_policeBasique, m_couleurs[BLANC]),
			*option2 = new Option("jouer par equipe (E)", "oui", "non",
					m_policeBasique, m_couleurs[BLANC]),
			*option3 = new Option("jouer par equipe (T)", "oui", "non",
					m_policeBasique, m_couleurs[BLANC]);
	SDL_Rect position = {100, 50};
	option1->position(position);
	position.y+= 50;
	option2->position(position);
	position.y+= 50;
	option3->position(position);

	m_options.push_back(option1);
	m_options.push_back(option2);
	m_options.push_back(option3);
}

void Zatacka::afficherMenuOptions() {
	effacer();

	vector<Option*>::iterator it = m_options.begin(),
			end = m_options.end();
	for ( ; it!=end; it++) {
		(*it)->afficher(m_ecran);
	}

	TexteSDL retour("Retour au menu principal (space)",
			m_policeBasique, m_couleurs[BLANC]);
	SDL_Rect position = {100, 400};
	retour.position(position);
	retour.afficher(m_ecran);

	SDL_Flip(m_ecran);

	// passer à l'étape suivante
	SDL_Event event;
	bool boucler = true;
	while (boucler) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			return;

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

void Zatacka::afficherJeu() {
	effacer();

	int indexJoueur = 0, nombreJoueursDansPartie = 0;
	for (vector<Option*>::iterator option = m_optionJoueurs.begin(),
			end = m_optionJoueurs.end(); option!=end; ++option) {
		if ((*option)->active()) {
			m_ecranJeu.joueur(indexJoueur)->activer(true);
			++nombreJoueursDansPartie;
		}
		else {
			m_ecranJeu.joueur(indexJoueur)->activer(false);
		}
		++indexJoueur;
	}
	if (nombreJoueursDansPartie<2) {
        m_ecranAAfficher = MENU_PRINCIPAL;
	}
	else {
        m_ecranJeu.demarrerPartie(nombreJoueursDansPartie);

        SDL_Event eventManche;
        int limiteScore = 10*(nombreJoueursDansPartie-1);
        bool bouclerPartie = true, attendre;
        while (bouclerPartie) {
            if (false==m_ecranJeu.jouerManche()) {
                return;
            }
            SDL_Delay(500);

            attendre = true;
            for (int indexJoueur = 0; indexJoueur<m_nombreJoueurs; ++indexJoueur) {
            	if (m_ecranJeu.joueur(indexJoueur)->score()>=limiteScore) {
            		m_ecranAAfficher = ECRAN_FINAL;
            		attendre = false;
            		bouclerPartie = false;
            		break;
            	}
            }
            while (attendre) {
                SDL_WaitEvent(&eventManche);
                switch (eventManche.type) {
        		case SDL_QUIT:
        			return;

        		case SDL_KEYDOWN:
                    switch (eventManche.key.keysym.unicode) {
                    case SDLK_ESCAPE:
                        return;

                    case SDLK_BACKSPACE:
                            m_ecranAAfficher = ACCUEIL;
                            bouclerPartie = false;
                            attendre = false;
                        break;

                    case SDLK_SPACE:
                        attendre = false;
                        break;

                    default:
                        break;
                    }

                default:
                    break;
                }
            }
        }
	}
	afficher(m_ecranAAfficher);
}

void Zatacka::afficherFin() {
	effacer();

	TexteSDL scoreFinal;
	Serpent* joueur;
	SDL_Rect position = {250, 50};

	scoreFinal.police(m_policeBasique);
	for (int indexJoueur = 0; indexJoueur<m_nombreJoueurs; ++indexJoueur) {
		joueur = m_ecranJeu.joueur(indexJoueur);
		if (joueur->actif()) {
			stringstream ss;
			ss << joueur->score();
			scoreFinal.contenu(ss.str());
			scoreFinal.couleur(m_couleurs[indexJoueur]);
			scoreFinal.position(position);
			scoreFinal.afficher(m_ecran);

			position.y+=50;
		}
	}
	TexteSDL fin("Konec Hry", m_policeCalligraphiee, m_couleurs[BLANC]);
	position.x = (m_largeur - fin.largeur())/2;
	position.y = m_hauteur - 100;
	fin.position(position);
	fin.afficher(m_ecran);
	SDL_Flip(m_ecran);

	bool attendre = true;
	SDL_Event event;
	while (attendre) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			return;

		case SDL_KEYDOWN:
			switch (event.key.keysym.unicode) {
			case SDLK_ESCAPE:
				return;

			case SDLK_SPACE:
				m_ecranAAfficher = ACCUEIL;
				attendre = false;
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

void Zatacka::afficher(NomEcran ecran) {
	switch(ecran) {
	case ACCUEIL:
		resetOptions();
		resetOptionJoueurs();
		afficherAccueil();
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

	case ECRAN_FINAL:
		afficherFin();
		break;

	default:
		break;
	}
}

void Zatacka::effacer() {
	SDL_FillRect(m_ecran, NULL,
		SDL_MapRGB(m_ecran->format, 0, 0, 0));
}

int Zatacka::hauteur() const throw()
{	return m_hauteur;	}

int Zatacka::largeur() const throw()
{	return m_largeur;	}

int Zatacka::hauteurJeu() const throw()
{	return m_hauteur;	}

int Zatacka::largeurJeu() const throw()
{	return m_largeur - m_largeurScores;	}

SDL_Color* Zatacka::couleur(Couleur couleur)
{	return m_couleurs[couleur];	}

TTF_Font* Zatacka::policeCalligraphiee()
{	return m_policeCalligraphiee;	}

TTF_Font* Zatacka::policeBasique()
{	return m_policeBasique;	}

SDL_Surface* Zatacka::ecran()
{	return m_ecran;	}

/**
 * Dessine un point d'une couleur donnée sur l'écran de jeu.
 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
 * sur un autre écran lancera une exception.
 *
 * @param position: position du point à tracer
 * @param couleur: nom de la couleur à utiliser
 *
 * @throw TraceImpossible
 */
void Zatacka::tracerPoint(SDL_Rect* position, Couleur couleur) {
	if (JEU!=m_ecranAAfficher) {
		throw TraceImpossible("impossible de tracer un point hors de l'écran de jeu");
	}

	m_ecranJeu.tracerPoint(m_ecran, position, couleur);
	SDL_Flip(m_ecran);
}

/**
 * Renvoie la couleur des pixels d'une position donnee
 */
Couleur Zatacka::donnerCouleur(const SDL_Rect& position)
        const throw(HorsLimite){
    if (position.x <0 || position.x >m_largeur) {
		throw HorsLimite("Acces a une position hors de l'ecran (largeur)");
	}

	if (position.y <0 || position.y >m_hauteur) {
		throw HorsLimite("Acces a une position hors de l'ecran (hauteur)");
	}

	Uint32 pixel = ((Uint32*)m_ecran->pixels)[position.y * m_ecran->w + position.x];

	SDL_Color couleurPixel = {0, 0, 0};
	SDL_GetRGB(pixel, m_ecran->format,
			&(couleurPixel.r), &(couleurPixel.g), &(couleurPixel.b));

	bool comparaison = false;
	int i = 0;
	for ( ; i<9; i++) {
		if (couleurPixel.r==m_couleurs[i]->r
		 && couleurPixel.g==m_couleurs[i]->g
		 && couleurPixel.b==m_couleurs[i]->b) {
			comparaison = true;
			break;
		}
	}

	if (false==comparaison) {
		throw ExceptionGenerale(
				"La couleur trouvee ne fait pas partie de la liste de couleurs");
	}

	return (Couleur)i;
}

/**
 * Met à jour le score d'un joueur
 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
 * sur un autre écran lancera une exception.
 *
 * @param couleurJoueur: Couleur du joueur dont le score change.
 * @param score: le nouveau score à afficher
 */
void Zatacka::changerScore(Couleur couleurJoueur, int score) throw() {
	m_ecranJeu.changerScore(couleurJoueur, score);
}

void Zatacka::reglerRepetition(int t) {
	if (t<1) {
		t = 1;
	}
	SDL_EnableKeyRepeat(t, t);
}

void Zatacka::afficherScores() throw() {
	m_ecranJeu.afficherScores(m_ecran);
	SDL_Flip(m_ecran);
}

void Zatacka::resetOptions() throw() {
	vector<Option*>::iterator it = m_options.begin(),
			end = m_options.end();
	for ( ; it!=end; it++) {
		(*it)->desactiver();
	}
}

void Zatacka::resetOptionJoueurs() throw() {
	for (vector<Option*>::iterator option = m_optionJoueurs.begin(),
			end = m_optionJoueurs.end(); option!=end; ++option) {
		(*option)->desactiver();
	}
}
