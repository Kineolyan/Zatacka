#include "jeu.h"
#include "zatacka.h"
#include <iostream>

using namespace std;

Jeu::Jeu(Zatacka& jeu, int largeurJeu, int largeurScores, int hauteur)
	throw(InstanceManquante):
		ItemEcran(largeurJeu, hauteur),
		m_jeu(jeu),
		m_largeurScores(largeurScores),
		m_ecranJeu(largeurJeu, hauteur),
		m_ecranScores(largeurScores, hauteur),
		m_joueurs(6),
		m_points(7),
		m_scores(6),
		m_nbJoueursActifs(0) {
	m_positionScores.x = m_largeur;
	m_positionScores.y = 0;

	m_ecranJeu.position(m_position);
	m_ecranScores.position(m_positionScores);

	for (vector<Serpent*>::iterator it = m_joueurs.begin(),
		end = m_joueurs.end() ; it!=end; it++) {
		*it = NULL;
	}

	for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		*it = NULL;
	}
}

Jeu::~Jeu() {
    for (vector<Serpent*>::iterator it = m_joueurs.begin(),
		end = m_joueurs.end() ; it!=end; it++) {
		delete *it;
	}

    for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		SDL_FreeSurface(*it);
	}
}

void Jeu::ajouterAudio(Audio audio){
  m_audio = audio;
}

void Jeu::initialiser() {
	initialiserPoints();
    colorerElements();
    initialiserJoueurs();
    initialiserScores();
}

void Jeu::initialiserJoueurs() throw(InstanceManquante) {
    int index = 0;
    vector<Serpent*>::iterator it = m_joueurs.begin(),
    		end = m_joueurs.end();
	try {
		for ( ; it!=end; it++) {
			*it = new Serpent((Couleur)index, 1, m_jeu);

			if (NULL==*it) {
				throw InstanceManquante(
						"Impossible de creer un motif de trace");
			}
			++index;
		}
	}
	catch (const exception& e) {
		vector<Serpent*>::iterator deleter = m_joueurs.begin();
		for ( ; deleter!=it; ++deleter) {
			delete *deleter;
		}
		m_joueurs.clear();
		throw;
	}
}

void Jeu::initialiserPoints() throw(InstanceManquante) {
	for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		*it = SDL_CreateRGBSurface(SDL_HWSURFACE,
			TAILLE_SERPENT, TAILLE_SERPENT, 32, 0, 0, 0, 0);

		if (NULL==*it) {
			for (vector<SDL_Surface*>::iterator deleter = m_points.begin();
					deleter!=it; ++deleter) {
				SDL_FreeSurface(*deleter);
			}
			m_points.clear();
			throw InstanceManquante(
					"Impossible de creer un motif de trace");
		}
	}
}

void Jeu::initialiserScores() throw() {
    SDL_Rect position = {10, 10};
    TTF_Font* police = m_jeu.policeCalligraphiee();

    int pas = (m_hauteur-20)/m_scores.size();
    for (vector<TexteSDL>::iterator score = m_scores.begin(),
    		end = m_scores.end(); score!=end; ++score) {
    	score->contenu("0");
    	score->police(police);
    	score->position(position);
    	position.y+= pas;
    }
}

int Jeu::largeur() const throw()
{   return m_largeur + m_largeurScores; }

Serpent* Jeu::joueur(int i) throw()
{   return m_joueurs[i]; }

/**
 * Remplit une surface de la couleur demandee
 */
void Jeu::colorer(SDL_Surface* ecran, Couleur couleur) throw() {
	SDL_FillRect(ecran, NULL,
		SDL_MapRGB(m_ecranJeu.format(),
			m_jeu.couleur(couleur)->r,
			m_jeu.couleur(couleur)->g,
			m_jeu.couleur(couleur)->b
		)
	);
}

