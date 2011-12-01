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
#include <vector>
#include <sstream>
#include "../util/exception.h"
#include "../util/keywords.h"

class Audio {
private:

//  SDL_AudioSpec audioSortie;

  /**
   * Nombre de joueurs participant à la partie.
   */
  int m_nombreJoueursActifs;

  /**
   * Nombre de joueurs encore en vie.
   */
  int m_nombreJoueursVivants;

  /**
   * Nombre de joueurs encore en vie au dernier chargement de fichier audio.
   */
  int m_nombreJoueursVivantsAvant;

  void chargerMusique();

  void chargerPaire(int numeroPaire, int numeroMorceau);

  std::string intVersString(int entier);

public:

  Audio();

  ~Audio();

//  void audioCallback(void *udata, Uint8 *stream, int len);

  void initialiserAudio();

  void chargerEffets();

  void actualiserNombreJoueurs(int nombreJoueursVivants);

//  void diminuerNombreJoueurs();

};
#endif /* AUDIO_H_ */
