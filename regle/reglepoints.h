/*
 * regle.h
 *
 *  Created on: 24 nov. 2011
 *      Author: Vince
 */

#ifndef REGLEPOINTS_H_
#define REGLEPOINTS_H_

#include <vector>

class ReglePoints
{
private:
	/**
	* matrice de taille 6 qui telle que M[i][j] donne le nombre de points attribues a i quand j meurt
	*/
	std::vector< std::vector<int> > m_matriceGains;
	
public:
	/**
	* createur de la regle de jeu standard
	*/
	ReglePoints();
	/**
	* createur de la regle de jeu custom
	*/
	ReglePoints(std::vector< std::vector<int> > matriceGains);
	/**
	* createur qui fusionne plusieurs regles
	*/
	ReglePoints(std::vector<ReglePoints> regles);
	/**
	* vecteur designant combien de points gagnent chaque serpent quand serpentMourrant meurt 
	*/
	std::vector<int> attribuePointsA(int numSerpentMourrant) const;
	/**
	* renvoie la valeur la case i,j de la matrice de gains 
	*/
	int valeurCase(int i, int j) const;
	
}


#endif /* REGLEPOINTS_H_ */

