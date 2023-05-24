#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Hand.h"

class Player {
private:
    std::string name;
    unsigned int id;
    unsigned int score = 0;
    Hand* hand = nullptr;
    int pick; // player's card pick to be viewed by the controller

    friend class Controller;

public:
    const string& getName() const { return name; }
    unsigned int getScore() const { return score; }
    const Hand* getHand() const { return hand; }
    void setHand(const Card* c[6]) {
        if (hand == nullptr) hand = new Hand(c);
    }
    void setHand(const Card** c, size_t n) {
        if (hand == nullptr) hand = new Hand(c, n);
    }

    // s'utilise avec getScore pour gérer le score de victoire de manches du joueur
    void updateScore() { std::cout << "\nscore mis a jour pour un joueur : " << score++; }

    // initialisation du joueur pour la partie
    void init() { std::cout << "\ninit variables de score pour manche"; score = 0;}
    // initRound lancée à chaque début de Manche
    void initRound() { std::cout << "\ninitializing player variables pour le debut de manche : fetching deck cards";}
    // méthode complexe qui déclenchera l'interface de choix de carte
    // la cascade d'événements suivants du tour
    // (vérifier une borne, intéragir avec l'effet d'une carte tactique...)
    // sera gérée par le contrôleur
    void playTurn() {
        cout << "Here's " << name << "!" << endl;
    }
    
protected :
    Player(const string& n)
        : name(n) {}
    ~Player() {
        delete hand;
    }
};

class PlayerAIRandom : public Player {
private:
    //
public:
    PlayerAIRandom(const string& n) : Player(n) {}
};
