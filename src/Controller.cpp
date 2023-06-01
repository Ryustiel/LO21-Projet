#include "../head/Controller.h"
#include "../head/Supervisor.h"
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

void Controller::initForNewRound() {
    std::cout << "\n========= initForNewRound-legacy";
    //init the board
    board = Board();
    std::cout << "\nBoard init;";

    //init the deck
    delete clanDeck;
    clanDeck = new Deck(clanGame);// initialiser la pioche tactique dans la m�thode fille
    std::cout << "\nclanDeck init;";

    //init players and their hands
    const Card** handCards = new const Card * [handSize];
    const Card** handCards2 = new const Card * [handSize];
    if (clanDeck->drawMultiple(handCards, handSize) != handSize) throw ShottenTottenException("Controller::initForNewRound error : unable to draw the right amount of cards.");
    player1->initForNewRound(handCards, handSize);
    if (clanDeck->drawMultiple(handCards2, handSize) != handSize) throw ShottenTottenException("Controller::initForNewRound error : unable to draw the right amount of cards.");
    player2->initForNewRound(handCards2, handSize);

    current_side = Side::s1;

    // TO DO : appliquer la méthode de changement référence de joueur
    //proposition : faire un Side turn, qui prend les valeurs s1/s2 ? + simple pour savoir où poser les éléments sur les bornes (évite les if)
    //(de +, la fct° claimStone demande une Side)
}

void Controller::newRound() {
    std::cout << "\n===================== newRound";
    initForNewRound();
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
    //winning = Side::none; // TEMP
    if (winning == Side::none) {

        if (current_side == Side::s1) { current_side = Side::s2; }
        else { current_side = Side::s1; }

        // initialiser les contraintes d'actions pour le tour en cours
        //display QT interface
        qtDisplayPlayerTurn();
    }
    else {

        if (winning == Side::s1) {
            player1->updateScore();
        }
        else {
            player2->updateScore();
        }
        checkRound();

    }
}

void Controller::claimStone(Side s, unsigned int n) {
    if (s == Side::none) throw ShottenTottenException("claimStone : inadequate side s");
    if (n < 0 || n > board.getStoneNb() ) throw ShottenTottenException("claimStone : inadequate stone number n");

    //to revendicate a stone, current player's combination must be completed
    if ((s == Side::s1) && (board.getStone(n).getSizeP1() != board.getStone(n).getMaxSize())) {
        cout << "You can't revendicate this stone ! (combination not completed yet)";
        return;
    }
    else if ((s == Side::s2) && (board.getStone(n).getSizeP2() != board.getStone(n).getMaxSize())) {
        cout << "You can't revendicate this stone ! (combination not completed yet)";
        return;
    }

    //defining available cards count
    size_t availableCardsCount = clanDeck->getCardCount();

    if (s == Side::s1) {
        if(player2->getHand() != nullptr) availableCardsCount += player2->getHand()->getSize();
    }
    else {
        if (player1->getHand() != nullptr) availableCardsCount += player1->getHand()->getSize();
    }

    //creating tab containing all available cards (deck + opponent's cards)
    const Card** availableCards = new const Card * [availableCardsCount];

    //adding deck cards
    size_t i = 0;
    for (; i < clanDeck->getCardCount(); i++) { //adding clan Deck cards
        availableCards[i] = clanDeck->getCard(i);
        cout << "(claimStone) Card" << i << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[i]->getName() << endl;
    }
    //cout << i;

    if (s == Side::s1) {
        //adding the opponent's cards to available cards
        if (player2->getHand() != nullptr) {
            for (size_t k = 0; k < player2->getHand()->getSize(); k++) {
                availableCards[i] = clanDeck->getCard(i);
                i++;
            }
        }
    } else {
        //adding the opponent's cards to available cards
        if (player1->getHand() != nullptr) {
            for (size_t k = 0; k < player1->getHand()->getSize(); k++) {
                availableCards[i] = clanDeck->getCard(i);
                i++;
            }
        }
    }

    //evaluating stone's winner
    const Side evaluated_side = board.evaluateStoneWinningSide(n, availableCards, availableCardsCount);
    if (evaluated_side == s) {
        //revendicating the stone
    }
    else {
        cout << "You can't revendicate this stone!" << endl;
    }
}


