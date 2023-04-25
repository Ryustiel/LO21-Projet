#include "Game.h"
#include "SchottenTottenException.h"

using namespace std;

Game::Game(const string& version) {
	if (version == "clan") {
		unsigned int i = 0;
		for (auto c : Colors) {
			for (auto n : Numbers) {
				cards[i] = new Clan(c, n);
				i++;
			}
		}
		card_count = i;
	}
	else if (version == "tactique") {
		cards[0] = new Elite("Chief1");
		cards[1] = new Elite("Chief2");
		cards[2] = new Elite("Spy");
		cards[3] = new Elite("Shield-Bearer");
		cards[4] = new CombatMode("Blind-Man’s Bluff");
		cards[5] = new CombatMode("Mud Fight");
		cards[6] = new Ruses("Recruiter");
		cards[7] = new Ruses("Strategist");
		cards[8] = new Ruses("Banshee");
		cards[9] = new Ruses("Traiter");
    card_count =  10;
	}
	else {
		throw stException("Version Game error : version not known");
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