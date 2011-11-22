/*
 * jeu.h
 *
 *  Created on: 3 nov. 2011
 *      Author: oliv
 */

#ifndef JEU_H_
#define JEU_H_

#include <SDL/SDL.h>
#include <vector>

#include "itemEcran.h"
#include "texte.h"
#include "couleurs.h"
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
	 * Ecran de jeu contenant les serpents
	 */
	SDL_Surface* m_ecranJeu;

	/**
	 * Ecran affichant les scores
	 */
	SDL_Surface* m_ecranScores;

	/**
	 * Bloc pour effacer un score
	 */
	SDL_Surface* m_blocEffaceur;

	/**
	 * Tableau des couleurs rgb à utiliser
	 */
	std::vector<SDL_Color*>* m_couleurs;

	/**
	 * Motifs de base pour le trace des serpents
	 */
	std::vector<SDL_Surface*> m_points;

	/**
	 * Tableau des textes affichant les scores sur l'écran
	 * de jeu
	 */
	std::vector<TexteSDL> m_scores;

	/**
	 * Tableau des serpents des joueurs
	 */
	std::vector<Serpent>* m_joueurs;

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserPoints();

	void colorer(SDL_Surface* ecran, Couleur couleur);

public:
	Jeu(int largeur, int hauteur, int largeurScore);
	~Jeu();

	void colorerElements(std::vector<SDL_Color*>* couleurs);

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserScores(TTF_Font* police);

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
	void tracerPoint(SDL_Surface* ecran, SDL_Rect* position, Couleur couleur);

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
