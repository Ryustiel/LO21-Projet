#pragma once
#include "../exception/ShottenTottenException.h"

class Player {
  std::string name;
  unsigned int id;
  bool is_IA;  //0 = non, 1 = oui
  unsigned int score;  //initialisé à 0
  Hand hand;
public:
  Player(const string& n, bool i, bool ia){};
    - ~Joueur() //suppr. main*
    + fonctionIA() 
    + getNom() const : const string&
    + getId() const : unsigned int
    + estIA() const : bool;
    + getScore() const : unsigned int
    + getMain() const : const Cartes**

}