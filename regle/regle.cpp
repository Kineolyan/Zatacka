#include "regle.h"
using namespace std;

Regle::Regle():
	m_active(false)
{}

Regle::Regle(RegleCollision& regleCollision,
		RegleInitialisation& regleInitialisation,
		ReglePoints& reglePoints):
	m_regleCollision(regleCollision),
	m_regleInitialisation(regleInitialisation),
	m_reglePoints(reglePoints),
	m_active(false)
{}

Regle::Regle(const Regle& origine):
	m_regleCollision(origine.m_regleCollision),
	m_regleInitialisation(origine.m_regleInitialisation),
	m_reglePoints(origine.m_reglePoints),
	m_active(origine.m_active),
	m_option(origine.m_option),
	m_touche(origine.m_touche)
{}

Regle::~Regle()
{}

RegleCollision& Regle::regleCollision()
{
	return m_regleCollision;
}

RegleInitialisation& Regle::regleInitialisation()
{
	return m_regleInitialisation;
}

ReglePoints& Regle::reglePoints()
{
	return m_reglePoints;
}

void Regle::activer() {
	m_active = true;
	m_option.activer();
}

void Regle::desactiver() {
	m_active = false;
	m_option.desactiver();
}

void Regle::echanger() {
	m_active = !m_active;
	m_option.echanger();
}

void Regle::option(string texte, string optionActive,
	string optionInactive, TTF_Font* police,
	SDL_Color* couleur, Uint16 touche) {
	Option nouvelleOption(texte, optionActive, optionInactive, police, couleur);
	m_option = nouvelleOption;
	m_touche = touche;
}

Option* Regle::option()
{	return &m_option;	}

void Regle::appliquerTouche(Uint16 touche, SDL_Surface* ecran) {
	if (touche==m_touche) {
		echanger();
		m_option.afficher(ecran);
	}
}

