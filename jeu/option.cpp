#include "option.h"

using namespace std;

Option::Option(string texte, string optionActive, string optionInactive,
		TTF_Font* police, SDL_Color* couleur):
		Ecran(0, 0),
		m_texte(texte, police, couleur),
		m_optionActive(optionActive, police, couleur),
		m_optionInactive(optionInactive, police, couleur),
		m_active(false), m_offset(40) {
	position(m_position);

	m_largeur = m_texte.largeur() + m_offset
		+ (m_optionActive.largeur() > m_optionInactive.largeur() ?
			m_optionActive.largeur(): m_optionInactive.largeur());
	m_hauteur = m_texte.hauteur();

	redimensionner(m_largeur, m_hauteur);
}

Option::~Option()
{}

void Option::position(const SDL_Rect& position) {
	Ecran::position(position);

	SDL_Rect positionTexte = {0, 0};
	m_texte.position(positionTexte);

	positionTexte.x+= m_offset + m_texte.largeur();
	m_optionActive.position(positionTexte);
	m_optionInactive.position(positionTexte);
}

void Option::position(const SDL_Rect& positionOption,
		const SDL_Rect& positionEtat) {
	Ecran::position(positionOption);

	SDL_Rect positionTexte = {0, 0};
	m_texte.position(positionTexte);

	positionTexte.x = positionEtat.x - positionOption.x;
	positionTexte.y = positionEtat.y - positionOption.y;
	m_optionActive.position(positionTexte);
	m_optionInactive.position(positionTexte);

	m_largeur = positionTexte.x
			+ (m_optionActive.largeur() > m_optionInactive.largeur() ?
				m_optionActive.largeur(): m_optionInactive.largeur());
	m_hauteur = positionTexte.y + m_texte.hauteur();

	redimensionner(m_largeur, m_hauteur);
}

void Option::activer()
{	m_active = true;	}

void Option::desactiver()
{	m_active = false;	}

void Option::echanger()
{	m_active = !m_active;	}

void Option::afficher(SDL_Surface* ecran) {
	effacer();

	m_texte.afficher(m_ecran);
	if (m_active) {
		m_optionActive.afficher(m_ecran);
	}
	else {
		m_optionInactive.afficher(m_ecran);
	}

	Ecran::afficher(ecran);
}
