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
    delete board;
    board = new Board();
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
    while (winning == Side::none) {
        newTurn();
        current_side = (current_side == Side::s1) ? Side::s2 : Side::s1;
        winning = board->evaluateGameWinner();
    }
    if (winning == Side::s1) {
        player1->updateScore();
    }
    else {
        player2->updateScore();
    }
    system("pause");
}

void Controller::checkRound() {
    std::cout << "\n=============================== checkRound";
    remainingRounds--;
    if (remainingRounds <= 0 || player1->getScore() >= maxScore || player2->getScore() >= maxScore) {
        qtGameOver();
    }
    else {
        newRound();
    }
}

void Controller::turnPlayCard() {
    std::cout << "\n=============== turnPlayCard()";

    std::cout << endl << "DEBUG BoardIterator and StoneIterator <= in Controller::turnPlayCard()" << endl;
    /*
    for (auto stone : getBoard()) { // iterator on Board
        for (auto it = stone.begin(Side::s1); it != stone.end(Side::s1); ++it) {
            std::cout << (*it)->getName() << " ";
        }
    }
    */


    Hand& curHand = getCurrentPlayerHand();
    unsigned int handSize = curHand.getSize();
    cout << "(Controller::turnPlayCard) - hand size (début de l'action : jouer une carte) = " << handSize << endl;
    if (handSize) {
        UserInterface::getInstance()->uiPrintPlayerHand();
        unsigned int selectedCardNb = UserInterface::getInstance()->uiSelectCard();

        const Card& selectedCard = *curHand.getCard(selectedCardNb);

        cout << "(Controller::turnPlayCard) - selectedCardNb = " << selectedCardNb << endl;
        cout << "(Controller::turnPlayCard) - selectedCard = " << selectedCard.getName() << endl;

        selectedCard.activate();
        curHand.withdraw(selectedCard);
    }
    cout << "(Controller::turnPlayCard) - hand size (fin de l'action : jouer une carte)) = " << curHand.getSize() << endl;
}

void Controller::turnDrawCard() {
    std::cout << "\n=============== turnDrawCard()";
    UserInterface::getInstance()->uiPrintPlayerHand();
    Deck* d = UserInterface::getInstance()->uiSelectDeck();
    if (d) {
        cout << "(Controller::turnDrawCard()) - selected deck card count (before draw) : " << d->getCardCount() << endl;
        getCurrentPlayerHand().add(d->draw());
        UserInterface::getInstance()->uiPrintPlayerHand();
        cout << "(Controller::turnDrawCard()) - selected deck card count (after draw) : " << d->getCardCount() << endl;
    }
}

void Controller::turnClaimStone() {
    std::cout << "\n=============== turnClaimStone()";
    bool choice_claim = false;
    PlayerAIRandom* playerAI = dynamic_cast<PlayerAIRandom*> (getCurrentPlayer());
    if (playerAI) { //is IA
        while (playerAI->WantClaimStone()) {
            unsigned int selectedStoneNB = playerAI->selectUnclaimedStone();
            cout << "(Controller::turnClaimStone) - IA protocole : stone selected : " << selectedStoneNB << endl;
            claimStone(selectedStoneNB);
            cout << "(Controller::turnClaimStone) - IA protocole : claimStone() done" << endl;
        }
    }
    else { //is Human
        while (UserInterface::getInstance()->uiWantClaimStone()) {
            //A DEFINIR !!!
            int selectedStoneNB = UserInterface::getInstance()->userSelectStoneForClaim();
            if (selectedStoneNB >= 0)
                claimStone(selectedStoneNB);
            else break; //if user's choice is wrong
        }
    }
}

void Controller::newTurn() {
    std::cout << "\n================== newTurn";
    UserInterface::getInstance()->uiPrintCurrentPlayer();
    UserInterface::getInstance()->uiPrintGame();
    turnPlayCard();
    UserInterface::getInstance()->uiPrintGame();
    turnDrawCard(); //pb quand pioche vide
    turnClaimStone();
    cout << "Your turn is over...!";
    //system("pause");
    //system("cls");
}

void TacticController::newTurn() {
    std::cout << "\n================== newTurn";
    UserInterface::getInstance()->uiPrintCurrentPlayer();
    UserInterface::getInstance()->uiPrintGame();
    UserInterfaceCmd::getInstance()->uiPrintDiscard();
    turnPlayCard();
    UserInterface::getInstance()->uiPrintGame();
    turnDrawCard(); //pb quand pioche vide
    turnClaimStone();
    cout << "Your turn is over...!";
    //system("pause");
    //system("cls");
}

