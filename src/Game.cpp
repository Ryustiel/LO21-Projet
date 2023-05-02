#include "../head/Game.h"


using namespace std;

Game::Game(const Version& version) {
	card_count = 0;
	if (version == Version::legacy) {
		cards = new Card*[clanCardsNumber];
	}else if (version == Version::expert) {
		cards = new Card * [clanCardsNumber+clanCardsNumber];
		cards[card_count++] = new Elite("Chief1");
		cards[card_count++] = new Elite("Chief2");
		cards[card_count++] = new Elite("Spy");
		cards[card_count++] = new Elite("Shield-Bearer");
		cards[card_count++] = new CombatMode("Blind-Man’s Bluff");
		cards[card_count++] = new CombatMode("Mud Fight");
		cards[card_count++] = new Ruses("Recruiter");
		cards[card_count++] = new Ruses("Strategist");
		cards[card_count++] = new Ruses("Banshee");
		cards[card_count++] = new Ruses("Traiter");
	}else{ throw stException("Version Game error : version not known"); }
	
	for (auto c : Colors) {
		for (auto n : Numbers) {
			cards[card_count++] = new Clan(c, n);
		}
	}
}

Game::~Game() {
	for (unsigned int i = 0; i < card_count; i++) {
		delete cards[i];
	}
	delete[] cards;
}

const Card& Game::getCard(unsigned int i) const {
	if (i > card_count) throw stException("getCard error : incorrect number");
	return *cards[i];
}

Game* Game::instance = nullptr;

Game& Game::getInstance() {
	if (instance == nullptr) {
		instance = new Game(getVersion());
	}
	return *instance;
}