#include "../head/Controller.h"
#include <iostream>

void Controller::newGame(int nmanches) { // + additional parameters
    std::cout << "\n\nINIT NEW GAME =====";
    std::cout << "\nmanches_restantes = parametre;";
    player1->init(); player2->init();
    
    manches_restantes = nmanches;
    manches_total = nmanches;
    while (manches_restantes > 0 && !stop) { // conditions d'arret des manches
        handleNewManche();
        manches_restantes--;
    }
    std::cout << "\n\nFIN DE PARTIE";
}

void Controller::handleNewManche() {
    std::cout << "\n\nINIT NEW MANCHE =====";
    std::cout << "\ntour = 0;";
    std::cout << "\npioche.init();";
    std::cout << "\nTacticController : pioche_tactique.init();";
    board->init();
    player1->initManche(); player2->initManche();

    TEMP_victory_counter = 0;

    runMancheLoop();

    std::cout << "\n\nEVENEMENTS DE FIN DE MANCHE --> DEBUT D'UNE NOUVELLE MANCHE OU FIN DE PARTIE (selon scores et nmanches definis)";
    std::cout << "\nSCORES : " << player1->getScore() << " vs " << player2->getScore();
}

void Controller::runMancheLoop() {
    std::cout << "\n\nManche Loop ================";
    // gere toute la manche
    while (!board->isWon() && !stop) { // conditions de fin de manche
        std::cout << "\n\nRunning Manche " << (manches_total - manches_restantes + 1);
        if (tour) {
            std::cout<<"\n\nplayer1 :";
            player1->playTurn();
            tour=false;
        } 
        else {
            std::cout<<"\n\nplayer2 :";
            player2->playTurn(); 
            tour=true;
        }
        runChecks(); // TEMP : should be triggered through Player::playTurn()
        
        // les scores de manche des joueurs seront mis a jour...
        // en meme temps que le statut de victoire du plateau (pas ici)
        // le controleur ne fait que changer l'état du jeu en réponse à l'événement de victoire.
    }
}

void Controller::runChecks() { // this is called by a player
    std::cout << "Triggering board checks, can update the state of the game";
    if (++TEMP_victory_counter >= 3) {
        board->setWon();
        player1->updateScore();
        std::cout << "\n\nTOUR GAGNE PAR JOUEUR 1";
    }
}

