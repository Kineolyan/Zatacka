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
#include "../exceptions/exception.h"

/**
 * Serpent, ça gère le serpent (1 par joueur).
 * Pour un serpent, la grille de jeu est de taille 100*largeur x 100*hauteur
 */
class Serpent {
private:

  /**
   * Taille de la grille en abscisses
   */
  int m_grilleX;

  /**
   * Taille de la grille en ordonnées
   */
  int m_grilleY;

	/**
 	 * Position de la tête
	 */
	SDL_Rect m_position;

	/**
	 * Direction, en radians [0;2Pi[
	 */
	double m_direction;

	/**
	 * Vitesse, en cases/iteration - attention, il y a une feinte quand le serpent ne se déplace pas horizontalement ou verticalement, mais nous y reviendrons :)
	 */
	double m_vitesse;

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


public:
	/**
	 * Constructeur
	 */
	Serpent(int ecranX, int ecranY, int posX, int posY, double direction, double vitesse/*, Regles reglesDirection, Regles reglesCollision*/);

	/**
	 * Destructeur
	 */
	~Serpent();

  /**
   * Change de direction - appelée à chaque itération pour déterminer la nouvelle direction du serpent
   * Peut être appelé
   *     - avec un argument pour définir une nouvelle direction
   *     - sans argument pour calculer une éventuelle nouvelle direction, et la modifier le cas échéant
   */
  void direction(double direction);
  void direction();

  /**
   * Change la position
   */
  void position(int posX, int posY);

  /**
   * Change la vitesse
   */
  void vitesse(double vitesse);

  /**
   * Change les règles :
   *    - nomRegles : peut prendre les valeurs "direction" et "collision"
   *    - regles : un set de règles correspondant
   */
  //void regles(string nomRegles, Regles regles);

  /**
   * Détermine si le serpent meurt à cette itération
   */
  bool vaMourir();

  /**
   * Fait avancer le serpent
   */
  void avance();

  /**
   * Trace une nouvelle section de serpent
   */
  void traceSerpent(int posX, int posY, int nouvellePosX, int nouvellePosY);

  /**
   * Convertit des coordonnées de la grille en coordonnées dans l'écran de jeu (en pixels)
   */
  std::pair<int,int> getPixel(int posX, int posY);
};

#endif /* SERPENT_H_ */
