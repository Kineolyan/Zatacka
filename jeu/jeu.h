/*
 * jeu.h
 *
 *  Created on: 3 nov. 2011
 *      Author: oliv
 */

#ifndef JEU_H_
#define JEU_H_

#include <SDL.h>
#include <map>
#include "texte.h"
#include "option.h"
#include "../exceptions/exception.h"

class Jeu {
protected:
	int m_largeur;
	int m_hauteur;
	SDL_Surface* m_ecran;
	TTF_Font* m_policeCalligraphiee;
	TTF_Font* m_policeBasique;
	std::map<std::string, SDL_Color*> m_couleurs;

	void chargerPolices();
	void initialiserCouleurs();

	void afficherEcranPrincipal();
	void afficherMenuPrincipal();
	void afficherMenuOptions();

public:
	Jeu(int widht, int hauteur);
	~Jeu();
};

#endif /* JEU_H_ */
