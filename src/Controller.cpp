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

void Controller::revendicateStone(Side s, unsigned int n) {
    if (s == Side::none) throw ShottenTottenException("revendicateStone : inadequate side s");
    if (n < 0 || n > board.getStoneNb() ) throw ShottenTottenException("revendicateStone : inadequate stone number n");

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
        cout << "(revendicateStone) Card" << i << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[i]->getName() << endl;
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
        
        //revendicate border

    }
    else if (s == Side::s2) {
        //play card
        //draw card
        //revendicate border
    }
    throw ShottenTottenException("playTurn : inadequate side s");
}



//TACTIC CONTROLLER METHODS

void TacticController::revendicateStone(Side s, unsigned int n) {
    if (s == Side::none) throw ShottenTottenException("revendicateStone : inadequate side s");
    if (n < 0 || n > getBoard().getStoneNb()) throw ShottenTottenException("revendicateStone : inadequate stone number n");

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
        cout << "(revendicateStone) Card" << i << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[i]->getName() << endl;
    }
    //cout << i;

    //addin tactic cards
    for (size_t k = 0; k < getClanDeck().getCardCount(); k++) { //adding clan Deck cards
        availableCards[i] = tacticDeck->getCard(i);
        cout << "(revendicateStone) Card" << i << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[i]->getName() << endl;
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