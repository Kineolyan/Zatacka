#include "itemEcran.h"

ItemEcran::ItemEcran():
		m_largeur(0), m_hauteur(0) {
	m_position.x = 0;
	m_position.y = 0;
}

ItemEcran::ItemEcran(int largeur, int hauteur):
		m_largeur(largeur), m_hauteur(hauteur) {
	m_position.x = 0;
	m_position.y = 0;
}

ItemEcran::ItemEcran(const SDL_Rect& position):
		m_largeur(0), m_hauteur(0) {
	m_position.x = position.x;
	m_position.y = position.y;
}

ItemEcran::ItemEcran(int largeur, int hauteur, const SDL_Rect& position):
		m_largeur(largeur), m_hauteur(hauteur) {
	m_position.x = position.x;
	m_position.y = position.y;
}

int ItemEcran::hauteur()
{	return m_hauteur;	}

int ItemEcran::largeur()
{	return m_largeur;	}

SDL_Rect ItemEcran::position()
{	return m_position;	}

void ItemEcran::position(const SDL_Rect& position) {
	m_position.x = position.x;
	m_position.y = position.y;
}
