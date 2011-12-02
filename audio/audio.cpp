#include "audio.h"

using namespace std;

int Audio::m_nombreJoueurs = 5;
int Audio::m_nombreJoueursVivants = 5;
int Audio::m_nombreJoueursVivantsAvant = 5;

Audio::Audio():
    m_transition(true) {
  initialiserAudio();
}

Audio::~Audio(){
  Mix_CloseAudio();
}



void* Audio::threadAudioCallback(void* audioVoid){
  Audio* m_audio = (Audio*) audioVoid;
  m_audio->fonctionThread();
  return 0;
}

void Audio::initialiserAudio(){
  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 1, 4096 ) == -1){
    //cout << "Error in Mix_OpenAudio" << endl;
  }
  //cout << "Initialisation de l'audio ! " << endl;
  m_numeroMorceau = 1;
  m_numeroSample = 0;
  //cout << "Initialisation de l'audio ! " << endl;
  pthread_create(&threadAudio, NULL, threadAudioCallback, (void*)this);
}

void Audio::chargerEffets(){

}

void Audio::fonctionThread(){
  while (true){

    if (!Mix_PlayingMusic()){
      //cout << "Aucune musique n'est en train d'être jouée" << endl;
      //cout << "Nombre de joueurs vivants : " << m_nombreJoueursVivants << "  ---  Nombre de joueurs vivants avant : " << m_nombreJoueursVivantsAvant << endl;
      const char* cheminFichier = construireCheminFichier();
      //cout << cheminFichier <<endl;
      m_sample = Mix_LoadMUS(cheminFichier);
      Mix_PlayMusic(m_sample,-1);

      if(m_transition){
        m_transition = false;
      }
    }

    if (m_nombreJoueursVivants != m_nombreJoueursVivantsAvant){
      //cout << "Coucou, m_nombreJoueursVivants et m_nombreJoueursVivantsAvant sont différents ! " << m_nombreJoueursVivants << " " << m_nombreJoueursVivantsAvant << endl;
      m_numeroSample += 1;
      m_transition = true;
      m_nombreJoueursVivantsAvant = m_nombreJoueursVivants;
    }

    SDL_Delay(5);
  }
}

zz//void Audio::chargerMusique(){
////  Mix_PlayMusic(Mix_LoadMUS("audio/musique_1/menu_1.wav"),1);
////  void (Audio::*ptrMusiqueFinie)() = &Audio::musiqueFinie;
////  Mix_HookMusicFinished(this->*ptrMusiqueFinie);

//  //HACK
//  int tempsActuel = 0;

//  if (tempsActuel-m_tempsPrecedent>=5600){
//    //SDL_Delay (max(5700 - (tempsActuel-m_tempsPrecedent),0));
//    //cout << "tempsActuel : " << tempsActuel << "  ---  tempsPrecedent : " << m_tempsPrecedent << "  ---  différence : " << (5700 - (tempsActuel-m_tempsPrecedent)) << endl;
//    //cout << "Nombre de joueurs vivants : " << m_nombreJoueursVivants << endl;
//    m_tempsPrecedent = tempsActuel;
//    Mix_PlayMusic(Mix_LoadMUS("audio/musique_1/jeu_3_2.wav"),1);
//  }
//}

void Audio::changerMusique(){

}

const char* Audio::construireCheminFichier(){
  string numeroMorceauString = intVersString(m_numeroMorceau);
  string numeroSampleString = intVersString(m_numeroSample);
  string chemin = "audio/musique_";
  chemin += numeroMorceauString;
  chemin += "/";
  chemin += numeroSampleString;
  if (m_transition){
    chemin += "_1.wav";
  } else {
    chemin += "_2.wav";
  }
  const char* cheminChar = chemin.c_str();
  return cheminChar;
}

string Audio::intVersString(int entier){
  std::stringstream stream;
  stream << entier;
  return stream.str();
}

void Audio::actualiserNombreJoueurs(int nombreJoueurs){
  //cout << "Coucou, j'actualise le nombre de joueurs ! " << nombreJoueurs << endl;
  m_nombreJoueurs = nombreJoueurs;
  m_nombreJoueursVivants = nombreJoueurs;
  m_nombreJoueursVivantsAvant = nombreJoueurs;
}

void Audio::actualiserNombreJoueursVivants(int nombreJoueursVivants){
  //cout << "Coucou, j'actualise le nombre de joueurs vivants ! " << nombreJoueursVivants << endl;
  m_nombreJoueursVivants = nombreJoueursVivants;
  //cout << "Je l'ai mis à la valeur : " << m_nombreJoueursVivants << endl ;
}
