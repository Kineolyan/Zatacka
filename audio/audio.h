/*
 * audio.h
 *
 *  Created on: 28 nov. 2011
 *      Author: mathias
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include "../util/exception.h"
#include "../util/keywords.h"

class Audio {
private:

//  SDL_AudioSpec audioSortie;

  //La musique qui sera jouée
  Mix_Music *m_musique;

  /**
   * Nombre de joueurs participant à la partie.
   */
  int m_nombreJoueursActifs;

  /**
   * Nombre de joueurs encore en vie.
   */
  int m_nombreJoueursVivants;

public:

  Audio();

  ~Audio();

  void audioCallback(void *udata, Uint8 *stream, int len);

//  int audio_Init(void);

  void chargerEffets();

  void chargerMusique(int numeroMorceau);

  void diminuerNombreJoueurs();

};
#endif /* AUDIO_H_ */
