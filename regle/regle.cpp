#include "regle.h"
using namespace std;

Regle::Regle()
{
	RegleCollision m_regleCollision;
	RegleInitialisation m_regleInitialisation;
	ReglePoints m_reglePoints;
}

Regle::Regle(RegleCollision regleCollision, RegleInitialisation regleInitialisation, ReglePoints reglePoints):m_regleCollision(regleCollision),m_regleInitialisation(regleInitialisation),m_reglePoints(reglePoints)
{

}

Regle::Regle(vector<Regle> regles)
{
	vector<RegleCollision> reglescoll(0);
	vector<RegleInitialisation> reglesinit(0);
	vector<ReglePoints> reglespts(0);

	for (double i(0); i<regles.size(); ++i)
	{
		reglescoll.push_back(regles[i].getRegleColl());
		reglesinit.push_back(regles[i].getRegleInit());
		reglespts.push_back(regles[i].getReglePts());
	}

	RegleCollision m_regleCollision(reglescoll);
	RegleInitialisation m_regleInitialisation(reglesinit);
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
	return m_regleCollision.collision(numSerpent,joueursRencontres);
}

vector<int> Regle::attribuePointsA(int serpentMourrant) const
{
	return m_reglePoints.attribuePointsA(serpentMourrant);
}

