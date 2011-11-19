#include "texte.h"

using namespace std;

TexteSDL::TexteSDL(string contenu, int positionX, int positionY):
		m_positionX(positionX), m_positionY(positionY), m_contenu(contenu),
		m_police(NULL), m_couleur(NULL),
		m_texte(NULL), m_surfaceAJour(false) {
	if (""==m_contenu) {
		m_contenu = " ";
	}
}

TexteSDL::TexteSDL(string contenu, TTF_Font* police, SDL_Color* couleur):
		m_positionX(0), m_positionY(0), m_contenu(contenu),
		m_police(police), m_couleur(couleur),
		m_texte(NULL), m_surfaceAJour(false) {
	if (""==m_contenu) {
		m_contenu = " ";
	}
}

TexteSDL::TexteSDL(string contenu, int positionX, int positionY,
		TTF_Font* police, SDL_Color* couleur):
		m_positionX(positionX), m_positionY(positionY), m_contenu(contenu),
		m_police(police), m_couleur(couleur),
		m_texte(NULL), m_surfaceAJour(false) {
	if (""==m_contenu) {
		m_contenu = " ";
	}
}

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
	if (NULL==m_police) {
		throw InstanceManquante(string("La police du texte '")
			+ m_contenu +"' n'est pas chargee");
	}
	if (NULL==m_couleur) {
		throw InstanceManquante(string("Le texte '")
			+ m_contenu +"' n'a pas de couleur");
	}

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
