#include "gestionnaire.h"
#include <iostream>

using namespace std;

GestionnaireRegles::GestionnaireRegles()
{}

void GestionnaireRegles::genererRegles() {
	vector<RegleCollision> reglescoll(1);
	vector<RegleInitialisation> reglesinit(1);
	vector<ReglePoints> reglespts(1);

	Regle regleParDefaut;
	reglescoll[0] = regleParDefaut.regleCollision();
	reglesinit[0] = regleParDefaut.regleInitialisation();
	reglespts[0] = regleParDefaut.reglePoints();

	for (vector<Regle>::iterator regle = m_regles.begin(),
			end = m_regles.end(); regle!=end; ++regle) {
		if (regle->active()) {
			reglescoll.push_back(regle->regleCollision());
			reglesinit.push_back(regle->regleInitialisation());
			reglespts.push_back(regle->reglePoints());
		}
	}

	m_regleCollision = RegleCollision(reglescoll);
	m_regleInitialisation = RegleInitialisation(reglesinit);
	m_reglePoints = ReglePoints(reglespts);
}

#ifdef DEBUG_ACTIVE
void GestionnaireRegles::afficher() {
	vector<pair<int, int> > position = positionsDepart();
	for (int i = 0; i<6; ++i) {
		cout << position[i].first << "-" << position[i].second << endl;
	}
}
#endif

void GestionnaireRegles::ajouterRegle(const Regle& regle)
{	m_regles.push_back(regle);	}

std::vector<Regle>& GestionnaireRegles::regles()
{	return m_regles;	}

vector< pair<int,int> > GestionnaireRegles::positionsDepart()
{
	return m_regleInitialisation.positionsDepart();
}

vector<double> GestionnaireRegles::directionsDepart() const
{
	return m_regleInitialisation.directionsDepart();
}

bool GestionnaireRegles::collision(Couleur serpent,
		const vector<Couleur>& joueursRencontres) const
{
	return m_regleCollision.collision(serpent,joueursRencontres);
}

const vector<int>& GestionnaireRegles::attribuePointsA(int serpentMourrant)
	const {
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