bool Controller::getAvailableCards(const PlacableCard**& availableCards, size_t& foundedSize) {
    //defining available cards count
    size_t availableCardsCount = clanDeck->getCardCount();

    availableCardsCount += player2->getHand()->getSize();
    availableCardsCount += player1->getHand()->getSize();

    //creating tab containing all available cards (deck + opponent's cards)
    availableCards = new const PlacableCard * [availableCardsCount];

    //adding deck cards
    foundedSize = 0;
    size_t j = 0;
    for (; j < clanDeck->getCardCount(); j++) { //adding clan Deck cards
        //On vérifie que les cartes prises en comptes sont bien des cartes placable. (si une d'entre elle ne l'est pas )
        const PlacableCard* cardCandidate = dynamic_cast<const PlacableCard*>(clanDeck->getCard(j));
        if (cardCandidate != nullptr) {
            availableCards[foundedSize++] = cardCandidate;
            cout << "(claimStone) Card" << foundedSize << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[foundedSize-1]->getName() << endl;
        }
        else {
            //dans ce cas la il reste des cartes tactiques importantes
            return false;
        }
    }
    //cout << i;
    const Hand* hands[2] = { player1->getHand(), player2->getHand() };
    for (int hi = 0; hi < 2; ++hi) {
        const Hand* curHand = hands[hi];
        //adding the opponent's cards to available cards
        if (curHand != nullptr) {
            for (size_t k = 0; k < curHand->getSize(); k++) {
                const PlacableCard* cardCandidate = dynamic_cast<const PlacableCard*>(curHand->getCard(k));
                if (cardCandidate != nullptr) {
                    availableCards[foundedSize] = cardCandidate;
                    foundedSize++;
                    cout << "(claimStone) Card" << foundedSize << "(copied) (availableCardsCount = " << availableCardsCount << ") : " << availableCards[foundedSize-1]->getName() << endl;
                }
                else {
                    return false;
                }
            }
        }
    }
    return true;
}

void Controller::claimStone(unsigned int n) {
    Side s = getCurSide();
    if (s == Side::none) throw ShottenTottenException("claimStone : inadequate side s");
    if (n < 0 || n > board->getStoneNb()) throw ShottenTottenException("claimStone : inadequate stone number n");
    Side evaluated_side;
    bool s1Completed = (board->getStone(n).getSizeP1() == board->getStone(n).getMaxSize());
    bool s2Completed = (board->getStone(n).getSizeP2() == board->getStone(n).getMaxSize());
    //to revendicate a stone, current player's combination must be completed
    if ((s == Side::s1 && !s1Completed) || (s == Side::s2) && !s2Completed) {
        evaluated_side = Side::none;
    }
    else if (!s1Completed || !s2Completed) {
        const PlacableCard** availableCards;
        size_t foundedSize;
        if (getAvailableCards(availableCards, foundedSize)) {
            evaluated_side = board->evaluateStoneWinningSide(n, availableCards, foundedSize);
        }
        else {
            //des cartes tactiques spéciale empêche le claim
            evaluated_side = Side::none;
        }
    }
    else {
        evaluated_side = board->evaluateStoneWinningSide(n);
    }
    //evaluating stone's winner
    if (evaluated_side == s) {
        //revendicating the stone
        board->getStone(n).setRevendication(s);
    }
    else {
        cout << endl << "You can't claim stone " << n << "!" << endl;
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

void TacticController::initForNewRound() {
    Controller::initForNewRound();
    std::cout << "\n========= initForNewRound-Tactic";
    //init the tactic deck
    delete tacticDeck;
    tacticDeck = new Deck(tacticGame);// initialiser la pioche tactique dans la m�thode fille

    delete discard;
    discard = new Discard();

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

bool TacticController::playerCanPlayTacticalCard() {
  cout << "(canPlayerPlayTacticalCard()) - p1TacticalCardPlayed =  " << p1TacticalCardPlayed << endl;
  cout << "(canPlayerPlayTacticalCard()) - p2TacticalCardPlayed =  " << p2TacticalCardPlayed << endl;
    if (getCurSide() == Side::s1) {
        return p1TacticalCardPlayed <= p2TacticalCardPlayed;
    }
    else {
        return p1TacticalCardPlayed >= p2TacticalCardPlayed;
    }
}

bool TacticController::getAvailableCards(const PlacableCard**& availableCards, size_t& foundedSize) {
    const PlacableCard** availableCardsTemp;
    size_t foundedSizeTemp;
    if (!Controller::getAvailableCards(availableCardsTemp, foundedSizeTemp)) { return false; }
    foundedSize = foundedSizeTemp + tacticDeck->getCardCount();
    availableCards = new const PlacableCard * [foundedSize];
    for (size_t i = 0; i < foundedSizeTemp; ++i) {
        availableCards[i] = availableCardsTemp[i];
    }
    for (size_t i = 0; i < tacticDeck->getCardCount(); ++i) {
        const PlacableCard* cardCandidate = dynamic_cast<const PlacableCard*>(tacticDeck->getCard(i));
        if (cardCandidate != nullptr) {
            availableCards[foundedSizeTemp + i] = cardCandidate;
        }
        else {
            return false;
        }

    }
    return true;
}
