#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

#include "serpent.h"
#include "../jeu/zatacka.h"
#include <iostream>

using namespace std;

Serpent::Serpent(Couleur couleur, int positionX, int positionY, double direction,
		int vitesse/*, Regles reglesDirection, Regles reglesCollision*/, Zatacka& ecranJeu):
    m_couleur(couleur),
    m_position({positionX*10000, positionY*10000}),
    m_pixel({positionX, positionY}),
    m_direction(direction),
    m_vitesse(vitesse*10000),
    m_vivant(true),
    m_score(0),
    m_jeu(ecranJeu)/*,
    m_reglesDirection(reglesDirection),
    m_reglesCollision(reglesCollision)*/ {
    m_limites.x = m_jeu.largeurJeu() - ECART;
    m_limites.y = m_jeu.hauteurJeu() - ECART;
}

Serpent::~Serpent(){

}

void Serpent::position(int posX, int posY) {
  m_position.x = posX;
  m_position.y = posY;
}

void Serpent::pixel(int pixelX, int pixelY) {
  m_pixel.x = pixelX;
  m_pixel.y = pixelY;
}

void Serpent::direction(double direction) {
  m_direction = direction;
}

void Serpent::direction(int multiplicateur) {
//ATTENTION, la grosse feinte : les ordonnées étant croissantes vers le bas, on compte les angles positivement dans le SENS ANTI-TRIGONOMÉTRIQUE
//  Une touche correspondant à ce serpent est-elle enfoncée ?
//  Le cas échéant :
//  if (turnLeft) {
//    m_direction = ( m_direction - M_PI/90 ) % ( 2*M_PI ); // Je rappelle qu'on a 180 directions possibles pour le serpent
//  } else if (turnRight) {
    m_direction += multiplicateur*M_PI/90;

//    while(m_direction < 0){
//      m_direction += 2*M_PI;
//    }
//    while(m_direction >= 2*M_PI) {
//      m_direction -= 2*M_PI;
//    }
//  }
}

void Serpent::vitesse(int vitesse){
  m_vitesse = vitesse;
}

/**
 * Teste de la couleur des cases adjacentes
 */
bool Serpent::collision(int pixelX, int pixelY)
        const throw(HorsLimite) {
    return false;
    int ecartX = pixelX - m_pixel.x,
        ecartY = pixelY - m_pixel.y;
    bool testCouleur = false;
    SDL_Rect positionPixel;

    positionPixel.y = pixelY + ecartY;
    for (int e = -ecartX, end = ecartX; e<=end; ++e) {
        positionPixel.x = pixelX + e;
        testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
    }

    positionPixel.x = pixelX + ecartX;
    for (int e = -ecartY, end = ecartY; e<end; ++e) {
        positionPixel.y = pixelY + e;
        testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
    }

    return testCouleur;
}

bool Serpent::vaMourir(int positionX, int positionY)
        const throw(HorsLimite) {
	if (ECART<=positionX && m_limites.x>positionX) {
        if (ECART<=positionY && m_limites.y>positionY) {
            return collision(positionX, positionY);
        }
	}
	return true;
}

void Serpent::seDirigeVers(Direction cote) {
    switch(cote) {
    case DROITE:
        direction(1);
        break;

    case GAUCHE:
        direction(-1);
        break;

    default:
        break;
    }
}

/**
 *
 */
bool Serpent::avance() throw(HorsLimite, TraceImpossible) {
    if (m_vivant) {
        int nouvellePosX = m_position.x + m_vitesse * cos(m_direction),
            nouvellePosY = m_position.y + m_vitesse * sin(m_direction),
            nouveauPixelX = getPixel(nouvellePosX),
            nouveauPixelY = getPixel(nouvellePosY);

        if (!vaMourir(nouveauPixelX, nouveauPixelY)) {
            trace(nouveauPixelX, nouveauPixelY);
            position(nouvellePosX, nouvellePosY);
            pixel(nouveauPixelX, nouveauPixelY);
            return true;
        }
        else {
            m_vivant = false;
        }
    }
    else {
    	return true;
    }
}

void Serpent::trace(int nouvellePosX, int nouvellePosY){
    SDL_Rect position = {nouvellePosX - ECART, nouvellePosY - ECART};
    //cout << nouvellePosX << " " << nouvellePosY << endl;
    m_jeu.tracerPoint(&position, m_couleur);
}

int Serpent::getPixel(int pos){   // à recoder avec un couple en entrée
  return pos/10000;
}

void Serpent::gagneUnPoint(Couleur couleurPerdant) {
	if (m_vivant) {
		++m_score;
		m_jeu.changerScore(m_couleur, m_score);
	}
}
