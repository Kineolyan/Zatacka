/*
 * option.h
 *
 *  Created on: 8 nov. 2011
 *      Author: oliv
 */

#ifndef OPTION_H_
#define OPTION_H_

#include "ecran.h"
#include "texte.h"
#include <string>

class Option: public Ecran {
protected:
	TexteSDL m_texte;
	TexteSDL m_optionActive;
	TexteSDL m_optionInactive;
	bool m_active;
	int m_offset;

public:
	Option(std::string texte, std::string optionActive,
			std::string optionInactive, TTF_Font* police,
			SDL_Color* couleur);
	~Option();

	void position(const SDL_Rect& position);
	void position(const SDL_Rect& positionOption,
			const SDL_Rect& positionEtat);
	void activer();
	void desactiver();
	void echanger();

	virtual void afficher(SDL_Surface* ecran);
};

#endif /* OPTION_H_ */
