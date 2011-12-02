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
#include <vector>
#include <algorithm>
#include "pthread.h"
#include "../util/exception.h"
#include "../util/keywords.h"

class Audio {
private:


  /**
   * Sample en cours de lecture
   */
  Mix_Music* m_basse;

  /**
   * Numéro du morceau en cours de lecture
   */
  int m_numeroMorceau;

  /**
   * Numéro du sample en cours de lecture
   */
  int m_numeroSample;

  /**
   * Nombre de joueurs participant à la partie.
   */
  static int m_nombreJoueurs;

  /**
   * Nombre de joueurs encore en vie.
   */
  static int m_nombreJoueursVivants;

  /**
   * Nombre de joueurs encore en vie au dernier chargement de fichier audio.
   */
  static int m_nombreJoueursVivantsAvant;

  /**
   * Le son joué actuellement est-il une transition (i.e. doit être joué une unique fois) ?
   */
  bool m_transition;

  const char* construireCheminFichier();

  std::string intVersString(int entier);

  pthread_t threadAudio;

public:

  Audio();

  ~Audio();

  static void* threadAudioCallback(void*);

  void fonctionThread();

  void chargerMusique();

  void musiqueFinie();

  void initialiserAudio();

  void chargerSamples();

  void actualiserNombreJoueurs(int nombreJoueurs);

  void actualiserNombreJoueursVivants(int nombreJoueursVivants);

//  void diminuerNombreJoueurs();

};
#endif /* AUDIO_H_ */
