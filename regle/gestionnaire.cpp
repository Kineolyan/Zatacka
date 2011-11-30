#include "gestionnaire.h"
using namespace std;

GestionnaireRegles::GestionnaireRegles()
{}

void GestionnaireRegles::genererRegles() {
	vector<RegleCollision> reglescoll(m_regles.size());
	vector<RegleInitialisation> reglesinit(m_regles.size());
	vector<ReglePoints> reglespts(m_regles.size());

	for (vector<Regle>::iterator regle = m_regles.begin(),
			end = m_regles.end(); regle!=end; ++regle) {
		reglescoll.push_back(regle->regleCollision());
		reglesinit.push_back(regle->regleInitialisation());
		reglespts.push_back(regle->reglePoints());
	}

	m_regleCollision = RegleCollision(reglescoll);
	m_regleInitialisation = RegleInitialisation(reglesinit);
	m_reglePoints = ReglePoints(reglespts);
}

void GestionnaireRegles::ajouterRegle(const Regle& regle)
{	m_regles.push_back(regle);	}

std::vector<Regle>& GestionnaireRegles::regles()
{	return m_regles;	}

vector< pair<int,int> > GestionnaireRegles::positionsDepart() const
{
	return m_regleInitialisation.positionsDepart();
}

vector<double> GestionnaireRegles::directionsDepart() const
{
	return m_regleInitialisation.directionsDepart();
}

bool GestionnaireRegles::collision(int numSerpent, vector<int> joueursRencontres) const
{
	return m_regleCollision.collision(numSerpent,joueursRencontres);
}

vector<int> GestionnaireRegles::attribuePointsA(int serpentMourrant) const
{
	return m_reglePoints.attribuePointsA(serpentMourrant);
}

void GestionnaireRegles::afficherOptions(SDL_Surface* ecran) {
	for (vector<Regle>::iterator regle = m_regles.begin(),
			end = m_regles.end(); regle!=end; ++regle) {
		regle->option()->afficher(ecran);
	}
}

void GestionnaireRegles::appliquerTouche(Uint16 touche, SDL_Surface* ecran) {
	for (vector<Regle>::iterator regle = m_regles.begin(),
			end = m_regles.end(); regle!=end; ++regle) {
		regle->appliquerTouche(touche, ecran);
	}
}

void GestionnaireRegles::reset() {
	for (vector<Regle>::iterator regle = m_regles.begin(),
			end = m_regles.end(); regle!=end; ++regle) {
		regle->option()->desactiver();
	}
}

