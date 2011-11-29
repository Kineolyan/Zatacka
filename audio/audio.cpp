#include "audio.h"

using namespace std;

Audio::Audio(){
  cout << "Entrée dans le constructeur" << endl;
  if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 ) == -1){
    cout << "Error in Mix_OpenAudio" << endl;
  };
  chargerMusique(1);
  Mix_PlayMusic(m_musique, 1);
  /*if (m_musique == NULL) {
    cout << "Error in LoadMUS" << endl;
  }*/
  if(Mix_PlayingMusic() == 0){
    cout << "Mix_PlayingMusic() == 0" << endl;
  }
}

Audio::~Audio(){
  Mix_FreeMusic(m_musique);
  Mix_CloseAudio();
}

void Audio::chargerEffets(){

}

void Audio::chargerMusique(int numeroMorceau){
  m_musique = Mix_LoadMUS("audio/musique.mp3");
  if (m_musique == NULL) {
    cout << "Error in LoadMUS" << endl;
  }
}

//int audio_Init(void) {
//    // Définition des propriétés audio
//    audioSortie.freq = 22050;
//    audioSortie.format = AUDIO_S16;
//    audioSortie.channels = 1;
//    audioSortie.samples = 1024;
//    audioSortie.callback = audioCallback;
//    audioSortie.userdata = NULL;

//    // Initialisation de la couche audio
//    if (SDL_OpenAudio(&audio, NULL) < 0)
//    {
//        fprintf(stderr, "Erreur d'ouverture audio: %s\n", SDL_GetError());
//        return (-1);
//    }

//    return 0;
//}

void Audio::diminuerNombreJoueurs(){

}
