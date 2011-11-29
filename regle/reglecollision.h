/*
 * regle.h
 *
 *  Created on: 24 nov. 2011
 *      Author: Vince
 */

#ifndef REGLECOLLISION_H_
#define REGLECOLLISION_H_

#include <vector>

class RegleCollision
{
private:
	/**
	* matrice de taille 6*6 qui telle que M[i][j] vaut true quand i meurt au contact de j, false si rien ne se passe
	*/
	std::vector< std::vector<bool> > m_matriceCollision;
	
public:
	/**
	* createur de la regle de jeu standard
	*/
	RegleCollision();
	/**
	* createur de la regle de jeu custom
	*/
	RegleCollision(std::vector< std::vector<bool> > matriceCollision);
	/**
	* createur qui fusionne 2 regles
	*/
	RegleCollision(std::vector<RegleCollision> regles);
	/**
	* vecteur designant si un serpent meurt au prochain deplacement
	*/
	bool collision(int numSerpent, std::vector<int> joueursRencontres) const;
	/**
	* renvoie la valeur la case i,j de la matrice de gains 
	*/
	bool valeurCase(int i, int j) const;
};


#endif /* REGLECOLLISION_H_ */

