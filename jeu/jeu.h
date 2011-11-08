/*
 * jeu.h
 *
 *  Created on: 3 nov. 2011
 *      Author: oliv
 */

#ifndef JEU_H_
#define JEU_H_

#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdexcept>
#include "texte.h"

class Jeu {
protected:
	int m_largeur;
	int m_hauteur;
	SDL_Surface* m_ecran;
	TTF_Font* m_policeCalligraphiee;
	TTF_Font* m_policeBasique;

	void chargerPolices();

	void afficherEcranPrincipal();
	void afficherMenuPrincipal();

public:
	Jeu(int widht, int hauteur);
	~Jeu();
};

#endif /* JEU_H_ */