void Jeu::colorerElements() throw() {
	m_ecranScores.couleur(m_jeu.couleur(GRIS));

	m_scores[ROUGE].couleur(m_jeu.couleur(ROUGE));
	m_scores[JAUNE].couleur(m_jeu.couleur(JAUNE));
	m_scores[ORANGE].couleur(m_jeu.couleur(ORANGE));
	m_scores[VERT].couleur(m_jeu.couleur(VERT));
	m_scores[VIOLET].couleur(m_jeu.couleur(VIOLET));
	m_scores[BLEU].couleur(m_jeu.couleur(BLEU));

	colorer(m_points[ROUGE], ROUGE);
	colorer(m_points[JAUNE], JAUNE);
	colorer(m_points[ORANGE], ORANGE);
	colorer(m_points[VERT], VERT);
	colorer(m_points[VIOLET], VIOLET);
	colorer(m_points[BLEU], BLEU);
	colorer(m_points[NOIR], NOIR);
}

void Jeu::afficher(SDL_Surface* ecran) {
	afficherJeu(ecran);
	afficherScores(ecran);
}

void Jeu::afficherJeu(SDL_Surface* ecran) {
	m_ecranJeu.afficher(ecran);
}

void Jeu::afficherScores(SDL_Surface* ecran) {
    m_ecranScores.effacer();

    int indexJoueur = 0;
	for (vector<TexteSDL>::iterator it = m_scores.begin(),
		end = m_scores.end() ; it!=end; it++) {
		if (m_joueurs[indexJoueur]->actif()) {
			it->afficher(m_ecranScores.ecran());
		}
		++indexJoueur;
	}
	m_ecranScores.afficher(ecran);
}

/**
 * Dessine un point d'une couleur donnée sur l'écran de jeu.
 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
 * sur un autre écran lancera une exception.
 *
 * @param ecran: ecran sur lequel on trace le point
 * @param position: position du point à tracer
 * @param couleur: nom de la couleur à utiliser
 *
 * @throw TraceImpossible
 */
void Jeu::tracerPoint(SDL_Surface* ecran, SDL_Rect* position,
		Couleur couleur) const throw(TraceImpossible) {
	if (position->x <0 || position->x >m_largeur - TAILLE_SERPENT) {
        cerr << position->x << " - " << position->y << endl;
		throw TraceImpossible("La position (largeur) est hors du cadre.");
	}

	if (position->y <0 || position->y >m_hauteur - TAILLE_SERPENT) {
		cerr << position->x << " - " << position->y << endl;
		throw TraceImpossible("La position (hauteur) est hors du cadre.");
	}

	SDL_BlitSurface(m_points[couleur], NULL, ecran, position);
}

/**
 * Met à jour le score d'un joueur
 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
 * sur un autre écran lancera une exception.
 *
 * @param couleurJoueur: Couleur du joueur dont le score change. Cela
 * 	correspond à l'index du texte de score dans le vecteur m_scores
 * @param score: le nouveau score à afficher
 */
void Jeu::changerScore(Couleur couleurJoueur, int score) throw() {
    stringstream convertisseur;
    convertisseur << score;
    m_scores[couleurJoueur].contenu(convertisseur.str());
}

/**
 * Démarre une partie de zatacka
 * On affiche l'écran de jeu (vide) et on remet les scores à 0
 * avant de les afficher.
 *
 * @param nombreJoueurs: nombre de joueurs qui vont jouer la partie
 */
void Jeu::demarrerPartie(int nombreJoueurs) {
	m_nbJoueursActifs = nombreJoueurs;
	m_audio.actualiserNombreJoueurs(m_nbJoueursActifs);

    afficherJeu(m_jeu.ecran());

    for (vector<Serpent*>::iterator joueur = m_joueurs.begin(),
			end = m_joueurs.end(); joueur<end; ++joueur) {
		(*joueur)->reset();
	}
	m_jeu.afficherScores();
  m_audio.commencerPartie();
}

