#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

#include "serpent.h"

using namespace std;

Serpent::Serpent(int posX, int posY, double direction, double vitesse, Regles reglesDirection, Regles reglesCollision):
    m_posX(posX), m_posY(posY), m_direction(direction), m_vitesse(vitesse),
    m_reglesDirection(reglesDirection), m_reglesCollision(reglesCollision)  {

}

void Serpent::changePosition(int posX, int posY) {
  m_posX(posX);
  m_posY(posY);
  return 0;
}

void Serpent::changeDirection(double direction) {
  m_direction = direction;
  return 0;
}

void Serpent::changeDirection() {
//  Une touche correspondant à ce serpent est-elle enfoncée ?
//  Le cas échéant :
//  if (turnLeft) {
//    m_direction = ( m_direction + M_PI/90 ) % ( 2*M_PI ); // Je rappelle qu'on a 180 directions possibles pour le serpent
//  } elif (turnRight) {
//    m_direction = ( m_direction + M_PI/90 ) % ( 2*M_PI );
//  }
}

void Serpent::changeVitesse(double vitesse){
  m_vitesse = vitesse;
}

// ChangeRegles ???

bool Serpent::vaMourir(){

}

void Serpent::avance(){
  if (!vaMourir()){
    int nouvellePosX;
    int nouvellePosY;
    nouvellePosX = m_posX + vitesse * cmath::cos(direction);
    nouvellePosY = m_posY + vitesse * cmath::sin(direction);
    traceSerpent(m_posX, m_posY, nouvellePosX, nouvellePosY);
    changePosition(nouvellePosX, nouvellePosY);
  }
}

void Serpent::traceSerpent(int posX, int posY, int nouvellePosX, int nouvellePosY){

}

pair <int,int> Serpent::getPixel(int posX, int posY){
  pair <int,int> result;
  result.first = posX/100;
  result.second = posY/100;
  return result;
}
