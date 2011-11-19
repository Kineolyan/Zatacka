/*
 * jeu.h
 *
 *  Created on: 3 nov. 2011
 *      Author: oliv
 */

#ifndef JEU_H_
#define JEU_H_

#include <SDL/SDL.h>

#include "itemEcran.h"
#include "texte.h"
#include "couleurs.h"
#include "zatacka.h"
#include "../serpent/serpent.h"

class Jeu: public ItemEcran {
private:
	/**
	 * Largeur du panneau des scores
	 */
	int m_largeurScores;

	/**
	 * Position des scores à l'écran
	 */
	SDL_Rect m_positionScores;

	/**
	 * Ecran principal du jeu
	 */
	Zatacka& m_ecranPrincipal;

	/**
	 * Ecran de jeu contenant les serpents
	 */
	SDL_Surface* m_ecranJeu;

	/**
	 * Ecran affichant les scores
	 */
	SDL_Surface* m_ecranScores;

	/**
	 * Motifs de base pour le trace des serpents
	 */
	SDL_Surface* m_points[6];

	/**
	 * Tableau des textes affichant les scores sur l'écran
	 * de jeu
	 */
	TexteSDL m_scores[6];

	/**
	 * Tableau des serpents des joueurs
	 */
	Serpent* m_joueurs;

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserPoints();

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserScores();

public:
	Jeu(Zatacka& ecranPrincipal, int largeurScore=100);
	~Jeu();

	virtual void afficher(SDL_Surface* ecran);
	void afficherJeu(SDL_Surface* ecran);
	void afficherScores(SDL_Surface* ecran);
	void demarrerManche();

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
	void tracerPoint(SDL_Rect* position, Couleur couleur);

	/**
	 * Renvoie la couleur des pixels d'une position donnee
	 */
	//Couleur donnerCouleurs(const SDL_Rect& position);

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
	void changerScore(int joueurId, int score);
};

#endif /* JEU_H_ */
