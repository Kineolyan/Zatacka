#include "texte.h"

using namespace std;

TexteSDL::TexteSDL():
		ItemEcran(), m_contenu(""),
		m_police(NULL), m_couleur(NULL),
		m_texte(NULL), m_surfaceAJour(false) {
	if (""==m_contenu) {
		m_contenu = " ";
	}
}

TexteSDL::TexteSDL(string contenu, TTF_Font* police, SDL_Color* couleur):
		ItemEcran(), m_contenu(contenu),
		m_police(police), m_couleur(couleur),
		m_texte(NULL), m_surfaceAJour(false) {
	if (""==m_contenu) {
		m_contenu = " ";
	}
}

TexteSDL::TexteSDL(string contenu, TTF_Font* police,
		SDL_Color* couleur, const SDL_Rect& position):
		ItemEcran(position), m_contenu(contenu),
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

void TexteSDL::contenu(string contenu) throw() {
	m_contenu = contenu;
	m_surfaceAJour = false;
}

void TexteSDL::police(TTF_Font* police) throw() {
	m_police = police;
	m_surfaceAJour = false;
}

void TexteSDL::couleur(SDL_Color* couleur) throw() {
	m_couleur = couleur;
	m_surfaceAJour = false;
}

void TexteSDL::position(const SDL_Rect& position) throw() {
	ItemEcran::position(position);
}

int TexteSDL::largeur() throw(InstanceManquante) {
	if (false==m_surfaceAJour) {
		texte();
	}
	return m_largeur;
}

int TexteSDL::hauteur() throw(InstanceManquante) {
	if (false==m_surfaceAJour) {
		texte();
	}
	return m_hauteur;
}

SDL_Surface* TexteSDL::texte() throw(InstanceManquante) {
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

	m_largeur = m_texte->w;
	m_hauteur = m_texte->h;

	return m_texte;
}

void TexteSDL::afficher(SDL_Surface* ecran) {
	texte();

	SDL_BlitSurface(m_texte, NULL, ecran, &m_position);
}
