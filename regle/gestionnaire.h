/*
 * regle.h
 *
 *  Created on: 26 nov. 2011
 *      Author: Vince
 */

#ifndef GESTIONNAIRE_REGLE_H_
#define GESTIONNAIRE_REGLE_H_

#include <vector>
#include <SDL/SDL.h>
#include "regle.h"

class GestionnaireRegles {
private:
	std::vector<Regle> m_regles;
	RegleCollision m_regleCollision;
	RegleInitialisation m_regleInitialisation;
	ReglePoints m_reglePoints;

public:
	GestionnaireRegles();

	void ajouterRegle(const Regle& regle);

	std::vector<Regle>& regles();

	std::vector< std::pair<int,int> > positionsDepart();
	std::vector<double> directionsDepart() const;
	bool collision(Couleur serpent,
			const std::vector<Couleur>& joueursRencontres) const;
	const std::vector<int>& attribuePointsA(int serpentMourrant) const;

	void genererRegles();

	void afficherOptions(SDL_Surface* ecran);

	void appliquerTouche(Uint16 touche, SDL_Surface* ecran);

	void reset();

	#ifdef DEBUG_ACTIVE
	void afficher();
	#endif
};


#endif /* GESTIONNAIRE_REGLE_H_ */
