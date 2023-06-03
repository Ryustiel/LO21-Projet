#include "../head/Player.h"
#include "../head/Supervisor.h"

unsigned int PlayerAIRandom::selectCard() const {
	unsigned int card_nb = 0;
	
	/*card_nb = Utility::randchoice(
		Supervisor::getInstance().getController()->getPickableCards()
	);*/
	
	bool* list_cards = new bool [getHand()->getSize()];
	list_cards = Supervisor::getInstance().getController()->getPickableCards();
	while (!list_cards[card_nb]) {
		card_nb++;
	}
	
	return card_nb;
}

unsigned int PlayerAIRandom::selectCard(size_t nchoices) const {
	// choses a random int based on n_stones
	std::cout << "MAKING RANDOM CHOICE " << nchoices << endl;
	return Utility::randInt(0, nchoices);
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
unsigned int PlayerAIRandom::selectStoneForClaim() const {
	unsigned int stone_nb = rand()%9;
	bool* list_stones = new bool[Supervisor::getInstance().getController()->getBoard().getStoneNb()];
	list_stones = Supervisor::getInstance().getController()->getUnclaimedStones();

	//vérification
	cout << "(PlayerAIRandom::selectStoneForClaim) - getUnclaimedStones : ";
	for (size_t i = 0; i < Supervisor::getInstance().getController()->getBoard().getStoneNb(); i++) {
		cout << list_stones[i] << "; ";
	}
	cout << "(PlayerAIRandom::selectStoneForClaim) - end of check" << endl;

	while (!list_stones[stone_nb]) {
		stone_nb = rand() % 9;
	}
	return stone_nb;
}

unsigned int PlayerAIRandom::selectDeck() const {
	unsigned int deck_count = Supervisor::getInstance().getController()->getDeckCount();
	return rand() % deck_count;
}

bool PlayerAIRandom::WantClaimStone() const {
	return rand() % 2;
}