/*
 * jeu.h
 *
 *  Created on: 3 nov. 2011
 *      Author: oliv
 */

#ifndef JEU_H_
#define JEU_H_

#include <SDL/SDL.h>
#include <map>
#include <vector>
#include "texte.h"
#include "option.h"
#include "../exceptions/exception.h"

/**
 * Instance de jeu gerant les différents écrans, les serpents, les options
 */
class Jeu {
private:
	enum NomEcran {
		ACCUEIL, MENU_PRINCIPAL, MENU_OPTIONS, JEU
	};

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
	SDL_Surface* m_ecranJeu;

	/**
	 * Ecran affichant les scores
	 */
	SDL_Surface* m_ecranScores;

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
	std::map<std::string, SDL_Color*> m_couleurs;

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
	 * Instancie les polices en chargeant le fichier et définit la taille
	 */
	void chargerPolices();

	/**
	 * Crée la liste des couleurs, en donnant les codes RGB
	 */
	void initialiserCouleurs();

	/**
	 * Donne à chaque score une couleur, une police et une position
	 */
	void initialiserScores();

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
	void afficherEcranPrincipal();

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
	 * @param ecran: nom de l'écran à afficher
	 */
	void afficher(NomEcran ecran);

	/**
	 * Efface l'écran
	 */
	void effacer();

public:
	/**
	 * Constructeur
	 * @param largeur: largeur de la fenetre
	 * @param hauteur: hauteur de la fenetre
	 */
	Jeu(int largeur, int hauteur);
	/**
	 * Destructeur
	 */
	~Jeu();
};

#endif /* JEU_H_ */
