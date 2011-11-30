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
	/**
	 * Constructeur par défaut
	 */
	ItemEcran();

	/**
	 * Constructeur
	 *
	 * @param largeur: largeur de l'écran
	 * @param hauteur: hauteur de l'écran
	 */
	ItemEcran(int largeur, int hauteur);

	/**
	 * Constructeur
	 *
	 * @param position: position de l'écran
	 */
	ItemEcran(const SDL_Rect& position);

	/**
	 * Constructeur
	 *
	 * @param largeur: largeur de l'écran
	 * @param hauteur: hauteur de l'écran
	 * @param position: position de l'écran
	 */
	ItemEcran(int largeur, int hauteur, const SDL_Rect& position);

	ItemEcran& operator=(const ItemEcran&);

	/* -- Accesseurs et mutateurs -- */
	int hauteur() const throw();
	int largeur() const throw();
	SDL_Rect position() const throw();
	void position(const SDL_Rect& position) throw();

	/**
	 * Affiche l'item sur l'écran de destination
	 */
	virtual void afficher(SDL_Surface* ecran)=0;
};

#endif /* ITEMECRAN_H_ */
