/*
 * regle.h
 *
 *  Created on: 26 nov. 2011
 *      Author: Vince
 */

#ifndef REGLE_H_
#define REGLE_H_

#include <vector>
#include <SDL/SDL.h>
#include "reglepoints.h"
#include "regleinitialisation.h"
#include "reglecollision.h"
#include "../jeu/option.h"

class Regle {
private:

	RegleCollision m_regleCollision;
	RegleInitialisation m_regleInitialisation;
	ReglePoints m_reglePoints;
	bool m_active;
	Option m_option;
	Uint16 m_touche;

public:
	Regle();
	Regle(RegleCollision& reglecollision,
			RegleInitialisation& regleinitialisation,
			ReglePoints& reglepoints);
	Regle(const Regle&);
	~Regle();

	RegleCollision& regleCollision();
	RegleInitialisation& regleInitialisation();
	ReglePoints& reglePoints();

	void option(std::string texte, std::string optionActive,
			std::string optionInactive, TTF_Font* police,
			SDL_Color* couleur, Uint16 touche);
	Option* option();

	void activer();
	void desactiver();
	void echanger();
	bool active();

	void appliquerTouche(Uint16 touche, SDL_Surface* ecran);
};


#endif /* REGLE_H_ */
