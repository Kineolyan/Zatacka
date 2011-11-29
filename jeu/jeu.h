/*
 * jeu.h
 *
 *  Created on: 3 nov. 2011
 *      Author: oliv
 */

#ifndef JEU_H_
#define JEU_H_

#define TAILLE_SERPENT 3
#define ECART 1

#include <SDL/SDL.h>
#include <vector>
#include <sstream>

#include "itemEcran.h"
#include "ecran.h"
#include "texte.h"
#include "../util/keywords.h"
#include "../serpent/serpent.h"
#include "../audio/audio.h"

class Serpent;

class Jeu: public ItemEcran {
private:
	Zatacka& m_jeu;

	/**
	 * Largeur du panneau des scores
	 */
	int m_largeurScores;

	/**
	 * Position des scores à l'écran
	 */
	SDL_Rect m_positionScores;

	/**
	 * Ecran de jeu contenant les serpents
	 */
	Ecran m_ecranJeu;

	/**
	 * Ecran affichant les scores
	 */
	Ecran m_ecranScores;

	/**
	 * Motifs de base pour le trace des serpents
	 */
	std::vector<Serpent*> m_joueurs;

	/**
	 * Motifs de base pour le trace des serpents
	 */
	std::vector<SDL_Surface*> m_points;

	/**
	 * Tableau des textes affichant les scores sur l'écran
	 * de jeu
	 */
	std::vector<TexteSDL> m_scores;

	/**
	 * Nombre de joueurs participant à la partie
	 */
	int m_nbJoueursActifs;

	/**
	 * Contrôleur audio
	 */
  Audio m_audio;

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserPoints() throw(InstanceManquante);

	void colorer(SDL_Surface* ecran, Couleur couleur) throw();

public:
	Jeu(Zatacka& jeu, int largeurJeu, int largeurScore, int hauteur)
		throw(InstanceManquante);
	~Jeu();

    int largeur() const throw();

	void colorerElements() throw();
	Serpent* joueur(int joueurId) throw();

	void initialiserJoueurs() throw(InstanceManquante);

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserScores() throw();

	virtual void afficher(SDL_Surface* ecran);
	void afficherJeu(SDL_Surface* ecran);
	void afficherScores(SDL_Surface* ecran);

	/**
	 * Démarre une partie de zatacka
	 * On affiche l'écran de jeu (vide) et on remet les scores à 0
	 * avant de les afficher.
	 *
	 * @param nombreJoueurs: nombre de joueurs qui vont jouer la partie
	 */
	void demarrerPartie(int nombreJoueurs);
	bool jouerManche();

	/**
	 * Dessine un point d'une couleur donnée sur l'écran de jeu.
	 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
	 * sur un autre écran lancera une exception.
	 *
	 * @param ecran: ecran sur lequel on trace le point
	 * @param position: position du point à tracer
	 * @param couleur: nom de la couleur à utiliser
	 *
	 * @throw TraceImpossible
	 */
	void tracerPoint(SDL_Surface* ecran, SDL_Rect* position,
			Couleur couleur) const throw(TraceImpossible);

	/**
	 * Met à jour le score d'un joueur
	 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
	 * sur un autre écran lancera une exception.
	 *
	 * @param couleurJoueur: Couleur du joueur dont le score change. Cela
	 * 	correspond à l'index du texte de score dans le vecteur m_scores
	 * @param score: le nouveau score à afficher
	 */
	void changerScore(Couleur couleurJoueur, int score) throw();

	void actualiserScores(int indexJoueurPerdant);
};

#endif /* JEU_H_ */
