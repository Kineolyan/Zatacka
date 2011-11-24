/*
 * ecran.h
 *
 *  Created on: 21 nov. 2011
 *      Author: oliv
 */

#ifndef ECRAN_H_
#define ECRAN_H_

#include <SDL/SDL.h>

#include "../util/exception.h"
#include "itemEcran.h"

class Ecran: public ItemEcran {
protected:
	SDL_Surface* m_ecran;

	SDL_Color m_couleur;

	void colorer() throw();

public:
	Ecran(int largeur =0, int hauteur =0);
	Ecran(int largeur, int hauteur, SDL_Color* couleur);
	~Ecran();

	/* -- Accesseurs et mutateurs -- */
    SDL_PixelFormat* format() const throw();
    SDL_Surface* ecran() const throw();
	void couleur(SDL_Color* couleur) throw();

	/**
	 * Affiche l'écran sur l'écran de destination
	 *
	 * @param ecran: ecran sur lequel on affiche l'instance
	 */
	virtual void afficher(SDL_Surface* ecran);

	/**
	 * Efface l'écran en lui redonnant sa couleur d'origine
	 */
	void effacer() throw();

	/**
	 * Redimensionne l'écran aux nouvelles spécifications
	 * L'écran précédent est libéré et un nouveau est alloué
	 *
	 * @param largeur: nouvelle largeur
	 * @param hauteur: nouvelle hauteur
	 */
	void redimensionner(int largeur, int hauteur) throw();
};

#endif /* ECRAN_H_ */
