/*
 * regle.h
 *
 *  Created on: 24 nov. 2011
 *      Author: Vince
 */

#ifndef REGLEDEPLACEMENT_H_
#define REGLEDEPLACEMENT_H_

#include <vector>

class RegleDeplacement
{
private:
	/**
	* coeff multiplicateur de direction
	*/
	double m_modificateurDirection;
	
public:
	/**
	* createur de la regle de jeu standard
	*/
	RegleDeplacement();
	/**
	* createur de la regle de jeu custom
	*/
	RegleDeplacement(double modificateurDirection);
	/**
	* createur qui fusionne 2 regles
	*/
	RegleDeplacement(RegleDeplacement regle1, RegleDeplacement regle2);
	/**
	* vecteur designant combien de points gagnent chaque serpent quand serpentMourrant meurt 
	*/
	double miseAJourDirection(Serpent serpent);
	
}


#endif /* REGLEDEPLACEMENT_H_ */

