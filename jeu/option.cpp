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

	m_largeur = m_position.x
		+ (m_optionActive.largeur() > m_optionInactive.largeur() ?
			m_optionActive.largeur(): m_optionInactive.largeur());
	m_hauteur = m_texte.hauteur();

	redimensionner(m_largeur, m_hauteur);
}

Option::~Option()
{}

void Option::position(const SDL_Rect& position) {
	m_position.x = position.x;
	m_position.y = position.y;
	m_texte.position(m_position);

	m_position.x+= m_offset + m_texte.largeur();
	m_optionActive.position(m_position);
	m_optionInactive.position(m_position);
}

void Option::position(const SDL_Rect& positionOption,
		const SDL_Rect& positionEtat) {
	m_position.x = positionOption.x;
	m_position.y = positionOption.y;
	m_texte.position(m_position);

	m_optionActive.position(positionEtat);
	m_optionInactive.position(positionEtat);

	m_largeur = positionEtat.x - m_position.x
			+ (m_optionActive.largeur() > m_optionInactive.largeur() ?
				m_optionActive.largeur(): m_optionInactive.largeur());
	m_hauteur = positionEtat.y - m_position.y + m_texte.hauteur();

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
	Ecran::afficher(ecran);

	m_texte.afficher(ecran);
	if (m_active) {
		m_optionActive.afficher(ecran);
	}
	else {
		m_optionInactive.afficher(ecran);
	}
}
