#include "../head/Player.h"
#include "../head/Supervisor.h"

int PlayerAIRandom::selectCard(bool* pickable) const {
	Controller* c = Supervisor::getInstance().getController();
	size_t size = c->getCurrentPlayerHand().getSize();
	bool allunpickable = true;
	for (int i = 0; i < size; ++i) {
		if (pickable[i]) {
			allunpickable = false;
			break;
		}
	}
	if (allunpickable) {
		cout << "No usable card ! Too bad for you :p";
		return -1;
	}
	unsigned int card_nb = Utility::randChoice(pickable, size);

	/*
	unsigned int card_nb = 0;
	bool* list_cards = new bool[getHand()->getSize()];
	list_cards = Supervisor::getInstance().getController()->getPickableCards();
	while (!list_cards[card_nb]) {
		card_nb++;
	}
	*/
	
	std::cout << endl << "DEBUG IN PlayerAIRandom::selectCard()";
	for (int i = 0; i < size; i++) {
		std::cout << endl << pickable[i] << " [" << i << "]";
	}
	std::cout << endl << card_nb << endl;

	return card_nb;
}


unsigned int PlayerAIRandom::selectStone(bool* pickable) const {
	unsigned int stone_nb = 0;
	unsigned int max_stones = Supervisor::getInstance().getController()->getBoard().getStoneNb();
	while (!pickable[stone_nb]) {
		stone_nb++;
	}
	// stone_nb sera toujours défini : 
	// la partie se termine nécessairement avant que list_stones = { false, false, ..., false }
	if (stone_nb >= max_stones) {
		std::cout << endl << "selectStone() DEBUG ALERT";
		std::cout << endl << "stone_nb [" << stone_nb << "] ; MAX stones [" << max_stones;
		std::cout << "]";
		for (int i = 0; i < max_stones; i++) {
			std::cout << endl << pickable[i] << " [" << i << "]";
		}
		std::cout << endl;

	}


	return stone_nb;
}

unsigned int PlayerAIRandom::selectStoneForCombatMode(bool* pickable) const {
	
	unsigned int stone_nb = 0;
	unsigned int max_stones = Supervisor::getInstance().getController()->getBoard().getStoneNb();
	while (!pickable[stone_nb]) {
		stone_nb++;
	}
	// stone_nb sera toujours défini : 
	// la partie se termine nécessairement avant que list_stones = { false, false, ..., false }
	if (stone_nb >= max_stones) {
		std::cout << endl << "selectStone() DEBUG ALERT";
		std::cout << endl << "stone_nb [" << stone_nb << "] ; MAX stones [" << max_stones;
		std::cout << "]";
		for (int i = 0; i < max_stones; i++) {
			std::cout << endl << pickable[i] << " [" << i << "]";
		}
		std::cout << endl;

	}


	return stone_nb;
}
unsigned int PlayerAIRandom::selectUnclaimedStone() const {
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

int PlayerAIRandom::selectCardOnStone(Side s, unsigned int stone_nb) const {
	Stone& cur_stone = Supervisor::getInstance().getController()->getBoard().getStone(stone_nb);
	size_t stone_size = cur_stone.getSideSize(s);
	if (stone_size == 0) return -1; //no card on this side
	int card_nb = rand() % stone_size;
	return card_nb;
}