/*
 * itemEcran.h
 *
 *  Created on: 19 nov. 2011
 *      Author: oliv
 */

#ifndef ITEMECRAN_H_
#define ITEMECRAN_H_

#include <SDL/SDL.h>

class ItemEcran {
protected:
	/**
	 * Largeur de la fenetre de jeu, scores compris
	 */
	int m_largeur;

	/**
	 * Hauteur de la fenetre
	 */
	int m_hauteur;

	SDL_Rect m_position;

public:
	ItemEcran();
	ItemEcran(int largeur, int hauteur);
	ItemEcran(const SDL_Rect& position);
	ItemEcran(int largeur, int hauteur, const SDL_Rect& position);

	int hauteur();
	int largeur();
	SDL_Rect position();
	void position(const SDL_Rect& position);

	virtual void afficher(SDL_Surface* ecran)=0;
};

#endif /* ITEMECRAN_H_ */
