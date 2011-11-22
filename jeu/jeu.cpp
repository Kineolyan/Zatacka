#include "jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu(int largeurJeu, int largeurScores, int hauteur):
		ItemEcran(largeurJeu, hauteur),
		m_largeurScores(largeurScores),
		m_ecranJeu(largeurJeu, hauteur),
		m_ecranScores(largeurScores, hauteur),
		m_couleurs(NULL),
		m_points(7),
		m_scores(6),
		m_joueurs(NULL) {
	m_positionScores.x = m_largeur;
	m_positionScores.y = 0;

	m_ecranJeu.position(m_position);
	m_ecranScores.position(m_positionScores);

	for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		*it = NULL;
	}

	initialiserPoints();
}

Jeu::~Jeu() {
    for (vector<SDL_Surface*>::iterator it = m_points.begin(),
		end = m_points.end() ; it!=end; it++) {
		SDL_FreeSurface(*it);
	}
}

void Jeu::initialiserPoints() {
	for (int i=0; i<7; i++) {
		m_points[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,
			3, 3, 32, 0, 0, 0, 0);

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

int Jeu::largeur()
{   return m_largeur + m_largeurScores; }

/**
 * Remplit une surface de la couleur demandee
 */
void Jeu::colorer(SDL_Surface* ecran, Couleur couleur) {
	SDL_FillRect(ecran, NULL,
		SDL_MapRGB(m_ecranJeu.format(),
			(*m_couleurs)[couleur]->r,
			(*m_couleurs)[couleur]->g,
			(*m_couleurs)[couleur]->b
		)
	);
}

void Jeu::colorerElements(vector<SDL_Color*>* couleurs) {
	m_couleurs = couleurs;

	m_ecranScores.couleur((*m_couleurs)[GRIS]);

	m_scores[0].couleur((*m_couleurs)[ROUGE]);
	m_scores[1].couleur((*m_couleurs)[JAUNE]);
	m_scores[2].couleur((*m_couleurs)[ORANGE]);
	m_scores[3].couleur((*m_couleurs)[VERT]);
	m_scores[4].couleur((*m_couleurs)[VIOLET]);
	m_scores[5].couleur((*m_couleurs)[BLEU]);

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
 * @param position: position du point à tracer
 * @param couleur: nom de la couleur à utiliser
 *
 * @throw TraceImpossible
 */
void Jeu::tracerPoint(SDL_Surface* ecran, SDL_Rect* position, Couleur couleur) {
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
 *
 * @throw TraceImpossible
 */
void Jeu::changerScore(int joueurId, int score) {
    stringstream convertisseur;
    convertisseur << score;
    m_scores[joueurId].contenu(convertisseur.str());
}

void Jeu::demarrerPartie(SDL_Surface* ecran) {
    afficherJeu(ecran);

    int i = 0, end = m_scores.size();
    for ( ; i<end; i++) {
		changerScore(i, 0);
	}
	afficherScores(ecran);
}

void Jeu::demarrerManche(SDL_Surface* ecran) {
    afficherJeu(ecran);
}
