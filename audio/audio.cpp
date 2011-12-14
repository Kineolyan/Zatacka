#include "audio.h"

using namespace std;

Audio::Audio():
    m_meilleurScore(0), m_meilleurScoreAvant(0), m_boucler(true) {
  initialiserThemes();
  changerTheme();
  initialiserAudio();
}

Audio::~Audio(){
  Mix_CloseAudio();
}

void Audio::initialiserThemes(){
  m_morceauxParTheme[1] = 5;
  m_nombreThemes = 1;
}

void Audio::initialiserAudio(){
  Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 1, 4096 );
  m_numeroMorceau = 0;
  m_nombreJoueurs = 6;
  srand(time(NULL));
  chargerMorceau();
}

void Audio::actualiserMeilleurScore(int score){
  if (score>m_meilleurScore){
    m_meilleurScore = score;
    if (testChangerMusique()){
      m_numeroMorceau += 1;
      chargerMorceau();
      m_meilleurScoreAvant = m_meilleurScore;
    }
  }
}

bool Audio::testChangerMusique(){
  bool test;
  int longueurSegment = ((m_nombreJoueurs -1)*10/m_morceauxParTheme[m_numeroTheme]);
  test = m_meilleurScore / longueurSegment > m_meilleurScoreAvant /longueurSegment;
  return test;
}

void Audio::chargerMorceau(){
  if (Mix_PlayingMusic()){
    Mix_HaltMusic();
  }
  if (finPartie()){
    m_boucler = false;
  }
  const char* cheminFichier = construireCheminFichier();
  m_musique = Mix_LoadMUS(cheminFichier);
  if (m_boucler){
    Mix_PlayMusic(m_musique, -1);
  } else {
    Mix_PlayMusic(m_musique, 1);
  }

}

void Audio::changerTheme(){
  m_numeroTheme = rand()%m_nombreThemes +1;
}

const char* Audio::construireCheminFichier(){
  string numeroMorceauString = intVersString(m_numeroTheme);
  string numeroSampleString = intVersString(m_numeroMorceau);
  string chemin = "audio/musique_";
  chemin += numeroMorceauString;
  chemin += "/";
  chemin += numeroSampleString;
  chemin += ".ogg";
  const char* cheminChar = chemin.c_str();
  return cheminChar;
}

string Audio::intVersString(int entier){
  std::stringstream stream;
  stream << entier;
  return stream.str();
}

void Audio::commencerPartie(){
  m_meilleurScore = 0;
  m_meilleurScoreAvant = 0;
  m_numeroMorceau = 1;
  m_boucler = true;
  chargerMorceau();
}

bool Audio::finPartie(){
  return (m_numeroMorceau == m_morceauxParTheme[m_numeroTheme] +1);
}

void Audio::menu(){
  m_numeroMorceau = 0;
  m_boucler = true;
  chargerMorceau();
}

void Audio::actualiserNombreJoueurs(int nombreJoueurs){
  m_nombreJoueurs = nombreJoueurs;
  m_meilleurScore = 0;
}
