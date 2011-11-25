#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

#include "serpent.h"
#include "../jeu/zatacka.h"
#include <iostream>

using namespace std;

Serpent::Serpent(Couleur couleur, int positionX, int positionY, double direction,
		int vitesse/*, Regles reglesDirection, Regles reglesCollision*/, Zatacka& ecranJeu):
    m_couleur(couleur), m_positionX(positionX*10000), m_positionY(positionY*10000),        // la position du serpent est 100 fois plus précise que la position d'un pixel.
    m_direction(direction), m_vitesse(vitesse*10000), m_ecranJeu(ecranJeu)/*,
    m_reglesDirection(reglesDirection), m_reglesCollision(reglesCollision)*/ {
}

Serpent::~Serpent(){

}

void Serpent::position(int posX, int posY) {
  m_positionX = posX;
  m_positionY = posY;
}

void Serpent::direction(double direction) {
  m_direction = direction;
}

void Serpent::direction(int multiplicateur) {  //ATTENTION, la grosse feinte : les ordonnées étant croissantes vers le bas, on compte les angles positivement dans le SENS ANTI-TRIGONOMÉTRIQUE
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

// ChangeRegles ???

bool Serpent::vaMourir(){
	return false;
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

bool Serpent::avance(){
  if (!vaMourir()){
    int nouvellePosX;
    int nouvellePosY;
    nouvellePosX = m_positionX + m_vitesse * cos(m_direction);
    nouvellePosY = m_positionY + m_vitesse * sin(m_direction);
    traceSerpent(m_positionX, m_positionY, nouvellePosX, nouvellePosY);
    position(nouvellePosX, nouvellePosY);
  }

  return true;
}

void Serpent::traceSerpent(int posX, int posY, int nouvellePosX, int nouvellePosY){
  int pixelX, pixelY;
  pixelX = getPixel(nouvellePosX);              // /!\ bricolage temporaire
  pixelY = getPixel(nouvellePosY);
  SDL_Rect position = {pixelX, pixelY};
//  cout << pixelX << " " << pixelY << " " << m_positionX << " " << m_positionY << endl;
  m_ecranJeu.tracerPoint(&position, m_couleur);
}

int Serpent::getPixel(int pos){   // à recoder avec un couple en entrée
  return pos/10000;
}
