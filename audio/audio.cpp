#include "audio.h"

using namespace std;

Audio::Audio(){
  cout << "coucou" << endl;
//  chargerMusique(1);
//  Mix_PlayMusic(m_musique, 1);
}

Audio::~Audio(){
  Mix_CloseAudio();
}

void Audio::initialiserAudio(){
  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 1, 4096 ) == -1){
    cout << "Error in Mix_OpenAudio" << endl;
  }
}

void Audio::chargerEffets(){

}

void Audio::chargerMusique(int numeroMorceau){
  m_musique = Mix_LoadMUS("audio/musique.wav");
  if (m_musique == NULL) {
    cout << "Error in LoadMUS" << endl;
  }
}
