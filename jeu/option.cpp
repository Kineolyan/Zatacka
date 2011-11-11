#include "option.h"

using namespace std;

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

void Option::position(const SDL_Rect& positionOption,
		const SDL_Rect& positionEtat) {
	m_positionOption.x = positionOption.x;
	m_positionOption.y = positionOption.y;
	m_texte.position(m_positionOption);

	m_positionOption.x = positionEtat.x;
	m_positionOption.y = positionEtat.y;
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
