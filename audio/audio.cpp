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
  chargerMusique(1);
}

void Audio::chargerEffets(){

}

void Audio::chargerMusique(){
    Mix_PlayMusic(Mix_LoadMUS("audio/musique_1/menu_1.wav"),1);
}

/*void Audio::chargerPaire(int numeroPaire, int numeroMorceau){
  pair <Mix_Music*, Mix_Music*> paire;
  string numeroMorceauString = intVersString(numeroMorceau);
  if (numeroPaire == -1){
    string chemin1 = "audio/musique_";     // Là c'est dégueulasse, mais je dois passer un const char* en argument à la fonction
    string chemin2 = "audio/musique_";
    chemin1 += numeroMorceauString;        // Mix_LoadMUS, donc je n'ai rien trouvé de mieux que de passer par les string pour
    chemin2 += numeroMorceauString;
    chemin1 += "/menu_1.wav";              // construire le chemin du fichier à ouvrir, et de revenir à un const char* après.
    chemin2 += "/menu_2.wav";
    const char* chemin1Char = chemin1.c_str();
    const char* chemin2Char = chemin2.c_str();
    paire.first = Mix_LoadMUS(chemin1Char);
    paire.second = Mix_LoadMUS(chemin2Char);
  } else {
    string numeroPaireString = intVersString(numeroPaire);
    string chemin1 = "audio/musique_";
    string chemin2 = "audio/musique_";
    chemin1 += numeroMorceauString;
    chemin2 += numeroMorceauString;
    chemin1 += "/jeu_";
    chemin2 += "/jeu_";
    chemin1 += numeroPaireString;
    chemin2 += numeroPaireString;
    chemin1 += "_1.wav";
    chemin2 += "_2.wav";
    const char* chemin1Char = chemin1.c_str();
    const char* chemin2Char = chemin2.c_str();
    paire.first = Mix_LoadMUS(chemin1Char);
    paire.second = Mix_LoadMUS(chemin2Char);
  }
  m_musiquePreChargee.push_back(paire);
}*/

string Audio::intVersString(int entier){
  std::stringstream stream;
  stream << entier;
  return stream.str();
}

void Audio::actualiserNombreJoueurs(int nombreJoueursVivants){
  m_nombreJoueursVivants = nombreJoueursVivants;
}