void Controller::playTurn(Side s) {
    if (s == Side::s1) { //player1
        //play card

        //draw card

        //claim stone

    }
    else if (s == Side::s2) { //player2
        //play card

        //draw card

        //claim stone
    }
    throw ShottenTottenException("playTurn : inadequate side s");
}



//TACTIC CONTROLLER METHODS

void TacticController::claimStone(Side s, unsigned int n) {
    if (s == Side::none) throw ShottenTottenException("claimStone : inadequate side s");
    if (n < 0 || n > getBoard().getStoneNb()) throw ShottenTottenException("claimStone : inadequate stone number n");

    //to revendicate a stone, current player's combination must be completed
    if ((s == Side::s1) && (getBoard().getStone(n).getSizeP1() != getBoard().getStone(n).getMaxSize())) {
        cout << "You can't revendicate this stone ! (combination not completed yet)";
        return;
    }
    else if ((s == Side::s2) && (getBoard().getStone(n).getSizeP2() != getBoard().getStone(n).getMaxSize())) {
        cout << "You can't revendicate this stone ! (combination not completed yet)";
        return;
    }

    //defining available cards count
    size_t availableCardsCount = getClanDeck().getCardCount() + tacticDeck->getCardCount();

    if (s == Side::s1) {
        if (getPlayer2().getHand() != nullptr) availableCardsCount += getPlayer2().getHand()->getSize();
    }
    else {
        if (getPlayer1().getHand() != nullptr) availableCardsCount += getPlayer1().getHand()->getSize();
    }

    //creating tab containing all available cards (deck + opponent's cards)
    const Card** availableCards = new const Card * [availableCardsCount];

    //adding clan deck cards
    size_t i = 0;
    for (; i < getClanDeck().getCardCount(); i++) { //adding clan Deck cards
        availableCards[i] = getClanDeck().getCard(i);
        cout << "(claimStone) Card" << i << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[i]->getName() << endl;
    }
    //cout << i;

    //adding tactic cards
    for (size_t k = 0; k < getClanDeck().getCardCount(); k++) { //adding clan Deck cards
        availableCards[i] = tacticDeck->getCard(i);
        cout << "(claimStone) Card" << i << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[i]->getName() << endl;
        i++;
    }
    //cout << i;

    if (s == Side::s1) {
        //adding the opponent's cards to available cards
        if (getPlayer2().getHand() != nullptr) {
            for (size_t k = 0; k < getPlayer2().getHand()->getSize(); k++) {
                availableCards[i] = getClanDeck().getCard(i);
                i++;
            }
        }
    }
    else {
        //adding the opponent's cards to available cards
        if (getPlayer1().getHand() != nullptr) {
            for (size_t k = 0; k < getPlayer1().getHand()->getSize(); k++) {
                availableCards[i] = getClanDeck().getCard(i);
                i++;
            }
        }
    }

    //evaluating stone's winner
    const Side evaluated_side = getBoard().evaluateStoneWinningSide(n, availableCards, availableCardsCount);
    if (evaluated_side == s) {
        //revendicating the stone
    }
    else {
        cout << "You can't revendicate this stone!" << endl;
    }
}

void TacticController::initForNewRound() {
    Controller::initForNewRound();
    std::cout << "\n========= initForNewRound-Tactic";

    //init the tactic deck
    delete tacticDeck;
    tacticDeck = new Deck(tacticGame);// initialiser la pioche tactique dans la m�thode fille
    std::cout << "\ntacticDeck init;";
}
