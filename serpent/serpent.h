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
#include "../exceptions/exception.h"

/**
 * Serpent, ça gère le serpent (1 par joueur).
 * Pour un serpent, la grille de jeu est de taille 100*largeur x 100*hauteur
 */
class Serpent {
private:

	/**
	* Abscisse de la tête
	*/
	int posX;

	/**
	* Ordonnée de la tête
	*/
	int posY;

	/**
	* Direction, en radians [0;2Pi[
	*/
	double direction;

	/**
	* Vitesse, en cases/iteration - attention, il y a une feinte quand le serpent ne se déplace pas horizontalement ou verticalement, mais nous y reviendrons :)
	*/
	double vitesse;

	/**
	* Score du serpent (en fait du joueur, mais on confond les deux)
	*/
  int score;

  /**
  * Règles de direction
  */
  Regles reglesDirection;

  /**
  * Règles de collision
  */
  Regles reglesCollision;


public:

  /**
  * Change de direction - appelée à chaque itération pour déterminer la nouvelle direction du serpent
  * Peut être appelé
  *     - avec un argument pour définir une nouvelle direction
  *     - sans argument pour calculer une éventuelle nouvelle direction, et la modifier le cas échéant
  */
  void changeDirection(double direction);

  /**
  * Change la position
  */
  void changePosition(int posX, int posY);

  /**
  * Change la vitesse
  */
  void changeVitesse(double vitesse);

  /**
  * Change les règles :
  *    - nomRegles : peut prendre les valeurs "direction" et "collision"
  *    - regles : un set de règles correspondant
  */
  void changeRegles(string nomRegles, Regles regles);

  /**
  * Détermine si le serpent meurt à cette itération
  */
  void vaMourir();

  /**
  * Fait avancer le serpent
  */
  void avance();

	/**
	 * Constructeur
	 */
	Serpent(int posX, int posY, double direction, double vitesse, Regles reglesDirection, Regles reglesCollision);

	/**
	 * Destructeur
	 */
	~Serpent();
};

#endif /* SERPENT_H_ */
