/*
 * couleurs.h
 *
 *  Created on: 19 nov. 2011
 *      Author: oliv
 */

#ifndef KEYWORDS_H_
#define KEYWORDS_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum Couleur {
	ROUGE = 0,
	JAUNE = 1,
	ORANGE = 2,
	VERT = 3,
	VIOLET = 4,
	BLEU = 5,
	NOIR = 6,
	BLANC = 7,
	GRIS = 8
};

enum Direction {
	TOUT_DROIT, GAUCHE, DROITE
};

#endif /* KEYWORDS_H_ */
