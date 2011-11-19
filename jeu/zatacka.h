#ifndef ZATACKA_H_
#define ZATACKA_H_

#include <SDL/SDL.h>
#include <map>
#include <vector>
#include "texte.h"
#include "option.h"
#include "../exceptions/exception.h"

/**
 * Instance de jeu gerant les différents écrans, les serpents, les options
 */
class Zatacka {
private:
	enum NomEcran {
		ACCUEIL, MENU_PRINCIPAL, MENU_OPTIONS, JEU
	};

public:
	enum Couleur {
		BLANC=0, JAUNE=1, BLEU=2, ROUGE=3, VERT=4, VIOLET=5, ORANGE=6,
		NOIR=7
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
	SDL_Surface* m_ecranJeu;

	/**
	 * Ecran affichant les scores
	 */
	SDL_Surface* m_ecranScores;

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
	 * Crée l'écran de jeu avec avec la zone de jeu et le panneau des scores.
	 * Les motifs utilises pour tracer les serpents sont egalement instancies.
	 *
	 * @throw InstanceManquante
	 */
	void creerJeu();

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
	Zatacka(int largeur, int hauteur);
	/**
	 * Destructeur
	 */
	~Zatacka();

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
	//Couleur donnerCouleurs(const SDL_Rect& position);

	/**
	 * Met à jour le score d'un joueur
	 * Cette methode ne permet que de tracer sur l'écran de jeu. Un tracé
	 * sur un autre écran lancera une exception.
	 *
	 * @param joueurId: Id du joueur dont le score change. Cela correspond
	 * 	a l'index du texte de score dans le vecteur m_scores
	 * @param score: le nouveau score à afficher
	 *
	 * @throw TraceImpossible
	 */
	void changerScore(int joueurId, int score);
};

#endif /* ZATACKA_H_ */
