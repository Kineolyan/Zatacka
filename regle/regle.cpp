#include "regle.h"
using namespace std;

Regle::Regle():
	m_active(false),
	m_option(NULL)
{}

Regle::Regle(RegleCollision& regleCollision,
		RegleInitialisation& regleInitialisation,
		ReglePoints& reglePoints):
	m_regleCollision(regleCollision),
	m_regleInitialisation(regleInitialisation),
	m_reglePoints(reglePoints),
	m_active(false),
	m_option(NULL)
{}

Regle::~Regle() {
	if (NULL!=m_option) {
		delete m_option;
	}
}

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

vector< pair<int,int> > Regle::positionsDepart() const
{
	return m_regleInitialisation.positionsDepart();
}

vector<double> Regle::directionsDepart() const
{
	return m_regleInitialisation.directionsDepart();
}

bool Regle::collision(int numSerpent, vector<int> joueursRencontres) const
{
	return m_regleCollision.collision(numSerpent,joueursRencontres);
}

vector<int> Regle::attribuePointsA(int serpentMourrant) const
{
	return m_reglePoints.attribuePointsA(serpentMourrant);
}

void Regle::activer() {
	m_active = true;
	m_option->activer();
}

void Regle::desactiver() {
	m_active = false;
	m_option->desactiver();
}

void Regle::echanger() {
	m_active = !m_active;
	m_option->echanger();
}

void Regle::option(string texte, string optionActive,
	string optionInactive, TTF_Font* police,
	SDL_Color* couleur, Uint16 touche) {
	if (NULL==m_option) {
		delete m_option;
	}
	m_option = new Option(texte, optionActive, optionInactive, police, couleur);
	m_touche = touche;
}

Option* Regle::option()
{	return m_option;	}

void Regle::appliquerTouche(Uint16 touche, SDL_Surface* ecran) {
	if (touche==m_touche) {
		echanger();
		m_option->afficher(ecran);
	}
}

