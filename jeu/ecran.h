/*
 * ecran.h
 *
 *  Created on: 21 nov. 2011
 *      Author: oliv
 */

#ifndef ECRAN_H_
#define ECRAN_H_

#include <SDL/SDL.h>

#include "../exceptions/exception.h"
#include "itemEcran.h"

class Ecran: public ItemEcran {
protected:
	SDL_Surface* m_ecran;

	SDL_Color m_couleur;

	void colorer();

public:
	Ecran(int largeur =0, int hauteur =0);
	Ecran(int largeur, int hauteur, SDL_Color* couleur);
	~Ecran();

    SDL_PixelFormat* format();
    SDL_Surface* ecran();
	void couleur(SDL_Color* couleur);
	virtual void afficher(SDL_Surface* ecran);
	void effacer();
	void redimensionner(int largeur, int hauteur);
};

#endif /* ECRAN_H_ */
