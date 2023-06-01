#include "../head/Player.h"
#include "../head/Supervisor.h"

unsigned int PlayerAIRandom::selectCard() const {
    unsigned int card_nb = 0;
    bool* list_cards = new bool [getHand()->getSize()];
    list_cards = Supervisor::getInstance().getController()->getPickableCards();
    while (!list_cards[card_nb]) {
        card_nb++;
    }
    return card_nb;
}

unsigned int PlayerAIRandom::selectStone() const {
    unsigned int stone_nb = 0;
    bool* list_stones = new bool[Supervisor::getInstance().getController()->getBoard().getStoneNb()];
    list_stones = Supervisor::getInstance().getController()->getPlayableStones();
    while (!list_stones[stone_nb]) {
        stone_nb++;
    }
    return stone_nb;
}
