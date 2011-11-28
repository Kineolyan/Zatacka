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
#include "../util/exception.h"

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

	int largeur() throw(InstanceManquante);
	int hauteur() throw(InstanceManquante);
	SDL_Surface* texte() throw(InstanceManquante);
	void contenu(std::string contenu) throw();
	void police(TTF_Font* police) throw();
	void couleur(SDL_Color* couleur) throw();
	void position(const SDL_Rect& position) throw();

	virtual void afficher(SDL_Surface* ecran);
};

#endif /* TEXTE_H_ */
