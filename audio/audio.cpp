#include "audio.h"

using namespace std;

Audio::Audio(){
  audio_Init();
  mixerInit();
}

Audio::~Audio(){

}

void mixerInit(){
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
    return false;
  }
}

int audio_Init(void) {
    // Définition des propriétés audio
    audioSortie.freq = 22050;
    audioSortie.format = AUDIO_S16;
    audioSortie.channels = 1;
    audioSortie.samples = 1024;
    audioSortie.callback = audioCallback;
    audioSortie.userdata = NULL;

    // Initialisation de la couche audio
    if (SDL_OpenAudio(&audio, NULL) < 0)
    {
        fprintf(stderr, "Erreur d'ouverture audio: %s\n", SDL_GetError());
        return (-1);
    }

    return 0;
}
