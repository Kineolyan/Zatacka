/*
 * texte.cpp
 *
 *  Created on: 6 nov. 2011
 *      Author: oliv
 */

#include "texte.h"

using namespace std;

/* -- TexteSDL -- */

TexteSDL::TexteSDL(string contenu, int positionX, int positionY):
		m_positionX(positionX), m_positionY(positionY), m_contenu(contenu),
		m_police(NULL), m_couleur(NULL),
		m_texte(NULL), m_surfaceAJour(false)
{}

TexteSDL::TexteSDL(string contenu, TTF_Font* police, SDL_Color* couleur):
		m_positionX(0), m_positionY(0), m_contenu(contenu),
		m_police(police), m_couleur(couleur),
		m_texte(NULL), m_surfaceAJour(false)
{}

TexteSDL::TexteSDL(string contenu, int positionX, int positionY,
		TTF_Font* police, SDL_Color* couleur):
		m_positionX(positionX), m_positionY(positionY), m_contenu(contenu),
		m_police(police), m_couleur(couleur),
		m_texte(NULL), m_surfaceAJour(false)
{}

TexteSDL::~TexteSDL() {
	if (NULL!=m_texte) {
		SDL_FreeSurface(m_texte);
	}
}

void TexteSDL::contenu(string contenu) {
	m_contenu = contenu;
	m_surfaceAJour = false;
}

void TexteSDL::police(TTF_Font* police) {
	m_police = police;
	m_surfaceAJour = false;
}

void TexteSDL::couleur(SDL_Color* couleur) {
	m_couleur = couleur;
	m_surfaceAJour = false;
}

void TexteSDL::position(const SDL_Rect& position) {
	m_positionX = position.x;
	m_positionY = position.y;
	m_surfaceAJour = false;
}

int TexteSDL::largeur() {
	if (false==m_surfaceAJour) {
		texte();
	}
	return m_texte->w;
}

int TexteSDL::hauteur() {
	if (false==m_surfaceAJour) {
		texte();
	}
	return m_texte->h;
}

SDL_Surface* TexteSDL::texte() {
	if (false==m_surfaceAJour) {
		SDL_FreeSurface(m_texte);
		m_texte = TTF_RenderText_Blended(
			m_police, m_contenu.c_str(), *m_couleur);
		m_surfaceAJour = true;
	}

	return m_texte;
}

void TexteSDL::afficher(SDL_Surface* ecran) {
	texte();

	SDL_Rect position = { m_positionX, m_positionY };
	SDL_BlitSurface(m_texte, NULL, ecran, &position);
}

/* -- Option -- */

Option::Option(string texte, string optionActive, string optionInactive,
		TTF_Font* police, SDL_Color* couleur):
		m_texte(texte, police, couleur),
		m_optionActive(optionActive, police, couleur),
		m_optionInactive(optionInactive, police, couleur),
		m_blocEffaceur(NULL),
		m_active(false), m_offset(40)
{}

Option::~Option() {
	SDL_FreeSurface(m_blocEffaceur);
}

void Option::position(const SDL_Rect& position) {
	m_positionOption.x = position.x;
	m_positionOption.y = position.y;
	m_texte.position(m_positionOption);

	m_positionOption.x+= m_offset + m_texte.largeur();
	m_optionActive.position(m_positionOption);
	m_optionInactive.position(m_positionOption);
}

void Option::activer()
{	m_active = true;	}

void Option::desactiver()
{	m_active = false;	}

void Option::echanger()
{	m_active = !m_active;	}

void Option::afficher(SDL_Surface* ecran) {
	if (NULL==m_blocEffaceur) {
		m_blocEffaceur = SDL_CreateRGBSurface(SDL_HWSURFACE,
				m_optionActive.largeur() > m_optionInactive.largeur() ?
						m_optionActive.largeur(): m_optionInactive.largeur(),
				m_optionActive.hauteur(),
				32, 0, 0, 0, 0);
		SDL_FillRect(m_blocEffaceur, NULL,
				SDL_MapRGB(ecran->format, 0, 0, 0));

		m_texte.afficher(ecran);
	}
	SDL_BlitSurface(m_blocEffaceur, NULL, ecran, &m_positionOption);
	if (m_active) {
		m_optionActive.afficher(ecran);
	}
	else {
		m_optionInactive.afficher(ecran);
	}
}
