#pragma once
#include <iostream>

class Player {
private:
    int pick; // player's card pick
    int manches_gagnees;
public:
    void init() { std::cout << "\ninit variables de score pour manche"; manches_gagnees = 0;}
    void initManche() { std::cout << "\ninitializing player variables pour le debut de manche : fetching deck cards";}
    void playTurn() { std::cout << "\n\nplayer picking a card, through the controller's methods : card's effect activated, game board updated, combination checks enacted (if player chooses so), scores updated";}
    void updateScore() { std::cout << "\nscore mis a jour pour un joueur : " << manches_gagnees++; }
    int getScore() { return manches_gagnees; }
};