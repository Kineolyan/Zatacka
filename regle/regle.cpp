#include "regle.h"

Regle::Regle()
{
	m_regleCollision = RegleCollision();
	m_regleInitialisation = RegleInitialisation();
	m_reglePoints = ReglePoints();
}

Regle::Regle(RegleCollision regleCollision, RegleInitialisation regleInitialisation, ReglePoints reglePoints):m_regleCollision(regleCollision),m_regleInitialisation(regleinitialisation),m_reglePoints(reglePoints)
{

}

Regle::Regle(vector<Regle> regles)
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
	
	m_regleCollision = RegleCollision(reglescoll);
	m_regleInitialisation = RegleInitialisation(reglesinit);
	m_reglePoints = ReglePoints(reglespts);
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




