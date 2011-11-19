/*
 * texte.h
 *
 *  Created on: 6 nov. 2011
 *      Author: oliv
 */

#ifndef TEXTE_H_
#define TEXTE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include "itemEcran.h"
#include "../exceptions/exception.h"

class TexteSDL: public ItemEcran {
protected:
	std::string m_contenu;
	TTF_Font* m_police;
	SDL_Color* m_couleur;
	SDL_Surface* m_texte;
	bool m_surfaceAJour;

public:
	TexteSDL();
	TexteSDL(std::string contenu, TTF_Font* police, SDL_Color* couleur);
	TexteSDL(std::string contenu, TTF_Font* police,
			SDL_Color* couleur, const SDL_Rect& position);
	~TexteSDL();

	int largeur();
	int hauteur();
	SDL_Surface* texte();
	void contenu(std::string contenu);
	void police(TTF_Font* police);
	void couleur(SDL_Color* couleur);
	void position(const SDL_Rect& position);

	virtual void afficher(SDL_Surface* ecran);
};

#endif /* TEXTE_H_ */
