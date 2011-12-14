/*
 * Audio.h
 *
 *  Created on: 28 nov. 2011
 *      Author: mathias
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cstdlib>
#include "pthread.h"
#include "../util/exception.h"
#include "../util/keywords.h"

class Audio {
private:

  /**
   * Nombre de joueurs dans la partie
   */
  int m_nombreJoueurs;

  /**
   * Meilleur score du moment
   */
  int m_meilleurScore;

  /**
   * Meilleur score au moment où on a changé de musique pour la dernière fois
   */
  int m_meilleurScoreAvant;

  /**
   * Musique en cours de lecture
   */
  Mix_Music* m_musique;

  /**
   * Nombre de thèmes disponibles
   */
  int m_nombreThemes;

  /**
   * Numéro du thème en cours de lecture
   */
  int m_numeroTheme;

  /**
   * Numéro du morceau en cours de lecture
   */
  int m_numeroMorceau;

  /**
   * Le morceau doit-il être joué en boucle ?
   */
  bool m_boucler;

  /**
   * Nombre de morceaux par thème (0 : musique du menu , 1-nombreMorceauxParTheme : musiques du jeu, nombreMorceauxParTheme +1 : game over)
   */
  std::map<int, int> m_morceauxParTheme;

  const char* construireCheminFichier();

  std::string intVersString(int entier);

public:

  Audio();

  ~Audio();

  int prochainMorceau();

  void chargerMorceau();

  bool testChangerMusique();

  void changerTheme();

  void initialiserAudio();

  void initialiserThemes();

  bool finPartie();

  void commencerPartie();

  void menu();

  void actualiserNombreJoueurs(int nombreJoueurs);

  void actualiserMeilleurScore(int score);

//  void diminuerNombreJoueurs();

};
#endif /* AUDIO_H_ */
