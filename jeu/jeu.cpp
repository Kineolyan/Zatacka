#include "jeu.h"

using namespace std;

Jeu::Jeu(Zatacka& ecranPrincipal, int largeurScores):
		ItemEcran(ecranPrincipal.largeur(),ecranPrincipal.hauteur()),
		m_largeurScores(largeurScores),
		m_ecranPrincipal(ecranPrincipal),
		m_ecranJeu(NULL), m_ecranScores(NULL) {
	m_ecranJeu = SDL_CreateRGBSurface(SDL_HWSURFACE,
			m_largeur - m_largeurScores, m_hauteur, 32, 0, 0, 0, 0);
	m_ecranScores = SDL_CreateRGBSurface(SDL_HWSURFACE,
			m_largeurScores, m_hauteur, 32, 0, 0, 0, 0);

	m_positionScores.x = m_largeur - m_largeurScores;
	m_positionScores.y = 0;

	for (int i=0; i<6; i++) {
		m_points[i] = NULL;
	}

	if (NULL==m_ecranJeu) {
		throw InstanceManquante("Impossible de creer l'ecran de jeu");
	}
	if (NULL==m_ecranScores) {
		throw InstanceManquante(
				"Impossible de creer le panneau des scores");
	}

	initialiserScores();
	initialiserPoints();
}

Jeu::~Jeu() {
    SDL_FreeSurface(m_ecranJeu);
    SDL_FreeSurface(m_ecranScores);

    for (int i=0; i<8; i++) {
    	SDL_FreeSurface(m_points[i]);
    }
}

void Jeu::initialiserPoints() {

	for (int i=0; i<8; i++) {
		m_points[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,
			4, 4, 32, 0, 0, 0, 0);

		if (NULL==m_points[i]) {
			throw InstanceManquante("Impossible de creer un motif de trace");
		}
	}

	m_ecranPrincipal.colorer(m_points[ROUGE], ROUGE);
	m_ecranPrincipal.colorer(m_points[JAUNE], JAUNE);
	m_ecranPrincipal.colorer(m_points[ORANGE], ORANGE);
	m_ecranPrincipal.colorer(m_points[VERT], VERT);
	m_ecranPrincipal.colorer(m_points[VIOLET], VIOLET);
	m_ecranPrincipal.colorer(m_points[BLEU], BLEU);
	m_ecranPrincipal.colorer(m_points[BLANC], BLANC);
	m_ecranPrincipal.colorer(m_points[NOIR], NOIR);
}

void Jeu::initialiserScores() {
    m_scores[0].couleur(m_ecranPrincipal.couleur(ROUGE));
    m_scores[1].couleur(m_ecranPrincipal.couleur(JAUNE));
    m_scores[2].couleur(m_ecranPrincipal.couleur(ORANGE));
    m_scores[3].couleur(m_ecranPrincipal.couleur(VERT));
    m_scores[4].couleur(m_ecranPrincipal.couleur(VIOLET));
    m_scores[5].couleur(m_ecranPrincipal.couleur(BLEU));

    SDL_Rect position = {m_largeur - m_largeurScores +10, 10};
    int pas = (m_hauteur-20)/6;
    for (int i=0; i<6; i++) {
        m_scores[i].police(m_ecranPrincipal.policeCalligraphiee());
    	m_scores[i].position(position);
    	position.y+= pas;
    }
}

void Jeu::afficher(SDL_Surface* ecran) {
	afficherJeu(ecran);
	afficherScores(ecran);
}

void Jeu::afficherJeu(SDL_Surface* ecran) {
	SDL_BlitSurface(m_ecranJeu, NULL, ecran, &m_position);
}

void Jeu::afficherScores(SDL_Surface* ecran) {
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
	SDL_BlitSurface(m_points[couleur], NULL, m_ecranJeu, position);
}
