#include "serpent.h"
#include "../jeu/zatacka.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>

using namespace std;

Serpent::Serpent(Couleur couleur, int vitesse, Zatacka& ecranJeu):
    m_actif(false),
    m_couleur(couleur),
    m_vitesse(vitesse*10000),
    m_vivant(true),
    m_score(0),
    m_jeu(ecranJeu) {
    m_limites.x = m_jeu.largeurJeu() - ECART;
    m_limites.y = m_jeu.hauteurJeu() - ECART;
}

Serpent::~Serpent() {}

int Serpent::score() const throw()
{	return m_score;	}

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

void Serpent::incrementeDirection(int multiplicateur) throw() {
//ATTENTION, la grosse feinte : les ordonnées étant croissantes vers le bas, on compte les angles positivement dans le SENS ANTI-TRIGONOMÉTRIQUE
    m_direction += multiplicateur;
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
	bool testCouleur = false;
	SDL_Rect positionPixel;
	stringstream ss;

	if (0!=pixelX - m_pixel.x && 0!=pixelY - m_pixel.y) {
		int ecartX = pixelX - m_pixel.x,
			ecartY = pixelY - m_pixel.y;
		positionPixel.x = pixelX + ecartX;
		positionPixel.y = pixelY;
		testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
		ss << m_jeu.donnerCouleur(positionPixel) << " ";

		positionPixel.y+= ecartY;
		testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
		ss << m_jeu.donnerCouleur(positionPixel) << " ";

		positionPixel.x-= ecartX;
		testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
		ss << m_jeu.donnerCouleur(positionPixel) << " ";
	}
	else if (0!=pixelX - m_pixel.x) {
		positionPixel.x = 2*pixelX - m_pixel.x;
		positionPixel.y = pixelY - ECART;
		for (int e = -ECART, end = ECART; e<=end; ++e) {
			testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
			ss << m_jeu.donnerCouleur(positionPixel) << " ";

			++positionPixel.y;
		}
	}
	else if (0!=pixelY - m_pixel.y) {
		positionPixel.x = pixelX - ECART;
		positionPixel.y = 2*pixelY - m_pixel.y;
		for (int e = -ECART, end = ECART; e<=end; ++e) {
			testCouleur|= (NOIR!=m_jeu.donnerCouleur(positionPixel));
			ss << m_jeu.donnerCouleur(positionPixel) << " ";

			++positionPixel.x;
		}
	}

	#ifdef DEBUG_ACTIVE
	if (testCouleur) {
		cout << "Collision(" << m_couleur << ") : "
			<< m_pixel.x << "-" << m_pixel.y << " | "
			<< pixelX << "-" << pixelY
			<< " [ " << ss.str() << "]" << endl;
	}
	#endif

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
	if (m_actif) {
		switch(cote) {
		case DROITE:
			incrementeDirection(1);
			break;

		case GAUCHE:
			incrementeDirection(-1);
			break;

		default:
			break;
		}
	}
}

/**
 *
 */
bool Serpent::avance() throw(HorsLimite, TraceImpossible) {
    if (m_vivant) {
        int nouvellePosX = m_position.x + m_vitesse * cos(m_direction*M_PI/90),
            nouvellePosY = m_position.y + m_vitesse * sin(m_direction*M_PI/90),
            nouveauPixelX = getPixel(nouvellePosX),
            nouveauPixelY = getPixel(nouvellePosY);

        if (!vaMourir(nouveauPixelX, nouveauPixelY)) {
        	if (--m_tempsAvantTrou < 10) {
        		traceTrou(nouveauPixelX, nouveauPixelY);
        		if (m_tempsAvantTrou==0) {
        			donnerProchainTrou();
        		}
        	}
            else {
            	trace(nouveauPixelX, nouveauPixelY, m_couleur);
            }
            position(nouvellePosX, nouvellePosY);
            pixel(nouveauPixelX, nouveauPixelY);
            return true;
        }
        else {
            m_vivant = false;
            return false;
        }
    }
    else {
    	return true;
    }
}

void Serpent::trace(int nouvellePosX, int nouvellePosY, Couleur couleur) {
    SDL_Rect position = {nouvellePosX - ECART, nouvellePosY - ECART};
    m_jeu.tracerPoint(&position, couleur);
}

void Serpent::traceTrou(int positionX, int positionY) {
	trace(m_pixel.x, m_pixel.y, NOIR);
	trace(positionX, positionY, m_couleur);
}

int Serpent::getPixel(int pos) const throw()
{   return pos/10000;	}

void Serpent::gagnePoints(int pointsGagnes) throw() {
	if (m_vivant) {
		m_score+= pointsGagnes;
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
		m_direction = rand()%180;
		m_pixel.x = 50 + (rand()%(m_limites.x - 100));
		m_pixel.y = 50 + (rand()%(m_limites.y - 100));
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
		donnerProchainTrou();
	}
	else {
		m_vivant = false;
	}
}

void Serpent::donnerProchainTrou() {
	m_tempsAvantTrou = 150 + rand()%200;
}
