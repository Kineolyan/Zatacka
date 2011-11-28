#include "regle.h"

Regle::Regle(Zatacka& jeu):m_jeu(jeu)
{
	RegleCollision m_regleCollision();
	RegleInitialisation m_regleInitialisation(jeu);
	ReglePoints m_reglePoints();
}

Regle::Regle(RegleCollision regleCollision, RegleInitialisation regleInitialisation, ReglePoints reglePoints,Zatacka& jeu):m_regleCollision(regleCollision),m_regleInitialisation(regleInitialisation),m_reglePoints(reglePoints), m_jeu(jeu)
{

}

Regle::Regle(vector<Regle> regles, Zatacka& jeu):m_jeu(jeu)
{
	vector<RegleCollision> reglescoll(0);
	vector<RegleInitialisation> reglesinit(0);
	vector<ReglePoints> reglespts(0);
	for (int i(0); i<regles.size(); ++i)
	{
		reglescoll.push_back(regles[i].getRegleColl());
		reglesinit.push_back(regles[i].getRegleInit());
		reglespts.push_back(regles[i].getReglePts());
	}
	
	RegleCollision m_regleCollision(reglescoll);
	RegleInitialisation m_regleInitialisation(reglesinit, Zatacka& jeu);
	ReglePoints m_reglePoints(reglespts);
}

RegleCollision Regle::getRegleColl() const
{
return m_regleCollision;
}
	
RegleInitialisation Regle::getRegleInit() const
{
return m_regleInitialisation;
}

ReglePoints Regle::getReglePts() const
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

bool Regle::collision(int numSerpent, std::vector<int> joueursRencontres) const
{
	return m_reglesCollision.collision(int numSerpent, std::vector<int> joueursRencontres);
}

vector<int> attribuePointsA(int serpentMourrant) const
{
	return m_reglePoints.attribuePointsA(int serpentMourrant);
}

