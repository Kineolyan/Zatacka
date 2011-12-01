/*
 * regles.h
 *
 *  Created on: 1 déc. 2011
 *      Author: oliv
 */

#ifndef REGLES_H_
#define REGLES_H_

# include "regle.h"
# include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

/**
* regles du jeu original
*/
Regle cestLeGameplay();

Regle sansDepartsProches(double distanceMin);

/**
* fait des equipes de nbrJoueurs joueurs : option=0 fait des equipes fixes haut contre bas,option=1 fait des equipes aleatoires equilibrees
*/
Regle parEquipe(int option = 0,int nbrEquipes = 3);

/**
* 3 joueurs de chaque coté dirigés vers l'autre coté
*/
Regle batailleRangee(int largeurJeu, int hauteurJeu);

Regle departAuCentre(int largeurJeu, int hauteurJeu);

Regle departAuxCoins(int largeurJeu, int hauteurJeu);

#endif /* REGLES_H_ */
