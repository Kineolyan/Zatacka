#include "jeu.h"

using namespace std;

Jeu::Jeu(int largeur, int hauteur, int largeurScores):
		ItemEcran(largeur, hauteur),
		m_largeurScores(largeurScores),
		m_ecranJeu(NULL), m_ecranScores(NULL),
		m_points(7), m_scores(6), m_joueurs(NULL) {
	m_ecranJeu = SDL_CreateRGBSurface(SDL_HWSURFACE,
			m_largeur - m_largeurScores, m_hauteur, 32, 0, 0, 0, 0);
	m_ecranScores = SDL_CreateRGBSurface(SDL_HWSURFACE,
			m_largeurScores, m_hauteur, 32, 0, 0, 0, 0);

	m_positionScores.x = m_largeur - m_largeurScores;
	m_positionScores.y = 0;

	for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		*it = NULL;
	}

	if (NULL==m_ecranJeu) {
		throw InstanceManquante("Impossible de creer l'ecran de jeu");
	}
	if (NULL==m_ecranScores) {
		throw InstanceManquante(
				"Impossible de creer le panneau des scores");
	}

	initialiserPoints();
}

Jeu::~Jeu() {
    SDL_FreeSurface(m_ecranJeu);
    SDL_FreeSurface(m_ecranScores);

	for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		SDL_FreeSurface(*it);
	}
}

void Jeu::initialiserPoints() {
	for (int i=0; i<7; i++) {
		m_points[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,
			4, 4, 32, 0, 0, 0, 0);

		if (NULL==m_points[i]) {
			throw InstanceManquante(
					"Impossible de creer un motif de trace");
		}
	}
}

void Jeu::initialiserScores(TTF_Font* police) {
    SDL_Rect position = {10, 10};

    int pas = (m_hauteur-20)/6;
    for (int i=0; i<6; i++) {
    	m_scores[i].contenu("0");
        m_scores[i].police(police);
    	m_scores[i].position(position);
    	position.y+= pas;
    }
}

/**
 * Remplit une surface de la couleur demandee
 */
void Jeu::colorer(SDL_Surface* ecran, SDL_Color* couleur,
		SDL_PixelFormat *format) {
	SDL_FillRect(ecran, NULL,
		SDL_MapRGB(format, couleur->r,	couleur->g, couleur->b)
	);
}

void Jeu::colorerElements(const vector<SDL_Color*>& couleurs,
		SDL_PixelFormat *format) {
	m_scores[0].couleur(couleurs[ROUGE]);
	m_scores[1].couleur(couleurs[JAUNE]);
	m_scores[2].couleur(couleurs[ORANGE]);
	m_scores[3].couleur(couleurs[VERT]);
	m_scores[4].couleur(couleurs[VIOLET]);
	m_scores[5].couleur(couleurs[BLEU]);

	colorer(m_ecranScores, couleurs[GRIS], format);
	colorer(m_points[0], couleurs[ROUGE], format);
	colorer(m_points[1], couleurs[JAUNE], format);
	colorer(m_points[2], couleurs[ORANGE], format);
	colorer(m_points[3], couleurs[VERT], format);
	colorer(m_points[4], couleurs[VIOLET], format);
	colorer(m_points[5], couleurs[BLEU], format);
	colorer(m_points[6], couleurs[NOIR], format);
}

void Jeu::afficher(SDL_Surface* ecran) {
	afficherJeu(ecran);
	afficherScores(ecran);
}

void Jeu::afficherJeu(SDL_Surface* ecran) {
	SDL_BlitSurface(m_ecranJeu, NULL, ecran, &m_position);
}

void Jeu::afficherScores(SDL_Surface* ecran) {
	for (vector<TexteSDL>::iterator it = m_scores.begin(),
		end = m_scores.end() ; it!=end; it++) {
		it->afficher(m_ecranScores);
	}
	SDL_BlitSurface(m_ecranScores, NULL, ecran, &m_positionScores);
}

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
void Jeu::tracerPoint(SDL_Rect* position, Couleur couleur) {
	if (position->x <0 || position->x >m_ecranJeu->w) {
		throw TraceImpossible("La position est hors du cadre.");
	}

	if (position->y <0 || position->x >m_hauteur) {
		throw TraceImpossible("La position est hors du cadre.");
	}

	SDL_BlitSurface(m_points[couleur], NULL, m_ecranJeu, position);
}
