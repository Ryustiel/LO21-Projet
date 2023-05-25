#include "../head/Controller.h"
#include <iostream>

void Controller::newRoundInit() {
    //init decks
    clanDeck = new Deck(clanGame);
    //init board
    board = Board();
}

void Controller::runChecks() { // this is called by a player
    std::cout << "Triggering board checks, can update the state of the game";
    if (++TEMP_victory_counter > 2) {
        //board.setWon();
        player1->updateScore();
        std::cout << "\n\nround GAGNE PAR JOUEUR 1";
    }
}

