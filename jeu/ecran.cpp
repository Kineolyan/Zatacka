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

void Ecran::colorer() {
	SDL_FillRect(m_ecran, NULL,
		SDL_MapRGB(m_ecran->format,
			m_couleur.r, m_couleur.g, m_couleur.b)
	);
}

void Ecran::couleur(SDL_Color* couleur) {
	m_couleur.r = couleur->r;
	m_couleur.g = couleur->g;
	m_couleur.b = couleur->b;

	colorer();
}

void Ecran::afficher(SDL_Surface* ecran) {
	SDL_BlitSurface(m_ecran, NULL, ecran, &m_position);
}

void Ecran::effacer() {
	colorer();
}

void Ecran::redimensionner(int largeur, int hauteur) {
	m_largeur = largeur;
	m_hauteur = hauteur;

	SDL_FreeSurface(m_ecran);
	m_ecran = SDL_CreateRGBSurface(SDL_HWSURFACE,
		m_largeur, m_hauteur, 32, 0, 0, 0, 0);
	colorer();
}


