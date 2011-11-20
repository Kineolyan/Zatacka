#include "serpent.h"

using namespace std;

Serpent::Serpent(int posX, int posY, double direction, double vitesse, Regles reglesDirection, Regles reglesCollision):{

  changePosition(posX, posY);
  changeDirection(direction);
  changeVitesse(vitesse);
  changeRegles(reglesDirection, reglesCollision);

}
