#include "jeu.h"
#include "zatacka.h"

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
		m_scores(6) {
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

	initialiserPoints();
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

void Jeu::initialiserJoueurs() throw(InstanceManquante) {
    int index = 0;
	for (vector<Serpent*>::iterator it = m_joueurs.begin(),
		end = m_joueurs.end() ; it!=end; it++) {
		*it = new Serpent((Couleur)index, 100 + index*20,
                    100 + index*10, -0.3, 1, m_jeu);

		if (NULL==*it) {
			throw InstanceManquante(
					"Impossible de creer un motif de trace");
		}
		++index;
	}
}

void Jeu::initialiserPoints() throw(InstanceManquante) {
	for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		*it = SDL_CreateRGBSurface(SDL_HWSURFACE,
			3, 3, 32, 0, 0, 0, 0);

		if (NULL==*it) {
			throw InstanceManquante(
					"Impossible de creer un motif de trace");
		}
	}
}

void Jeu::initialiserScores() throw() {
    SDL_Rect position = {10, 10};
    TTF_Font* police = m_jeu.policeCalligraphiee();

    int pas = (m_hauteur-20)/6;
    for (int i=0; i<6; i++) {
    	m_scores[i].contenu("0");
        m_scores[i].police(police);
    	m_scores[i].position(position);
    	position.y+= pas;
    }
}

int Jeu::largeur() const throw()
{   return m_largeur + m_largeurScores; }

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

	m_scores[0].couleur(m_jeu.couleur(ROUGE));
	m_scores[1].couleur(m_jeu.couleur(JAUNE));
	m_scores[2].couleur(m_jeu.couleur(ORANGE));
	m_scores[3].couleur(m_jeu.couleur(VERT));
	m_scores[4].couleur(m_jeu.couleur(VIOLET));
	m_scores[5].couleur(m_jeu.couleur(BLEU));

	colorer(m_points[0], ROUGE);
	colorer(m_points[1], JAUNE);
	colorer(m_points[2], ORANGE);
	colorer(m_points[3], VERT);
	colorer(m_points[4], VIOLET);
	colorer(m_points[5], BLEU);
	colorer(m_points[6], NOIR);
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

	for (vector<TexteSDL>::iterator it = m_scores.begin(),
		end = m_scores.end() ; it!=end; it++) {
		it->afficher(m_ecranScores.ecran());
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
	if (position->x <0 || position->x >m_largeur) {
		throw TraceImpossible("La position est hors du cadre.");
	}

	if (position->y <0 || position->y >m_hauteur) {
		throw TraceImpossible("La position (hauteur) est hors du cadre.");
	}

	SDL_BlitSurface(m_points[couleur], NULL, ecran, position);
}

/**
 * Met à jour le score d'un joueur
 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
 * sur un autre écran lancera une exception.
 *
 * @param joueurId: Id du joueur dont le score change. Cela correspond
 * 	a l'index du texte de score dans le vecteur m_scores
 * @param score: le nouveau score à afficher
 */
void Jeu::changerScore(int joueurId, int score) throw() {
    stringstream convertisseur;
    convertisseur << score;
    m_scores[joueurId].contenu(convertisseur.str());
}

/**
 * Démarre une partie de zatacka
 * On affiche l'écran de jeu (vide) et on remet les scores à 0
 * avant de les afficher.
 *
 * @param ecran: écran sur lequel on affiche la partie
 */
void Jeu::demarrerPartie() {
    afficherJeu(m_jeu.ecran());

    int i = 0, end = m_scores.size();
    for ( ; i<end; i++) {
		changerScore(i, 0);
	}
	afficherScores(m_jeu.ecran());
}

bool Jeu::jouerManche() {
	for (int i=0 ; i<180 ; i++) {
	  m_joueurs[0]->avance();
	  m_joueurs[1]->avance();
	  m_joueurs[2]->avance();
	  m_joueurs[3]->avance();
	  m_joueurs[4]->avance();
	  m_joueurs[5]->avance();
	  SDL_Delay(5);
	}

    afficherJeu(m_jeu.ecran());

    SDL_Event eventJeu;
    bool bouclerManche = true;
    while (bouclerManche) {
		SDL_PollEvent(&eventJeu);
		switch (eventJeu.type) {
		case SDL_KEYDOWN:
			switch (eventJeu.key.keysym.unicode) {
			case SDLK_ESCAPE:
				return false;

			case SDLK_BACKSPACE:
				bouclerManche = false;
				break;

			case SDLK_AMPERSAND:
			case SDLK_a:
				//m_joueurs[0].joueur(event);
				break;

			case SDLK_x:
			case SDLK_c:
				//m_joueurs[1].joueur(event);
				break;

			case SDLK_COMMA:
			case SDLK_SEMICOLON:
				//m_joueurs[2].joueur(event);
				break;

			case SDLK_SLASH:
			case SDLK_ASTERISK:
				//m_joueurs[4].joueur(event);
				break;

			default:
				break;
			}

			switch (eventJeu.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_DOWN:
				//m_joueurs[3].joueur(event);
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (eventJeu.button.button) {
			case SDL_BUTTON_LEFT:
			case SDL_BUTTON_RIGHT:
				//m_joueurs[5].joueur(event);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
    return true;
}
