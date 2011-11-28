#ifndef ZATACKA_H_
#define ZATACKA_H_

#include <SDL/SDL.h>
#include <map>
#include <vector>
#include <iostream>
#include "texte.h"
#include "option.h"
#include "../util/keywords.h"
#include "jeu.h"
#include "../util/exception.h"
#include "../serpent/serpent.h"

/**
 * Instance de jeu gerant les différents écrans, les serpents, les options
 */
class Zatacka {
private:
	enum NomEcran {
		ACCUEIL, MENU_PRINCIPAL, MENU_OPTIONS, JEU
	};

private:

	/**
	 * Largeur de la fenetre de jeu
	 */
	int m_largeur;

	/**
	 * Hauteur de la fenetre
	 */
	int m_hauteur;

	/**
	 * Largeur du panneau des scores
	 */
	int m_largeurScores;

	/**
	 * Ecran principal
	 */
	SDL_Surface* m_ecran;

	/**
	 * Ecran de jeu contenant les serpents
	 */
	Jeu m_ecranJeu;

	/**
	 * Motifs de base pour le trace des serpents
	 */
	std::vector<SDL_Surface*> m_points;

	/**
	 * Ecran à afficher
	 */
	NomEcran m_ecranAAfficher;

	/**
	 * Police calligraphiee pour l'accueil et les scores
	 */
	TTF_Font* m_policeCalligraphiee;

	/**
	 * Police basique pour les textes de menu
	 */
	TTF_Font* m_policeBasique;

	/**
	 * Tableau des couleurs rgb à utiliser
	 */
	std::vector<SDL_Color*> m_couleurs;

	/**
	 * Options pour activer ou pas un joueur
	 */
	std::vector<Option*> m_optionJoueurs;

	/**
	 * Options pour activer les différentes règles de jeu
	 */
	std::vector<Option*> m_options;

	/**
	 * Tableau des textes affichant les scores sur l'écran
	 * de jeu
	 */
	TexteSDL m_scores[6];

	/**
	 * Tableau des joueurs
	 */
	//Serpent m_joueurs[6];

	/**
	 * Instancie les polices en chargeant le fichier et définit la taille
	 */
	void chargerPolices();

	/**
	 * Crée la liste des couleurs, en donnant les codes RGB
	 */
	void initialiserCouleurs();

	/**
	 *
	 */
	void initialiserJeu();

	/**
     * Crée une couleur
     * Le but de cette méthode est d'éviter le warning du compilateur
     */
    SDL_Color* creerCouleur(Uint8 r, Uint8 g, Uint8 b) throw();

	/**
	 * Créer les options du menu principal et leur assigne une position à
	 * l'écran
	 */
	void creerMenuPrincipal();

	/**
	 * Crée les options du menu d'options et leur assigne une position.
	 */
	void creerMenuOptions();

	/**
	 * Affiche l'écran d'accueil
	 */
	void afficherAccueil();

	/**
	 * Affiche le menu principal
	 */
	void afficherMenuPrincipal();

	/**
	 * Affiche le menu des options
	 */
	void afficherMenuOptions();

	/**
	 * Affiche l'écran de jeu
	 */
	void afficherJeu();

	/**
	 * Afficher l'écran demandé
	 *
	 * @param ecran: nom de l'écran à afficher
	 */
	void afficher(NomEcran ecran);

	/**
	 * Efface l'écran
	 */
	void effacer();

	/**
	 * Regle les temps de répétition des touches
	 * Lorsqu'une touche reste enfoncée, on regénère un événement au bout de
	 * t millisecondes.
	 *
	 * @param t: temps d'écart entre deux répétitions
	 */
	void reglerRepetition(int t);

	void resetOptions() throw();

	void resetOptionJoueurs() throw();

public:
	/**
	 * Constructeur
	 * @param largeur: largeur de la fenetre
	 * @param hauteur: hauteur de la fenetre
	 */
	Zatacka(int largeur, int hauteur);
	/**
	 * Destructeur
	 */
	~Zatacka();

	int hauteur() const throw();
	int largeur() const throw();
	int hauteurJeu() const throw();
	int largeurJeu() const throw();
	SDL_Color* couleur(Couleur couleur);
	TTF_Font* policeCalligraphiee();
	TTF_Font* policeBasique();
	SDL_Surface* ecran();

	/**
	 * Remplit une surface de la couleur demandee
	 */
	void colorer(SDL_Surface* ecran, Couleur couleur);

	/**
	 * Dessine un point d'une couleur donnée sur l'écran de jeu.
	 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
	 * sur un autre écran lancera une exception.
	 *
	 * @param position: position du point à tracer
	 * @param couleur: nom de la couleur à utiliser
	 *
	 * @throw TraceImpossible
	 */
	void tracerPoint(SDL_Rect* position, Couleur couleur);

	/**
	 * Renvoie la couleur des pixels d'une position donnee
	 */
	Couleur donnerCouleur(const SDL_Rect& position) const throw(HorsLimite);

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

	void afficherScores() throw();
};

#endif /* ZATACKA_H_ */
