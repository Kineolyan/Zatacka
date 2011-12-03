#include "audio.h"

using namespace std;

Audio::Audio():
    m_transition(true) {
  initialiserAudio();
}

Audio::~Audio(){
  Mix_CloseAudio();
}

void Audio::initialiserAudio(){
  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 1, 4096 ) == -1){
    //cout << "Error in Mix_OpenAudio" << endl;
  }
  //cout << "Initialisation de l'audio ! " << endl;

  /* Configuration des morceaux */
  m_morceauxParTheme[1] = 5;
  m_nombreThemes = 1;

  m_numeroTheme = rand()%m_nombreThemes +1;
  m_numeroMorceau = 0;
  m_nombreJoueurs = 6;
  srand(time(NULL));
  Mix_PlayMusic(m_sampleTransition,1);
  Mix_HookMusicFinished(threadAudioCallback);
  //cout << "Initialisation de l'audio ! " << endl;
  //pthread_create(&threadAudio, NULL, threadAudioCallback, (void*)this);
}

void actualiserMeilleurScore(int meilleurScore){

}

void Audio::changerMusique(){
  Mix_HaltMusic();
  const char* cheminFichier = construireCheminFichier();
  m_musique = Mix_LoadMUS(cheminFichier);
  Mix_PlayMusic(m_musique,-1);
}

void Audio::changerTheme(){
  m_numeroTheme =
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

const char* Audio::construireCheminFichier(){
  string numeroMorceauString = intVersString(m_numeroTheme);
  string numeroSampleString = intVersString(m_numeroMorceau);
  string chemin = "audio/musique_";
  chemin += numeroMorceauString;
  chemin += "/";
  chemin += numeroSampleString;
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
