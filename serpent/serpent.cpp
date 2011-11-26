#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

#include "serpent.h"
#include "../jeu/zatacka.h"
#include <iostream>

using namespace std;

Serpent::Serpent(Couleur couleur, int vitesse/*, Regles reglesDirection, Regles reglesCollision*/, Zatacka& ecranJeu):
    m_actif(false),
    m_couleur(couleur),
    m_vitesse(vitesse*10000),
    m_vivant(true),
    m_score(0),
    m_jeu(ecranJeu)/*,
    m_reglesDirection(reglesDirection),
    m_reglesCollision(reglesCollision)*/ {
    m_limites.x = m_jeu.largeurJeu() - ECART;
    m_limites.y = m_jeu.hauteurJeu() - ECART;
}

Serpent::~Serpent() {}

void Serpent::position(int posX, int posY) throw() {
  m_position.x = posX;
  m_position.y = posY;
}

void Serpent::pixel(int pixelX, int pixelY) throw() {
  m_pixel.x = pixelX;
  m_pixel.y = pixelY;
}

void Serpent::direction(double direction) throw()
{	m_direction = direction;	}

void Serpent::direction(int multiplicateur) throw() {
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

bool Serpent::actif() const throw()
{	return m_actif;	}

void Serpent::activer(bool actif) throw()
{	m_actif = actif;	}

void Serpent::vitesse(int vitesse) throw()
{	m_vitesse = vitesse;	}

/**
 * Teste de la couleur des cases adjacentes
 */
bool Serpent::collision(int pixelX, int pixelY)
		const throw(HorsLimite) {
//	if (m_couleur==0) {
//		cout << "positionCourante : " << m_pixel.x << " " << m_pixel.y << endl;
//		cout << "positionAVenir : " << pixelX << " " << pixelY << endl;
//	}
	bool testCouleur = false;
	SDL_Rect positionPixel;

	if (0!=pixelX - m_pixel.x) {
		positionPixel.x = 2*pixelX - m_pixel.x;
		positionPixel.y = pixelY - ECART;
		for (int e = -ECART, end = ECART; e<=end; ++e) {
			++positionPixel.y;
			testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
//			if (m_couleur==0) {
//				cout << "testDplctX : " << positionPixel.x << " "
//						<< positionPixel.y << "-" << boolalpha << testCouleur
//						<< endl;
//			}
		}
	}

	if (0!=pixelY - m_pixel.y) {
		positionPixel.x = pixelX - ECART;
		positionPixel.y = 2*pixelY - m_pixel.y;
		for (int e = -ECART, end = ECART; e<=end; ++e) {
			++positionPixel.x;
			testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
//			if (m_couleur==0) {
//				cout << "testDplctY : " << positionPixel.x << " "
//						<< positionPixel.y << "-" << boolalpha << testCouleur
//						<< endl;
//			}
		}
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

void Serpent::trace(int nouvellePosX, int nouvellePosY) {
    SDL_Rect position = {nouvellePosX - ECART, nouvellePosY - ECART};
    m_jeu.tracerPoint(&position, m_couleur);
}

int Serpent::getPixel(int pos) const throw()
{   return pos/10000;	}

void Serpent::gagneUnPoint(Couleur couleurPerdant) throw() {
	if (m_vivant) {
		++m_score;
		m_jeu.changerScore(m_couleur, m_score);
	}
}

/**
 * Réssucite, puis place le serpent aléatoirement sur la grille et lui donne
 * une nouvelle direction initiale
 */
void Serpent::placer() {
	if (m_actif) {
		m_vivant = true;
		srand(time(NULL));
		m_direction = M_PI * (rand()%1);
		m_pixel.x = 10 + (rand()%(m_limites.x - 20));
		m_pixel.y = 10 + (rand()%(m_limites.y - 20));
		m_position.x = m_pixel.x * 10000;
		m_position.y = m_pixel.y * 10000;

		clignoter();
	}
}

void Serpent::clignoter() {
    SDL_Rect position = {m_pixel.x - ECART, m_pixel.y - ECART};
    //cout << nouvellePosX << " " << nouvellePosY << endl;
	for (int i = 0; i < 3; ++i) {
		m_jeu.tracerPoint(&position, m_couleur);
		SDL_Delay(100);
		m_jeu.tracerPoint(&position, NOIR);
		SDL_Delay(100);
	}
	m_jeu.tracerPoint(&position, m_couleur);
}

/**
 * Réinitialise le serpent.
 * Le score retourne à 0 et le serpent reprend vie.
 */
void Serpent::reset() {
	if (m_actif) {
		m_score = 0;
		m_vivant = true;
		m_jeu.changerScore(m_couleur, m_score);
	}
	else {
		m_vivant = false;
	}
}