bool Jeu::jouerManche() {
    afficherJeu(m_jeu.ecran());

    vector<pair<int, int> > positionsDepart = m_jeu.positionsDepart();
    vector<double> directionsDepart = m_jeu.directionsDepart();
    int indexJoueur = 0;
    for (vector<Serpent*>::iterator joueur = m_joueurs.begin(),
    		end = m_joueurs.end(); joueur<end; ++joueur) {
    	(*joueur)->placer(
			positionsDepart[indexJoueur].first,
			positionsDepart[indexJoueur].second,
			directionsDepart[indexJoueur]
		);
    	++indexJoueur;
    }

    SDL_Event eventJeu;
    bool bouclerManche = true;
    int nombreJoueursVivants = m_nbJoueursActifs,
    	tempsActuel, tempsPrecedent = 0;
    Uint8* etatTouches = NULL;
    while (bouclerManche) {
		SDL_PollEvent(&eventJeu);
		switch (eventJeu.type) {
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			switch (eventJeu.key.keysym.unicode) {
			case SDLK_ESCAPE:
				return false;

			default:
				break;
			}
			break;

		default:
			break;
		}

    	tempsActuel = SDL_GetTicks();
    	if (tempsActuel - tempsPrecedent>=15) {
    		etatTouches = SDL_GetKeyState(NULL);

            #if defined(WIN32) || defined(WIN64)
			if (etatTouches[SDLK_1]) {
				m_joueurs[0]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_q]) {
				m_joueurs[0]->seDirigeVers(DROITE);
			}
			#else
			if (etatTouches[SDLK_AMPERSAND]) {
				m_joueurs[0]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_a]) {
				m_joueurs[0]->seDirigeVers(DROITE);
			}
			#endif

			if (etatTouches[SDLK_x]) {
				m_joueurs[1]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_c]) {
				m_joueurs[1]->seDirigeVers(DROITE);
			}

			#if defined(WIN32) || defined(WIN64)
			if (etatTouches[SDLK_m]) {
				m_joueurs[2]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_COMMA]) {
				m_joueurs[2]->seDirigeVers(DROITE);
			}
			#else
			if (etatTouches[SDLK_COMMA]) {
				m_joueurs[2]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_SEMICOLON]) {
				m_joueurs[2]->seDirigeVers(DROITE);
			}
			#endif

			if (etatTouches[SDLK_KP_DIVIDE]) {
				m_joueurs[4]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_KP_MULTIPLY]) {
				m_joueurs[4]->seDirigeVers(DROITE);
			}

			if (etatTouches[SDLK_LEFT]) {
				m_joueurs[3]->seDirigeVers(GAUCHE);
			}
			else if (etatTouches[SDLK_DOWN]) {
				m_joueurs[3]->seDirigeVers(DROITE);
			}

			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) {
				m_joueurs[5]->seDirigeVers(GAUCHE);
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3)) {
				m_joueurs[5]->seDirigeVers(DROITE);
			}

			for (int indexJoueur = 0, end = m_joueurs.size();
					indexJoueur <end; ++indexJoueur) {
				if (!m_joueurs[indexJoueur]->avance()) {
					--nombreJoueursVivants;
					actualiserScores(indexJoueur);
				}
			}
			tempsPrecedent = tempsActuel;
		}
		else {
			SDL_Delay(15 - (tempsActuel - tempsPrecedent));
		}

		if (nombreJoueursVivants<2) {
			bouclerManche = false;
		}
	}
	for (int i=0, end = m_joueurs.size(); i<end; ++i) {
    m_audio.actualiserMeilleurScore(m_joueurs[i]->score());
  }
    return true;
}

void Jeu::actualiserScores(int indexPerdant) {
	const vector<int>& scores = m_jeu.donnerScores(indexPerdant);
	for (int i=0, end = m_joueurs.size(); i<end; ++i) {
		m_joueurs[i]->gagnePoints(scores[i]);
	}

	m_jeu.afficherScores();
}
