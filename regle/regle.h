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

class Regle
{
private:

	RegleCollision m_regleCollision;
	RegleInitialisation m_regleInitialisation;
	ReglePoints m_reglePoints;
	
		
	
public:
	Regle();
	Regle(RegleCollision reglecollision, RegleInitialisation regleinitialisation, ReglePoints reglepoints);
	Regle(vector<Regle> regles);
	RegleCollision getRegleColl() const;	
	RegleInitialisation getRegleInit() const;
	ReglePoints getReglePts() const;

}


#endif /* REGLE_H_ */
