#include "itemEcran.h"

/**
 * Constructeur par défaut
 */
ItemEcran::ItemEcran():
		m_largeur(0), m_hauteur(0) {
	m_position.x = 0;
	m_position.y = 0;
}

/**
 * Constructeur
 *
 * @param largeur: largeur de l'écran
 * @param hauteur: hauteur de l'écran
 */
ItemEcran::ItemEcran(int largeur, int hauteur):
		m_largeur(largeur), m_hauteur(hauteur) {
	m_position.x = 0;
	m_position.y = 0;
}

/**
 * Constructeur
 *
 * @param position: position de l'écran
 */
ItemEcran::ItemEcran(const SDL_Rect& position):
		m_largeur(0), m_hauteur(0) {
	m_position.x = position.x;
	m_position.y = position.y;
}

/**
 * Constructeur
 *
 * @param largeur: largeur de l'écran
 * @param hauteur: hauteur de l'écran
 * @param position: position de l'écran
 */
ItemEcran::ItemEcran(int largeur, int hauteur, const SDL_Rect& position):
		m_largeur(largeur), m_hauteur(hauteur) {
	m_position.x = position.x;
	m_position.y = position.y;
}

/* -- Accesseurs et mutateurs -- */
int ItemEcran::hauteur() const throw()
{	return m_hauteur;	}

int ItemEcran::largeur() const throw()
{	return m_largeur;	}

SDL_Rect ItemEcran::position() const throw()
{	return m_position;	}

void ItemEcran::position(const SDL_Rect& position)  throw(){
	m_position.x = position.x;
	m_position.y = position.y;
}
