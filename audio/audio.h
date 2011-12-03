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
   * Nombre de morceaux par thème (0 : musique du menu , 1-nombreMorceauxParTheme : musiques du jeu, nombreMorceauxParTheme +1 : game over)
   */
  std::map<int, int> m_morceauxParTheme;

  const char* construireCheminFichier();

  std::string intVersString(int entier);

public:

  Audio();

  ~Audio();

  void changerMusique();

  void changerTheme();

  void initialiserAudio();

  void actualiserNombreJoueurs(int nombreJoueurs);

  void actualiserMeilleurScore(int score);

//  void diminuerNombreJoueurs();

};
#endif /* AUDIO_H_ */
