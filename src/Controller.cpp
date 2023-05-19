#include "../head/Controller.h"
#include <iostream>

void Controller::eventNewGame(int nturns) { // + additional parameters

    std::cout << "\n===================== newGame";
    std::cout << "\n(RE)INITIALISE...";
    std::cout << "les informations qui restent constantes d'une manche a l'autre";
    std::cout << "\n>> le nombre de tours selectionnes";
    std::cout << "\n(RE)INITIALISE egalmement les elements variables qui gardent trace du jeu";
    std::cout << "\n>> le nombre de tours restants";
    std::cout << "\n>> le score des joueurs";

    // player1->init(); player2->init();
    
    setRemainingRounds(2);
    setTotalRounds(2);

    newRound();
}

void Controller::newRound() {
    std::cout << "\n===================== newRound";
    std::cout << "\n(RE)INITIALISE les variables qui doivent l'etre au debut de chanque manche";
    std::cout << "\n>> round = 0 ou un random number, garde trace du joueur qui doit jouer";
    std::cout << "\n>> DECREMENTE le compteur de rounds restants";
    std::cout << "\n>> TacticController : pioche_tactique.init();";
    std::cout << "\n>> initialise le plateau"; // board.init();
    std::cout << "\n>> initialise les pioches";
    std::cout << "\n>> initialise les joueurs et leurs mains";

    // player1->initRound(); player2->initRound();

    TEMP_victory_counter = 0;

    eventStartTurn();
}

void Controller::checkRound() {
    std::cout << "\n=============================== checkRound";
    std::cout << "\nregarde le score de la manche";
    // std::cout << "\nSCORES : " << player1->getScore() << " vs " << player2->getScore();
    std::cout << "\nrelance un round si le score est sous la limite";
    std::cout << "\narrete la partie si score atteint ou nombre max de rounds depasse";
    std::cout << "\ndeclenche qtDisplayVictoryMenu()";
    std::cout << "\nsinon declenche newRound()";
}

void Controller::eventStartTurn() {
    std::cout << "\n====================== startTurn";

    std::cout << "\nINITIALISE les variables pour le tour en cours";
    std::cout << "\nil s'agit essentiellement du compteur d'actions = pioche? revendication?";
    std::cout << "\npour empecher le joueur de faire trop d'actions";

    std::cout << "\nVERIFIE les conditions de victoire pour la manche en cours (bornes)";
    std::cout << "\nsi manche gagnee declenche checkRound()";
    std::cout << "\nsinon enregistre un callback pour eventStartTurn()";
    std::cout << "\ndeclenche qtDisplayPlayerTurn()";

}