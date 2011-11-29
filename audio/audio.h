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
#include "../util/exception.h"
#include "../util/keywords.h"

class Audio {
private:

  SDL_AudioSpec audioSortie;

  //La musique qui sera jouée
  Mix_Music *music = NULL;

  //Les effets sonores que nous allons utiliser
  Mix_Chunk *crash = NULL;
  Mix_Chunk *high = NULL;
  Mix_Chunk *med = NULL;
  Mix_Chunk *low = NULL;

public:

  void audioCallback(void *udata, Uint8 *stream, int len);

  int audio_Init(void);

  int mixerInit();

}
#endif /* AUDIO_H_ */
