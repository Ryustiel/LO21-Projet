#pragma once
#include "../exception/ShottenTottenException.h"
#include "Hand.h"

class Player {
public:
  Player(const string& n, bool i, bool ia){};
    + fonctionIA() 
    + getNom() const : const string&
    + getId() const : unsigned int
    + estIA() const : bool;
    + getScore() const : unsigned int
    + getMain() const : const Cartes**

}class PlayerAIRandom : public Player {
    PlayerAIRandom(const string& n, bool idPlayer) : Player(n, idPlayer) {}
};
