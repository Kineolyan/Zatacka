#include "ecran.h"

using namespace std;

Ecran::Ecran(int largeur, int hauteur):
		ItemEcran(largeur, hauteur),
		m_ecran(NULL) {
	m_ecran = SDL_CreateRGBSurface(SDL_HWSURFACE,
			m_largeur, m_hauteur, 32, 0, 0, 0, 0);
	if (NULL==m_ecran) {
		throw InstanceManquante("Impossible de creer un ecran");
	}

	m_couleur.r = 0;
	m_couleur.g = 0;
	m_couleur.b = 0;
	colorer();
}

Ecran::Ecran(int largeur, int hauteur, SDL_Color* couleur):
		ItemEcran(largeur, hauteur),
		m_ecran(NULL) {
	m_ecran = SDL_CreateRGBSurface(SDL_HWSURFACE,
			m_largeur, m_hauteur, 32, 0, 0, 0, 0);
	if (NULL==m_ecran) {
		throw InstanceManquante("Impossible de creer un ecran");
	}

	this->couleur(couleur);
}

Ecran::~Ecran() {
	SDL_FreeSurface(m_ecran);
}

SDL_PixelFormat* Ecran::format() const throw()
{   return m_ecran->format; }

SDL_Surface* Ecran::ecran() const throw()
{   return m_ecran; }

void Ecran::colorer() throw() {
	SDL_FillRect(m_ecran, NULL,
		SDL_MapRGB(m_ecran->format,
			m_couleur.r, m_couleur.g, m_couleur.b)
	);
}

void Ecran::couleur(SDL_Color* couleur) throw() {
	m_couleur.r = couleur->r;
	m_couleur.g = couleur->g;
	m_couleur.b = couleur->b;

	colorer();
}

/**
 * Affiche l'écran sur l'écran de destination
 *
 * @param ecran: ecran sur lequel on affiche l'instance
 */
void Ecran::afficher(SDL_Surface* ecran) {
	SDL_BlitSurface(m_ecran, NULL, ecran, &m_position);
}

/**
 * Efface l'écran en lui redonnant sa couleur d'origine
 */
void Ecran::effacer() throw() {
	colorer();
}

/**
 * Redimensionne l'écran aux nouvelles spécifications
 * L'écran précédent est libéré et un nouveau est alloué
 *
 * @param largeur: nouvelle largeur
 * @param hauteur: nouvelle hauteur
 */
void Ecran::redimensionner(int largeur, int hauteur) throw() {
	m_largeur = largeur;
	m_hauteur = hauteur;

	SDL_FreeSurface(m_ecran);
	m_ecran = SDL_CreateRGBSurface(SDL_HWSURFACE,
		m_largeur, m_hauteur, 32, 0, 0, 0, 0);
	colorer();
}


