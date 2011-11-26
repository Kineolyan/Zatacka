/*
 * serpent.h
 *
 *  Created on: 17 nov. 2011
 *      Author: oliv
 */

#ifndef SERPENT_H_
#define SERPENT_H_

#include <SDL/SDL.h>
#include <map>
#include <vector>
#include <cmath>
#include "../util/exception.h"
#include "../util/keywords.h"

class Zatacka;

/**
 * Serpent, ça gère le serpent (1 par joueur).
 * Pour un serpent, la grille de jeu est de taille 100*largeur x 100*hauteur
 */
class Serpent {
private:
	struct Coordonnees {
		int x;
		int y;
	};

	/**
	 * Couleur du serpent
	 */
	Couleur m_couleur;

	/**
	 * Cordonnées du serpent sur sa grille virtuelle
	 */
	Coordonnees m_position;

	/**
	 * Coordonnées du pixel à l'écran
	 */
	Coordonnees m_pixel;

	/**
	 * Coordonnées du pixel du bas de l'écran
	 */
	Coordonnees m_limites;

	/**
	 * Direction, en radians (sur IR)
	 */
	double m_direction;

	/**
	 * Vitesse, en pixels/iteration
	 */
	int m_vitesse;

	bool m_vivant;

	/**
	 * Score du serpent (en fait du joueur, mais on confond les deux)
	 */
	int m_score;

	/**
	 * Règles de direction
	 */
	//Regles m_reglesDirection;

	/**
	 * Règles de collision
	 */
	//Regles m_reglesCollision;

	/**
	 * Gestionnaire de l'écran de jeu
	 */
	Zatacka& m_jeu;

public:
	/**
	 * Constructeur :
	 * - posX et posY sont les coordonnées de la tête du serpent en PIXELS
	 */
	Serpent(Couleur couleur, int posX, int posY, double direction, int vitesse/*, Regles reglesDirection, Regles reglesCollision*/, Zatacka& ecranJeu);

	/**
	 * Destructeur
	 */
	~Serpent();

	/**
	 * Fait avancer le serpent dans la direction donnée
	 * Le serpent calcule sa direction à partir de l'ordre donné, puis
	 * vérifie s'il n'entre pas en collision, et se déplace à l'écran.
	 *
	 * @param direction: la direction demandée
	 *
	 * @return: true si le serpent entre en collision
	 */
	bool jouer(Direction direction);

	/**
	 * Change de direction - appelée à chaque itération pour déterminer la nouvelle direction du serpent
	 * Peut être appelé
	 *     - avec un argument pour définir une nouvelle direction
	 *     - sans argument pour calculer une éventuelle nouvelle direction, et la modifier le cas échéant
	 */
	void direction(double direction);
	void direction(int multiplicateur);

	/**
	 * Change la position
	 */
	void position(int posX, int posY);
	void pixel(int pixelX, int pixelY);

	/**
	 * Change la vitesse
	 */
	void vitesse(int vitesse);

	/**
	 * Change les règles :
	 *    - nomRegles : peut prendre les valeurs "direction" et "collision"
	 *    - regles : un set de règles correspondant
	 */
	//void regles(string nomRegles, Regles regles);

	bool collision(int positionX, int positionY)
	const throw(HorsLimite);

	/**
	 * Détermine si le serpent meurt à cette itération
	 */
	bool vaMourir(int positionX, int positionY)
	const throw(HorsLimite);

	void seDirigeVers(Direction direction);

	/**
	 * Fait avancer le serpent
	 */
	bool avance() throw(HorsLimite, TraceImpossible);

	/**
	 * Trace une nouvelle section de serpent
	 */
	void trace(int nouvellePosX, int nouvellePosY);

	/**
	 * Convertit des coordonnées de la grille en coordonnées dans l'écran de jeu (en pixels)
	 */
	int getPixel(int pos);

	void gagneUnPoint(Couleur couleurPerdant);
};

#endif /* SERPENT_H_ */
