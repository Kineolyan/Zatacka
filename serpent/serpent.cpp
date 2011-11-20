#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

#include "serpent.h"

using namespace std;

Serpent::Serpent(int ecranX, int ecranY, int positionX, int positionY, double direction,
		double vitesse/*, Regles reglesDirection, Regles reglesCollision*/):
    m_grilleX(ecranX), m_grilleY(ecranY),
    m_position({positionX, positionY}),
    m_direction(direction), m_vitesse(vitesse)/*,
    m_reglesDirection(reglesDirection), m_reglesCollision(reglesCollision)*/ {
}

void Serpent::position(int posX, int posY) {
  m_position.x = posX;
  m_position.y = posY;
}

void Serpent::direction(double direction) {
  m_direction = direction;
}

void Serpent::direction() {
//  Une touche correspondant à ce serpent est-elle enfoncée ?
//  Le cas échéant :
//  if (turnLeft) {
//    m_direction = ( m_direction + M_PI/90 ) % ( 2*M_PI ); // Je rappelle qu'on a 180 directions possibles pour le serpent
//  } elif (turnRight) {
//    m_direction = ( m_direction + M_PI/90 ) % ( 2*M_PI );
//  }
}

void Serpent::vitesse(double vitesse){
  m_vitesse = vitesse;
}

// ChangeRegles ???

bool Serpent::vaMourir(){
	return false;
}

void Serpent::avance(){
  if (!vaMourir()){
    int nouvellePosX;
    int nouvellePosY;
    nouvellePosX = m_position.x + m_vitesse * cos(m_direction);
    nouvellePosY = m_position.y + m_vitesse * sin(m_direction);
    traceSerpent(m_position.x, m_position.y, nouvellePosX, nouvellePosY);
    position(nouvellePosX, nouvellePosY);
  }
}

void Serpent::traceSerpent(int posX, int posY, int nouvellePosX, int nouvellePosY){

}

pair<int,int> Serpent::getPixel(int posX, int posY){
  pair<int,int> result;
  result.first = posX/100;
  result.second = posY/100;
  return result;
}
