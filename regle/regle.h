/*
 * regle.h
 *
 *  Created on: 26 nov. 2011
 *      Author: Vince
 */

#ifndef REGLE_H_
#define REGLE_H_

#include <vector>
#include "reglepoints.h"
#include "regleinitialisation.h"
#include "reglecollision.h"

class Zatacka;

class Regle
{
private:

	RegleCollision m_regleCollision;
	RegleInitialisation m_regleInitialisation;
	ReglePoints m_reglePoints;
	Zatacka& m_jeu;
	
public:
	Regle(Zatacka& jeu);
	Regle(RegleCollision reglecollision, RegleInitialisation regleinitialisation, ReglePoints reglepoints, Zatacka& jeu);
	Regle(std::vector<Regle> regles, Zatacka& jeu);
	RegleCollision getRegleColl() const;	
	RegleInitialisation getRegleInit() const;
	ReglePoints getReglePts() const;
	std::vector< std::pair<int,int> > positionsDepart() const;
	std::vector<double> directionsDepart() const;
	bool collision(int numSerpent, std::vector<int> joueursRencontres) const;
	std::vector<int> attribuePointsA(int serpentMourrant) const;
};


#endif /* REGLE_H_ */
