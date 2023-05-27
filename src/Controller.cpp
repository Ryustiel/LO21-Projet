#include "../head/Controller.h"
#include <iostream>

void Controller::newGame(int nbTurns) { // + additional parameters
    std::cout << "\n\nINIT NEW GAME =====";
    std::cout << "\nremainingRounds = parametre;";
    //player1->init(); player2->init();
    
    remainingRounds = nbTurns;
    totalRounds = nbTurns;
    while (remainingRounds > 0 && !stop) { // conditions d'arret des manches
        handleNewRound();
        remainingRounds--;
    }
    std::cout << "\n\nFIN DE PARTIE";
}

void Controller::handleNewRound() {
    std::cout << "\n\nINIT NEW MANCHE =====";
    std::cout << "\nround = 0;";
    std::cout << "\npioche.init();";
    std::cout << "\nTacticController : pioche_tactique.init();";
    //board.init();
    //player1->initRound(); player2->initRound();

    TEMP_victory_counter = 0;

    runRoundLoop();

    std::cout << "\n\nEVENEMENTS DE FIN DE MANCHE --> DEBUT D'UNE NOUVELLE MANCHE OU FIN DE PARTIE (selon scores et nbTurns definis)";
    std::cout << "\nSCORES : " << player1->getScore() << " vs " << player2->getScore();
}

void Controller::runRoundLoop() {
    /*
    std::cout << "\n\nManche Loop ================";
    // gere toute la manche
    while (!board.isWon() && !stop) { // conditions de fin de manche
        std::cout << "\n\nRunning Manche " << (totalRounds - remainingRounds + 1);
        if (round) {
            std::cout<<"\n\nplayer1 :";
            player1->playTurn();
            round=false;
        } 
        else {
            std::cout<<"\n\nplayer2 :";
            player2->playTurn(); 
            round=true;
        }
        runChecks(); // TEMP : should be triggered through Player::playTurn()
        
        // les scores de manche des joueurs seront mis a jour...
        // en meme temps que le statut de victoire du plateau (pas ici)
        // le controleur ne fait que changer l'état du jeu en réponse à l'événement de victoire.
    }*/
}

void Controller::runChecks() { // this is called by a player
    std::cout << "Triggering board checks, can update the state of the game";
    if (++TEMP_victory_counter > 2) {
        //board.setWon();
        player1->updateScore();
        std::cout << "\n\nround GAGNE PAR JOUEUR 1";
    }
}

