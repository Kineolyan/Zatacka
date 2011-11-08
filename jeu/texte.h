/*
 * texte.h
 *
 *  Created on: 6 nov. 2011
 *      Author: oliv
 */

#ifndef TEXTE_H_
#define TEXTE_H_

#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

class TexteSDL {
protected:
	int m_positionX;
	int m_positionY;
	std::string m_contenu;
	TTF_Font* m_police;
	SDL_Color* m_couleur;
	SDL_Surface* m_texte;
	bool m_surfaceAJour;

public:
	TexteSDL(std::string contenu, int positionX, int positionY);
	TexteSDL(std::string contenu, TTF_Font* police, SDL_Color* couleur);
	TexteSDL(std::string contenu, int positionX, int positionY,
			TTF_Font* police, SDL_Color* couleur);
	~TexteSDL();

	void contenu(std::string contenu);
	void police(TTF_Font* police);
	void couleur(SDL_Color* couleur);
	void position(const SDL_Rect& position);
	int largeur();
	int hauteur();
	SDL_Surface* texte();

	void afficher(SDL_Surface* ecran);
};

class Option {
protected:
	TexteSDL m_texte;
	TexteSDL m_optionActive;
	TexteSDL m_optionInactive;
	SDL_Surface* m_blocEffaceur;
	SDL_Rect m_positionOption;
	bool m_active;
	int m_offset;

public:
	Option(std::string texte, std::string optionActive,
			std::string optionInactive, TTF_Font* police,
			SDL_Color* couleur);
	~Option();

	void position(const SDL_Rect& position);
	void activer();
	void desactiver();
	void echanger();

	void afficher(SDL_Surface* ecran);
};

#endif /* TEXTE_H_ */
