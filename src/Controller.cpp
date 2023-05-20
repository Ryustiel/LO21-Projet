#include "../head/Controller.h"
#include <iostream>

void Controller::runGame(int nturns, int winthreshold) { // + additional parameters

    std::cout << "\n===================== newGame";

    player1->initForNewGame();
    player2->initForNewGame();
    
    // le plateau a-t-il besoin d'�tre initialis� � ce niveau ?

    remainingRounds = nturns;
    totalRounds = nturns;
    maxScore = winthreshold;

    newRound();
}

void Controller::newRound() {
    std::cout << "\n===================== newRound";

    player1->initForNewRound();
    player2->initForNewRound();

    board.init();
    clanDeck->init(); // initialiser la pioche tactique dans la m�thode fille

    turn = false;

    eventStartTurn();
}

void Controller::checkRound() {
    std::cout << "\n=============================== checkRound";
    remainingRounds--;
    if (remainingRounds <= 0 || player1->getScore() >= maxScore || player2->getScore() >= maxScore) {
        qtGameOver();
    } else {
        newRound();
    }
}

void Controller::eventStartTurn() {
    std::cout << "\n====================== startTurn";

    Side winning = board.evaluateGameWinner();
    winning = Side::s1; // TEMP
    if (winning == Side::none) {

        if (turn == false) { turn = true; }
        else { turn = false; }
        // initialiser les contraintes d'actions pour le tour en cours
        qtDisplayPlayerTurn();

    } else {

        if (winning == Side::s1) {
            player1->updateScore();
        }
        else {
            player2->updateScore();
        }
        checkRound();

    }

    

    

}