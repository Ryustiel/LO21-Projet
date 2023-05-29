#include "../head/Controller.h"
#include "../head/Supervisor.h" 
#include <iostream>
#include "../head/UserInterface.h"

void Controller::runGame(int nturns, int winthreshold) { // + additional parameters

    std::cout << "\n===================== newGame";

    player1->initForNewGame();
    player2->initForNewGame();
    
    // le plateau a-t-il besoin d'�tre initialis� � ce niveau ?

    remainingRounds = nturns;
    totalRounds = nturns;
    maxScore = winthreshold;
    Controller* c = Supervisor::getInstance().getController();

    while (c->getRemainingRounds() != 0) {
        cout << "* ROUND " << c->getTotalRounds() - c->getRemainingRounds() + 1 << " (on " << c->getTotalRounds() << ") *" << endl;

        newRound();

        //decrementing remaining rounds
        unsigned int r = c->getRemainingRounds();
        c->setRemainingRounds(r - 1);
    }
    Player* winner = c->getWinner();
    if (winner != nullptr) {
        cout << endl << "The winner is : " << winner->getName() << "! Congratulations!" << endl;
    }
    else {
        cout << endl << "It's a draw! Perhaps could you decide the winner by playing again..." << endl;
    }
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

    current_side = Side::s1; // TO DO : appliquer la méthode de changement référence de joueur
    //proposition : faire un Side turn, qui prend les valeurs s1/s2 ? + simple pour savoir où poser les éléments sur les bornes (évite les if)
    //(de +, la fct° claimStone demande une Side)
}

void Controller::newRound() {
    std::cout << "\n===================== newRound";
    initForNewRound();
    Side winning = Side::none;
    while (winning == Side::none){
        newTurn();
        current_side = (current_side == Side::s1) ? Side::s2 : Side::s1;
        winning = board.evaluateGameWinner();
    }
    if (winning == Side::s1) {
        player1->updateScore();
    }
    else {
        player2->updateScore();
    }
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

void Controller::turnPlayCard() {
    std::cout << "\n=============== turnPlayCard()";
    unsigned int selectedCardNb = ui->UISelectCard();
    Hand& curHand = getCurrentPlayerHand();
    const Card& selectedCard = *curHand.getCard(selectedCardNb);
    selectedCard.activate();
    curHand.withdraw(selectedCard);
}

void Controller::turnDrawCard() {
    std::cout << "\n=============== turnDrawCard()";
    getCurrentPlayerHand().add(clanDeck->draw());
}

void Controller::turnClaimStone() {
    std::cout << "\n=============== turnClaimStone()";
    //A DEFINIR !!!
    while (ui->UIWantClaimStone()) {
        //A DEFINIR !!!
        unsigned int selectedStoneNB = ui->UISelectStone();
        claimStone(selectedStoneNB);
    }
}

void Controller::newTurn() {
    std::cout << "\n================== newTurn";
    turnPlayCard();
    turnDrawCard();
    turnClaimStone();
}

void Controller::claimStone(unsigned int n) {
    Side s = getCurSide();
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

void TacticController::incrementTacticalPlayed(Side s) {
    if (s == Side::s1) {
        ++p1TacticalCardPlayed;
    }
    else if (s == Side::s2) {
        ++p2TacticalCardPlayed;
    }
}

bool TacticController::canPlayerPlayTacticalCard() {
    if (getCurSide() == Side::s1) {
        return p1TacticalCardPlayed <= p2TacticalCardPlayed;
    }else {
        return p1TacticalCardPlayed >= p2TacticalCardPlayed;
    }
}