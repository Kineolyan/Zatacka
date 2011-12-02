/*
 * regle.h
 *
 *  Created on: 24 nov. 2011
 *      Author: Vince
 */

#ifndef REGLEINITIALISATION_H_
#define REGLEINITIALISATION_H_

#include <vector>

class RegleInitialisation
{
private:
	/**
	* distance minimale entre deux serpent au début du jeu
	*/
	double m_distanceMin;
	/**
	* active des positions fixes pour les serpents
	*/
	bool m_positionsFixes;
	/**
	* vecteurs des directions possibles dans le cas de positions fixes
	*/
	std::vector<double> m_directionsPossibles;
	/**
	* vecteur des positions possibles, l'indice est commun avec le precedent
	*/
	std::vector< std::pair<int,int> > m_positionsPossibles;
	/**
	* matrice de taille a definir en fonction de la taille du terrain de jeu
	* remplie avec des 1 et 0 qui represente le terrain de jeu : 
	* 0 correspond a une position impossible
	*/
	int m_dimJ;
	int m_dimI;
	std::vector< std::vector<int> > m_positionsExclues;
	
	int m_hauteurJeu;
	int m_largeurJeu;
public:

	/**
	* createur de la regle de jeu standard
	*/
	RegleInitialisation();
	/**
	* createur de regle avec positionsFixes
	*/
	RegleInitialisation(std::vector<double> directionsPossibles,
			std::vector< std::pair<int,int> > positionsPossibles);
	/**
	* createur de regle avec matrice d'exclusion
	*/
	RegleInitialisation(double distanceMin,
			std::vector< std::vector<int> > positionsExclues,
			int dimJ, int dimI);
	/**
	* createur qui fusionne 2 regles
	*/
	RegleInitialisation(std::vector<RegleInitialisation> regles);
	/**
	* determination des positions de depart
	*/
	std::vector< std::pair<int,int> > positionsDepart() const;
	/**
	* determination des positions de depart
	*/
	std::vector<double> directionsDepart() const;
	/**
	* methodes de recuperation des parametres
	*/
	double distanceMin() const;
	bool positionsFixes() const;
	int positionExclue(int i, int j) const;
	int dimJ() const;
	int dimI() const;
	double direction(int i) const;
	std::pair<int,int> position(int i) const;
};



#endif /* REGLEINITIALISATION_H_ */

